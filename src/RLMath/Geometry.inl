#pragma once

//=====================================================================================================================
// Ray
//=====================================================================================================================

// Constructors
constexpr Ray::Ray() : origin(Vec2()), direction(Vec2()) {}
inline Ray::Ray( Vec2 _position, Vec2 _direction ) : origin( _position ), direction(_direction.Normalize()) {}

// Overrides
inline bool Ray::operator==( const Ray& other ) const {
	return (origin == other.origin && direction == other.direction);
}

// Custom
inline const char* Ray::ToString() const {
	static char str[47 * (sizeof( Ray ) / sizeof( float )) + 10];
	snprintf( str, sizeof( str ), "(%f, %f) (%f, %f)", origin.x, origin.y, direction.x, direction.y );

	return str;
}

// Collision and Distance detection
inline Vec2 Ray::GetClosestPoint( const Vec2 point ) const {
	// Project point onto ray
	float t = Vec2::Dot( point - origin, direction );

	// We only want to clamp t in the positive direction.
	// The ray extends infinatley in this direction!
	t = RL_max( t, 0.0f );

	// Compute the projected position from the clamped t
	// Notice we multiply r.Normal by t, not AB.
	// This is becuase we want the ray in the direction 
	// of the normal, which technically the line segment is
	// but this is much more explicit and easy to read.
	return Vec2(origin + (direction * t));
}

// Static functions

//=====================================================================================================================
// AABB
//=====================================================================================================================

// Constructors
constexpr AABB::AABB() : origin( Vec2() ), extents( Vec2() ) {}
constexpr AABB::AABB( Vec2 _center, Vec2 _extents ) : origin( _center ), extents( RL_abs( _extents ) ) {}

// Overrides
bool AABB::operator==( const AABB& other ) const {
	return (origin == other.origin && extents == other.extents);
}

// Custom
inline const char* AABB::ToString() const {
	static char str[47 * (sizeof( AABB ) / sizeof( float )) + 10];
	snprintf( str, sizeof( str ), "(%f, %f) (%f, %f)", origin.x, origin.y, extents.x, extents.y );

	return str;
}

inline Vec2 AABB::mins() const {
	return origin - extents;
}

inline Vec2 AABB::maxs() const {
	return origin + extents;
}

inline Vec2 AABB::size() const {
	return extents * 2;
}

inline AABB& AABB::SetMinsMaxs( const Vec2 mins, const Vec2 maxs ) {
	origin = (mins + maxs) * 0.5f;
	extents = (mins - maxs) * 0.5f;
	return *this;
}

// Collision and Distance detection
inline Vec2 AABB::GetClosestPoint( const Vec2 point ) const {
	Vec2 closestPoint = point;

	Vec2 min = mins();
	Vec2 max = maxs();

	if ( closestPoint.x < min.x ) {
		closestPoint.x = min.x;
	}
	else if ( closestPoint.x > max.x ) {
		closestPoint.x = max.x;
	}

	if ( closestPoint.y < min.y ) {
		closestPoint.y = min.y;
	}
	else if ( closestPoint.y > max.y ) {
		closestPoint.y = max.y;
	}

	return closestPoint;
}

inline Vec2 AABB::GetClosestPoint( const AABB aabb ) const {
	Vec2 aMins = mins();
	Vec2 aMaxs = maxs();
	Vec2 bMins = aabb.mins();
	Vec2 bMaxs = aabb.maxs();

	Vec2 direction;

	return origin + Vec2::Scale( direction, extents );
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