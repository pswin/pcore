//##############################################################################
//#	title:	An interface for dealing with Udev
//#	c-date:	May-20-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################


#ifndef _PCORE_LINUX_UDEV_H
#define _PCORE_LINUX_UDEV_H

#include "include/pcore/pcore_def.h"

#if PCORE_OS == PCORE_OS_LINUX

#include <QString>
#include <QSharedPointer>
#include <libudev.h>
#include <QDebug>

namespace PCore
{
	namespace core
	{
		class Udev
		{
			//=====================================
			// public classes
			//=====================================
		public:

			class UdevDevice
			{
				//-----------------
				// public methods
				//-----------------
			public:

				/*!
				 * \brief Constructor
				 * \param _udev: Pointer to the udev.
				 * \param _device: Pointer to the device.
				 */
				UdevDevice( udev *_udev, udev_device* _device );


				/*!
				 * \brief Copy constructor
				 */
				UdevDevice( const UdevDevice& _dev );

				/*!
				 * \brief Move constructor
				 */
				UdevDevice( UdevDevice&& _dev );

				/*!
				 * \brief Returns a propertie's value by specified name.
				 * \param _name: name of the property.
				 * \return Value's of property.
				 */
				QString getProperty( const char* _name ) const;


				/*!
				 * \brief Returns a system attributes's value by specified name.
				 * \param _name: name of the system attribute.
				 * \return Value's of system attribute.
				 */
				QString getSystemAttribute( const char* _name ) const;


				/*!
				 * \brief Returns name of the device.
				 * \return name of device.
				 */
				QString getNode( void ) const;


				/*!
				 * \brief Returns path of the device.
				 * \return name of the path.
				 */
				QString getPath( void ) const;


				/*!
				 * \brief Returns type of the device.
				 * \return type of the device
				 */
				QString getType( void ) const;


				/*!
				 * \brief Returns system name of device.
				 * \return system name of device.
				 */
				QString getSystemName( void ) const;


				/*!
				 * \brief Returns parent node.
				 * \return Parent node.
				 */
				UdevDevice getParent( void ) const;


				/*!
				 * \brief Return a parent by specified subsystem and device type.
				 * \param _sub_system: name of subsystem.
				 * \param _dev_type: device type;
				 * \return
				 */
				UdevDevice getParentBySubsystemAndDevType(
											const char* _sub_system,
											const char* _dev_type );


				/*!
				 * \brief Retrieves all subsystems, specified by subsystem.
				 * \param _name: name of subsystem.
				 * \return All subsystems specified by name.
				 */
				QList<UdevDevice> getSubSystems( const char* _name ) const;


				/*!
				 * \brief return first child subsystem, specified by name.
				 * \param _name: name of subsystem.
				 * \return first chid subsystem
				 */
				UdevDevice getChildSubsystem( const char* _name ) const;


				/*!
				 * \brief Returns true if current device is null.
				 * \return Returns true if current device is null.
				 */
				bool isNull( void ) const { return m_pDevice == nullptr; }

				/*!
				 * \brief release this device
				 */
				void release( void );


				//-----------------
				// private members
				//-----------------
			private:
				//! pointer to the device
				udev_device* m_pDevice = nullptr;
				//! pointer to the udev
				struct udev* m_pUdev = nullptr;
				//! refrence count
				quint32	m_pRefrences = 1;

			}; // UdevDevice


			//=====================================
			// public methods
			//=====================================
		public:

			//! constructor
			Udev( );

			//! destructor
			~Udev( );


			/*!
			 * \brief Add a subsystem for matching in scans.
			 * \param _sub_system
			 */
			void addMatchSubsystem( const char* _sub_system );


			/*!
			 * \brief Add a property for matching scans.
			 * \param _property_name: name of the property.
			 * \param _property_value:	value of the property.
			 */
			void addMatchProperty (
									const char* _property_name,
									const char* _property_value
								);

			/*!
			 * \brief Add a class filter
			 * \param _name: name of class
			 */
			void addMatchClass( const char* _name );


			/*!
			 * \brief Scan devices by specified filters.
			 * \return a list of devices which are mached with specified filters.
			 */
			QList<UdevDevice> scan( void );


			//=====================================
			// private members
			//=====================================
		private:
			//! Pointer to the udev.
			struct udev* m_pUdev = nullptr;
			//! Pointer to the udev_enumerate.
			struct udev_enumerate* m_pEnumerate = nullptr;

		}; // Udev
	} // Core
} // PCore
#endif // PCORE_OS_LINUX
#endif // _PCORE_LINUX_UDEV_H

