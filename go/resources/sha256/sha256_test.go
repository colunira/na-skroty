package sha256

import (
	"github.com/stretchr/testify/assert"
	"testing"
)


func TestEncode(t *testing.T) {

	t.Run("should return the same encoded value", func(t *testing.T) {
		//given
		raw, encoded := "abcd","88d4266fd4e6338d13b845fcf289579d209c897823b9217da3e161936f031589"
		//when
		result := Encode(raw)

		//then
		assert.Equal(t, result,encoded)
	})
}
