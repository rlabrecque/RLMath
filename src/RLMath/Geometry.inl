#pragma once

//=====================================================================================================================
// Ray
//=====================================================================================================================

// Constructors
constexpr Ray::Ray() : position(Vec2()), direction(Vec2()) {}
inline Ray::Ray( Vec2 _position, Vec2 _direction ) : position( _position ), direction(_direction.Normalize()) {}

// Overrides
inline bool Ray::operator==( const Ray& other ) const {
	return (position == other.position && direction == other.direction);
}

// Custom
inline const char* Ray::ToString() const {
	static char str[47 * (sizeof( Ray ) / sizeof( float )) + 10];
	snprintf( str, sizeof( str ), "(%f, %f) (%f, %f)", position.x, position.y, direction.x, direction.y );

	return str;
}

// Collision and Distance detection
inline Vec2 Ray::GetClosestPoint( const Vec2 point ) const {
	// Project point onto ray
	float t = Vec2::Dot( point - position, direction );

	// We only want to clamp t in the positive direction.
	// The ray extends infinatley in this direction!
	t = RL_max( t, 0.0f );

	// Compute the projected position from the clamped t
	// Notice we multiply r.Normal by t, not AB.
	// This is becuase we want the ray in the direction 
	// of the normal, which technically the line segment is
	// but this is much more explicit and easy to read.
	return Vec2(position + (direction * t));
}

// Static functions

//=====================================================================================================================
// AABB
//=====================================================================================================================

// Constructors
constexpr AABB::AABB() : center( Vec2() ), extents( Vec2() ) {}
constexpr AABB::AABB( Vec2 _center, Vec2 _extents ) : center( _center ), extents( RL_abs( _extents ) ) {}

// Overrides
bool AABB::operator==( const AABB& other ) const {
	return (center == other.center && extents == other.extents);
}

// Custom
inline const char* AABB::ToString() const {
	static char str[47 * (sizeof( AABB ) / sizeof( float )) + 10];
	snprintf( str, sizeof( str ), "(%f, %f) (%f, %f)", center.x, center.y, extents.x, extents.y );

	return str;
}

inline Vec2 AABB::mins() const {
	return center - extents;
}

inline Vec2 AABB::maxs() const {
	return center + extents;
}

inline Vec2 AABB::size() const {
	return extents * 2;
}

inline AABB& AABB::SetMinsMaxs( const Vec2 mins, const Vec2 maxs ) {
	center = (mins + maxs) * 0.5f;
	extents = (mins - maxs) * 0.5f;
	return *this;
}

// Collision and Distance detection
inline Vec2 AABB::GetClosestPoint( const Vec2 point ) const {
	float s, d = 0;

	if ( point.x < mins().x ) {
		s = point.x - mins().x;
		d += s*s;
	}
	else if (point.x > maxs().x) {
		s = point.x + maxs().x;
		d += s*s;
	}

	if ( point.y < mins().y ) {
		s = point.y - mins().y;
		d += s*s;
	}
	else if ( point.y > maxs().y ) {
		s = point.y + maxs().y;
		d += s*s;
	}

	return Vec2(center.x + d, center.y + d);
}

// Static functions
inline AABB AABB::FromMinsMaxs( const Vec2 mins, const Vec2 maxs ) {
	return AABB( (mins + maxs) * 0.5f, (mins - maxs) * 0.5f );
}

//=====================================================================================================================
// Circle
//=====================================================================================================================

// Constructors
constexpr Circle::Circle() : origin( Vec2() ), radius( 0 ) {}
constexpr Circle::Circle( Vec2 _center, float _radius ) : origin( _center ), radius( RL_abs( _radius ) ) {}

// Overrides
inline bool Circle::operator==( const Circle& other ) const {
	return (origin == other.origin && radius == other.radius);
}

// Custom
inline const char* Circle::ToString() const {
	static char str[47 * (sizeof( Circle ) / sizeof( float )) + 6];
	snprintf( str, sizeof( str ), "(%f, %f) %f", origin.x, origin.y, radius );

	return str;
}

// Collision and distance detection
inline Vec2 Circle::GetClosestPoint( const Vec2 point ) const {
	Vec2 direction = (point - origin).Normalize();
	return Vec2( origin + direction * radius );
}

inline Vec2 Circle::GetClosestPoint( const Circle other ) const {
	Vec2 direction = (other.origin - origin).Normalize();
	return Vec2( origin + direction * radius );
}

// Static functions