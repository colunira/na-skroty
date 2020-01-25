package md5

import (
	"fmt"
	"math"
	"bytes"
	"encoding/binary"
)

var shift = [...]uint{7, 12, 17, 22, 5, 9, 14, 20, 4, 11, 16, 23, 6, 10, 15, 21}
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
		for j := 0; j < 64; j++ {
			var f uint32
			bufferIndex := j
			round := j >> 4
			switch round {
			case 0:
				f = (b1 & c1) | (^b1 & d1)
			case 1:
				f = (b1 & d1) | (c1 & ^d1)
				bufferIndex = (bufferIndex*5 + 1) & 0x0F
			case 2:
				f = b1 ^ c1 ^ d1
				bufferIndex = (bufferIndex*3 + 5) & 0x0F
			case 3:
				f = c1 ^ (b1 | ^d1)
				bufferIndex = (bufferIndex * 7) & 0x0F
			}
			sa := shift[(round<<2)|(j&3)]
			a1 += f + buffer[bufferIndex] + table[j]
			a1, d1, c1, b1 = d1, c1, b1, a1<<sa|a1>>(32-sa)+b1
		}
		a, b, c, d = a+a1, b+b1, c+c1, d+d1
	}
	err=binary.Write(bytes.NewBuffer(r[:0]), binary.LittleEndian, []uint32{a, b, c, d})
	if err!=nil {
		panic(err)
	}
	return fmt.Sprintf("%x", r)
}