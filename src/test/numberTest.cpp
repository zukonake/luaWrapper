#include <memory>
//
#include <boost/test/unit_test.hpp>
//
#include <luna/typedef.hpp>
#include <luna/rawStack.hpp>
#include <luna/element/number.hpp>

namespace Luna
{

BOOST_AUTO_TEST_SUITE( numberTest );

BOOST_AUTO_TEST_CASE( test )
{
	RawStack tRawStack01;
	BOOST_REQUIRE_NO_THROW( tRawStack01.pushNumber( 32 ));
	BOOST_REQUIRE_NO_THROW( tRawStack01.pushNumber( 24 ));
	Number tNumber01( tRawStack01, -2 );
	BOOST_CHECK_EQUAL( tNumber01, 32 );
	BOOST_CHECK_EQUAL( tRawStack01.getSize(), 2 );
}

BOOST_AUTO_TEST_SUITE_END();

}
