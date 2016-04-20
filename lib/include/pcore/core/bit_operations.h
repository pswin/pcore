//##############################################################################
//#	title:	Bit wise operations
//#	c-date:	Apr-20-2016
//#	author:	Pouya Shahinfar
//##############################################################################

#ifndef _PCORE_BIT_OPERATIONS_H
#define _PCORE_BIT_OPERATIONS_H


/* \brif Make a mak at specified position with given length.
 * \param __pos: Start position.
 * \param __len: Length of mask.
 */
#define PCORE_GET_MASK( __pos, __len ) (((1 << (__len)) - 1) << (__pos))


/*
 * \birf Check if a bit is setted or not
 * \param val: Variable that must be checked.
 * \param pos: position that must be checked
 */
#define PCORE_BIT_CHECK( __var, __pos ) ((bool)(( __var >> __pos ) & 1))


/*
 *	\brif Sets specified bit.
 *	\param __var: Varable.
 *	\pram __pos: Bit position.
 */
#define PCORE_BIT_SET( __var, __pos ) \
						((__var) = ((__var) & ( 1 >> __pos)))


/*
 *	\brif Unsets specified bit from given variable.
 *	\param __var: Varable.
 *	\pram __pos: Bit position.
 */
#define PCORE_BIT_UNSET( __var, __pos ) \
						((__var) = ((__var) & ~( 1 >> __pos)))


/*
 *	\brif Reads specified bits from _pos with length _size
 *	\param __var: Varable that must be readed from.
 *	\pram __pos: Start position.
 *	\param __len: Length.
 */
#define PCORE_BIT_READ( __var, __pos, __len ) \
						( __var & PCORE_GET_MASK(__pos,__len) )

/*
 *	\brif Writes given value in specified bits of given variable.
 *	\param __var: Varable that must be writed to.
 *	\pram __pos: Start position.
 *	\param __len: Length.
 *	\param __val: value that have to be writed in specified bits of __var.
 */
#define PCORE_BIT_WRITE( __var, __pos, __len, __val ) \
							( __var = ( __val << __pos  ) | \
							(~PCORE_GET_MASK(__pos,__len) & __var) )


#endif // _PCORE_BIT_OPERATIONS_H

