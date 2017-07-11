#pragma once

//=====================================================================================================================
// Vectors
//=====================================================================================================================

struct Vec2 {
	union {
		float data[2];
		struct {
			float x, y;
		};
	};

	Vec2();
	explicit Vec2( float _x, float _y );
	explicit Vec2( Vec3 other );
	explicit Vec2( Vec4 other );

	static const Vec2& zero;
	static const Vec2& one;
	static const Vec2& up;
	static const Vec2& down;
	static const Vec2& left;
	static const Vec2& right;

	inline float& operator[]( int index );
	inline const float& operator[]( int index ) const;

	inline bool operator==( const Vec2& other ) const;
	inline bool operator!=( const Vec2& other ) const;

	inline Vec2 operator+( const Vec2& other ) const;
	inline Vec2& operator+=( const Vec2& other );
	inline Vec2 operator-( const Vec2& other ) const;
	inline Vec2& operator-=( const Vec2& other );
	inline Vec2 operator- () const;
	inline Vec2 operator* ( const float scalar ) const;
	inline Vec2 operator*=( const float scalar );
	inline Vec2 operator/ ( const float scalar ) const;
	inline Vec2 operator/=( const float scalar );

	inline float magnitude() const;
	inline float squaredMagnitude() const;
	inline Vec2 normalized() const;
	inline Vec2& Normalize();

	static float Dot( const Vec2 v1, const Vec2 v2 );

	inline const char* ToString() const {
		static char str[47 * (sizeof( Vec2 ) / sizeof( float )) + 5];
		snprintf( str, sizeof( str ), "(%f, %f)", x, y );

		return str;
	}
};

struct Vec3 {
	union {
		float data[3];
		struct {
			float x, y, z;
		};
		struct {
			float r, g, b;
		};
	};

	Vec3();
	explicit Vec3( float _x, float _y, float _z );
	explicit Vec3( Vec2 other );
	explicit Vec3( Vec4 other );

	static const Vec3& zero;
	static const Vec3& one;
	static const Vec3& up;
	static const Vec3& down;
	static const Vec3& left;
	static const Vec3& right;
	static const Vec3& back;
	static const Vec3& forward;

	inline float& operator[]( int index );
	inline const float& operator[]( int index ) const;

	inline bool operator==( const Vec3& other ) const;
	inline bool operator!=( const Vec3& other ) const;

	inline Vec3 operator+ ( const Vec3& other ) const;
	inline Vec3& operator+=( const Vec3& other );
	inline Vec3 operator- ( const Vec3& other ) const;
	inline Vec3& operator-=( const Vec3& other );
	inline Vec3 operator- () const;
	inline Vec3 operator* ( const float scalar ) const;
	inline Vec3 operator*=( const float scalar );
	inline Vec3 operator/ ( const float scalar ) const;
	inline Vec3 operator/=( const float scalar );

	inline float magnitude() const;
	inline float squaredMagnitude() const;
	inline Vec3 normalized() const;
	inline Vec3& Normalize();

	static float Dot( const Vec3 v1, const Vec3 v2 );

	inline const char* ToString() const {
		static char str[47 * (sizeof( Vec3 ) / sizeof( float )) + 5];
		snprintf( str, sizeof( str ), "(%f, %f, %f)", x, y, z );

		return str;
	}
};

struct Vec4 {
	union {
		float data[4];
		struct {
			float x, y, z, w;
		};
		struct {
			float r, g, b, a;
		};
	};

	Vec4();
	explicit Vec4( float _x, float _y, float _z, float _w );
	explicit Vec4( Vec2 other );
	explicit Vec4( Vec3 other );

	static const Vec4& zero;
	static const Vec4& one;

	inline float& operator[]( int index );
	inline const float& operator[]( int index ) const;

	inline bool operator==( const Vec4& other ) const;
	inline bool operator!=( const Vec4& other ) const;

	inline Vec4 operator+ ( const Vec4& other ) const;
	inline Vec4& operator+=( const Vec4& other );
	inline Vec4 operator- ( const Vec4& other ) const;
	inline Vec4& operator-=( const Vec4& other );
	inline Vec4 operator- () const;
	inline Vec4 operator* ( const float scalar ) const;
	inline Vec4 operator*=( const float scalar );
	inline Vec4 operator/ ( const float scalar ) const;
	inline Vec4 operator/=( const float scalar );

	inline float magnitude() const;
	inline float squaredMagnitude() const;
	inline Vec4 normalized() const;
	inline Vec4& Normalize();

	static float Dot( const Vec4 v1, const Vec4 v2 );


	inline const char* ToString() const {
		static char str[47 * (sizeof( Vec4 ) / sizeof( float )) + 5];
		snprintf( str, sizeof( str ), "(%f, %f, %f, %f)", x, y, z, w );

		return str;
	}
};

#include "Vectors.inl"
