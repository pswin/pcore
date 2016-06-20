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
using namespace PCore::cryptography;


void print_hex( const QByteArray& _ar )
{
	const unsigned char * p = (const unsigned char*)_ar.constData();

	if ( _ar.isNull() == true )
	{
		printf("NULL");
	}
	else
	{
		for (int i = 0; i < _ar.size(); ++i )
			printf( "%02X ", *p++ );
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


	AES aes;
	aes.setPass( "123" );

	// encrypt
	auto out = aes.encrypt( "Hello world!" );
	printf( "Encrypted: " );
	print_hex( out );
	printf( "IV:        " );
	print_hex( aes.getIV() );

	// decrypt
	out = aes.decrypt( out );
	printf( "Decrypted: %s\n\n", out.data() );


	//=====================================
	// DES
	//=====================================

	printf("\n=====================================\n");
	printf("DES\n");
	printf("=====================================\n");


	DES des;
	des.setPass( "password" ); // key must be at least 8 char for DES

	out = des.encrypt( "Hallo welt!" );
	printf( "Encrypted: " );
	print_hex( out.data() );
	printf( "IV:        " );
	print_hex( des.getIV() );

	// decrypt
	out = des.decrypt( out );
	printf( "Decrypted: %s\n\n", out.data() );



	//=====================================
	// RSA
	//=====================================

	printf("\n=====================================\n");
	printf("RSA\n");
	printf("=====================================\n");

	Rsa rsa;

	out = rsa.encrypt( "Salam donya!" );
	printf( "Encrypted: " );
	print_hex( out.data() );
	printf( "\n" );

	out = rsa.decrypt( out );
	qDebug() << "Encrypted: " << out;

	return 0;
}

