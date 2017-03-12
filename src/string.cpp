#include <luna/typedef.hpp>
#include <luna/element/string.hpp>
#include <luna/rawStack.hpp>

namespace Luna
{

String::String( const RawStack &rawStack, const Index &index ) :
	Element( rawStack, index ),
	mValue( rawStack.toString( index ))
{
	
}

const String::Value &String::operator*() const noexcept
{
	return mValue;
}

Type String::getType() const noexcept
{
	return STRING;
}

const String::Value &String::get() const noexcept
{
	return mValue;
}

}
