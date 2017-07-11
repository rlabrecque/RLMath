#pragma once

//=====================================================================================================================
// Ray
//=====================================================================================================================

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

// Static functions
//=====================================================================================================================
// AABB
//=====================================================================================================================

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
inline bool Circle::ContainsPoint( Vec2 point ) const {
	return (point - center).magnitude() <= radius;
}

inline bool Circle::Intersects( Circle other ) const {
	return (center - other.center).magnitude() <= (radius + other.radius);
}

// Static functions