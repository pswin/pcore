//##############################################################################
//#	title:	Cache
//#	c-date:	Jun-27-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################


#include <pcore/pcore.h>
#include <QDebug>


using namespace PCore::core::cachefx;


int main()
{

	// initializing PCore
	PCORE_INIT();


	//=====================================
	// LRU Cache
	//=====================================

	qDebug() << "-------------------------------------";
	qDebug() << "LRU Cache";
	qDebug() << "-------------------------------------\n";


	LRUCache<QString,QString> lru_cache( 10 );

	lru_cache.setMaxCost( 3 ); // Just 3 items in the cache
	lru_cache.insert( "Item1", "I am Item #1" );
	lru_cache.insert( "Item2", "I am Item #2" );
	lru_cache.insert( "Item3", "I am Item #3" );
	lru_cache.insert( "Item4", "I am Item #4" ); // Item1 will be removed.


	/* always check the given results from the cahce. there is not any guarantee
	 * for existence of the requested element (or item).
	 */
	auto it = lru_cache.get( "Item1");
	if ( it != nullptr )
	{
		qDebug() << "Item 1:" << lru_cache.get("Item1");
	}
	else
	{
		qDebug() << "Item 1 have removed from the cache.";
	}

	qDebug() << "Item 2:" << *lru_cache.get( "Item2" );


	/* printCacheOrder is a helper method for debuging. you can use it for
	 * observeing items (elements) in the cache.
	 */
	lru_cache.printCacheOrder();

	return 0;
}

