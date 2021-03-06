/* @file luna/element/table.hpp
 * @copyright Copyleft zukonake
 * @license Distributed under GNU General Public License Version 3
 */

#pragma once

#include <cstddef>
#include <string>
//
#include <luna/typedef.hpp>
#include <luna/rawStack.hpp>
#include <luna/element/element.hpp>

namespace Luna
{

/**
 * Represents a table value on the stack.
 */
class Table : public Element
{
public:
	Table( Table const &that );
	using Element::Element;
	
	~Table() = default;
	
	Table &operator=( Table const &that );
	
	/* TODO
	 * Changes the value of the element on the stack.
	 *
	 * @param value Desired value.
	 *
	Table &operator=( TableValue const &that );*/
	using Element::operator=;
	
	//operator TableValue() const noexcept; TODO
	
	
	/**
	 * Sets the given field.
	 *
	 * @param index Index of the field.
	 * @param value Desired value.
	 */
	template< typename T >
	void set( std::size_t const &index, T const &value );
	
	/**
	 * Sets the given field.
	 *
	 * @param key Key of the field.
	 * @param value Desired value.
	 */
	template< typename T >
	void set( std::string const &key, T const &value );
	
	
	
	/**
	 * Gets the given field.
	 *
	 * @param index Index of the field.
	 */
	template< typename T >
	T get( std::size_t const &index );
	
	/**
	 * Gets the given field.
	 *
	 * @param key Key of the field.
	 */
	template< typename T >
	T get( std::string const &key );
};

template< typename T >
void Table::set( std::size_t const &index, T const &value )
{
	value.getValue();
	Element::getValue();
	Element::mRawStack.setRawTableField( -1, index, -2 );
	Element::mRawStack.remove( -2 );
	Element::setValue();
}

template< typename T >
void Table::set( std::string const &key, T const &value )
{
	value.getValue();
	Element::getValue();
	Element::mRawStack.setRawTableField( -1, key, -2 );
	Element::mRawStack.remove( -2 );
	Element::setValue();
}

template< typename T >
T Table::get( std::size_t const &index )
{
	Element::getValue();
	Element::mRawStack.getRawTableField( -1, index );
	Element::mRawStack.remove( -2 );
	return T( Element::mRawStack );
}

template< typename T >
T Table::get( std::string const &key )
{
	//TODO check if T is element interface
	Element::getValue();
	Element::mRawStack.getRawTableField( -1, key );
	Element::mRawStack.remove( -2 );
	return T( Element::mRawStack );
}

}
