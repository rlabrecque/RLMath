#pragma once

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
	return RL_sqrt( Dot( *this, *this ) );
}

float Vec2::squaredMagnitude() const {
	return Dot( *this, *this );
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
	return RL_sqrt( Dot( *this, *this ) );
}

float Vec3::squaredMagnitude() const {
	return Dot(*this, *this);
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
	return RL_sqrt( Dot(*this, *this) );
}

float Vec4::squaredMagnitude() const {
	return Dot( *this, *this );
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
