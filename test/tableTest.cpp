#include <stdexcept>
//
#include <boost/test/unit_test.hpp>
//
#include <luna/element/number.hpp>
#include <luna/element/string.hpp>
#include <luna/element/table.hpp>
#include "stackFixture.hpp"

namespace Luna::Test
{

BOOST_FIXTURE_TEST_SUITE( tableTest, StackFixture,
	* boost::unit_test::depends_on( "rawStackTest" )
	* boost::unit_test::depends_on( "elementTest" )
	* boost::unit_test::depends_on( "numberTest" )
	* boost::unit_test::depends_on( "stringTest" ));

BOOST_AUTO_TEST_CASE( atTest00 ) //TODO get instead of at?
{
	BOOST_REQUIRE_NO_THROW( fStack.doFile( "tableTest.lua" ));
	Table tTable00 = fStack.loadGlobal< Table >( "test" );
	tTable00.getValue();
	BOOST_CHECK( fStack.getType() == TABLE );
	BOOST_CHECK_EQUAL( tTable00.get< Number >( "var" ), 12 );
	/*BOOST_CHECK_EQUAL( tTable00.get< String >( "var1" ), "test" );
	BOOST_CHECK_EQUAL( tTable00.get< Number >( 1 ), 25 );
	BOOST_CHECK_EQUAL( tTable00.get< String >( 2 ), "test2" );
	
	Table tTable01 = tTable00.get< Table >( "var2" );
	BOOST_CHECK_EQUAL( tTable01.get< Number >( "var0" ), 120 );
	BOOST_CHECK_EQUAL( tTable01.get< String >( "var11" ), "test1" );
	BOOST_CHECK_EQUAL( tTable01.get< Number >( 1 ), 24 );
	BOOST_CHECK_EQUAL( tTable01.get< String >( 2 ), "test3" );
	BOOST_CHECK_THROW( tTable00.get< String >( "invalidVar" ), std::out_of_range );
	BOOST_CHECK_THROW( tTable00.get< Table >( 3 ), std::out_of_range );
	BOOST_CHECK_THROW( tTable00.get< Number >( -1 ), std::out_of_range );
	BOOST_CHECK_THROW( tTable00.get< String >( 0 ), std::out_of_range );*/
}

//TODO set test

BOOST_AUTO_TEST_SUITE_END();

}
