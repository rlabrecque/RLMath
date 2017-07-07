#include "RLMath.h"

Vec2::Vec2() : x( 0.0f ), y( 0.0f ) {}

Vec2::Vec2( float _x, float _y ) : x( _x ), y( _y ) {}

Vec2::Vec2( Vec3 other ) : x( other.x ), y( other.y ) {}

Vec2::Vec2( Vec4 other ) : x( other.x ), y( other.y ) {}

const Vec2& Vec2::zero = Vec2( 0.0f, 0.0f );
const Vec2& Vec2::one = Vec2( 1.0f, 1.0f );
const Vec2& Vec2::up = Vec2( 0.0f, 1.0f );
const Vec2& Vec2::down = Vec2( 0.0f, -1.0f );
const Vec2& Vec2::left = Vec2( -1.0f, 0.0f );
const Vec2& Vec2::right = Vec2( 1.0f, 0.0f );

float Vec2::Dot( const Vec2 v1, const Vec2 v2 ) {
	return (v1.x * v2.x + v1.y * v2.y);
}

//=====================================================================================================================

Vec3::Vec3() : x( 0.0f ), y( 0.0f ), z( 0.0f ) {}

Vec3::Vec3( float _x, float _y, float _z ) : x( _x ), y( _y ), z( _z ) {}

Vec3::Vec3( Vec2 other ) : x( other.x ), y( other.y ), z( 0.0f ) {}

Vec3::Vec3( Vec4 other ) : x( other.x ), y( other.y ), z( other.z ) {}

const Vec3& Vec3::zero = Vec3( 0.0f, 0.0f, 0.0f );
const Vec3& Vec3::one = Vec3( 1.0f, 1.0f, 1.0f );
const Vec3& Vec3::up = Vec3( 0.0f, 1.0f, 0.0f );
const Vec3& Vec3::down = Vec3( 0.0f, -1.0f, 0.0f );
const Vec3& Vec3::left = Vec3( -1.0f, 0.0f, 0.0f );
const Vec3& Vec3::right = Vec3( 1.0f, 0.0f, 0.0f );
const Vec3& Vec3::back = Vec3( 0.0f, 0.0f, -1.0f );
const Vec3& Vec3::forward = Vec3( 0.0f, 0.0f, 1.0f );

float Vec3::Dot( const Vec3 v1, const Vec3 v2 ) {
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

//=====================================================================================================================

Vec4::Vec4() : x( 0.0f ), y( 0.0f ), z( 0.0f ), w( 0.0f ) {}

Vec4::Vec4( float _x, float _y, float _z, float _w ) : x( _x ), y( _y ), z( _z ), w( _w ) {}

Vec4::Vec4( Vec2 other ) : x( other.x ), y( other.y ), z( 0.0f ), w( 0.0f ) {}

Vec4::Vec4( Vec3 other ) : x( other.x ), y( other.y ), z( other.z ), w( 0.0f ) {}

const Vec4& Vec4::zero = Vec4( 0.0f, 0.0f, 0.0f, 0.0f );
const Vec4& Vec4::one = Vec4( 1.0f, 1.0f, 1.0f, 1.0f );

float Vec4::Dot( const Vec4 v1, const Vec4 v2 ) {
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}
