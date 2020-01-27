package adler32

import "fmt"

func Encode(str string) string {
	data:=[]byte(str)
	a:=uint16(1)
	b:=uint16(0)
	for _, d:=range data {
		a+=uint16(d) % 65521
		b+=a % 65521
	}

	return fmt.Sprintf("%04x%04x",b,a)
}
