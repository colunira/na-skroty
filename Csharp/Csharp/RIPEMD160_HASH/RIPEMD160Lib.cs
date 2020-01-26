using System;
using System.Security.Cryptography;
using System.IO;

namespace HashProgram.RIPEMD160_HASH
{
    class RIPEMD160Lib
    {

        public RIPEMD160Lib(string fileName)
        {

        }

        public string Compute(string fileName)
        {
            string directory = fileName;
            try
            {

                RIPEMD160 myRIPEMD160 = RIPEMD160.Create();
                byte[] hashValue;
                hashValue = myRIPEMD160.ComputeHash(File.ReadAllBytes(fileName));
                return PrintByteArray(hashValue);
            }
            catch (DirectoryNotFoundException)
            {
                Console.WriteLine("Error: The directory specified could not be found.");
                return "";
            }
            catch (IOException)
            {
                Console.WriteLine("Error: A file in the directory could not be accessed.");
                return "";
            }
            return "";
        }

        private string PrintByteArray(byte[] array)
        {
                string hash = "";
                for (int i = 0; i < array.Length; i++)
                {
                hash += String.Format("{0:X2}", array[i]).ToUpper();
                }
            return hash;
        }


    }
}
