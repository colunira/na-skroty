using System;
using System.Text;
using System.Security.Cryptography;
using System.IO;

namespace HashProgram.SHA1_HASH
{
    class SHA1Lib
    {
        public SHA1Lib(string fileName)
        {
                using (SHA1 sha1Hash = SHA1.Create())
                {
                    string hash = GetSha1Hash(sha1Hash, fileName);
                }
        }

        public string Compute(string fileName)
        {
            using (SHA1 sha1Hash = SHA1.Create())
            {
                string hash = GetSha1Hash(sha1Hash, fileName);

                return hash.ToUpper();
            }
        }

        static string GetSha1Hash(SHA1 sha1Hash, string fileName)
        {
            byte[] data = sha1Hash.ComputeHash(File.ReadAllBytes(fileName));
            StringBuilder sBuilder = new StringBuilder();
            for (int i = 0; i < data.Length; i++)
            {
                sBuilder.Append(data[i].ToString("x2"));
            }
            return sBuilder.ToString();
        }

    }
}
