using System;
using System.Security.Cryptography;
using System.IO;

namespace HashProgram.RIPEMD160_HASH
{
    class RIPEMD160Lib
    {

        public RIPEMD160Lib(string fileName)
        {
            string directory = fileName;
            try
            {
                RIPEMD160 myRIPEMD160 = RIPEMD160.Create();
                byte[] hashValue;
                hashValue = myRIPEMD160.ComputeHash(File.ReadAllBytes(fileName));
                Console.Write("The RIPEMD160 LIB hash is: ");
                PrintByteArray(hashValue);
            }
            catch (DirectoryNotFoundException)
            {
                Console.WriteLine("Error: The directory specified could not be found.");
            }
            catch (IOException)
            {
                Console.WriteLine("Error: A file in the directory could not be accessed.");
            }
        }

        private static void PrintByteArray(byte[] array)
        {
            for (int i = 0; i < array.Length; i++)
            {
                Console.Write(String.Format("{0:X2}", array[i]).ToUpper());
            }
            Console.WriteLine();
        }


    }
}
