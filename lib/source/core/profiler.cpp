//##############################################################################
//#	c-date:	Apr-08-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################


#include "include/pcore/core/profiler.h"
#include "include/pcore/core/logger.h"
#include "include/pcore/globals.h"
#include <QTextStream>
#include <QDateTime>
#include <QFile>



namespace PCore
{
	namespace core
	{
		//======================================================================
		// Profiler
		//======================================================================

		//! constructor
		Profiler::Profiler( const QString& _name )
		{
			PCORE_LOG_TRACE_FUNC_START();
			m_sName = _name;
		}

		//! destructor
		Profiler::~Profiler()
		{
			PCORE_LOG_TRACE_FUNC_START();
			pProfileManager->stopProfile( m_sName );
		}

		//! start
		void Profiler::start()
		{
			PCORE_LOG_TRACE_FUNC_START();
			pProfileManager->startProfile( m_sName );
		}

		//! stop
		quint64 Profiler::stop( void )
		{
			PCORE_LOG_TRACE_FUNC_START();
			return pProfileManager->stopProfile( m_sName );
		}


		//======================================================================
		// ProfileManager
		//======================================================================

		//! constructor
		ProfileManager::ProfileManager( QObject* _parent )
			: QObject ( _parent )
		{

		}

		//! startProfile
		void ProfileManager::startProfile( const QString& _name )
		{
			PCORE_LOG_TRACE_FUNC_START();

			auto it = m_Map.find( _name );


			if ( it != m_Map.end() )
			{
				it.value()->lock.lock();
				it.value()->call_num++;
				it.value()->pending_count++;

				if ( it.value()->is_started != true )
				{
					// optimize: it could be replaced by more accurate function
					it.value()->last_time = QDateTime::currentMSecsSinceEpoch();
				}

				it.value()->is_started = true;
				it.value()->lock.unlock();
			}
			else
			{
				m_MapLock.lock();
				Profile* p = new Profile();
				p->name = _name;
				p->call_num = 1;
				p->pending_count =1;
				p->last_time =  QDateTime::currentMSecsSinceEpoch();
				m_Map[_name] = p;
				m_MapLock.unlock();
			}
		}

		//! stopProfile
		quint64 ProfileManager::stopProfile( const QString& _name )
		{
			PCORE_LOG_TRACE_FUNC_START();

			auto it = m_Map.find( _name );

			if ( it == m_Map.end() ) return 0;

			Profile* p = it.value();

			p->lock.lock();
			p->pending_count--;

			quint64 elapsed_time = \
					QDateTime::currentMSecsSinceEpoch() - p->last_time;

			if ( it.value()->pending_count == 0 )
			{

				p->total_time += elapsed_time;
				p->is_started = false;

				if ( elapsed_time > p->max_time ) p->max_time = elapsed_time;
				if ( elapsed_time < p->min_time ) p->min_time = elapsed_time;
			}

			it.value()->lock.unlock();

			return elapsed_time;
		}


		//! getProfiles
		ProfileManager::ProfileMap ProfileManager::getProfiles() const
		{
			PCORE_LOG_TRACE_FUNC_START();
			return m_Map;
		}


		//! printToFile
		bool ProfileManager::printToFile( const QString& _filename )
		{
			PCORE_LOG_TRACE_FUNC_START();
			try
			{
				m_MapLock.lock();
				QFile f( _filename );

				if ( f.open(QFile::WriteOnly ) == false )
				{
					PCORE_LOG_ERROR( "Saving profiles to '"+_filename+"' failed." );
					m_MapLock.unlock();
					return false;
				}

				QTextStream st(&f);

				st << "name, call num, total time, max time, min time" <<
					  PCORE_NEW_LINE;

				for ( auto it : m_Map )
				{
					st << it->name << ", " << it->call_num << ", " << \
						  it->total_time << ", " << it->max_time << ", " << \
						  it->min_time << PCORE_NEW_LINE;
				}

				st.flush();
				f.close();

				m_MapLock.unlock();

			}
			catch( ... )
			{
				PCORE_LOG_ERROR( "Unexpected Error in saving profiles in " + _filename );
				m_MapLock.unlock();
				return false;
			}

			return true;
		}


	} // core
} // PCore

