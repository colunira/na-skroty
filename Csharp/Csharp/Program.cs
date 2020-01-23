using System;
using System.Diagnostics;
using HashProgram.MD5_HASH;
using HashProgram.RIPEMD160_HASH;
using HashProgram.SHA1_HASH;
using HashProgram.SHA256_HASH;
using HashProgram.SHA512_HASH;
using HashProgram.ADLER32_HASH;
using HashProgram.CRC32_HASH;
using HashProgram.CRC64_HASH;
using System.IO;
using System.Text;
using HashProgram.MD4_HASH;
using HashProgram.MD2_HASH;

namespace HashProgram
{
    class Program
    {
        static void Main(string[] args)
        {
            string fileName = args[0];//@"D:\JK\InzOpr\HashProgram\Pliki\pliktekstowy8.txt";
            try
            {
                Console.WriteLine("Hash of file: " + fileName);
                Console.WriteLine();

                Console.WriteLine("---------------------------------------------------------------");
                var watchMD2 = Stopwatch.StartNew();
                MD2Own md2 = new MD2Own();
                Console.WriteLine("The MD2 OWN hash is: " + md2.GetHash(File.ReadAllBytes(fileName)).ToUpper());
                watchMD2.Stop();
                Console.WriteLine("Time to execute: " + watchMD2.ElapsedMilliseconds + "ms\n");
                Console.WriteLine("---------------------------------------------------------------");

                Console.WriteLine("---------------------------------------------------------------");
                var watchMD4 = Stopwatch.StartNew();
                MD4Own md4 = new MD4Own();
                Console.WriteLine("The MD4 OWN hash is: " + md4.Md4Hash(File.ReadAllBytes(fileName)).ToUpper());
                watchMD4.Stop();
                Console.WriteLine("Time to execute: " + watchMD4.ElapsedMilliseconds + "ms\n");
                Console.WriteLine("---------------------------------------------------------------");

                Console.WriteLine("---------------------------------------------------------------");
                var watchMD5 = Stopwatch.StartNew();
                MD5Lib md5 = new MD5Lib();
                Console.WriteLine("The MD5 LIB hash is: " + md5.Compute(fileName).ToUpper() + ".");
                watchMD5.Stop();
                Console.WriteLine("Time to execute: " + watchMD5.ElapsedMilliseconds + "ms\n");
                Console.WriteLine("---------------------------------------------------------------");

                Console.WriteLine("---------------------------------------------------------------");
                var watchMD5Own = Stopwatch.StartNew();
                MD5Own md = new MD5Own(fileName);
                Console.WriteLine("The MD5 OWN hash is: " + md.FingerPrint.ToUpper() + ".");
                watchMD5Own.Stop();
                Console.WriteLine("Time to execute: " + watchMD5Own.ElapsedMilliseconds + "ms");
                Console.WriteLine("---------------------------------------------------------------");

                Console.WriteLine("---------------------------------------------------------------");
                var watchRIPEMD160 = Stopwatch.StartNew();
                RIPEMD160Lib RIPEMD160 = new RIPEMD160Lib(fileName);
                watchRIPEMD160.Stop();
                Console.WriteLine("Time to execute: " + watchRIPEMD160.ElapsedMilliseconds + "ms\n");
                Console.WriteLine("---------------------------------------------------------------");

                Console.WriteLine("---------------------------------------------------------------");
                var watchRIPEMD160Own = Stopwatch.StartNew();
                RIPEMD160Own ripemd160Own = new RIPEMD160Own();
                ripemd160Own.HashCore(File.ReadAllBytes(fileName), 0, File.ReadAllBytes(fileName).Length);
                var hashRMD = "";
                using (var fs = File.Open(fileName, FileMode.Open))
                    foreach (byte b in ripemd160Own.HashFinal()) hashRMD += b.ToString("x2").ToUpper();
                Console.WriteLine("The RIPEMD160 OWN hash is {0}", hashRMD.ToUpper());
                watchRIPEMD160Own.Stop();
                Console.WriteLine("Time to execute: " + watchRIPEMD160Own.ElapsedMilliseconds + "ms\n");
                Console.WriteLine("---------------------------------------------------------------");


                Console.WriteLine("---------------------------------------------------------------");
                var watchSHA1 = Stopwatch.StartNew();
                SHA1Lib SHA1 = new SHA1Lib(fileName);
                watchSHA1.Stop();
                Console.WriteLine("Time to execute: " + watchSHA1.ElapsedMilliseconds + "ms\n");
                Console.WriteLine("---------------------------------------------------------------");

                Console.WriteLine("---------------------------------------------------------------");
                var watchSHA1Own = Stopwatch.StartNew();
                SHA1Own sha1Own = new SHA1Own();
                sha1Own.glowna(File.ReadAllBytes(fileName));
                watchSHA1Own.Stop();
                Console.WriteLine("Time to execute: " + watchSHA1Own.ElapsedMilliseconds + "ms\n");
                Console.WriteLine("---------------------------------------------------------------");

                Console.WriteLine("---------------------------------------------------------------");
                var watchSHA256 = Stopwatch.StartNew();
                SHA256Lib SHA256 = new SHA256Lib(fileName);
                watchSHA256.Stop();
                Console.WriteLine("Time to execute: " + watchSHA256.ElapsedMilliseconds + "ms\n");
                Console.WriteLine("---------------------------------------------------------------");

                Console.WriteLine("---------------------------------------------------------------");
                var watchSHA256Own = Stopwatch.StartNew();
                SHA256Own SHA256Own = new SHA256Own();
                Console.WriteLine("The SHA256 OWN hash is: " + SHA256Own.Compute(fileName).ToUpper() + ".");
                watchSHA256Own.Stop();
                Console.WriteLine("Time to execute: " + watchSHA256Own.ElapsedMilliseconds + "ms\n");
                Console.WriteLine("---------------------------------------------------------------");

                Console.WriteLine("---------------------------------------------------------------");
                var watchSHA512 = Stopwatch.StartNew();
                SHA512Lib SHA512 = new SHA512Lib(fileName);
                watchSHA512.Stop();
                Console.WriteLine("Time to execute: " + watchSHA512.ElapsedMilliseconds + "ms\n");
                Console.WriteLine("---------------------------------------------------------------");

                Console.WriteLine("---------------------------------------------------------------");
                var watchSHA512Own = Stopwatch.StartNew();
                SHA512Own SHA512Owna = new SHA512Own();
                var hash512 = String.Empty;
                byte[] a = SHA512Owna.Compute(File.ReadAllBytes(fileName), 512);
                foreach (byte b in SHA512Owna.Compute(File.ReadAllBytes(fileName), 512)) hash512 += b.ToString("x2").ToUpper();
                Console.WriteLine("The SHA512 OWN hash is: {0}", hash512);
                Console.WriteLine(".");
                watchSHA512Own.Stop();
                Console.WriteLine("Time to execute: " + watchSHA512Own.ElapsedMilliseconds + "ms\n");
                Console.WriteLine("---------------------------------------------------------------");

                Console.WriteLine("---------------------------------------------------------------");
                var watchADLER32 = Stopwatch.StartNew();
                ADLER32Own ADLER32 = new ADLER32Own();
                ADLER32.reset();
                ADLER32.update(File.ReadAllBytes(fileName));
                watchADLER32.Stop();
                Console.WriteLine("ADLER32 is: " + ADLER32.getValue() + ".");
                Console.WriteLine("Time to execute: " + watchADLER32.ElapsedMilliseconds + "ms\n");
                Console.WriteLine("---------------------------------------------------------------");

                Console.WriteLine("---------------------------------------------------------------");
                var watchcrc32 = Stopwatch.StartNew();
                CRC32Own crc32 = new CRC32Own();
                var hash = String.Empty;

                using (var fs = File.Open(fileName, FileMode.Open))
                    foreach (byte b in crc32.ComputeHash(fs)) hash += b.ToString("x2").ToUpper();
                watchcrc32.Stop();
                Console.WriteLine("CRC 32 is {0}", hash);
                Console.WriteLine("Time to execute: " + watchcrc32.ElapsedMilliseconds + "ms\n");
                Console.WriteLine("---------------------------------------------------------------");

                Console.WriteLine("---------------------------------------------------------------");
                var watchcrc64 = Stopwatch.StartNew();
                CRC64Own crc64 = new CRC64Own();
                Console.WriteLine("CRC 64 is {0}", (crc64.Compute(File.ReadAllBytes(fileName), 0, 3) - 1).ToString("x2"));
                watchcrc64.Stop();
                Console.WriteLine("Time to execute: " + watchcrc64.ElapsedMilliseconds + "ms\n");
                Console.WriteLine("---------------------------------------------------------------");

                Console.ReadKey();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }

        }

    }
}
