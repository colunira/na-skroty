package main

import (
	md5go "crypto/md5"
	ripemd160go "golang.org/x/crypto/ripemd160"
	"fmt"
	"github.com/colunira/na-skroty/go/internal"
	"github.com/colunira/na-skroty/go/internal/adler32"
	"github.com/colunira/na-skroty/go/internal/crc32"
	"github.com/colunira/na-skroty/go/internal/crc64"
	adler32go "hash/adler32"
	crc32go "hash/crc32"
	crc64go "hash/crc64"

	"time"
)

var testCases = []string{
	"ala ma kota",
}

func main() {
	fmt.Println("MD5:")
	elapsedTime(md5.Encode, "ours")
	elapsedTime(md5hash, "library")

	fmt.Println("CRC32:")
	elapsedTime(crc32.Encode, "ours")
	elapsedTime(crc32hash, "library")

	fmt.Println("CRC64:")
	elapsedTime(crc64.Encode, "ours")
	elapsedTime(crc64hash, "library")

	fmt.Println("Adler32:")
	elapsedTime(adler32.Encode, "ours")
	elapsedTime(adler32hash, "library")

	fmt.Println("RipeMD-160")

	elapsedTime(ripemd160hash, "library")
}

func elapsedTime(hashFunc func(string) string, who string) {
	start:=time.Now()
	for _, tc := range testCases {
		fmt.Println(hashFunc(tc))
	}
	elapsed:=time.Since(start)
	fmt.Printf("%s time elapsed: %s\n", who, elapsed)
}

func md5hash(str string) string {
	data := []byte(str)
	return fmt.Sprintf("%x", md5go.Sum(data))
}

func crc32hash(str string) string {
	result := crc32go.ChecksumIEEE([]byte(str))
	return fmt.Sprintf("%x\n", result)
}

func crc64hash(str string) string {
	result := crc64go.Checksum([]byte(str),crc64go.MakeTable(crc64go.ISO))
	return fmt.Sprintf("%x", result)
}

func adler32hash(str string) string {
	result:=adler32go.Checksum([]byte(str))
	return fmt.Sprintf("%x", result)
}

func ripemd160hash(str string) string {
	h:=ripemd160go.New()
	h.Write([]byte(str))
	return fmt.Sprintf("%x",h.Sum(nil))
}