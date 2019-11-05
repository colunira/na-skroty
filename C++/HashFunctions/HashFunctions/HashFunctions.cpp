#include "../cryptopp/cryptlib.h"

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include "../cryptopp/md5.h"
#include "../cryptopp/sha.h"
#include "../cryptopp/filters.h"
#include "../cryptopp/hex.h"
#include "../cryptopp/channels.h"
#include "../cryptopp/md5.h"
#include <iostream>
#include <cstring>

using namespace std;

int main() {
	using namespace CryptoPP;
	using namespace Weak1;

	string message = "Now is the time for all good men to come to the aide of their country";

	string s1, s2, s3, s4, s5;
	SHA1 sha1; SHA224 sha224; SHA256 sha256; SHA512 sha512;
	MD5 md5;

	HashFilter f1(sha1, new HexEncoder(new StringSink(s1)));
	HashFilter f2(sha224, new HexEncoder(new StringSink(s2)));
	HashFilter f3(sha256, new HexEncoder(new StringSink(s3)));
	HashFilter f4(sha512, new HexEncoder(new StringSink(s4)));
	HashFilter f5(md5, new HexEncoder(new StringSink(s5)));

	ChannelSwitch cs;
	cs.AddDefaultRoute(f1);
	cs.AddDefaultRoute(f2);
	cs.AddDefaultRoute(f3);
	cs.AddDefaultRoute(f4);
	cs.AddDefaultRoute(f5);

	StringSource ss(message, true /*pumpAll*/, new Redirector(cs));

	cout << "Message: " << message << endl;
		cout << "SHA-1: " << s1 << endl;
	cout << "SHA-224: " << s2 << endl;
	cout << "SHA-256: " << s3 << endl;
	cout << "SHA-512: " << s4 << endl;
	cout << "MD5: " << s5 << endl;

	getchar();

	return 0;
}