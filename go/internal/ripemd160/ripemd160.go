package ripemd160

import (
	"bytes"
	"encoding/binary"
	"fmt"
	"math/bits"
)


var	h0=uint32(0x67452301)
var	h1=uint32(0xefcdab89)
var	h2=uint32(0x98badcfe)
var	h3=uint32(0x10325476)
var	h4=uint32(0xc3d2e1f0)

var	K  = []uint32{0x00000000, 0x5a827999, 0x6ed9eba1, 0x8f1bbcdc, 0xa953fd4e}

var	KK = []uint32{0x50a28be6, 0x5c4dd124, 0x6d703ef3, 0x7a6d76e9, 0x00000000}

var	R  = []int{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	7, 4, 13, 1, 10, 6, 15, 3, 12, 0, 9, 5, 2, 14, 11, 8,
	3, 10, 14, 4, 9, 15, 8, 1, 2, 7, 0, 6, 13, 11, 5, 12,
	1, 9, 11, 10, 0, 8, 12, 4, 13, 3, 7, 15, 14, 5, 6, 2,
	4, 0, 5, 9, 7, 12, 2, 10, 14, 1, 3, 8, 11, 6, 15, 13}

var	RR = []int{5, 14, 7, 0, 9, 2, 11, 4, 13, 6, 15, 8, 1, 10, 3, 12,
	6, 11, 3, 7, 0, 13, 5, 10, 14, 15, 8, 12, 4, 9, 1, 2,
	15, 5, 1, 3, 7, 14, 6, 9, 11, 8, 12, 2, 10, 0, 4, 13,
	8, 6, 4, 1, 3, 11, 15, 0, 5, 12, 2, 13, 9, 7, 10, 14,
	12, 15, 10, 4, 1, 5, 8, 7, 6, 2, 13, 14, 0, 3, 9, 11}

var	S  = []int{11, 14, 15, 12, 5, 8, 7, 9, 11, 13, 14, 15, 6, 7, 9, 8,
	7, 6, 8, 13, 11, 9, 7, 15, 7, 12, 15, 9, 11, 7, 13, 12,
	11, 13, 6, 7, 14, 9, 13, 15, 14, 8, 13, 6, 5, 12, 7, 5,
	11, 12, 14, 15, 14, 15, 9, 8, 9, 14, 5, 6, 8, 6, 5, 12,
	9, 15, 5, 11, 6, 8, 13, 12, 5, 12, 13, 14, 11, 8, 5, 6}

var	SS = []int{8, 9, 9, 11, 13, 15, 15, 5, 7, 7, 8, 11, 14, 14, 12, 6,
	9, 13, 15, 7, 12, 8, 9, 11, 7, 7, 12, 7, 6, 15, 13, 11,
	9, 7, 15, 11, 8, 6, 6, 14, 12, 13, 5, 14, 13, 13, 7, 5,
	15, 5, 8, 11, 14, 14, 6, 14, 6, 9, 12, 9, 12, 5, 15, 8,
	8, 5, 12, 9, 12, 5, 14, 6, 8, 13, 6, 5, 15, 13, 11, 11}


func Encode(str string) string {
	padded := bytes.NewBuffer([]byte(str))
	padded.WriteByte(0x80)
	for padded.Len() % 64 != 56 {
		padded.WriteByte(0)
	}
	messageLenBits := uint64(len(str)) * 8
	err:=binary.Write(padded, binary.LittleEndian, messageLenBits)
	if err!=nil {
		panic(err)
	}

	var buffer [16]uint32
	for binary.Read(padded, binary.LittleEndian, buffer[:]) == nil {
		A, B, C, D, E := h0, h1, h2, h3, h4
		AA, BB, CC, DD, EE := h0, h1, h2, h3, h4
		for j:=0; j<80; j++ {
			//fmt.Printf("%x\n",buffer[R[j]])
			tmp := (A + f(j,B,C,D) + buffer[R[j]] + chooseK(j)) % (2^32)
			T:=bits.RotateLeft32(tmp,S[j]) + E
			A, E, D, C, B = E, D, bits.RotateLeft32(C, 10), B, T

			tmp=(AA+f(79-j,BB,CC,DD)+buffer[RR[j]]+chooseKK(j)) % (2^32)
			T=bits.RotateLeft32(tmp, SS[j]) + EE
			AA, EE, DD, CC, BB = EE, DD, bits.RotateLeft32(CC, 10), BB, T
		}
		T := (h1 + C + DD) % (2^32)
		h1 = (h2+D+EE) % (2^32)
		h2 = (h3+E+AA) % (2^32)
		h3 = (h4+A+BB) % (2^32)
		h4 = (h0 + B + CC) % (2^32)
		h0 = T
	}
	var r [20]byte
	err=binary.Write(bytes.NewBuffer(r[:0]), binary.BigEndian, []uint32{h0,h1,h2,h3,h4})
	if err!=nil {
		panic(err)
	}

	return fmt.Sprintf("%x", r)
}

func f(j int, x uint32, y uint32, z uint32) uint32 {
	if j>=0 && j<=15 {
		return x^y^z
	} else if j>=16 && j<=31 {
		return (x & y) | (^x & z)
	} else if j>=32 && j<=47 {
		return (x | ^y) ^ z
	} else if j>=48 && j<=63 {
		return (x & z) | (y & ^z)
	} else if j>=64 && j<=79 {
		return x ^ (y | ^z)
	} else {
		return 0
	}
}

func chooseK(j int) uint32 {
	if j>=0 && j<=15 {
		return K[0]
	} else if j>=16 && j<=31 {
		return K[1]
	} else if j>=32 && j<=47 {
		return K[2]
	} else if j>=48 && j<=63 {
		return K[3]
	} else if j>=64 && j<=79 {
		return K[4]
	} else {
		return 0
	}
}

func chooseKK(j int) uint32 {
	if j>=0 && j<=15 {
		return KK[0]
	} else if j>=16 && j<=31 {
		return KK[1]
	} else if j>=32 && j<=47 {
		return KK[2]
	} else if j>=48 && j<=63 {
		return KK[3]
	} else if j>=64 && j<=79 {
		return KK[4]
	} else {
		return 0
	}
}