package main

import (
	"fmt"
	"github.com/colunira/na-skroty/go/internal"
	"github.com/colunira/na-skroty/go/internal/crc32"
	"time"
	md5go "crypto/md5"
	crc32go "hash/crc32"
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