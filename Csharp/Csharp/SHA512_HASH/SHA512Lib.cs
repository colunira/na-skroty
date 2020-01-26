using System;
using System.IO;
using System.Security.Cryptography;
using System.Text;

namespace HashProgram.SHA512_HASH
{
    class SHA512Lib
    {
        public SHA512Lib(string fileName)
        {
                using (SHA512 sha512Hash = SHA512.Create())
                {
                    string hash = GetSha512Hash(sha512Hash, fileName);
                }
        }

        public string Compute(string fileName)
        {
            using (SHA512 sha512Hash = SHA512.Create())
            {
                string hash = GetSha512Hash(sha512Hash, fileName);

                return hash;
            }
        }

        static string GetSha512Hash(SHA512 sha512Hash, string fileName)
        {
            byte[] data = sha512Hash.ComputeHash(File.ReadAllBytes(fileName));
            StringBuilder sBuilder = new StringBuilder();
            for (int i = 0; i < data.Length; i++)
            {
                sBuilder.Append(data[i].ToString("x2"));
            }
            return sBuilder.ToString().ToUpper();
        }
    }
}
