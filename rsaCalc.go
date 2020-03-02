package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/sha256"
	"crypto"
	"time"
	"fmt"
	"os"
   )  
  
func rsaCalc(){
	// Generate 2048-bit RSA key
	keyPrivA, error := rsa.GenerateKey( rand.Reader, 2048 )

	if error != nil{
	  fmt.Println( error.Error )
	  os.Exit( 1 )
	}

	// Extract Public Key from RSA Private Key
	keyPubA := &keyPrivA.PublicKey

	// Generate 2048-bit RSA key
	keyPrivB, error := rsa.GenerateKey( rand.Reader, 2048 )

	if error != nil{
	  fmt.Println( error.Error )
	  os.Exit( 1 )
	}

	// Extract Public Key from RSA Private Key
	keyPubB := &keyPrivB.PublicKey

	fmt.Println( "Private key A: ", *keyPrivA )
	fmt.Println()
	fmt.Println( "Public key A: ", keyPubA )
	fmt.Println()
	fmt.Println( "Private key B: ", *keyPrivB )
	fmt.Println()
	fmt.Println( "Public key B: ", keyPubB )
	fmt.Println()

	// Encryption
	message := []byte("The MBCFET is similar to the FinFET in it's topology, where a large area of gate-to-channel contact allows for a very small channel length.")
	label := []byte("")
	hash := sha256.New()

	ciphertext, error := rsa.EncryptOAEP(
		hash,
		rand.Reader,
		keyPubB,
		message,
		label)

	if error != nil{
	  fmt.Println( error.Error )
	  os.Exit( 1 )
	}

	fmt.Printf( "Encrypted %s as:\n%x\n", string( message ), ciphertext )
	fmt.Println()

	// Signing
	var opts rsa.PSSOptions
	opts.SaltLength = rsa.PSSSaltLengthAuto
	PSSmessage := message
	newhash := crypto.SHA256
	pssh := newhash.New()
	pssh.Write( PSSmessage )
	hashed := pssh.Sum( nil )

	signature, error := rsa.SignPSS(
		rand.Reader,
		keyPrivA,
		newhash,
		hashed,
		&opts)

	if error != nil{
	  fmt.Println( error.Error )
	  os.Exit( 1 )
	}

	fmt.Printf( "PSS signature: %x\n", signature )
	fmt.Println()

	// Decrypting
	plaintext, error := rsa.DecryptOAEP(
		hash,
		rand.Reader,
		keyPrivB,
		ciphertext,
		label)

	if error != nil{
	  fmt.Println( error.Error )
	  os.Exit( 1 )
	}

	fmt.Printf( "Decrypted %x as:\n%s\n",  ciphertext, plaintext )
	fmt.Println()

	// Signature verification
	error = rsa.VerifyPSS(
		keyPubA,
		newhash,
		hashed,
		signature,
		&opts)

	if error != nil{
		fmt.Println( "Verify signature failed" )
		os.Exit( 1 )
	}

	fmt.Println( "Verify signature successful" )
}

func main() {
	t0 := time.Now()
	rsaCalc()
	t1 := time.Now()
	fmt.Printf( "RSA calculations took %v to run.\n", t1.Sub( t0 ) )
}
