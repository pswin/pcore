//##############################################################################
//#	title:	LRU ( Last Recently Used) based cache.
//#	c-date:	Jun-21-2016
//#	author: Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################


#ifndef _PCORE_LRU_CACHE_H
#define _PCORE_LRU_CACHE_H

//==============================================================================
// includes
//==============================================================================

#include "../../pcore_def.h"
#include <QReadWriteLock>
#include <QReadLocker>
#include <QWriteLocker>
#include <QHash>
#include <QList>
#include <QSharedPointer>
#include <QObject>
#include <QDebug>

//==============================================================================
// code
//==============================================================================

namespace PCore
{
	namespace core
	{
		namespace cachefx
		{
			template< typename KEY, typename T >
			class LRUCache
			{
				//=====================================
				// Typedefs
				//=====================================
			public:

				#if PCORE_ARCH_WORD_SIZE == 64
					using cost_t = quint64;
				#elif PCORE_ARCH_WORD_SIZE == 32
					using cost_t = quint32;
				#else
					#warning "Undefined word size for the cache system; 64-bit has used."
					using cost_t = quint64;
				#endif

				//=====================================
				// Structs
				//=====================================
			private:

				/*!
				 * \brief Cache node.
				 */
				struct Node
				{
					Node*				previous	= nullptr;	//! Previous node.
					Node*				next		= nullptr;	//! Next node.
					cost_t				cost		= 0;		//! Cost of the node.
					KEY					key;					//! Key
					QSharedPointer<T>	value		;			//! Value of the node.
				};


				//=====================================
				// public methods
				//=====================================
			public:


				/*!
				 * \brief Constructor.
				 * \param _max_cost: Maximim cost (size) of the cahce.
				 */
				explicit LRUCache(cost_t _max_cost = PCORE_CONFIG_DEFAULT_CACHE_SIZE )
				{
					m_uMaxCost = _max_cost;
				}


				/*!
				 * \brief Destructor.
				 */
				~LRUCache( )
				{
					clear();
				}


				/*!
				 * \brief Returns the object associated with key key, or nullptr
				 *			if the key does not exist in the cache.
				 */
				QSharedPointer<T> get( const KEY& _key )
				{
					QReadLocker lock( &m_Lock );
					if ( m_Items.find( _key ) != m_Items.end() )
					{
						Node* n = m_Items[ _key ];
						if ( m_pFirst != nullptr ) m_pFirst->previous = n;
						if ( m_pLast == n )
						{
							m_pLast = n->previous;
							m_pLast->next = nullptr;
						}

						n->next = m_pFirst;
						m_pFirst = n;
						n->previous = nullptr;

						return n->value;
					}

					return QSharedPointer<T>( nullptr );
				}


				/*!
				 * \brief Inserts an item to the cache.
				 * \param _key: Key of the item.
				 * \param _val: Item's itself.
				 * \param _cost: Cost of the item.
				 * \return Returns true if inserting new item was successful;
				 *			otherwise returns false.
				 */
				bool insert( const KEY& _key, const T& _val, cost_t _cost = 1 )
				{
					QWriteLocker lock( &m_Lock );

					Node* n = nullptr;
					bool update = false;

					// cost (size) of the item is more than maximum cost
					if ( _cost > m_uMaxCost )
					{
						return false;
					}

					if ( m_Items.find( _key) != m_Items.end() )
					{
						n = m_Items[_key];
						n->previous->next = n->next;
						n->next->previous = n->previous;
						m_uUsedCost -= n->cost;
						update = true;
					}

					// create free space for the new item
					if ( (_cost + m_uUsedCost) > m_uMaxCost )
					{
						trim( _cost );
					}

					if ( update == false )
					{
						n = new Node();
					}

					n->cost = _cost;
					n->next = m_pFirst;
					n->key = _key;
					n->previous = nullptr;
					n->value = QSharedPointer<T>( new T( _val ) );

					if ( m_pFirst != nullptr )
					{
						m_pFirst->previous = n;
					}
					else
					{
						m_pLast = n;
					}

					m_pFirst = n;
					m_uUsedCost += _cost;
					m_Items[ _key ] = n;


					return true;
				} // insert


				/*!
				 * \brief Rermoves specified item by given key from the cache.
				 * \param _key: Key of the item.
				 * \return Returns true if removing key was successful
				 */
				bool remove( const KEY& _key )
				{
					QWriteLocker lock( &m_Lock );

					auto it = m_Items.find( _key );
					if ( _key == m_Items.end() ) return false;

					Node* n = it.value();
					if ( n->next != nullptr ) n->next->previous = n->previous;
					if ( n->previous != nullptr ) n->previous->next = n->next;
					m_uUsedCost -= n->cost;

					m_Items.remove( _key );
					delete n;

					return true;
				} // remove


				/*!
				 * \brief Removes all items from the cache.
				 */
				void clear( void )
				{
					QWriteLocker lock( &m_Lock );

					m_Items.clear();

					Node* n = m_pFirst;
					Node* m;
					while ( n != nullptr )
					{
						m = n->next;
						delete n;
						n = m;
					}
				} // clear


				/*!
				 * \brief Returns true if the cache is empty; otherwise, returns false.
				 */
				bool isEmpty( void )
				{
					QReadLocker lock( &m_Lock );
					return m_Items.size() == 0;
				}


				/*!
				 * \brief Returns the number of the cached items.
				 */
				int size( void )
				{
					QReadLocker lock( &m_Lock );
					return m_Items.size();
				}


				/*!
				 * \brief Return maximum cost (size) of the cache.
				 */
				cost_t maxCost( void )
				{
					QReadLocker lock( &m_Lock );
					return m_uMaxCost;
				}


				/*!
				 * \brief Sets maximum cost (Size) of the cache
				 * \param _max_cost: new maximum cost;
				 */
				void setMaxCost( cost_t _max_cost )
				{
					QWriteLocker lock( &m_Lock );
					m_uMaxCost = _max_cost;
				}


				/*!
				 * \brief Returns used size of the cache.
				 */
				cost_t usedCost( void )
				{
					QReadLocker lock( &m_Lock );
					return m_uUsedCost;
				}


				/*!
				 * \brief This function is for testing only
				 */
				void printCacheOrder( )
				{
					Node* n = m_pFirst;
					int i = 0;
					while ( n != nullptr )
					{
						qDebug() << i++ << n->key << *n->value;
						n = n->next;
					}
				}

				//=====================================
				// private members
				//=====================================
			private:

				//! Fist node (The most recently used node).
				Node* m_pFirst = nullptr;

				//! Last node (The less recently used node).
				Node* m_pLast = nullptr;

				//! Maximum cost (size) of the cache.
				cost_t m_uMaxCost = PCORE_CONFIG_DEFAULT_CACHE_SIZE;

				//! Total used size of the cache.
				cost_t m_uUsedCost = 0;

				//! items
				QHash<KEY,Node*> m_Items;

				//! Reader-Writer lock
				QReadWriteLock m_Lock;


				//=====================================
				// private methods
				//=====================================
			private:

				void trim ( cost_t _cost )
				{
					cost_t cost = 0;
					while ( m_pLast != nullptr )
					{
						if ( cost >= _cost ) return;

						m_Items.remove( m_pLast->key );
						cost += m_pLast->cost;
						m_uUsedCost -= m_pLast->cost;
						Node* n = m_pLast->previous;
						delete m_pLast;
						m_pLast = n;
						if ( m_pLast != nullptr ) m_pLast->next = nullptr;
					}
				}

			}; // LRUCache
		} // cachefx
	} // core
} // PCore


//==============================================================================
//  Typedefs
//==============================================================================

#if PCORE_CONFIG_USE_TYPEDEF == PCORE_ENABLE
	template< class KEY, class T>
	using PLRUCache = PCore::core::cachefx::LRUCache<KEY,T>;
#endif



#endif // _PCORE_LRU_CACHE_H
