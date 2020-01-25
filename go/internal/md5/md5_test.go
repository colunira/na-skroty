package md5

import (
	"github.com/stretchr/testify/assert"
	"testing"
)


func TestEncode(t *testing.T) {

	t.Run("should return the same encoded value", func(t *testing.T) {
		//given
		raw, encoded := "abcd","e2fc714c4727ee9395f324cd2e7f331f"
		//when
		result := Encode(raw)

		//then
		assert.Equal(t, result,encoded)
	})
}
