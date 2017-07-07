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
};
