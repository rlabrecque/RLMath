#pragma once
#include <limits.h>
#include <float.h>
#include <stdio.h>
#include <cstdio>
#include <math.h>

// Misc, needs to be moved.
// Modern ARRAY_SIZE
template <typename T, size_t N>
constexpr size_t countof( T( &)[N] ) {
	return N;
}

constexpr int FLOAT_MAX_PRINT_LENGTH = 47;

struct Vec2;
struct Vec3;
struct Vec4;
struct Matrix4x4;

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
constexpr float RL_abs( const float f );
constexpr Vec2 RL_abs( const Vec2 vec );
constexpr Vec3 RL_abs( const Vec3 vec );
constexpr Vec4 RL_abs( const Vec4 vec );

//=================
// sqrt
//=================
inline float RL_sqrt( const float f );
inline Vec2 RL_sqrt( const Vec2 vec );
inline Vec3 RL_sqrt( const Vec3 vec );
inline Vec4 RL_sqrt( const Vec4 vec );

//=================
// sin
//=================
inline float RL_sin( const float f );
inline Vec2 RL_sin( const Vec2 vec );
inline Vec3 RL_sin( const Vec3 vec );
inline Vec4 RL_sin( const Vec4 vec );

//=================
// cos
//=================
inline float RL_cos( const float f );
inline Vec2 RL_cos( const Vec2 vec );
inline Vec3 RL_cos( const Vec3 vec );
inline Vec4 RL_cos( const Vec4 vec );

//=================
// min
//=================
inline float RL_min( const float a, const float b );

//=================
// max
//=================
inline float RL_max( const float a, const float b );

#include "Vectors.h"
#include "Matrix.h"
#include "Geometry.h"

#include "RLMath.inl"

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
			const size_t h2( std::hash<Vec2>{}(ray.origin) );
			return h1 ^ (h2 << 1);
		}
	};

	template<> struct hash<AABB> {
		size_t operator()( AABB const& aabb ) const {
			const size_t h1( std::hash<Vec2>{}(aabb.origin) );
			const size_t h2( std::hash<Vec2>{}(aabb.extents) );
			return h1 ^ (h2 << 1);
		}
	};

	template<> struct hash<Circle> {
		size_t operator()( Circle const& aabb ) const {
			const size_t h1( std::hash<Vec2>{}(aabb.origin) );
			const size_t h2( std::hash<float>{}(aabb.radius) );
			return h1 ^ (h2 << 1);
		}
	};
}
