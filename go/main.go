package main

import (
	md5go "crypto/md5"
	"github.com/colunira/na-skroty/go/internal/ripemd160"
	"github.com/colunira/na-skroty/go/internal/sha1"
	md4go "golang.org/x/crypto/md4"
	"fmt"
	"github.com/colunira/na-skroty/go/internal/adler32"
	"github.com/colunira/na-skroty/go/internal/crc32"
	"github.com/colunira/na-skroty/go/internal/crc64"
	"github.com/colunira/na-skroty/go/internal/md2"
	"github.com/colunira/na-skroty/go/internal/md5"
	"github.com/colunira/na-skroty/go/internal/md4"
	md2go "github.com/htruong/go-md2"
	ripemd160go "golang.org/x/crypto/ripemd160"
	adler32go "hash/adler32"
	crc32go "hash/crc32"
	crc64go "hash/crc64"
	sha1go "crypto/sha1"
	"io"

	"time"
)

var testCases = []string{
	"abcd",
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

	fmt.Println("MD2:")
	elapsedTime(md2.Encode, "ours")
	elapsedTime(md2hash, "library")

	fmt.Println("MD4:")
	elapsedTime(md4.Encode, "ours")
	elapsedTime(md4hash, "library")

	fmt.Println("RipeMD-160")
	elapsedTime(ripemd160.Encode, "ours")
	elapsedTime(ripemd160hash, "library")

	fmt.Println("SHA1")
	elapsedTime(sha1hash, "library")
	elapsedTime(sha1.Encode,"ours")
}

func elapsedTime(hashFunc func(string) string, who string) {
	res:=""
	start:=time.Now()
	for _, tc := range testCases {
		res=hashFunc(tc)
	}
	elapsed:=time.Since(start)
	fmt.Printf("%s time elapsed: %s,\n code: %s\n", who, elapsed, res)
}

func sha1hash(str string) string {
	h := sha1go.New()
	h.Write([]byte(str))
	res:= h.Sum(nil)
	return fmt.Sprintf("%x",res)
}

func md5hash(str string) string {
	data := []byte(str)
	return fmt.Sprintf("%x", md5go.Sum(data))
}

func md4hash(str string) string {
	h := md4go.New()
	io.WriteString(h, str)
	return fmt.Sprintf("%x", h.Sum(nil))
}

func md2hash(str string) string {
	h := md2go.New()
	io.WriteString(h, str)
	return fmt.Sprintf("%x", h.Sum(nil))
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