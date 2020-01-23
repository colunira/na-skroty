using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HashProgram.MD2_HASH
{
    class MD2Own
    {
        private string Text;

        private static byte[] T_Table = new byte[]
        {
          41,    46,  67,  201, 162, 216, 124, 1,   61,  54,  84,  161, 236, 240, 6,   19,
          98,  167, 5,   243, 192, 199, 115, 140, 152, 147, 43,  217, 188, 76,  130, 202,
          30,  155, 87,  60,  253, 212, 224, 22,  103, 66,  111, 24,  138, 23,  229, 18,
          190, 78,  196, 214, 218, 158, 222, 73,  160, 251, 245, 142, 187, 47,  238, 122,
          169, 104, 121, 145, 21,  178, 7,   63,  148, 194, 16,  137, 11,  34,  95,  33,
          128, 127, 93,  154, 90,  144, 50,  39,  53,  62,  204, 231, 191, 247, 151, 3,
          255, 25,  48,  179, 72,  165, 181, 209, 215, 94,  146, 42,  172, 86,  170, 198,
          79,  184, 56,  210, 150, 164, 125, 182, 118, 252, 107, 226, 156, 116, 4,   241,
          69,  157, 112, 89,  100, 113, 135, 32,  134, 91,  207, 101, 230, 45,  168, 2,
          27,  96,  37,  173, 174, 176, 185, 246, 28,  70,  97,  105, 52,  64,  126, 15,
          85,  71,  163, 35,  221, 81,  175, 58,  195, 92,  249, 206, 186, 197, 234, 38,
          44,  83,  13,  110, 133, 40,  132, 9,   211, 223, 205, 244, 65,  129, 77,  82,
          106, 220, 55,  200, 108, 193, 171, 250, 36,  225, 123, 8,   12,  189, 177, 74,
          120, 136, 149, 139, 227, 99,  232, 109, 233, 203, 213, 254, 59,  0,   29 , 57,
          242, 239, 183, 14,  102, 88,  208, 228, 166, 119, 114, 248, 235, 117, 75 , 10,
          49,  68,  80,  180, 143, 237, 31,  26,  219, 153, 141, 51,  159, 17,  131, 20
        };


        public string GetHash(byte[] input)
        {
            Encoding encode = Encoding.UTF8;

            byte[] textByte = input;

            byte c = (byte)(16 - textByte.Length % 16);

            if (textByte.Length % 16 == 0)
            {
                c = 16;
                byte[] useless = new byte[textByte.Length + 1];
                Array.Copy(textByte, 0, useless, 0, textByte.Length);
                useless[useless.Length - 1] = c;

                textByte = useless;
            }



            while (textByte.Length % 16 != 0)
            {
                byte[] useless = new byte[textByte.Length + 1];

                Array.Copy(textByte, 0, useless, 0, textByte.Length);

                useless[useless.Length - 1] = c;

                textByte = useless;
            }

            textByte = StepTwo(textByte);
            byte[] result = LastStep(textByte);

            byte[] finish = new byte[16];
            Array.Copy(result, 0, finish, 0, 16);


            string output = ByteArrayToString(finish);

            return output;
        }


        private byte[] StepTwo(byte[] array)
        {
            byte[] output = new byte[array.Length + 16];
            Array.Copy(array, 0, output, 0, array.Length);

            byte[] C = new byte[16];
            byte L = 0;

            for (int i = 0; i < array.Length / 16; i++)
            {
                for (int j = 0; j < 16; j++)
                {
                    byte c = array[i * 16 + j];
                    C[j] = (byte)(C[j] ^ T_Table[c ^ L]);

                    L = C[j];
                }
            }

            Array.Copy(C, 0, output, array.Length, 16);

            return output;
        }


        static byte[] LastStep(byte[] array)
        {
            byte[] X = new byte[48];

            for (int i = 0; i < array.Length / 16; i++)
            {
                for (int j = 0; j < 16; j++)
                {
                    X[16 + j] = array[i * 16 + j];
                    X[32 + j] = (byte)(X[16 + j] ^ X[j]);
                }


                byte t = 0;

                for (int f = 0; f < 18; f++)
                {
                    for (int k = 0; k < 48; k++)
                    {
                        X[k] = (byte)(X[k] ^ T_Table[t]);
                        t = X[k];
                    }

                    t = (byte)((t + f) % 256);
                }
            }

            return X;
        }



        public static string ByteArrayToString(byte[] ba)
        {
            StringBuilder hex = new StringBuilder(ba.Length * 2);
            foreach (byte b in ba)
                hex.AppendFormat("{0:x2}", b);
            return hex.ToString();
        }
    }
}
