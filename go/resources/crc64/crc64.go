package crc64

import (
	"fmt"
	crc64go "hash/crc64"
)

var crc64Table = crc64go.MakeTable(crc64go.ISO)

func Encode(str string) string {
	crc64:=uint64(0xffffffffffffffff)
	data:=[]byte(str)
	for _, b :=range data {
		index:=(crc64 ^ uint64(b)) & 0xff
		crc64=(crc64 >> 8) ^ crc64Table[index]
	}
	crc64=crc64^0xffffffffffffffff
	return fmt.Sprintf("%x", crc64)
}