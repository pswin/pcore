//##############################################################################
//#	title:	Test for Crypto
//#	c-date:	May-25-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################


#include <pcore/pcore.h>
#include <QDebug>
#include <QByteArray>
#include <QDate>

using namespace PCore::core;


void print_hex( const void* pv, size_t len )
{
	const unsigned char * p = (const unsigned char*)pv;
	if (NULL == pv)
		printf("NULL");
	else
	{
		size_t i = 0;
		for (; i<len;++i)
			printf("%02X ", *p++);
	}
	printf("\n");
}


int main()
{

	// initializing PCore
	PCORE_INIT();


	//=====================================
	// AES
	//=====================================

	printf("\n=====================================\n");
	printf("AES\n");
	printf("=====================================\n");

	QByteArray ivec;
	QByteArray key;
	key.fill( '1', 32 ); // Key at least must be 32 char for AES-256
	QByteArray data = "Hello world!";

	// encrypt
	auto out = Crypto::aesEncrypt( data, key, &ivec );
	printf( "IV: " );
	print_hex( ivec.data(), ivec.size() );
	printf( "Encrypted: " );
	print_hex( out.data(), out.size() );

	// decrypt
	out = Crypto::aesDecrypt( out, key, &ivec );
	printf( "Decrypted: %s\n\n", out.data() );


	//=====================================
	// AES with default IVEC
	//=====================================

	data = "Salam donya!";

	// encrypt
	out = Crypto::aesEncrypt( data, key );
	printf( "Encrypted: " );
	print_hex( out.data(), out.size() );

	// decrypt
	out = Crypto::aesDecrypt( out, key );
	printf( "Decrypted: %s\n\n", out.data() );


	//=====================================
	// DES
	//=====================================

	printf("\n=====================================\n");
	printf("DES\n");
	printf("=====================================\n");


	key = "password"; // key must be at least 8 char for DES
	data = "Hallo welt!";

	out = Crypto::desEncrypt( data, key );
	printf( "Encrypted: " );
	print_hex( out.data(), out.size() );

	// decrypt
	out = Crypto::desDecrypt( out, key );
	printf( "Decrypted: %s\n\n", out.data() );

	return 0;
}

