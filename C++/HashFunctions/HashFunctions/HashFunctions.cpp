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
#include "MD2.h"
#include "MD5.h"
#include "Ripemd160.h"
#include "Sha256.h"

using namespace std;

int main() {
	string message = "abc";

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

	CryptoPP::StringSource ss(message, true /*pumpAll*/, new CryptoPP::Redirector(cs));

	cout << "Message: " << message << endl;
	cout << "SHA-1: " << s1 << endl;
	cout << "MD4: " << s2 << endl;
	cout << "SHA-256: " << s3 << endl;
	cout << "SHA-512: " << s4 << endl;
	cout << "MD5: " << s5 << endl;
	cout << "MD2: " << s6 << endl;
	cout << "CRC32: " << s7 << endl;
	cout << "ADLER32: " << s8 << endl;
	cout << "RIPEMD-160: " << s9 << endl;

	cout << endl;
	CRC64 Mycrc64 = CRC64();
	CRC32 Mycrc32 = CRC32();
	ADLER32 Myadler32 = ADLER32();
	MD5 Mymd5 = MD5();
	RIPEMD_160 Myripemd160 = RIPEMD_160();
	Sha256 Mysha256 = Sha256();
	cout << endl;

	cout << "My CRC32: " << hex << Mycrc32.crc32(0, (unsigned char*)message.c_str(), message.length()) << dec << endl;
	cout << "My CRC64: " << hex << Mycrc64.crc64_ecma182(0, (unsigned char*)message.c_str(), message.length()) << dec << endl;
	cout << "My ADLER32: " << hex << Myadler32.adler32(0, (unsigned char*)message.c_str(), message.length()) << endl;
	Mymd5.update(message.c_str(), message.length());
	Mymd5.finalize();
	cout << "My MD5: " << Mymd5.toString() << endl;
	cout << "My ripe: " << Myripemd160.ripemd_160(message) << endl;
	cout << "My Sha256: " << Mysha256.SHA256((char*)message.c_str());

	getchar();
	return 0;
}

