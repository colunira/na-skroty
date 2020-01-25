package md2

import (
	"github.com/stretchr/testify/assert"
	"testing"
)


func TestEncode(t *testing.T) {

	t.Run("should return the same encoded value", func(t *testing.T) {
		//given
		raw, encoded := "abcd","f790d2a3940dde4056387c787f3062f8"
		//when
		result := Encode(raw)

		//then
		assert.Equal(t, result,encoded)
	})
}
