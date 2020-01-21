using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace HashProgram.SHA1_HASH
{
    class SHA1Own
    {
        public void glowna(byte[] byteblock)
        {
            byte[] paddedBytes = padInput(byteblock);
            uint[] paddedUints = padInputToWords(byteblock);
            uint[] bigpadded = new uint[80];
            byte[] hash = (byte[])hasher.ComputeHash(paddedBytes, 0, byteblock.Length);
            uint[] hashByGPU = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0 };
            processBlock(paddedUints, hashByGPU, bigpadded);
            Console.WriteLine("The SHA1 OWN hash is: " + byteArrayToString(hash) + ".");

        }


        public static string byteArrayToString(byte[] input)
        {
            string tempst = "";

            for (int i = 0; i < input.Length; i++)
                tempst += input[i].ToString("X2");
            return tempst;
        }

        public static byte[] padInput(byte[] input)
        {
            uint bytesToPad = Convert.ToUInt32((64 - (input.Length % 64)) % 64);
            byte[] paddedInput = new byte[input.Length + bytesToPad];
            if (bytesToPad == 0)
            {
                Array.Copy(input, paddedInput, paddedInput.Length);
            }
            else
            {
                for (int i = 0; i < input.Length; i++)
                {
                    paddedInput[i] = input[i];
                }
                paddedInput[input.Length] = 0x80;

                for (int i = 1; i < bytesToPad - 2; i++)
                {
                    paddedInput[input.Length + i] = 0;
                }
                paddedInput[paddedInput.Length - 2] = getByte((64 - bytesToPad) * 8, 1);
                paddedInput[paddedInput.Length - 1] = getByte((64 - bytesToPad) * 8, 0);
            }
            return paddedInput;
        }

        public static string uintArrayToString(uint[] input)
        {
            string result = "";
            for (int i = 0; i < input.Length; i++)
            {
                uint high = input[i] >> 24;
                uint midhigh = (input[i] << 8) >> 24;
                uint midlow = (input[i] << 16) >> 24;
                uint low = (input[i] << 24) >> 24;
                result += high.ToString("X2") + midhigh.ToString("X2") + midlow.ToString("X2") + low.ToString("X2");
            }
            return result;
        }
        SHA1 hasher = SHA1CryptoServiceProvider.Create();
        public static uint[] padInputToWords(byte[] input)
        {
            uint bytesToPad = Convert.ToUInt32((64 - (input.Length % 64)) % 64);
            byte[] paddedInput = new byte[input.Length + bytesToPad];
            if (bytesToPad == 0)
            {
                Array.Copy(input, paddedInput, paddedInput.Length);
            }
            else
            {
                for (int i = 0; i < input.Length; i++)
                {
                    paddedInput[i] = input[i];
                }
                paddedInput[input.Length] = 0x80;

                for (int i = 1; i < bytesToPad - 2; i++)
                {
                    paddedInput[input.Length + i] = 0;
                }
                paddedInput[paddedInput.Length - 2] = getByte((64 - bytesToPad) * 8, 1);
                paddedInput[paddedInput.Length - 1] = getByte((64 - bytesToPad) * 8, 0);
            }
            uint[] result = new uint[paddedInput.Length / 4];
            for (int i = 0; i < paddedInput.Length; i += 4)
            {
                uint tempword = 0;
                tempword += paddedInput[i];
                tempword = tempword << 8;

                tempword += paddedInput[i + 1];
                tempword = tempword << 8;

                tempword += paddedInput[i + 2];
                tempword = tempword << 8;

                tempword += paddedInput[i + 3];
                result[i / 4] = tempword;
            }
            return result;
        }

        public static byte getByte(uint x, int n)
        {
            return (byte)((x >> 8 * n) & 0xFF);
        }

        public static uint circularShift(int bits, uint word)
        {
            uint output = (word << bits | word >> (32 - bits));
            return output;
        }
        public static void processBlock(uint[] block, uint[] hash, uint[] bigarray)
        {
            uint temp = 0;
            const uint k0 = 0x5a827999;
            const uint k1 = 0x6ed9eba1;
            const uint k2 = 0x8f1bbcdc;
            const uint k3 = 0xca62c1d6;
            int t = 0;
            for (t = 0; t < 16; t++)
            {
                bigarray[t] = block[t];
            }

            for (t = 16; t < 80; t++)
            {
                bigarray[t] = circularShift(1, (bigarray[t - 3] ^ bigarray[t - 8] ^ bigarray[t - 14] ^ bigarray[t - 16]));
            }

            uint A = hash[0];
            uint B = hash[1];
            uint C = hash[2];
            uint D = hash[3];
            uint E = hash[4];

            for (t = 0; t < 20; t++)
            {
                temp = circularShift(5, A) + ((B & C) | ((~B) & D)) + E + bigarray[t] + k0;
                E = D;
                D = C;
                C = circularShift(30, B);
                B = A;
                A = temp;
            }

            for (t = 20; t < 40; t++)
            {
                temp = circularShift(5, A) + (B ^ C ^ D) + E + bigarray[t] + k1;
                E = D;
                D = C;
                C = circularShift(30, B);
                B = A;
                A = temp;
            }

            for (t = 40; t < 60; t++)
            {
                temp = circularShift(5, A) + ((B & C) | (B & D) | (C & D)) + E + bigarray[t] + k2;
                E = D;
                D = C;
                C = circularShift(30, B);
                B = A;
                A = temp;
            }

            for (t = 60; t < 80; t++)
            {
                temp = circularShift(5, A) + (B ^ C ^ D) + E + bigarray[t] + k3;
                E = D;
                D = C;
                C = circularShift(30, B);
                B = A;
                A = temp;
            }


            hash[0] += A;
            hash[1] += B;
            hash[2] += C;
            hash[3] += D;
            hash[4] += E;

        }
    }
}
