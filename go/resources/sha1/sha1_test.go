package sha1

import (
	"github.com/stretchr/testify/assert"
	"testing"
)


func TestEncode(t *testing.T) {

	t.Run("should return the same encoded value", func(t *testing.T) {
		//given
		raw, encoded := "abcd","81fe8bfe87576c3ecb22426f8e57847382917acf"
		//when
		result := Encode(raw)

		//then
		assert.Equal(t, result,encoded)
	})
}
