#pragma once
#include <limits.h>
#include <float.h>
#include <stdio.h>
#include <cstdio>

template <typename T, size_t N>
constexpr size_t countof( T( &)[N] ) {
	return N;
}

//=====================================================================================================================
// Defines
//=====================================================================================================================

constexpr float PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062f;
constexpr float TAU = PI * 2;

//=====================================================================================================================
// Functions
//=====================================================================================================================

/// TODO MOVE DOWN and rename to degrees/radians
constexpr float RL_Deg2Rad( const float deg ) {
	return deg * TAU / 360.0f;
}

constexpr float RL_Rad2Deg( const float rad ) {
	return rad * 360.0f / TAU;
}
///

//=================
// abs
//=================
constexpr float RL_abs( const float f ) {
	// todo remove '=' and this temp
	float ret = f;
	return reinterpret_cast<float&>(reinterpret_cast<int&>(ret) &= ~(1 << 31));
}

constexpr float RL_abs( const int f ) {
	return RL_abs( static_cast<float>(f) );
}

template <typename T>
constexpr T RL_abs( const T vec ) {
	T ret;
	for ( int i = 0; i < sizeof( T ) / sizeof( float ); ++i ) {
		ret[i] = RL_abs( vec[i] );
	}

	return ret;
}

//=================
// sqrt
//=================
float RL_sqrt( const float f );
float RL_sqrt( const int f );
template <typename T>
T RL_sqrt( const T vec ) {
	T ret;
	for ( int i = 0; i < sizeof( T ) / sizeof( float ); ++i ) {
		ret[i] = RL_sqrt( vec[i] );
	}

	return ret;
}

#include <Vectors.inl>
#include <Matrix.inl>
#include <Geometry.inl>

/// GARBAGE DAY
#include <functional>
namespace std {
	template<> struct hash<Vec2> {
		size_t operator()( Vec2 const& vec ) const {
			const size_t h1( std::hash<float>{}(vec.x) );
			const size_t h2( std::hash<float>{}(vec.y) );
			return h1 ^ (h2 << 1);
		}
	};

	template<> struct hash<Ray> {
		size_t operator()( Ray const& ray ) const {
			const size_t h1( std::hash<Vec2>{}(ray.direction) );
			const size_t h2( std::hash<Vec2>{}(ray.position) );
			return h1 ^ (h2 << 1);
		}
	};
}
