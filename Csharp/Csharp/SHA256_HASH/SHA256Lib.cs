using System;
using System.Text;
using System.Security.Cryptography;
using System.IO;

namespace HashProgram.SHA256_HASH
{
    class SHA256Lib
    {
        public SHA256Lib(string fileName)
        {
            using (SHA256 sha256Hash = SHA256.Create())
            {
                string hash = GetSha256Hash(sha256Hash, fileName);

                Console.WriteLine("The SHA256 LIB hash is: " + hash.ToUpper() + ".");
            }
        }

        static string GetSha256Hash(SHA256 sha256Hash, string fileName)
        {
            byte[] data = sha256Hash.ComputeHash(File.ReadAllBytes(fileName));
            StringBuilder sBuilder = new StringBuilder();
            for (int i = 0; i < data.Length; i++)
            {
                sBuilder.Append(data[i].ToString("x2"));
            }
            return sBuilder.ToString();
        }
    }
}
