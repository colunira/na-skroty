package adler32

import (
	"github.com/stretchr/testify/assert"
	"testing"
)


func TestEncode(t *testing.T) {

	t.Run("should return the same encoded value", func(t *testing.T) {
		//given
		raw, encoded := "abcd","03d8018b"
		//when
		result := Encode(raw)

		//then
		assert.Equal(t, result,encoded)
	})
}
