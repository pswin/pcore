

#include "headers/cryptography/cryptography_engine.h"
#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/evp.h>

namespace PCore
{
	namespace cryptography
	{

		// init
		bool CryptographyEngine::init( void )
		{
			ERR_load_CRYPTO_strings();
			OpenSSL_add_all_algorithms();
			OPENSSL_config( NULL );

			return true;
		}

		// shutdown
		bool CryptographyEngine::shutdown()
		{
			EVP_cleanup();
			ERR_free_strings();

			return true;
		}

	} // cryptography
} // PCore

