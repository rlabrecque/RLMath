#pragma once

//=====================================================================================================================
// Geometry
//=====================================================================================================================

struct Ray {
	Vec2 position;
	Vec2 direction;

	Ray() {}

	explicit Ray( Vec2 _position, Vec2 _direction ) {
		position = _position;
		direction = _direction;
	}

	bool operator==( const Ray& other ) const {
		return (position == other.position && direction == other.direction);
	}

	inline const char* ToString() const {
		static char str[47 * (sizeof( Ray ) / sizeof( float )) + 10];
		snprintf( str, sizeof( str ), "(%f, %f) (%f, %f)", position.x, position.y, direction.x, direction.y );

		return str;
	}
};



Vec2 GetClosestPointOnRay( Ray ray, Vec2 point );