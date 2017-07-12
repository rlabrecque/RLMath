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

	// Constructors
	constexpr Vec2();
	constexpr explicit Vec2( float _x, float _y );
	constexpr explicit Vec2( Vec3 other );
	constexpr explicit Vec2( Vec4 other );

	static const Vec2& zero;
	static const Vec2& one;
	static const Vec2& up;
	static const Vec2& down;
	static const Vec2& left;
	static const Vec2& right;

	// Overrides
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

	// Custom
	inline const char* ToString() const;
	inline float length() const;
	inline float squaredLength() const;
	inline Vec2 normalized() const;
	inline Vec2& Normalize();

	// Static functions
	static inline float Dot( const Vec2 v1, const Vec2 v2 );
	static inline Vec2 Scale( const Vec2 v1, const Vec2 v2 );
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

	// Constructors
	constexpr Vec3();
	constexpr explicit Vec3( float _x, float _y, float _z );
	constexpr explicit Vec3( Vec2 other );
	constexpr explicit Vec3( Vec4 other );

	static const Vec3& zero;
	static const Vec3& one;
	static const Vec3& up;
	static const Vec3& down;
	static const Vec3& left;
	static const Vec3& right;
	static const Vec3& back;
	static const Vec3& forward;

	// Overrides
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

	// Custom
	inline const char* ToString() const;
	inline float length() const;
	inline float squaredLength() const;
	inline Vec3 normalized() const;
	inline Vec3& Normalize();

	// Static functions
	static inline float Dot( const Vec3 v1, const Vec3 v2 );
	static inline Vec3 Scale( const Vec3 v1, const Vec3 v2 );
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

	// Constructors
	constexpr Vec4();
	constexpr explicit Vec4( float _x, float _y, float _z, float _w );
	constexpr explicit Vec4( Vec2 other );
	constexpr explicit Vec4( Vec3 other );

	static const Vec4& zero;
	static const Vec4& one;

	// Overrides
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

	// Custom
	inline const char* ToString() const;
	inline float length() const;
	inline float squaredLength() const;
	inline Vec4 normalized() const;
	inline Vec4& Normalize();

	// Static functions
	static inline float Dot( const Vec4 v1, const Vec4 v2 );
	static inline Vec4 Scale( const Vec4 v1, const Vec4 v2 );
};

#include "Vectors.inl"
