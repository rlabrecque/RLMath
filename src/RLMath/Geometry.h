#pragma once

struct Ray;
struct AABB;
struct Circle;

//=====================================================================================================================
// Geometry
//=====================================================================================================================

//=====================================================================================================================
// Ray
//=====================================================================================================================
struct Ray {
	Vec2 position;
	Vec2 direction;

	// Constructors
	constexpr Ray();
	inline explicit Ray( Vec2 _position, Vec2 _direction );

	// Overrides
	inline bool operator==( const Ray& other ) const;

	// Custom
	inline const char* ToString() const;
	
	// Distance and Collision detection
	inline Vec2 GetClosestPoint( const Vec2 point ) const;

	// Static functions
};

//=====================================================================================================================
// AABB
//=====================================================================================================================
struct AABB {
	Vec2 center;
	Vec2 extents;

	// Constructors
	constexpr AABB();
	constexpr explicit AABB( Vec2 _center, Vec2 _extents);

	// Overrides
	inline bool operator==( const AABB& other ) const;

	// Custom
	inline const char* ToString() const;
	inline Vec2 mins() const;
	inline Vec2 maxs() const;
	inline Vec2 size() const;

	inline AABB& SetMinsMaxs( Vec2 mins, Vec2 maxs );

	// Distance and Collision detection
	inline Vec2 GetClosestPoint( const Vec2 point ) const;

	// Static functions
	inline static AABB FromMinsMaxs( const Vec2 mins, const Vec2 maxs );
};

//=====================================================================================================================
// Circle
//=====================================================================================================================
struct Circle {
	Vec2 origin;
	float radius;

	// Constructors
	constexpr Circle();
	constexpr explicit Circle( Vec2 _center, float _radius );

	// Overrides
	inline bool operator==( const Circle& other ) const;

	// Custom
	inline const char* ToString() const;

	// Distance and Collision detection
	inline Vec2 GetClosestPoint( Vec2 point ) const;
	inline Vec2 GetClosestPoint( const Circle other ) const;

	// Static functions
};

#include "Geometry.inl"

inline bool RayIntersectsPoint( const Ray ray, const Vec2 point ) {
	if ( point == ray.position ) {
		return true;
	}
	
	Vec2 norm = (point - ray.position).Normalize();
	
	float diff = Vec2::Dot( norm, ray.direction );
	return diff >= (1 - 0.0005f);
}

inline bool RayIntersectsAABB( const Ray ray, const AABB aabb ) {
	// Slab method taken from:
	// https://tavianator.com/fast-branchless-raybounding-box-intersections/

	Vec2 mins = aabb.mins();
	Vec2 maxs = aabb.maxs();

	float t1 = (mins.x - ray.position.x) / ray.direction.x;
	float t2 = (maxs.x - ray.position.x) / ray.direction.x;

	float tmin = RL_min( t1, t2 );
	float tmax = RL_max( t1, t2 );

	t1 = (mins.y - ray.position.y) / ray.direction.y;
	t2 = (maxs.y - ray.position.y) / ray.direction.y;

	tmin = RL_max( tmin, RL_min( RL_min( t1, t2 ), tmax ) );
	tmax = RL_min( tmax, RL_max( RL_max( t1, t2 ), tmin ) );

	return tmax > RL_max( tmin, 0.0f );
}

inline bool RayIntersectsRay( const Ray ray, const Ray ray2 ) {
	return false;
}

inline bool AABBContainsPoint( const AABB aabb, const Vec2 point ) {
	Vec2 distance = RL_abs( aabb.center - point );
	return distance.x <= aabb.extents.x && distance.y <= aabb.extents.y;
}

inline bool AABBIntersectsAABB( const AABB aabb, const AABB aabb2 ) {
	Vec2 distance = RL_abs( aabb.center - aabb2.center );
	return distance.x <= (aabb.extents.x + aabb2.extents.x) && distance.y <= (aabb.extents.y + aabb2.extents.y);
}

inline bool AABBIntersectsCircle( const AABB aabb, const Circle circle ) {
	Vec2 closestPoint = circle.origin;

	Vec2 mins = aabb.mins();
	Vec2 maxs = aabb.maxs();

	if ( closestPoint.x < mins.x ) {
		closestPoint.x = mins.x;
	}
	else if ( closestPoint.x > maxs.x ) {
		closestPoint.x = maxs.x;
	}

	if ( closestPoint.y < mins.y ) {
		closestPoint.y = mins.y;
	}
	else if ( closestPoint.y > maxs.y ) {
		closestPoint.y = maxs.y;
	}

	return (circle.origin - closestPoint).squaredLength() <= circle.radius * circle.radius;
}

inline bool CircleContainsPoint( const Circle circle, const Vec2 point ) {
	return (point - circle.origin).length() <= circle.radius;
}

inline bool CircleIntersectsCircle( const Circle circle, const Circle circle2 ) {
	const float radiiSum = circle.radius + circle2.radius;
	return (circle.origin - circle2.origin).squaredLength() <= radiiSum * radiiSum;
}
