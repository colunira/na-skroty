package md4

import (
	"fmt"
	"math"
	"bytes"
	"encoding/binary"
)

var s1 = [...]uint{3,7,11,19,3,7,11,19,3,7,11,19,3,7,11,19,
	3,5,9,13,3,5,9,13,3,5,9,13,3,5,9,13,
	3,9,11,15,3,9,11,15,3,9,11,15,3,9,11,15,}
var shift2 = [...]int{0,4,8,12,1,5,9,13,2,6,10,14,3,7,9,15}
var shift3 = [...]int{0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15}
var table [64]uint32

func init() {
	for i := range table {
		table[i] = uint32((1 << 32) * math.Abs(math.Sin(float64(i + 1))))
	}
}

func Encode(s string) (string) {
	var r [16]byte
	padded := bytes.NewBuffer([]byte(s))
	padded.WriteByte(0x80)
	for padded.Len() % 64 != 56 {
		padded.WriteByte(0)
	}
	messageLenBits := uint64(len(s)) * 8
	err:=binary.Write(padded, binary.LittleEndian, messageLenBits)
	if err!=nil {
		panic(err)
	}

	var a, b, c, d uint32 = 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476
	var buffer [16]uint32
	for binary.Read(padded, binary.LittleEndian, buffer[:]) == nil { // read every 64 bytes
		a1, b1, c1, d1 := a, b, c, d
		for j := 0; j < 48; j++ {
			var f uint32
			bufferIndex := j
			if j<16 {
				f = (b1 & c1) | (^b1 & d1)
			} else if j>=16 && j<32 {
				f = (b1 & c1) | (b1 & d1) | (c1 & d1)
				bufferIndex = shift2[j%16]
			} else if j>=32{
				f = b1 ^ c1 ^ d1
				bufferIndex = shift3[j%16]
			}
			a1 += a1 + f + buffer[bufferIndex]
			a1, d1, c1, b1 = d1, c1, b1, a1<<s1[j]|a1>>(32-s1[j])
		}
		a, b, c, d = a+a1, b+b1, c+c1, d+d1
	}
	err=binary.Write(bytes.NewBuffer(r[:0]), binary.LittleEndian, []uint32{a, b, c, d})
	if err!=nil {
		panic(err)
	}
	return fmt.Sprintf("%x", r)
}