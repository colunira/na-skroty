package main

import (
	md5go "crypto/md5"
	sha1go "crypto/sha1"
	sha256go "crypto/sha256"
	sha512go "crypto/sha512"
	"flag"
	"fmt"
	"github.com/colunira/na-skroty/go/resources/adler32"
	"github.com/colunira/na-skroty/go/resources/crc32"
	"github.com/colunira/na-skroty/go/resources/crc64"
	"github.com/colunira/na-skroty/go/resources/md2"
	"github.com/colunira/na-skroty/go/resources/md4"
	"github.com/colunira/na-skroty/go/resources/md5"
	"github.com/colunira/na-skroty/go/resources/ripemd160"
	"github.com/colunira/na-skroty/go/resources/sha1"
	"github.com/colunira/na-skroty/go/resources/sha256"
	"github.com/colunira/na-skroty/go/resources/sha512"
	md2go "github.com/htruong/go-md2"
	md4go "golang.org/x/crypto/md4"
	ripemd160go "golang.org/x/crypto/ripemd160"
	adler32go "hash/adler32"
	crc32go "hash/crc32"
	crc64go "hash/crc64"
	"io"
	"io/ioutil"
	"time"
)

var testCases []string

func main() {
	filepath := flag.String("files-path", "files", "Absolute or realtive path to files to encode")
	flag.Parse()

	fmt.Println(*filepath)
	testCases = readCases(*filepath)

	fmt.Println("\nCRC32:")
	elapsedTime(crc32.Encode, "ours")
	elapsedTime(crc32hash, "library")

	fmt.Println("\nCRC64:")
	elapsedTime(crc64.Encode, "ours")
	elapsedTime(crc64hash, "library")

	fmt.Println("\nAdler32:")
	elapsedTime(adler32.Encode, "ours")
	elapsedTime(adler32hash, "library")

	fmt.Println("\nMD2:")
	elapsedTime(md2.Encode, "ours")
	elapsedTime(md2hash, "library")

	fmt.Println("\nMD4:")
	elapsedTime(md4.Encode, "ours")
	elapsedTime(md4hash, "library")

	fmt.Println("\nMD5:")
	elapsedTime(md5.Encode, "ours")
	elapsedTime(md5hash, "library")

	fmt.Println("\nRipeMD-160")
	elapsedTime(ripemd160.Encode, "ours")
	elapsedTime(ripemd160hash, "library")

	fmt.Println("\nSHA1")
	elapsedTime(sha1hash, "library")
	elapsedTime(sha1.Encode,"ours")

	fmt.Println("\nSHA256")
	elapsedTime(sha256hash, "library")
	elapsedTime(sha256.Encode, "ours")

	fmt.Println("\nSHA512")
	elapsedTime(sha512hash, "library")
	elapsedTime(sha512.Encode, "ours")
}

func elapsedTime(hashFunc func(string) string, who string) {
	var start time.Time
	var elapsed time.Duration
	var results []time.Duration
	for _, tc := range testCases {
		start = time.Now()
		_d = hashFunc(tc)
		elapsed = time.Since(start)
		results = append(results, elapsed)
	}
	fmt.Println(who + ":" )
	for i, res:= range results {
		fmt.Printf("%d. %s\n", i+1, res)
	}

}

func sha512hash(str string) string {
	h := sha512go.New()
	h.Write([]byte(str))

	return fmt.Sprintf("%x", h.Sum(nil))
}

func sha256hash(str string) string {
	h := sha256go.New()
	h.Write([]byte(str))
	return fmt.Sprintf("%x", h.Sum(nil))
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

func readCases(path string) []string {
	var cases []string
	files, err := ioutil.ReadDir(path)
	if err!=nil {
		panic(err)
	}
	for _, file:= range files {
		res, err := ioutil.ReadFile(path + "/" + file.Name())
		if err!=nil {
			panic(err)
		}
		cases = append(cases, fmt.Sprintf("%s",res))
	}
	return cases
}