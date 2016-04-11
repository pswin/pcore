//##############################################################################
//#	title:	Profiling Tool
//#	c-date:	Apr-08-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#ifndef _PCORE_PROFILER_H
#define _PCORE_PROFILER_H

#include "../pcore_def.h"
#include <QObject>
#include <QString>
#include <QMap>


//=====================================
// Macros
//=====================================

#define PCORE_PROFILE_FUNCTION( ) \
	PCore::core::Profiler ___profiler( PCORE_FUNC_NAME );\
        ___profiler.start();


//=====================================
// Classes
//=====================================

namespace PCore
{
	namespace core
	{
		//=====================================
		// Profiler
		//=====================================
		class PCORE_API Profiler
		{
		public:

			/*!
			 * \brief Default constructor
			 * \param _name: Name of profiler
			 */
			Profiler ( const QString& _name );


			//! destructor
			~Profiler( );


			/*!
			 * \brief Returns name of profiler.
			 * \return Returns name of profiler.
			 */
			QString getName( void ) const { return m_sName; }


			/*!
			 * \brief Start profiling.
			*/
			void start( void );


			/*!
			 * \brief Stop profiling.
			*/
			quint64 stop( void );

		private:
			//! name of profiler
			QString	m_sName;
		}; // Profiler



		//======================================================================
		// ProfileManager
		//======================================================================
		class PCORE_API ProfileManager : QObject
		{
			//=====================================
			// metadata
			//=====================================
			Q_OBJECT
			Q_CLASSINFO( "author", "Pouya Shahinfar" )
			Q_CLASSINFO( "version", "1.0.0" )

		public:
			//=====================================
			// Profile
			//=====================================
			struct Profile
			{
				QString	name;				//! name of profile
				quint64	call_num = 0;		//! call number
				quint64	total_time = 0;		//! total time
				quint64	max_time = 0;		//! maximum time
                                quint64	min_time = -1;		//! minimum time
				bool	is_started = false;	//! is started?
				quint64	last_time = 0;		//!	last time
				quint32	pending_count = 0;	//! pending call cout for reverse functions or multithread use
				QMutex	lock;				//! lock for protecting structure in multithread use
			};

			//=====================================
			// typedefs
			//=====================================
		public:
			using ProfileMap = QMap<QString,Profile*>;


			//=====================================
			// public methods
			//=====================================
		public:

			//! default constructor
			explicit ProfileManager( QObject* _parent = nullptr );

			/*!
			 * \brief Start a profile by given name.
			 * \param _name: Name of the profile.
			 */
			void startProfile( const QString& _name );

			/*!
			 * \brief Stops a profile by given name.
			 * \param _name: Name of profile.
			 * \return Number of miliseconds that elapsed from start.
			 */
			quint64 stopProfile( const QString& _name );

			/*!
			 * \brief Returns all profiles.
			 * \return All profiles.
			 */
			ProfileMap getProfiles( void ) const;

			/*!
			 * \brief Print all profiles to the specified file.
			 * \param _filename: destionation file.
			 */
			bool printToFile( const QString& _filename );


			//=====================================
			// private members
			//=====================================
		private:
			//! list of profiles
			ProfileMap	m_Map;

			//! lock for map
			QMutex		m_MapLock;
		}; // ProfileManager
	} // core
} // PCore


#endif // _PCORE_PROFILER_H

