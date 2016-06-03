//##############################################################################
//#	title:	An interface for dealing with Udev
//#	c-date:	May-20-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#include "headers/core/linux/udev.h"

#if PCORE_OS == PCORE_OS_LINUX

namespace PCore
{
	namespace core
	{
		//======================================================================
		// Device
		//======================================================================

		//! constructor
		Udev::UdevDevice::UdevDevice( udev *_udev , udev_device *_device )
		{
			m_pUdev = _udev;
			m_pDevice = _device;

		}

		//! Copy constructor
		Udev::UdevDevice::UdevDevice(const Udev::UdevDevice &_dev)
		{
			m_pDevice = _dev.m_pDevice;
			m_pUdev = _dev.m_pUdev;
		}

		//! move constructor
		Udev::UdevDevice::UdevDevice( Udev::UdevDevice &&_dev )
		{
			m_pDevice = _dev.m_pDevice;
			_dev.m_pDevice = nullptr;
			m_pUdev = _dev.m_pUdev;
		}

		//! getProperty
		QString Udev::UdevDevice::getProperty( const char *_name ) const
		{
			if ( m_pDevice == nullptr ) return nullptr;
			return QString(udev_device_get_property_value( m_pDevice, _name )).trimmed();

		}

		//! getSystemAttribute
		QString Udev::UdevDevice::getSystemAttribute( const char *_name ) const
		{
			if ( m_pDevice == nullptr ) return nullptr;
			return QString(udev_device_get_sysattr_value( m_pDevice, _name )).trimmed();
		}

		//! getNode
		QString Udev::UdevDevice::getNode() const
		{
			if ( m_pDevice == nullptr ) return nullptr;
			return udev_device_get_devnode( m_pDevice );
		}

		//! getPath
		QString Udev::UdevDevice::getPath() const
		{
			if ( m_pDevice == nullptr ) return nullptr;
			return udev_device_get_devpath( m_pDevice );
		}


		//! getType
		QString Udev::UdevDevice::getType() const
		{
			if ( m_pDevice == nullptr ) return nullptr;
			return udev_device_get_devtype( m_pDevice );
		}


		//! getSystemName
		QString Udev::UdevDevice::getSystemName() const
		{
			if ( m_pDevice == nullptr ) return nullptr;
			return udev_device_get_sysname( m_pDevice );
		}


		//! getParent
		Udev::UdevDevice Udev::UdevDevice::getParent() const
		{
			if ( m_pDevice == nullptr ) return UdevDevice( m_pUdev, nullptr );
			return UdevDevice( m_pUdev, udev_device_get_parent( m_pDevice ) );
		}


		//! getParentBySubsystemAndDevType
		Udev::UdevDevice Udev::UdevDevice::getParentBySubsystemAndDevType(
						const char *_sub_system,
						const char *_dev_type)
		{
			if ( m_pDevice == nullptr ) return UdevDevice( m_pUdev, nullptr );
			return UdevDevice ( m_pUdev,
					udev_device_get_parent_with_subsystem_devtype
								( m_pDevice, _sub_system, _dev_type ) );
		}


		//! getSubsystems
		QList<Udev::UdevDevice> Udev::UdevDevice::getSubSystems(
													const char *_name ) const
		{
			QList<Udev::UdevDevice> children;

			udev_enumerate *enumerate = udev_enumerate_new( m_pUdev );

			udev_enumerate_add_match_parent( enumerate, m_pDevice );
			udev_enumerate_add_match_subsystem( enumerate, _name );
			udev_enumerate_scan_devices( enumerate );

			udev_list_entry *devices = udev_enumerate_get_list_entry( enumerate );
			udev_list_entry *entry;

			udev_list_entry_foreach( entry, devices )
			{
				const char *path = udev_list_entry_get_name(entry);
				children.push_back( UdevDevice( m_pUdev,
							udev_device_new_from_syspath( m_pUdev, path ) ) );
			}

			 udev_enumerate_unref(enumerate);
			 return children;
		}

		//! getChildSubsystem
		Udev::UdevDevice Udev::UdevDevice::getChildSubsystem
													(const char *_name) const
		{
			udev_enumerate *enumerate = udev_enumerate_new( m_pUdev );

			if ( enumerate == nullptr ) return UdevDevice( m_pUdev, nullptr);

			udev_enumerate_add_match_parent( enumerate, m_pDevice );
			udev_enumerate_add_match_subsystem( enumerate, _name );
			udev_enumerate_scan_devices( enumerate );

			udev_list_entry *devices = udev_enumerate_get_list_entry( enumerate );
			udev_list_entry *entry;

			udev_device* dev = nullptr;
			udev_list_entry_foreach( entry, devices )
			{
				const char *path = udev_list_entry_get_name(entry);
				dev = udev_device_new_from_syspath( m_pUdev, path );
				break;
			}

			 udev_enumerate_unref(enumerate);
			 return UdevDevice( m_pUdev, dev);
		}

		//! release
		void Udev::UdevDevice::release()
		{
			if ( m_pDevice == nullptr ) return;
			udev_device_unref( m_pDevice );
			m_pDevice = nullptr;
		}


		//======================================================================
		// Device
		//======================================================================

		//! constructor
		Udev::Udev()
		{
			m_pUdev =  udev_new();

			if ( m_pUdev != nullptr )
			{
				m_pEnumerate = udev_enumerate_new( m_pUdev );
			}
		}


		//! destructor
		Udev::~Udev()
		{
			if ( m_pUdev != nullptr )
			{
				udev_unref( m_pUdev );
			}

			if ( m_pEnumerate != nullptr)
			{
				udev_enumerate_unref( m_pEnumerate );
			}
		}

		//! addMatchSubsystem
		void Udev::addMatchSubsystem( const char *_sub_system )
		{
			if ( m_pEnumerate == nullptr ) return;

			udev_enumerate_add_match_subsystem( m_pEnumerate, _sub_system );
		}

		//! addMatchProperty
		void Udev::addMatchProperty(
									const char *_property_name,
									const char *_property_value
									)
		{

			if ( m_pEnumerate == nullptr ) return;

			udev_enumerate_add_match_property( m_pEnumerate,
											   _property_name,
											   _property_value );
		}

		//! addMatchClass
		void Udev::addMatchClass( const char *_name )
		{
			if ( m_pEnumerate == nullptr ) return;

			udev_enumerate_add_match_subsystem( m_pEnumerate, _name );
		}


		//! scan
		QList<Udev::UdevDevice> Udev::scan()
		{
			QList<Udev::UdevDevice> list;
			if ( m_pEnumerate == nullptr ) return list;

			udev_enumerate_scan_devices( m_pEnumerate );

			udev_list_entry *devices =
								udev_enumerate_get_list_entry( m_pEnumerate );

			udev_list_entry *entry;
			udev_list_entry_foreach(entry, devices)
			{
				const char* path = udev_list_entry_get_name( entry );
				udev_device* dev = udev_device_new_from_syspath( m_pUdev, path);
				list.push_back( Udev::UdevDevice( m_pUdev, dev ) );
			}

			return list;
		}




	} // core
} // PCore

#endif // PCORE_OS_LINUX

