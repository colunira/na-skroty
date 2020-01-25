#include "../cryptopp/cryptlib.h"

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include "../cryptopp/md5.h"
#include "../cryptopp/sha.h"
#include "../cryptopp/filters.h"
#include "../cryptopp/hex.h"
#include "../cryptopp/channels.h"
#include "../cryptopp/md5.h"
#include "../cryptopp/md4.h"
#include "../cryptopp/md2.h"
#include "../cryptopp/CRC.h"
#include "../cryptopp/adler32.h"
#include "../cryptopp/ripemd.h"
#include <iostream>
#include <cstring>
#include <windows.h>
#include <vector>
#include <stdio.h>
#include <stdint.h>
#include "crc64.h"
#include "crc32.h"
#include "Adler32.h"
#include <stddef.h>
#include <stdint.h>
#include <sstream>
#include "MD5.h"
#include "Ripemd160.h"
#include "Sha256.h"
#include "Sha1.h"
#include "Sha512.h"
#include "MD2.h"
#include "MD4.h"

static string message;
void libraries(double*);
void customImplementations(double*);

bool is_file_exist(const char* fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}

void readFile(std::string path) {

	if (!is_file_exist(path.c_str()))
	{
		std::cout << "Podany plik nie istnieje: " + path << endl;
		exit(-879213);
	}

	std::ifstream t(path);
	std::stringstream buffer;
	buffer << t.rdbuf();
	message = buffer.str();
}

int main(int argc, char* argv[]) {
	string fp = "";
	if (argc > 1)
		fp = argv[1];


	double allCustomDurations[8][10];
	double allLibrariesDurations[8][10];
	for (int i = 1; i <= 8; i++)
	{
		string fileName = "pliktekstowy" + std::to_string(i) + ".txt";
		string filePath;
		if (fp.length() == 0)
			filePath = "F:\\Projekty\\cpp\\na-skroty\\Pliki\\" + fileName;
		else
			filePath = fp + fileName;

		std::cout << "Plik: " << fileName << endl;
		readFile(filePath);

		std::cout << "#############################L I B R A R I E S#####################" << endl;
		clock_t start = clock();
		double libsdurations[10];
		libraries(libsdurations);
		std::cout << "£¹czny czas wykonywania: " << ((clock() - start) / (double)CLOCKS_PER_SEC) << "s\n";

		std::cout << endl;

		std::cout << "#############################C U S T O M\tI M P L E M E N T A T I O N#####################" << endl;
		start = clock();

		double durations[10];
		customImplementations(durations);
		std::cout << "£¹czny czas wykonywania: " << ((clock() - start) / (double)CLOCKS_PER_SEC) << "s\n";
		std::cout << endl;


		string outFilePath;
		string outFilePathLibs;
		if (fp.length() == 0)
		{
			outFilePath = "F:\\Projekty\\cpp\\na-skroty\\Pliki\\out" + fileName;
			outFilePathLibs = "F:\\Projekty\\cpp\\na-skroty\\Pliki\\outlib" + fileName;
		}
		else
		{
			outFilePath = "out" + fileName;
			outFilePathLibs = "outlib" + fileName;
		}


		ofstream outfile;
		ofstream outlibfile;
		outfile.open(outFilePath);
		outlibfile.open(outFilePathLibs);
		for (int j = 0; j < 10; j++)
		{
			outfile << durations[j];
			if (j != 9)
				outfile << endl;

			outlibfile << libsdurations[j];
			if (j != 9)
				outlibfile << endl;
		}

	}
	cout << endl << endl << "KONIEC";
	return 0;
}

void libraries(double* durations) {
	clock_t start;
	double duration;


	string s1, s2, s3, s4, s5, s6, s7, s8, s9, s10;
	CryptoPP::SHA1 sha1; CryptoPP::SHA256 sha256; CryptoPP::SHA512 sha512;
	CryptoPP::Weak1::MD4 md4; CryptoPP::Weak1::MD5 md5; CryptoPP::Weak1::MD2 md2;
	CryptoPP::CRC32 crc32;
	CryptoPP::Adler32 adler32;
	CryptoPP::RIPEMD160 ripemd160;

	CryptoPP::HashFilter f6(md2, new CryptoPP::HexEncoder(new CryptoPP::StringSink(s6)));
	CryptoPP::HashFilter f2(md4, new CryptoPP::HexEncoder(new CryptoPP::StringSink(s2)));
	CryptoPP::HashFilter f5(md5, new CryptoPP::HexEncoder(new CryptoPP::StringSink(s5)));
	CryptoPP::HashFilter f1(sha1, new CryptoPP::HexEncoder(new CryptoPP::StringSink(s1)));
	CryptoPP::HashFilter f3(sha256, new CryptoPP::HexEncoder(new CryptoPP::StringSink(s3)));
	CryptoPP::HashFilter f4(sha512, new CryptoPP::HexEncoder(new CryptoPP::StringSink(s4)));
	CryptoPP::HashFilter f9(ripemd160, new CryptoPP::HexEncoder(new CryptoPP::StringSink(s9)));
	CryptoPP::HashFilter f7(crc32, new CryptoPP::HexEncoder(new CryptoPP::StringSink(s7)));
	CryptoPP::HashFilter f8(adler32, new CryptoPP::HexEncoder(new CryptoPP::StringSink(s8)));

	CryptoPP::ChannelSwitch cs1;
	CryptoPP::ChannelSwitch cs2;
	CryptoPP::ChannelSwitch cs3;
	CryptoPP::ChannelSwitch cs4;
	CryptoPP::ChannelSwitch cs5;
	CryptoPP::ChannelSwitch cs6;
	CryptoPP::ChannelSwitch cs7;
	CryptoPP::ChannelSwitch cs8;
	CryptoPP::ChannelSwitch cs9;

	cs1.AddDefaultRoute(f6);
	cs2.AddDefaultRoute(f2);
	cs3.AddDefaultRoute(f5);
	cs4.AddDefaultRoute(f1);
	cs5.AddDefaultRoute(f3);
	cs6.AddDefaultRoute(f4);
	cs7.AddDefaultRoute(f9);
	cs8.AddDefaultRoute(f7);
	cs9.AddDefaultRoute(f8);

	start = clock();
	CryptoPP::StringSource ss1(message, true, new CryptoPP::Redirector(cs1));
	duration = ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000;
	durations[0] = duration;
	start = clock();
	CryptoPP::StringSource ss2(message, true, new CryptoPP::Redirector(cs2));
	duration = ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000;
	durations[1] = duration;
	start = clock();
	CryptoPP::StringSource ss3(message, true, new CryptoPP::Redirector(cs3));
	duration = ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000;
	durations[2] = duration;
	start = clock();
	CryptoPP::StringSource ss4(message, true, new CryptoPP::Redirector(cs4));
	duration = ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000;
	durations[3] = duration;
	start = clock();
	CryptoPP::StringSource ss5(message, true, new CryptoPP::Redirector(cs5));
	duration = ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000;
	durations[4] = duration;
	start = clock();
	CryptoPP::StringSource ss6(message, true, new CryptoPP::Redirector(cs6));
	duration = ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000;
	durations[5] = duration;
	start = clock();
	CryptoPP::StringSource ss7(message, true, new CryptoPP::Redirector(cs7));
	duration = ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000;
	durations[6] = duration;
	start = clock();
	CryptoPP::StringSource ss8(message, true, new CryptoPP::Redirector(cs8));
	duration = ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000;
	durations[7] = duration;
	durations[8] = 0.0;
	start = clock();
	CryptoPP::StringSource ss9(message, true, new CryptoPP::Redirector(cs9));
	duration = ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000;
	durations[9] = duration;

	std::cout << "MD2: " << s6 << endl;
	std::cout << "MD4: " << s2 << endl;
	std::cout << "MD5: " << s5 << endl;
	std::cout << "SHA-1: " << s1 << endl;
	std::cout << "SHA-256: " << s3 << endl;
	std::cout << "SHA-512: " << s4 << endl;
	std::cout << "RIPEMD-160: " << s9 << endl;
	std::cout << "CRC32: " << s7 << endl;
	std::cout << "CRC64: " << "-----------" << endl;
	std::cout << "ADLER32: " << s8 << endl;
}

void customImplementations(double* durations) {
	clock_t start;
	double duration;


	CRC64 Mycrc64 = CRC64();
	CRC32 Mycrc32 = CRC32();
	ADLER32 Myadler32 = ADLER32();
	MD5 Mymd5 = MD5();
	RIPEMD_160 Myripemd160 = RIPEMD_160();
	Sha256 Mysha256 = Sha256();
	SHA1 Mysha1 = SHA1();
	SHA512 Mysha512 = SHA512();
	MD2 Mymd2 = MD2();
	MD4 Mymd4 = MD4();

	start = clock();
	std::cout << "Custom implementation MD2: " << hex;
	BYTE buf[16];
	Mymd2.md2((unsigned char*)message.c_str(), message.length(), buf);
	for (int i = 0; i < 16; i++)
		std::cout << static_cast<unsigned>(*(buf + i));
	std::cout << endl;
	duration = ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000;
	durations[0] = duration;

	start = clock();
	std::cout << "Custom implementation MD4: ";
	BYTE buff[128];
	Mymd4.mdfour(buff, (unsigned char*)message.c_str(), message.length());
	for (int i = 0; i < 16; i++)
		std::cout << static_cast<unsigned>(*(buff + i));
	std::cout << endl;
	duration = ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000;
	durations[1] = duration;

	start = clock();
	std::cout << "Custom implementation MD5: " << Mymd5.md5((unsigned char*)message.c_str(), message.length()) << endl;
	duration = ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000;
	durations[2] = duration;

	start = clock();
	std::cout << "Custom implementation Sha1: " << Mysha1.sha1(message) << endl;
	duration = ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000;
	durations[3] = duration;

	start = clock();
	std::cout << "Custom implementation Sha256: " << Mysha256.SHA256((char*)message.c_str()) << endl;
	duration = ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000;
	durations[4] = duration;

	start = clock();
	std::cout << "Custom implementation Sha512: " << Mysha512.hash(message) << endl;
	duration = ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000;
	durations[5] = duration;

	start = clock();
	std::cout << "Custom implementation ripe: " << Myripemd160.ripemd_160(message) << endl;
	duration = ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000;
	durations[6] = duration;

	start = clock();
	std::cout << "Custom implementation CRC32: " << hex << Mycrc32.crc32(0, (unsigned char*)message.c_str(), message.length()) << dec << endl;
	duration = ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000;
	durations[7] = duration;

	start = clock();
	std::cout << "Custom implementation CRC64: " << hex << Mycrc64.crc64_ecma182(0, (unsigned char*)message.c_str(), message.length()) << dec << endl;
	duration = ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000;
	durations[8] = duration;

	start = clock();
	std::cout << "Custom implementation ADLER32: " << hex << Myadler32.adler32(0, (unsigned char*)message.c_str(), message.length()) << endl;
	duration = ((clock() - start) / (double)CLOCKS_PER_SEC) * 1000;
	durations[9] = duration;
}




