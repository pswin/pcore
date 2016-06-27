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
	//lru_cache.printCacheOrder();
	lru_cache.insert( "Item2", "I am Item #2" );
	//lru_cache.printCacheOrder();
	lru_cache.insert( "Item3", "I am Item #3" );

	//lru_cache.printCacheOrder();
	lru_cache.insert( "Item4", "I am Item #4" );

	lru_cache.printCacheOrder();
	auto it = lru_cache.get( "Item2");

	lru_cache.printCacheOrder();

	return 0;
}

