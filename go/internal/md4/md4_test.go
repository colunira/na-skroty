package md4

import (
	"github.com/stretchr/testify/assert"
	"testing"
)


func TestEncode(t *testing.T) {

	t.Run("should return the same encoded value", func(t *testing.T) {
		//given
		raw, encoded := "abcd","41decd8f579255c5200f86a4bb3ba740"
		//when
		result := Encode(raw)

		//then
		assert.Equal(t, result,encoded)
	})
}
