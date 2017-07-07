#pragma once

//=====================================================================================================================
// Vector
//=====================================================================================================================

struct Vec2;
struct Vec3;
struct Vec4;

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
		static char str[47 * (sizeof(data) / sizeof(float)) + 5];
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
		static char str[47 * (sizeof( data ) / sizeof( float )) + 5];
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
		static char str[47 * (sizeof( data ) / sizeof( float )) + 5];
		snprintf( str, sizeof( str ), "(%f, %f, %f, %f)", x, y, z, w );

		return str;
	}
};

//=====================================================================================================================

float& Vec2::operator[]( int index ) {
	return data[index];
}

const float& Vec2::operator[]( int index ) const {
	return data[index];
}

bool Vec2::operator==( const Vec2& other ) const {
	return (x == other.x && y == other.y);
}

bool Vec2::operator!=( const Vec2& other ) const {
	return !(*this == other);
}

Vec2 Vec2::operator+ ( const Vec2& other ) const {
	return Vec2( x + other.x, y + other.y );
}

Vec2& Vec2::operator+=( const Vec2& other ) {
	x += other.x;
	y += other.y;
	return *this;
}

Vec2 Vec2::operator- ( const Vec2& other ) const {
	return Vec2( x - other.x, y - other.y );
}

Vec2& Vec2::operator-=( const Vec2& other ) {
	x -= other.x;
	y -= other.y;
	return *this;
}

Vec2 Vec2::operator- () const {
	return Vec2( -x, -y );
}

Vec2 Vec2::operator* ( const float scalar ) const {
	return Vec2( x * scalar, y * scalar );
}

Vec2 Vec2::operator*=( const float scalar ) {
	x *= scalar;
	y *= scalar;
	return *this;
}

Vec2 Vec2::operator/ ( const float scalar ) const {
	return Vec2( x / scalar, y / scalar );
}

Vec2 Vec2::operator/=( const float scalar ) {
	x /= scalar;
	y /= scalar;
	return *this;
}

float Vec2::magnitude() const {
	return RL_sqrt( (x * x) + (y * y) );
}

float Vec2::squaredMagnitude() const {
	return (x * x) + (y * y);
}

Vec2 Vec2::normalized() const {
	return Vec2( *this ).Normalize();
}

Vec2& Vec2::Normalize() {
	float magnitude = (*this).magnitude();
	if ( magnitude < 1E-05f ) {
		return (*this = Vec2::zero);
	}

	*this /= magnitude;
	return *this;
}

//=====================================================================================================================

float& Vec3::operator[]( int index ) {
	return data[index];
}

const float& Vec3::operator[]( int index ) const {
	return data[index];
}

bool Vec3::operator==( const Vec3& other ) const {
	return (x == other.x && y == other.y && z == other.z);
}

bool Vec3::operator!=( const Vec3& other ) const {
	return !(*this == other);
}

Vec3 Vec3::operator+( const Vec3& other ) const {
	return Vec3( x + other.x, y + other.y, z + other.z );
}

Vec3& Vec3::operator+=( const Vec3& other ) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vec3 Vec3::operator-( const Vec3& other ) const {
	return Vec3( x - other.x, y - other.y, z - other.z );
}

Vec3& Vec3::operator-=( const Vec3& other ) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vec3 Vec3::operator-() const {
	return Vec3( -x, -y, -z );
}

Vec3 Vec3::operator*( const float scalar ) const {
	return Vec3( x * scalar, y * scalar, z * scalar );
}

Vec3 Vec3::operator*=( const float scalar ) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

Vec3 Vec3::operator/( const float scalar ) const {
	return Vec3( x / scalar, y / scalar, z / scalar );
}

Vec3 Vec3::operator/=( const float scalar ) {
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

float Vec3::magnitude() const {
	return RL_sqrt( (x * x) + (y * y) + (z *z) );
}

float Vec3::squaredMagnitude() const {
	return (x * x) + (y * y) + (z *z);
}

Vec3 Vec3::normalized() const {
	return Vec3( *this ).Normalize();
}

Vec3& Vec3::Normalize() {
	float magnitude = (*this).magnitude();
	if ( magnitude < 1E-05f ) {
		return (*this = Vec3::zero);
	}

	*this /= magnitude;
	return *this;
}

//=====================================================================================================================

float& Vec4::operator[]( int index ) {
	return data[index];
}

const float& Vec4::operator[]( int index ) const {
	return data[index];
}

bool Vec4::operator==( const Vec4& other ) const {
	return (x == other.x && y == other.y && z == other.z && w == other.w);
}

bool Vec4::operator!=( const Vec4& other ) const {
	return !(*this == other);
}

Vec4 Vec4::operator+ ( const Vec4& other ) const {
	return Vec4( x + other.x, y + other.y, z + other.z, w + other.w );
}

Vec4& Vec4::operator+=( const Vec4& other ) {
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
	return *this;
}

Vec4 Vec4::operator-( const Vec4& other ) const {
	return Vec4( x - other.x, y - other.y, z - other.z, w - other.w );
}

Vec4& Vec4::operator-=( const Vec4& other ) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
	return *this;
}

Vec4 Vec4::operator-() const {
	return Vec4( -x, -y, -z, -w );
}

Vec4 Vec4::operator*( const float scalar ) const {
	return Vec4( x * scalar, y * scalar, z * scalar, w * scalar );
}

Vec4 Vec4::operator*=( const float scalar ) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
}

Vec4 Vec4::operator/( const float scalar ) const {
	return Vec4( x / scalar, y / scalar, z / scalar, w / scalar );
}

Vec4 Vec4::operator/=( const float scalar ) {
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;
	return *this;
}

float Vec4::magnitude() const {
	return RL_sqrt( (x * x) + (y * y) + (z *z) + (w * w) );
}

float Vec4::squaredMagnitude() const {
	return (x * x) + (y * y) + (z * z) + (w * w);
}

Vec4 Vec4::normalized() const {
	return Vec4( *this ).Normalize();
}

Vec4& Vec4::Normalize() {
	float magnitude = (*this).magnitude();
	if ( magnitude < 1E-05f ) {
		return (*this = Vec4::zero);
	}

	*this /= magnitude;
	return *this;
}
