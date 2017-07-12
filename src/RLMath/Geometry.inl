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
inline Vec2 Ray::GetClosestPoint( Vec2 point ) const {
	Vec2 diff = point - position;

	float paramater = Vec2::Dot( direction, diff );
	if ( paramater > 0 ) {
		return position + (direction * paramater);
	}
	else {
		return position;
	}
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

inline AABB& AABB::SetMinsMaxs( Vec2 mins, Vec2 maxs ) {
	center = (mins + maxs) * 0.5f;
	extents = (mins - maxs) * 0.5f;
	return *this;
}

// Collision and Distance detection
inline Vec2 AABB::GetClosestPoint( Vec2 point ) const {
	Vec2 direction = (point - center).Normalize();
	return Vec2( center + Vec2::Scale(direction, extents) );
}

inline bool AABB::ContainsPoint( Vec2 point ) const {
	Vec2 distance = RL_abs(center - point);
	return distance.x <= extents.x && distance.y <= extents.y;
}

inline bool AABB::Intersects( AABB other ) const {
	Vec2 distance = RL_abs( center - other.center );
	return distance.x <= (extents.x + other.extents.x) && distance.y <= ( extents.y + other.extents.y );
}

// Static functions
inline AABB AABB::FromMinsMaxs( Vec2 mins, Vec2 maxs ) {
	return AABB( (mins + maxs) * 0.5f, (mins - maxs) * 0.5f );
}

//=====================================================================================================================
// Circle
//=====================================================================================================================

// Constructors
constexpr Circle::Circle() : center( Vec2() ), radius( 0 ) {}
constexpr Circle::Circle( Vec2 _center, float _radius ) : center( _center ), radius( RL_abs( _radius ) ) {}

// Overrides
inline bool Circle::operator==( const Circle& other ) const {
	return (center == other.center && radius == other.radius);
}

// Custom
inline const char* Circle::ToString() const {
	static char str[47 * (sizeof( Circle ) / sizeof( float )) + 6];
	snprintf( str, sizeof( str ), "(%f, %f) %f", center.x, center.y, radius );

	return str;
}

// Collision and distance detection
inline Vec2 Circle::GetClosestPoint( Vec2 point ) const {
	Vec2 direction = (point - center).Normalize();
	return Vec2( center + direction * radius );
}

inline Vec2 Circle::GetClosestPoint( Circle other ) const {
	Vec2 direction = (other.center - center).Normalize();
	return Vec2( center + direction * radius );
}


inline bool Circle::ContainsPoint( Vec2 point ) const {
	return (point - center).length() <= radius;
}

inline bool Circle::Intersects( Circle other ) const {
	return (center - other.center).length() <= (radius + other.radius);
}

// Static functions