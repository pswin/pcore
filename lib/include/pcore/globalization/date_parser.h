//#############################################################################
//#	title:	This class is for parsing a string date using given format
//#	c-date:	May-27-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//#############################################################################

#ifndef _PCORE_DATE_PARSER_H
#define _PCORE_DATE_PARSER_H


//==============================================================================
// Include
//==============================================================================

#include "../pcore_def.h"
#include <QString>
#include <QList>
#include <QLocale>


//==============================================================================
// DateParser
//==============================================================================

namespace PCore
{
	namespace globalization
	{
		class PCORE_API DateParser
		{
			//=====================================
			// public structs
			//=====================================
		public:

			//! date
			struct Date
			{
				int		year	= 0;
				int		month	= 0;
				int		day		= 0;
				int		week_day= 0;
				bool	valid	= false;
			};


			//=====================================
			// public methods
			//=====================================
		public:

			//! default constructor
			DateParser( ){}

			/*!
			 * \brief Constructor.
			 * \param _lang: Language.
			 * \param _country: Countery.
			 * \param _script: Script.
			 */
			DateParser( QLocale::Language _lang,
						QLocale::Country  _country	= QLocale::AnyCountry,
						QLocale::Script   _script	= QLocale::AnyScript
					);


			/*!
			 * \brief Sets format of the date.
			 */
			void setFormat( const QString& _format );


			/*!
			 * \brief Sets input and out put format for parsing.
			 * \param _lang: Language
			 * \param _country: Country
			 * \param _script: Script
			 */
			void setLocale( QLocale::Language _lang,
							QLocale::Country  _country	= QLocale::AnyCountry,
							QLocale::Script   _script	= QLocale::AnyScript
						);


			/*!
			 * \brief Returns the format of the date.
			 */
			QString format( void ) const { return m_sFormat; }
			QString getFormat( void ) const { return m_sFormat; }


			/*!
			 * \brief Parse the given date in string, and return it.
			 */
			DateParser::Date parseFromString( const QString& _date );


			/*!
			 * \brief Converts given date to a string.
			 * \param _year Year.
			 * \param _month Month.
			 * \param _day Day.
			 * \return
			 */
			QString toString( int _year, int _month, int _day );


			//=====================================
			// private classes
			//=====================================
		public:

			class Node
			{
				//-----------------
				// public enums
				//-----------------
			public:

				/*!
				 * \brief Type of the node
				 */
				enum Type
				{
					//! year
					Year				= 0,
					YearLong			= 1,
					//! month
					Month				= 2,
					MonthLeadingZero	= 3,
					MonthNameAbbreviated= 4,
					MonthNameFull		= 5,
					//! Day
					Day					= 6,
					DayLeadingZero		= 7,
					DayNameAbbreviated	= 8,
					DayNameFull			= 9,
					//! sperator
					Sperator
				}; // Type


				//-----------------
				// public methods
				//-----------------
			public:

				/*!
				 * \brief Default constructor
				 */
				Node( ) {}


				/*!
				 * \brief Constructor
				 * \param Type of the node.
				 * \param _value Value of the node
				 */
				Node( Node::Type _type,
					  const QString& _value = nullptr );


				/*!
				 * \brief Sets node's type.
				 * \param _type Type of the node
				 */
				void setType( Node::Type _type ){ m_eType = _type; }


				/*!
				 * \brief Sets value of the node.
				 * \param _str: Value in string.
				 */
				void setValue( const QString& _str ) { m_sValue = _str; }


				/*!
				 * \brief Returns type of the node
				 */
				Node::Type getType( void ) const { return m_eType; }
				Node::Type type( void ) const { return m_eType; }


				/*!
				 * \brief Retuns value of the node.
				 */
				QString value( void ) const { return m_sValue; }
				QString getValue( void ) const { return m_sValue; }


				//-----------------
				// private members
				//-----------------
			private:
				QString	m_sValue;	//! Value in String
				Type	m_eType;	//! Type of node
			};

			//=====================================
			// private members
			//=====================================
		private:

			//! format of date
			QString		m_sFormat;

			//! a list of node
			QList<Node>	m_Nodes;

			//! Local information
			QLocale::Language	m_eLanguage	= QLocale::AnyLanguage;
			QLocale::Country	m_eCountry	= QLocale::AnyCountry;
			QLocale::Script		m_eScript	= QLocale::AnyScript;
		};
	} // globalization
} // PCore


//==============================================================================
// typedefs
//==============================================================================

#if PCORE_CONFIG_USE_TYPEDEF == PCORE_ENABLE
	using PDateParser = PCore::globalization::DateParser;
#endif


#endif // _PCORE_DATE_PARSER_H
