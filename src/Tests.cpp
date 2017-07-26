#include "RLMath.h"
#include "lest.hpp"

const lest::test VectorTests[] = {
CASE( "Unexpected exception is reported" ) {
	EXPECT( Vec2( 128, -128 ).x == 128.0f );
},

CASE( "Check getting scalars" )
{
	EXPECT( Vec2( 128, -128 ).x == 128.0f );
	EXPECT( Vec2( 128, -128 ).y == -128.0f );

	EXPECT( Vec3( 128, -128, 5 ).x == 128.0f );
	EXPECT( Vec3( 128, -128, 5 ).y == -128.0f );
	EXPECT( Vec3( 128, -128, 5 ).z == 5 );

	EXPECT( Vec4( 128, -128, 5, 1000 ).x == 128.0f );
	EXPECT( Vec4( 128, -128, 5, 1000 ).y == -128.0f );
	EXPECT( Vec4( 128, -128, 5, 1000 ).z == 5 );
	EXPECT( Vec4( 128, -128, 5, 1000 ).w == 1000 );
},

CASE( "Test Conversion" )
{
	EXPECT( Vec2( Vec3( 1, 2, 3 ) ) == Vec2( 1, 2 ) );
	EXPECT( Vec2( Vec4( 1, 2, 3, 4 ) ) == Vec2( 1, 2 ) );

	EXPECT( Vec3( Vec2( 1, 2 ) ) == Vec3( 1, 2, 0 ) );
	EXPECT( Vec3( Vec4( 1, 2, 3, 4 ) ) == Vec3( 1, 2, 3 ) );

	EXPECT( Vec4( Vec2( 1, 2 ) ) == Vec4( 1, 2, 0, 0 ) );
	EXPECT( Vec4( Vec3( 1, 2, 3) ) == Vec4( 1, 2, 3, 0 ) );
},

CASE( "Constant vectors" )
{
	EXPECT( Vec2::zero == Vec2( 0.0f, 0.0f ) );
	EXPECT( Vec2::one == Vec2( 1.0f, 1.0f ) );
	EXPECT( Vec2::up == Vec2( 0.0f, 1.0f ) );
	EXPECT( Vec2::down == Vec2( 0.0f, -1.0f ) );
	EXPECT( Vec2::left == Vec2( -1.0f, 0.0f ) );
	EXPECT( Vec2::right == Vec2( 1.0f, 0.0f ) );

	EXPECT( Vec3::zero == Vec3( 0.0f, 0.0f, 0.0f ) );
	EXPECT( Vec3::one == Vec3( 1.0f, 1.0f, 1.0f ) );
	EXPECT( Vec3::up == Vec3( 0.0f, 1.0f, 0.0f ) );
	EXPECT( Vec3::down == Vec3( 0.0f, -1.0f, 0.0f ) );
	EXPECT( Vec3::left == Vec3( -1.0f, 0.0f, 0.0f ) );
	EXPECT( Vec3::right == Vec3( 1.0f, 0.0f, 0.0f ) );
	EXPECT( Vec3::back == Vec3( 0.0f, 0.0f, -1.0f ) );
	EXPECT( Vec3::forward == Vec3( 0.0f, 0.0f, 1.0f ) );

	EXPECT( Vec4::zero == Vec4( 0.0f, 0.0f, 0.0f, 0.0f ) );
	EXPECT( Vec4::one == Vec4( 1.0f, 1.0f, 1.0f, 1.0f ) );
},

CASE( "Test operator +" )
{
	EXPECT( Vec2( 1000, -1000 ) + Vec2( 500, 500 ) == Vec2( 1500, -500 ) );
	EXPECT( Vec3( 1000, -1000, 100 ) + Vec3( 500, 500, 100 ) == Vec3( 1500, -500, 200 ) );
	EXPECT( Vec4( 1000, -1000, 100, 1337 ) + Vec4( 500, 500, 100, 1 ) == Vec4( 1500, -500, 200, 1338 ) );
},

CASE( "Test operator +=" )
{
	EXPECT( (Vec2( 1000, -1000 ) += Vec2( 500, 500 )) == Vec2( 1500, -500 ) );
	EXPECT( (Vec3( 1000, -1000, 100 ) += Vec3( 500, 500, 100 )) == Vec3( 1500, -500, 200 ) );
	EXPECT( (Vec4( 1000, -1000, 100, 1337 ) += Vec4( 500, 500, 100, 1 )) == Vec4( 1500, -500, 200, 1338 ) );
},

CASE( "Test operator - (subtract)" )
{
	EXPECT( Vec2( 1000, -1000 ) - Vec2( 500, 500 ) == Vec2( 500, -1500 ) );
	EXPECT( Vec3( 1000, -1000, 100 ) - Vec3( 500, 500, 100 ) == Vec3( 500, -1500, 0 ) );
	EXPECT( Vec4( 1000, -1000, 100, 1337 ) - Vec4( 500, 500, 100, 37 ) == Vec4( 500, -1500, 0, 1300 ) );
},

CASE( "Test operator -=" )
{
	EXPECT( (Vec2( 1000, -1000 ) -= Vec2( 500, 500 )) == Vec2( 500, -1500 ) );
	EXPECT( (Vec3( 1000, -1000, 100 ) -= Vec3( 500, 500, 100 )) == Vec3( 500, -1500, 0 ) );
	EXPECT( (Vec4( 1000, -1000, 100, 1337 ) -= Vec4( 500, 500, 100, 37 )) == Vec4( 500, -1500, 0, 1300 ) );
},

CASE( "Test operator - (negate)" )
{
	EXPECT( -Vec2( 1000, -999 ) == Vec2( -1000, 999 ) );
	EXPECT( -Vec3( 1000, -1000, 100)  == Vec3( -1000, 1000, -100 ) );
	EXPECT( -Vec4( 1000, -1000, 100, 1337) == Vec4( -1000, 1000, -100, -1337 ) );
},

CASE( "Test operator *" )
{
	EXPECT( Vec2( 500, -100 ) * 2 == Vec2( 1000, -200 ) );
	EXPECT( Vec3( 1000, -1000, 100 ) * 2 == Vec3( 2000, -2000, 200 ) );
	EXPECT( Vec4( 1000, -1000, 100, 1300 ) * 2 == Vec4( 2000, -2000, 200, 2600 ) );
},

CASE( "Test operator *=" )
{
	EXPECT( (Vec2( 500, -100 ) *= 2) == Vec2( 1000, -200 ) );
	EXPECT( (Vec3( 1000, -1000, 100 ) *= 2) == Vec3( 2000, -2000, 200 ) );
	EXPECT( (Vec4( 1000, -1000, 100, 1300 ) *= 2) == Vec4( 2000, -2000, 200, 2600 ) );
},

CASE( "Test operator /" )
{
	EXPECT( Vec2( 500, -100 ) / 2 == Vec2( 250, -50 ) );
	EXPECT( Vec3( 1000, -1000, 100 ) / 2 == Vec3( 500, -500, 50 ) );
	EXPECT( Vec4( 1000, -1000, 100, 1300 ) / 2 == Vec4( 500, -500, 50, 650 ) );
},

CASE( "Test operator /=" )
{
	EXPECT( (Vec2( 500, -100 ) /= 2) == Vec2( 250, -50 ) );
	EXPECT( (Vec3( 1000, -1000, 100 ) /= 2) == Vec3( 500, -500, 50 ) );
	EXPECT( (Vec4( 1000, -1000, 100, 1300 ) /= 2) == Vec4( 500, -500, 50, 650 ) );
},

CASE( "Verify length" )
{
	EXPECT( Vec2( 1, 1 ).length() == 1.41421356237f );
	EXPECT( Vec3( 2, 1, 2 ).length() == 3 );
	EXPECT( Vec4( 2, 1, 2, 9 ).length() == 9.48683298051f );
},

CASE( "Verify squaredLength" )
{
	EXPECT( Vec2( 1, 1 ).lengthSq() == 2 );
	EXPECT( Vec3( 2, 1, 2 ).lengthSq() == 9 );
	EXPECT( Vec4( 2, 1, 2, 9 ).lengthSq() == 90.0f );
},

CASE( "Verify normalized" )
{
	EXPECT( Vec2( 1, 0 ).normalized() == Vec2( 1, 0 ) );
	EXPECT( Vec2( 3, 2 ).normalized() == Vec2( 0.83205029433f, 0.55470019622f ) );
	EXPECT( Vec3( 0, 1, 0 ).normalized() == Vec3(0, 1, 0) );
	EXPECT( Vec3( 0, 2, 0 ).normalized() == Vec3( 0, 1, 0 ) );
	EXPECT( Vec4( 2, 2, 2, 2 ).normalized() == Vec4( 0.5f, 0.5f, 0.5f, 0.5f ) );
},

	CASE( "Verify normalized" )
	{
		EXPECT( Vec2( 1, 0 ).Normalize() == Vec2( 1, 0 ) );
		EXPECT( Vec2( 3, 2 ).Normalize() == Vec2( 0.83205029433f, 0.55470019622f ) );
		EXPECT( Vec3( 0, 1, 0 ).Normalize() == Vec3( 0, 1, 0 ) );
		EXPECT( Vec3( 0, 2, 0 ).Normalize() == Vec3( 0, 1, 0 ) );
		EXPECT( Vec4( 2, 2, 2, 2 ).Normalize() == Vec4( 0.5f, 0.5f, 0.5f, 0.5f ) );
	},
};

const lest::test VectorStaticFunctionTests[] = {

	CASE( "Verify Dot" ) {
		EXPECT( Vec2::Dot( Vec2( 5, 4 ), Vec2( 4, 3 ) ) == 32 );
		EXPECT( Vec3::Dot( Vec3( 8, 10, 100 ), Vec3( 4, 3, 2 ) ) == 262 );
		EXPECT( Vec4::Dot( Vec4( 4, 1, 3, -100 ), Vec4( 2, 0, 3, 2 ) ) == -183 );
	},

	CASE( "Verify Scale" ) {
		EXPECT( Vec2::Scale( Vec2(2, 0), Vec2( 2, 0 )) == Vec2( 4, 0 ) );
		EXPECT( Vec3::Scale( Vec3( 2, 0, 100 ), Vec3( 2, 0, 3 ) ) == Vec3( 4, 0, 300 ) );
		EXPECT( Vec4::Scale( Vec4( 2, 0, 100, -100 ), Vec4( 2, 0, 3, -1 ) ) == Vec4( 4, 0, 300, 100 ) );
	},

};

const lest::test MathFunctionsTests[] = {
CASE( "abs" ) {
	EXPECT( RL_abs( 1 ) == 1 );
	EXPECT( RL_abs( 0 ) == 0 );
	EXPECT( RL_abs( -0 ) == 0 );
	EXPECT( RL_abs( -1 ) == 1 );
	EXPECT( RL_abs( SHRT_MAX ) == SHRT_MAX );
	EXPECT( RL_abs( SHRT_MIN ) == SHRT_MAX + 1 );

	EXPECT( RL_abs( 1.0f ) == 1.0f );
	EXPECT( RL_abs( 0.0f ) == 0.0f );
	EXPECT( RL_abs( -0.5f ) == 0.5f );
	EXPECT( RL_abs( -1.0f ) == 1.0f );
	EXPECT( RL_abs( 1337.0f ) == 1337.0f );
	EXPECT( RL_abs( -1337.5f ) == 1337.5f );

	EXPECT( RL_abs( Vec2( -1.0f, 1.0f ) ) == Vec2( 1.0f, 1.0f ) );
	EXPECT( RL_abs( Vec2( -1337.5f, -1234.9f ) ) == Vec2( 1337.5f, 1234.9f ) );

	EXPECT( RL_abs( Vec3( -1.0f, 0.0f, 1.0f ) ) == Vec3( 1.0f, 0.0f, 1.0f ) );
	EXPECT( RL_abs( Vec3( -1337.5f, -101010.1f, -1234.9f ) ) == Vec3( 1337.5f, 101010.1f, 1234.9f ) );

	EXPECT( RL_abs( Vec4( -1.0f, 0.0f, 1.0f, -999.0f ) ) == Vec4( 1.0f, 0.0f, 1.0f, 999.0f ) );
	EXPECT( RL_abs( Vec4( -1337.5f, -101010.1f, -1234.9f, 808.0f ) ) == Vec4( 1337.5f, 101010.1f, 1234.9f, 808.0f ) );
},

CASE( "sqrt" ) {
	EXPECT( RL_sqrt( 0 ) == 0 );
	EXPECT( RL_sqrt( 1.0f ) == 1 );
	EXPECT( RL_sqrt( 2 ) == 1.41421356237f );
	EXPECT( RL_sqrt( 4.0f ) == 2.0f );
	EXPECT( RL_sqrt( 49 ) == 7.0f );

	EXPECT( RL_sqrt( Vec2( 100.0f, 64.0f ) ) == Vec2( 10.0f, 8.0f ) );

	EXPECT( RL_sqrt( Vec3( 81.0f, 121.0f, 144.0f ) ) == Vec3( 9.0f, 11, 12.0f ) );

	EXPECT( RL_sqrt( Vec4( 100.0f, 64.0f, 121.0f, 144.0f ) ) == Vec4( 10.0f, 8.0f, 11, 12.0f ) );
},
};


void RunTests() {
	char * args[] = { "*" };
	lest::run( VectorTests, 1, args );
	lest::run( VectorStaticFunctionTests, 1, args );
	lest::run( MathFunctionsTests, 1, args );
}
