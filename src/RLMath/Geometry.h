#pragma once

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
	Ray();
	explicit Ray( Vec2 _position, Vec2 _direction );

	// Overrides
	inline bool operator==( const Ray& other ) const;

	// Custom
	inline const char* ToString() const;
	
	// Distance and Collision detection
	Vec2 Ray::GetClosestPoint( Vec2 point ) const;

	// Static functions
};


//=====================================================================================================================
// AABB
//=====================================================================================================================
struct AABB {
	Vec2 center;
	Vec2 extents;

	// Constructors
	AABB();
	explicit AABB( Vec2 _center, Vec2 _extents);

	// Overrides
	inline bool operator==( const AABB& other ) const;

	// Custom
	inline const char* ToString() const;
	inline Vec2 mins() const;
	inline Vec2 maxs() const;
	inline Vec2 size() const;

	inline AABB& SetMinsMaxs( Vec2 mins, Vec2 maxs );

	// Distance and Collision detection
	//inline float DistanceTo( Vec2 point ) const;
	//inline float DistanceTo( AABB other ) const;
	inline bool ContainsPoint( Vec2 point ) const;
	inline bool Intersects( AABB other ) const;

	// Static functions
	inline static AABB FromMinsMaxs( Vec2 mins, Vec2 maxs );
};

//=====================================================================================================================
// Circle
//=====================================================================================================================
struct Circle {
	Vec2 center;
	float radius;

	// Constructors
	Circle();
	explicit Circle( Vec2 _center, float _radius );

	// Overrides
	inline bool operator==( const Circle& other ) const;

	// Custom
	inline const char* ToString() const;

	// Distance and Collision detection
	//inline float DistanceTo( Vec2 point ) const;
	//inline float DistanceTo( Circle other ) const;
	inline bool ContainsPoint( Vec2 point ) const;
	inline bool Intersects( Circle other ) const;

	// Static functions
};

#include "Geometry.inl"
