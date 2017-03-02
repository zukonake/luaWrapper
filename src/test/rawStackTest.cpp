#include <utility>
//
#include <boost/test/unit_test.hpp>
//
#include <luna/rawStack.hpp>

namespace Luna
{

BOOST_AUTO_TEST_SUITE( rawStackTest );

BOOST_AUTO_TEST_CASE( constructorDestructorTest )
{
	RawStack *tRawStack01 = nullptr;
	BOOST_REQUIRE_NO_THROW( tRawStack01 = new RawStack());
	BOOST_REQUIRE_NO_THROW( delete tRawStack01 );
}

BOOST_AUTO_TEST_CASE( moveTest )
{
	RawStack tRawStack01;	
	RawStack tRawStack02 = std::move( tRawStack01 );
	BOOST_CHECK( static_cast< LuaState *>( tRawStack01.getState()) == nullptr );
	BOOST_CHECK( static_cast< LuaState *>( tRawStack02.getState()) != nullptr );

	RawStack tRawStack03;	
	RawStack tRawStack04( std::move( tRawStack03 ));
	BOOST_CHECK( static_cast< LuaState *>( tRawStack03.getState()) == nullptr );
	BOOST_CHECK( static_cast< LuaState *>( tRawStack04.getState()) != nullptr );
}

BOOST_AUTO_TEST_CASE( readingTest )
{
	RawStack tRawStack01;
	BOOST_REQUIRE_NO_THROW( tRawStack01.loadFile( "src/test/test.lua" ));
	BOOST_REQUIRE_NO_THROW( tRawStack01.call());
	BOOST_REQUIRE_NO_THROW( tRawStack01.loadGlobal( "var" ));
	BOOST_CHECK_EQUAL( tRawStack01.toNumber(), 10 );

	RawStack tRawStack02;
	BOOST_REQUIRE_NO_THROW( tRawStack02.loadString( "var = 'test'" ));
	BOOST_REQUIRE_NO_THROW( tRawStack02.call());
	BOOST_REQUIRE_NO_THROW( tRawStack02.loadGlobal( "var" ));
	BOOST_CHECK_EQUAL( tRawStack02.toString(), "test" );

	RawStack tRawStack03;
	BOOST_REQUIRE_NO_THROW( tRawStack03.doFile( "src/test/test.lua" ));
	BOOST_REQUIRE_NO_THROW( tRawStack03.loadGlobal( "var" ));
	BOOST_CHECK_EQUAL( tRawStack03.toNumber(), 10 );

	RawStack tRawStack04;
	BOOST_REQUIRE_NO_THROW( tRawStack04.doString( "var = 'test'" ));
	BOOST_REQUIRE_NO_THROW( tRawStack04.loadGlobal( "var" ));
	BOOST_CHECK_EQUAL( tRawStack04.toString(), "test" );

	RawStack tRawStack05;
	BOOST_REQUIRE_NO_THROW( tRawStack05.doFile( "src/test/test.lua" ));
	BOOST_REQUIRE_NO_THROW( tRawStack05.loadGlobal( "var" ));
	BOOST_CHECK_THROW( tRawStack05.toString(), std::runtime_error );
	BOOST_CHECK_THROW( tRawStack05.toNumber( -5 ), std::out_of_range );
	BOOST_CHECK_THROW( tRawStack05.toNumber( 0 ), std::out_of_range );
	BOOST_CHECK_THROW( tRawStack05.toNumber( 50 ), std::out_of_range );

	RawStack tRawStack06;
	BOOST_REQUIRE_NO_THROW( tRawStack06.loadString( "var = 'test'" ));
	BOOST_CHECK_THROW( tRawStack06.call( -20 ), std::out_of_range );
	BOOST_CHECK_THROW( tRawStack06.call( 0 ), std::out_of_range );
	BOOST_CHECK_THROW( tRawStack06.call( 20 ), std::out_of_range );

	RawStack tRawStack07;
	BOOST_REQUIRE_NO_THROW( tRawStack07.doString( "var = 'test'" ));
	BOOST_CHECK_THROW( tRawStack07.loadGlobal( "var" ), std::runtime_error );

	RawStack tRawStack04;
	BOOST_CHECK_THROW( tRawStack04.loadFile( "src/test/nofile.lua" ), std::runtime_error );
	BOOST_CHECK_THROW( tRawStack04.loadString( "invalidCode" ), std::runtime_error );
}

BOOST_AUTO_TEST_SUITE_END();

}