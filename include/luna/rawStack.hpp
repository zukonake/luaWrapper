/**
 * @file luna/rawStack.hpp
 * Copyleft zukonake
 * Distributed under GNU General Public License Version 3
 */

#pragma once

#include <cstddef>
#include <string>
//
#include <luna/typedef.hpp>

namespace Luna
{

/**
 * Represents the Lua C API stack.
 */

class RawStack
{
public:

	/**
	 * Construct a new RawStack, from an existing LuaState.
	 */
	RawStack( LuaState const &luaState ) noexcept;

	virtual ~RawStack() = default;

	/**
	 * Loads file.
	 *
	 * The file is loaded and pushed as a function to the stack.
	 *
	 * @param path Path to the file.
	 */
	void loadFile( std::string const &path );

	/**
	 * Loads a script as a std::string.
	 *
	 * The script is loaded and pushed as a function to the stack.
	 *
	 * @param value The Lua script to load.
	 */
	void loadString( std::string const &value );


	/**
	 * Loads a file and calls it.
	 *
	 * The file is loaded and pushed as a function to the stack.
	 * The Lua function may return return multiple values,
	 * as defined by the returnNumber, if LuaMultiReturn is used,
	 * all of the return values will be pushed to the stack.
	 * The Lua function may pop multiple values,
	 * as defined by the arguments.
	 *
	 * @param path Path to the file.
	 * @param returnNumber Number of returned values to push to the stack.
	 * @param arguments Number of values to pop from the stack and pass to the function.
	 * @see LuaMultiReturn
	 * @return Returns the number of returnedValues.
	 */
	Size doFile( std::string const &path, Size returnNumber = LuaMultiReturn, Size const &arguments = 0 );

	/**
	 * Loads a script as a std::string and calls it.
	 *
	 * The string is loaded and pushed as a function to the stack.
	 * The Lua function may return return multiple values,
	 * as defined by the returnNumber, if LuaMultiReturn is used,
	 * all of the return values will be pushed to the stack.
	 * The Lua function may pop multiple values,
	 * as defined by the arguments.
	 *
	 * @param value The Lua script to load.
	 * @param returnNumber Number of returned values to push to the stack.
	 * @param arguments Number of values to pop from the stack and pass to the function.
	 * @see LuaMultiReturn
	 * @return Returns the number of returnedValues.
	 */
	Size doString( std::string const &value, Size returnNumber = LuaMultiReturn, Size const &arguments = 0 );

	/**
	 * Calls a function on the stack.
	 *
	 * The Lua function may return return multiple values,
	 * as defined by the returnNumber, if LuaMultiReturn is used,
	 * all of the return values will be pushed to the stack.
	 * The Lua function may pop multiple values,
	 * as defined by the arguments.
	 *
	 * @param index Index to the function.
	 * @param returnNumber Number of returned values to push to the stack.
	 * @param arguments Number of values to pop from the stack and pass to the function.
	 * @see LuaMultiReturn
	 * @return Returns the number of returnedValues.
	 */
	Size call( Index const &index = -1, Size returnNumber = LuaMultiReturn, Size const &arguments = 0 );

	/**
	 * Calls a meta method of a value.
	 *
	 * The target value is passed as meta method's only argument.
	 * The meta method may return value onto the stakc.
	 *
	 * @param index Index of target value.
	 * @param name Name of the meta method to call.
	 */
	void callMetaMethod( Index const &index, std::string const &name );

	void pushNil();
	void pushBoolean( BooleanValue const &value );
	void pushNumber( NumberValue const &value );
	void pushString( StringValue const &value );
	void pushTable( Size const &arrayLength = 0, Size const &mapLength = 0 );
	void pushLightUserData( UserDataValue const &userdata );
	void pushUserData( std::size_t const &size );
	void pushFunction( FunctionValue function );
	void pushClosure( FunctionValue closure, Size const &capture = 0 );
	void pushThread( ThreadValue const &thread );
	void pushMetaTable( std::string const &name );

	void loadGlobal( std::string const &name );
	void loadGlobalTable();

	ThreadValue newThread();
	LuaReference newReference( const Index &table, const Index &value );

	void dereference( const Index &table, const LuaReference &reference );

	void registerLibrary( Library const &library );
	void registerFunction( FunctionValue function, std::string const &name );
	void registerValue( Index const &index, std::string const &name );

	NumberValue toNumber( Index const &index = -1 ) const;
	BooleanValue toBoolean( Index const &index = -1 ) const;
	StringValue toString( Index const &index = -1 ) const;
	TableValue toTable( Index const &index = -1 ) const;
	UserDataValue toUserData( Index const &index = -1 ) const;
	FunctionValue toFunction( Index const &index = -1 ) const;
	ThreadValue toThread( Index const &index = -1 ) const;

	Size getLength( Index const &index = -1 ) const;
	Type getType( Index const &index = -1 ) const; 

	Type getTableField( Index const &table = -1 ) const;
	Type getTableField( Index const &table, std::size_t const &index ) const;
	Type getTableField( Index const &table, std::string const &key ) const;

	Type getRawTableField( Index const &table = -1 ) const;
	Type getRawTableField( Index const &table, std::size_t const &index ) const;
	Type getRawTableField( Index const &table, std::string const &key ) const;

	Type getMetaField( Index const &index, std::string const &name ) const;
	Type getMetaTable( std::string const &name ) const;

	void setTableField( Index const &table );
	void setTableField( Index const &table, std::size_t const &index );
	void setTableField( Index const &table, std::string const &key );

	void setRawTableField( Index const &table );
	void setRawTableField( Index const &table, std::size_t const &index, Index const &value = -1 );
	void setRawTableField( Index const &table, std::string const &key, Index const &value = -1 );

	void setMetaTable( Index const &target, std::string const &metaTable );
	void setMetaTable( Index const &target, Index const &metaTable );

	void setUserData( Index const &value, Index const &userData );

	void copy( Index const &from  = -1 );
	void insert( Index const &index );

	void remove( Index const &index );
	void erase( Index const &index );
	void pop( Size const &space = 1 );
	void clear() noexcept;

	void replace( Index const &from, Index const &to );
	void move( Index const &from, Index const &to );
	void swap( Index const &one, Index const &two );
	bool iterate( Index const &index );

	bool isValid( Index const &index = -1 ) const noexcept;

	Index getRelativeIndex( AbsoluteIndex const &index ) const;
	AbsoluteIndex getAbsoluteIndex( Index const &index ) const;

	Size getSize() const noexcept;
	LuaState const &getLuaState() const noexcept;
private:
	void allocate( Size const &size = 1 );
	void validate( Index const &index ) const;
	void validateType( Index const &index, Type const &type ) const;
	void checkForError( LuaErrorCode const &code, std::string const &message = "" ) const;

	LuaState const &mLuaState;
};

}
