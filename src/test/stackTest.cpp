#include <boost/test/unit_test.hpp>
//
#include <luna/typedef.hpp>
#include <luna/stack.hpp>

namespace Luna
{

BOOST_AUTO_TEST_SUITE( stackTest );

BOOST_AUTO_TEST_CASE( constructorDestructorTest )
{
	Stack *tStack01 = nullptr;
	BOOST_REQUIRE_NO_THROW( tStack01 = new Stack());
	BOOST_REQUIRE_NO_THROW( delete tStack01 );
}

BOOST_AUTO_TEST_CASE( moveTest )
{
	Stack tStack01;	
	Stack tStack02 = std::move( tStack01 );
	BOOST_CHECK( static_cast< const LuaState *>( tStack01.getState()) == nullptr );
	BOOST_CHECK( static_cast< const LuaState *>( tStack02.getState()) != nullptr );

	Stack tStack03;	
	Stack tStack04( std::move( tStack03 ));
	BOOST_CHECK( static_cast< const LuaState *>( tStack03.getState()) == nullptr );
	BOOST_CHECK( static_cast< const LuaState *>( tStack04.getState()) != nullptr );
}

BOOST_AUTO_TEST_CASE( bindTest )
{
	
}

BOOST_AUTO_TEST_SUITE_END();

}