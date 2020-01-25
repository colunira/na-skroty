package crc64

import (
	"github.com/stretchr/testify/assert"
	"testing"
)


func TestEncode(t *testing.T) {

	t.Run("should return the same encoded value", func(t *testing.T) {
		//given
		raw, encoded := "abcd","336776c420000000"
		//when
		result := Encode(raw)

		//then
		assert.Equal(t, result,encoded)
	})
}
