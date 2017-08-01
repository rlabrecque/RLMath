#pragma once

// Constructors
constexpr Vec2::Vec2() : x( 0.0f ), y( 0.0f ) {}
constexpr Vec2::Vec2( float _x, float _y ) : x( _x ), y( _y ) {}
constexpr Vec2::Vec2( Vec3 other ) : x( other.x ), y( other.y ) {}
constexpr Vec2::Vec2( Vec4 other ) : x( other.x ), y( other.y ) {}

// Overrides
inline float& Vec2::operator[]( int index ) {
	return data[index];
}

inline const float& Vec2::operator[]( int index ) const {
	return data[index];
}

inline bool Vec2::operator==( const Vec2& other ) const {
	return (x == other.x && y == other.y);
}

inline bool Vec2::operator!=( const Vec2& other ) const {
	return !(*this == other);
}

inline Vec2 Vec2::operator+ ( const Vec2& other ) const {
	return Vec2( x + other.x, y + other.y );
}

inline Vec2& Vec2::operator+=( const Vec2& other ) {
	x += other.x;
	y += other.y;
	return *this;
}

inline Vec2 Vec2::operator- ( const Vec2& other ) const {
	return Vec2( x - other.x, y - other.y );
}

inline Vec2& Vec2::operator-=( const Vec2& other ) {
	x -= other.x;
	y -= other.y;
	return *this;
}

inline Vec2 Vec2::operator- () const {
	return Vec2( -x, -y );
}

inline Vec2 Vec2::operator* ( const float scalar ) const {
	return Vec2( x * scalar, y * scalar );
}

inline Vec2 Vec2::operator*=( const float scalar ) {
	x *= scalar;
	y *= scalar;
	return *this;
}

inline Vec2 Vec2::operator/ ( const float scalar ) const {
	return Vec2( x / scalar, y / scalar );
}

inline Vec2 Vec2::operator/=( const float scalar ) {
	x /= scalar;
	y /= scalar;
	return *this;
}

// Custom
inline const char* Vec2::ToString() const {
	static char str[FLOAT_MAX_PRINT_LENGTH * (sizeof( Vec2 ) / sizeof( float )) + 5];
	snprintf( str, sizeof( str ), "(%f, %f)", x, y );

	return str;
}

inline float Vec2::length() const {
	return RL_sqrt( Dot( *this, *this ) );
}

inline float Vec2::lengthSq() const {
	return Dot( *this, *this );
}

inline Vec2 Vec2::normalized() const {
	return Vec2( *this ).Normalize();
}

inline Vec2& Vec2::Normalize() {
	float length = (*this).length();
	if ( length < 1E-05f ) {
		*this = Vec2::zero;
		 return *this;
	}

	*this /= length;
	return *this;
}

// Static functions
inline float Vec2::Dot( const Vec2 v1, const Vec2 v2 ) {
	return (v1.x * v2.x + v1.y * v2.y);
}

inline Vec2 Vec2::Scale( const Vec2 v1, const Vec2 v2 ) {
	return Vec2(v1.x * v2.x, v1.y * v2.y);
}

//=====================================================================================================================

// Constructors
constexpr Vec3::Vec3() : x( 0.0f ), y( 0.0f ), z( 0.0f ) {}
constexpr Vec3::Vec3( float _x, float _y, float _z ) : x( _x ), y( _y ), z( _z ) {}
constexpr Vec3::Vec3( Vec2 other ) : x( other.x ), y( other.y ), z( 0.0f ) {}
constexpr Vec3::Vec3( Vec4 other ) : x( other.x ), y( other.y ), z( other.z ) {}

// Overrides
inline float& Vec3::operator[]( int index ) {
	return data[index];
}

inline const float& Vec3::operator[]( int index ) const {
	return data[index];
}

inline bool Vec3::operator==( const Vec3& other ) const {
	return (x == other.x && y == other.y && z == other.z);
}

inline bool Vec3::operator!=( const Vec3& other ) const {
	return !(*this == other);
}

inline Vec3 Vec3::operator+( const Vec3& other ) const {
	return Vec3( x + other.x, y + other.y, z + other.z );
}

inline Vec3& Vec3::operator+=( const Vec3& other ) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

inline Vec3 Vec3::operator-( const Vec3& other ) const {
	return Vec3( x - other.x, y - other.y, z - other.z );
}

inline Vec3& Vec3::operator-=( const Vec3& other ) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

inline Vec3 Vec3::operator-() const {
	return Vec3( -x, -y, -z );
}

inline Vec3 Vec3::operator*( const float scalar ) const {
	return Vec3( x * scalar, y * scalar, z * scalar );
}

inline Vec3 Vec3::operator*=( const float scalar ) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

inline Vec3 Vec3::operator/( const float scalar ) const {
	return Vec3( x / scalar, y / scalar, z / scalar );
}

inline Vec3 Vec3::operator/=( const float scalar ) {
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

// Custom
inline const char* Vec3::ToString() const {
	static char str[FLOAT_MAX_PRINT_LENGTH * (sizeof( Vec3 ) / sizeof( float )) + 5];
	snprintf( str, sizeof( str ), "(%f, %f, %f)", x, y, z );

	return str;
}

inline float Vec3::length() const {
	return RL_sqrt( Dot( *this, *this ) );
}

inline float Vec3::lengthSq() const {
	return Dot(*this, *this);
}

inline Vec3 Vec3::normalized() const {
	return Vec3( *this ).Normalize();
}

inline Vec3& Vec3::Normalize() {
	float length = (*this).length();
	if ( length < 1E-05f ) {
		*this = Vec3::zero;
		return *this;
	}

	*this /= length;
	return *this;
}

// Static functions
inline float Vec3::Dot( const Vec3 v1, const Vec3 v2 ) {
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

inline Vec3 Vec3::Scale( const Vec3 v1, const Vec3 v2 ) {
	return Vec3( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z );
}

//=====================================================================================================================

// Constructors
constexpr Vec4::Vec4() : x( 0.0f ), y( 0.0f ), z( 0.0f ), w( 0.0f ) {}
constexpr Vec4::Vec4( float _x, float _y, float _z, float _w ) : x( _x ), y( _y ), z( _z ), w( _w ) {}
constexpr Vec4::Vec4( Vec2 other ) : x( other.x ), y( other.y ), z( 0.0f ), w( 0.0f ) {}
constexpr Vec4::Vec4( Vec3 other ) : x( other.x ), y( other.y ), z( other.z ), w( 0.0f ) {}

// Overrides
inline float& Vec4::operator[]( int index ) {
	return data[index];
}

inline const float& Vec4::operator[]( int index ) const {
	return data[index];
}

inline bool Vec4::operator==( const Vec4& other ) const {
	return (x == other.x && y == other.y && z == other.z && w == other.w);
}

inline bool Vec4::operator!=( const Vec4& other ) const {
	return !(*this == other);
}

inline Vec4 Vec4::operator+ ( const Vec4& other ) const {
	return Vec4( x + other.x, y + other.y, z + other.z, w + other.w );
}

inline Vec4& Vec4::operator+=( const Vec4& other ) {
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
	return *this;
}

inline Vec4 Vec4::operator-( const Vec4& other ) const {
	return Vec4( x - other.x, y - other.y, z - other.z, w - other.w );
}

inline Vec4& Vec4::operator-=( const Vec4& other ) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
	return *this;
}

inline Vec4 Vec4::operator-() const {
	return Vec4( -x, -y, -z, -w );
}

inline Vec4 Vec4::operator*( const float scalar ) const {
	return Vec4( x * scalar, y * scalar, z * scalar, w * scalar );
}

inline Vec4 Vec4::operator*=( const float scalar ) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
}

inline Vec4 Vec4::operator/( const float scalar ) const {
	return Vec4( x / scalar, y / scalar, z / scalar, w / scalar );
}

inline Vec4 Vec4::operator/=( const float scalar ) {
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;
	return *this;
}

// Custom
inline const char* Vec4::ToString() const {
	static char str[FLOAT_MAX_PRINT_LENGTH * (sizeof( Vec4 ) / sizeof( float )) + 5];
	snprintf( str, sizeof( str ), "(%f, %f, %f, %f)", x, y, z, w );

	return str;
}

inline float Vec4::length() const {
	return RL_sqrt( Dot(*this, *this) );
}

inline float Vec4::lengthSq() const {
	return Dot( *this, *this );
}

inline Vec4 Vec4::normalized() const {
	return Vec4( *this ).Normalize();
}

inline Vec4& Vec4::Normalize() {
	float length = (*this).length();
	if ( length < 1E-05f ) {
		*this = Vec4::zero;
		return *this;
	}

	*this /= length;
	return *this;
}

// Static functions
inline float Vec4::Dot( const Vec4 v1, const Vec4 v2 ) {
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}

inline Vec4 Vec4::Scale( const Vec4 v1, const Vec4 v2 ) {
	return Vec4( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w );
}