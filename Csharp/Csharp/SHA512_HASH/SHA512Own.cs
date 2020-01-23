using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace HashProgram.SHA512_HASH
{
    using Word64 = System.UInt64;
    class SHA512Own
    {
        static Word64[] H0Sha512;
        static Word64[] K512;
        public byte[] Compute(byte[] message, int numberBits = 512)  
        {
            DefineH0Sha512();
            DefineK512();

            byte[] paddedMessage = PadMessage1024(message);

            Block1024[] blocks = ConvertPaddedMessageToBlock1024Array(paddedMessage);
            
            Word64[] H = H0Sha512;

            for (int i = 0; i < blocks.Length; i++)
            {
                Word64[] W = CreateMessageScheduleSha512(blocks[i]);
                
                Word64 a = H[0];
                Word64 b = H[1];
                Word64 c = H[2];
                Word64 d = H[3];
                Word64 e = H[4];
                Word64 f = H[5];
                Word64 g = H[6];
                Word64 h = H[7];

                for (int t = 0; t < 80; t++)
                {
                    Word64 T1 = h + Sigma1_512(e) + Ch(e, f, g) + K512[t] + W[t];
                    Word64 T2 = Sigma0_512(a) + Maj(a, b, c);
                    h = g;
                    g = f;
                    f = e;
                    e = d + T1;
                    d = c;
                    c = b;
                    b = a;
                    a = T1 + T2;
                }
                
                H[0] += a;
                H[1] += b;
                H[2] += c;
                H[3] += d;
                H[4] += e;
                H[5] += f;
                H[6] += g;
                H[7] += h;
            }
            byte[] hash = ShaUtil.Word64ArrayToByteArray(H);
            
            int numberBytes = numberBits / 8;
            byte[] truncatedHash = new byte[numberBytes];
            Array.Copy(hash, truncatedHash, numberBytes);

            return truncatedHash;
        }

        static Word64[] CreateMessageScheduleSha512(Block1024 block)
        {
            Word64[] W = new Word64[80];
            
            for (int t = 0; t < 80; t++)
            {
                if (t < 16)
                {
                    W[t] = block.words[t];
                }
                else
                {
                    W[t] = sigma1_512(W[t - 2]) + W[t - 7] + sigma0_512(W[t - 15]) + W[t - 16];
                }
            }

            return W;
        }

        static Word64 Ch(Word64 x, Word64 y, Word64 z)
        {
            return (x & y) ^ (~x & z);
        }

        static Word64 Maj(Word64 x, Word64 y, Word64 z)
        {
            return (x & y) ^ (x & z) ^ (y & z);
        }

        static Word64 Sigma0_512(Word64 x)
        {
            return RotR(28, x) ^ RotR(34, x) ^ RotR(39, x);
        }
        static Word64 sigma0_512(Word64 x)
        {
            return RotR(1, x) ^ RotR(8, x) ^ ShR(7, x);
        }

        static Word64 sigma1_512(Word64 x)
        {
            return RotR(19, x) ^ RotR(61, x) ^ ShR(6, x);
        }

        static Word64 Sigma1_512(Word64 x)
        {
            return RotR(14, x) ^ RotR(18, x) ^ RotR(41, x);
        }

        static Word64 RotR(int n, Word64 x)
        {
            // should have 0 <= n < 64
            return (x >> n) | (x << 64 - n);
        }

        static Word64 ShR(int n, Word64 x)
        {
            // should have 0 <= n < 64
            return (x >> n);
        }

        static void DefineH0Sha512()
        {
            // These eight 64-bit words are obtained by taking the first 64 bits of the 
            // fractional parts of the square roots of the first eight prime numbers.

            H0Sha512 = new Word64[]
            {
                0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1,
                0x510e527fade682d1, 0x9b05688c2b3e6c1f, 0x1f83d9abfb41bd6b, 0x5be0cd19137e2179
            };
        }

        static void DefineK512()
        {
            // The eighty 64-bit words in the array K512 are used in Sha-384, Sha-512, Sha-512/224, Sha-512/256. 
            // They are obtained by taking the first 64 bits of the fractional
            // parts of the cube roots of the first eighty primes. 

            K512 = new Word64[]
            {
                0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
                0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
                0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
                0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
                0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
                0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
                0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
                0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
                0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
                0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
                0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
                0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
                0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
                0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
                0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
                0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
                0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
                0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
                0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
                0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
            };
        }

        static byte[] PadMessage1024(byte[] message)
        {
            // After padding the total bits of the message will be divisible by 1024.
            int numberBits = message.Length * 8;
            int t = (numberBits + 8 + 128) / 1024;

            // Note that 1024 * (t + 1) is the least multiple of 1024 greater than (numberBits + 8 + 128)
            // Therefore the number of zero bits we need to add is
            int k = 1024 * (t + 1) - (numberBits + 8 + 128);

            // Since numberBits % 8 = 0, we know k % 8 = 0. So n = k / 8 is the number of zero bytes to add.
            int n = k / 8;

            List<byte> paddedMessage = message.ToList();

            // Start the padding by concatenating 1000_0000 = 0x80 = 128
            paddedMessage.Add(0x80);

            // Next add n zero bytes
            for (int i = 0; i < n; i++)
            {
                paddedMessage.Add(0);
            }

            // Now add 16 bytes (128 bits) to represent the length of the message in bits.
            // C# does not have 128 bit integer.
            // For now just add 8 zero bytes and then 8 bytes to represent the int

            for (int i = 0; i < 8; i++)
            {
                paddedMessage.Add(0);
            }

            byte[] B = BitConverter.GetBytes((ulong)numberBits); //TODO write this function yourself!
            Array.Reverse(B);

            for (int i = 0; i < B.Length; i++)
            {
                paddedMessage.Add(B[i]);
            }

            return paddedMessage.ToArray();
        }

        static Block1024[] ConvertPaddedMessageToBlock1024Array(byte[] M)
        {
            // We are assuming M is padded, so the number of bits in M is divisible by 1024 
            int numberBlocks = (M.Length * 8) / 1024;  // same as: M.Length / 128
            Block1024[] blocks = new Block1024[numberBlocks];

            for (int i = 0; i < numberBlocks; i++)
            {
                // First extract the relavant subarray from M
                byte[] B = new byte[128]; // 128 * 8 = 1024

                for (int j = 0; j < 128; j++)
                {
                    B[j] = M[i * 128 + j];
                }

                Word64[] words = ShaUtil.ByteArrayToWord64Array(B);
                blocks[i] = new Block1024(words);
            }

            return blocks;
        }

        public class Block1024
        {
            // A Block1024 consists of an array of 16 elements of type Word64.
            // set this as a property?
            public Word64[] words;

            public Block1024(Word64[] words)
            {
                if (words.Length == 16)
                {
                    this.words = words;
                }
                else
                {
                    Console.WriteLine("ERROR: A block must be 16 words");
                    this.words = null;
                }
            }
        }
  
    }
    
    public class ShaUtil
    {
        public static Word64[] ByteArrayToWord64Array(byte[] B)
        {
            // We assume B is not null, is not empty and number elements is divisible by 8
            int numberWords = B.Length / 8; // 8 bytes for each Word32
            Word64[] wordArray = new Word64[numberWords];

            for (int i = 0; i < numberWords; i++)
            {
                wordArray[i] = ByteArrayToWord64(B, 8 * i);
            }

            return wordArray;
        }

        public static Word64 ByteArrayToWord64(byte[] B, int startIndex)
        {
            // We assume: 0 <= startIndex < B. Length, and startIndex + 8 <= B.Length

            Word64 c = 256;
            Word64 output = 0;

            for (int i = startIndex; i < startIndex + 8; i++)
            {
                output = output * c + B[i];
            }

            return output;
        }


        public static byte[] Word64ArrayToByteArray(Word64[] words)
        {
            List<byte> b = new List<byte>();

            for (int i = 0; i < words.Length; i++)
            {
                b.AddRange(Word64ToByteArray(words[i]));
            }

            return b.ToArray();
        }

        public static byte[] Word64ToByteArray(Word64 x)
        {
            byte[] b = BitConverter.GetBytes(x);
            Array.Reverse(b);
            return b;
        }

    }

}