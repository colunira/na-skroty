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
#include "MD5.h"
#include "Ripemd160.h"
#include "Sha256.h"
#include "Sha1.h"
#include "Sha512.h"
#include "MD2.h"
#include "MD4.h"

using namespace std;

static const string message = "abc";
void libraries();
void customImplementations();
void readFile() {

}

int main() {

	readFile();

	cout << "Message: " << message << endl;
	cout << "######################################################";
	cout << endl << endl;

	libraries();

	cout << endl;

	customImplementations();

	getchar();
	return 0;
}

void libraries() {
	string s1, s2, s3, s4, s5, s6, s7, s8, s9, s10;
	CryptoPP::SHA1 sha1; CryptoPP::SHA256 sha256; CryptoPP::SHA512 sha512;
	CryptoPP::Weak1::MD4 md4; CryptoPP::Weak1::MD5 md5; CryptoPP::Weak1::MD2 md2;
	CryptoPP::CRC32 crc32;
	CryptoPP::Adler32 adler32;
	CryptoPP::RIPEMD160 ripemd160;

	CryptoPP::HashFilter f1(sha1, new CryptoPP::HexEncoder(new CryptoPP::StringSink(s1)));
	CryptoPP::HashFilter f2(md4, new CryptoPP::HexEncoder(new CryptoPP::StringSink(s2)));
	CryptoPP::HashFilter f3(sha256, new CryptoPP::HexEncoder(new CryptoPP::StringSink(s3)));
	CryptoPP::HashFilter f4(sha512, new CryptoPP::HexEncoder(new CryptoPP::StringSink(s4)));
	CryptoPP::HashFilter f5(md5, new CryptoPP::HexEncoder(new CryptoPP::StringSink(s5)));
	CryptoPP::HashFilter f6(md2, new CryptoPP::HexEncoder(new CryptoPP::StringSink(s6)));
	CryptoPP::HashFilter f7(crc32, new CryptoPP::HexEncoder(new CryptoPP::StringSink(s7)));
	CryptoPP::HashFilter f8(adler32, new CryptoPP::HexEncoder(new CryptoPP::StringSink(s8)));
	CryptoPP::HashFilter f9(ripemd160, new CryptoPP::HexEncoder(new CryptoPP::StringSink(s9)));

	CryptoPP::ChannelSwitch cs;
	cs.AddDefaultRoute(f1);
	cs.AddDefaultRoute(f2);
	cs.AddDefaultRoute(f3);
	cs.AddDefaultRoute(f4);
	cs.AddDefaultRoute(f5);
	cs.AddDefaultRoute(f6);
	cs.AddDefaultRoute(f7);
	cs.AddDefaultRoute(f8);
	cs.AddDefaultRoute(f9);

	CryptoPP::StringSource ss(message, true, new CryptoPP::Redirector(cs));

	cout << "SHA-1: " << s1 << endl;
	cout << "SHA-256: " << s3 << endl;
	cout << "SHA-512: " << s4 << endl;
	cout << "MD2: " << s6 << endl;
	cout << "MD4: " << s2 << endl;
	cout << "MD5: " << s5 << endl;
	cout << "CRC32: " << s7 << endl;
	cout << "ADLER32: " << s8 << endl;
	cout << "RIPEMD-160: " << s9 << endl;
}

void customImplementations() {
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
	cout << endl;

	cout << "Custom implementation Sha1: " << Mysha1.sha1(message) << endl;
	cout << "Custom implementation Sha256: " << Mysha256.SHA256((char*)message.c_str()) << endl;
	cout << "Custom implementation Sha512: " << Mysha512.hash(message) << endl;
	cout << "Custom implementation MD2: " << hex;
	BYTE buf[16];
	Mymd2.md2((unsigned char*)message.c_str(), message.length(), buf);
	for (int i = 0; i < 16; i++)
		cout << static_cast<unsigned>(*(buf + i));
	cout << endl;

	cout << "Custom implementation MD4: ";
	BYTE buff[128];
	Mymd4.mdfour(buff, (unsigned char*)message.c_str(), message.length());
	for (int i = 0; i < 16; i++)
		cout << static_cast<unsigned>(*(buff + i));
	cout << endl;
	cout << "Custom implementation MD5: " << Mymd5.md5((unsigned char*)message.c_str(), message.length()) << endl;
	cout << "Custom implementation CRC32: " << hex << Mycrc32.crc32(0, (unsigned char*)message.c_str(), message.length()) << dec << endl;
	cout << "Custom implementation CRC64: " << hex << Mycrc64.crc64_ecma182(0, (unsigned char*)message.c_str(), message.length()) << dec << endl;
	cout << "Custom implementation ADLER32: " << hex << Myadler32.adler32(0, (unsigned char*)message.c_str(), message.length()) << endl;
	cout << "Custom implementation ripe: " << Myripemd160.ripemd_160(message) << endl;
	
	
	
	
}




