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
#include <stddef.h>
#include <stdint.h>

using namespace std;

int main() {
	using namespace CryptoPP;
	using namespace Weak1;

	string message = "abc";

	string s1, s2, s3, s4, s5, s6, s7, s8, s9, s10;
	SHA1 sha1; SHA256 sha256; SHA512 sha512;
	MD4 md4; MD5 md5; MD2 md2;
	CRC32 crc32; CRC64 crc64 = CRC64();
	Adler32 adler32;
	RIPEMD160 ripemd160;

	HashFilter f1(sha1, new HexEncoder(new StringSink(s1)));
	HashFilter f2(md4, new HexEncoder(new StringSink(s2)));
	HashFilter f3(sha256, new HexEncoder(new StringSink(s3)));
	HashFilter f4(sha512, new HexEncoder(new StringSink(s4)));
	HashFilter f5(md5, new HexEncoder(new StringSink(s5)));
	HashFilter f6(md2, new HexEncoder(new StringSink(s6)));
	HashFilter f7(crc32, new HexEncoder(new StringSink(s7)));
	HashFilter f8(adler32, new HexEncoder(new StringSink(s8)));
	HashFilter f9(ripemd160, new HexEncoder(new StringSink(s9)));

	ChannelSwitch cs;
	cs.AddDefaultRoute(f1);
	cs.AddDefaultRoute(f2);
	cs.AddDefaultRoute(f3);
	cs.AddDefaultRoute(f4);
	cs.AddDefaultRoute(f5);
	cs.AddDefaultRoute(f6);
	cs.AddDefaultRoute(f7);
	cs.AddDefaultRoute(f8);
	cs.AddDefaultRoute(f9);

	StringSource ss(message, true /*pumpAll*/, new Redirector(cs));

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
	cout << hex << crc64.crc64_ecma182(0, (unsigned char*)"abc", 3);

	getchar();

	return 0;
}