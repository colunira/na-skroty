using System;
using System.IO;
using System.Security.Cryptography;
using System.Text;

namespace HashProgram.MD5_HASH
{
    class MD5Lib
    {
        public MD5Lib()
        {
        }


        public string Compute(string fileName)
        {
            using (MD5 md5Hash = MD5.Create())
            {
                return GetMd5Hash(md5Hash, fileName);

                //Console.WriteLine("The MD5 LIB hash is: " + hash + ".");
            }
        }

        static string GetMd5Hash(MD5 md5Hash, string fileName)
        {
            byte[] data = md5Hash.ComputeHash(File.ReadAllBytes(fileName));
            StringBuilder sBuilder = new StringBuilder();
            for (int i = 0; i < data.Length; i++)
            {
                sBuilder.Append(data[i].ToString("x2"));
            }
            return sBuilder.ToString().ToUpper();
        }

    }
}
