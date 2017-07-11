#include "RLMath.h"

//=====================================================================================================================
// Ray
//=====================================================================================================================

Ray::Ray() {
}

Ray::Ray( Vec2 _position, Vec2 _direction ) {
	position = _position;
	direction = _direction;
}

Vec2 Ray::GetClosestPoint( Vec2 point ) const {
	Vec2 AP = point - position;
	Vec2 AB = direction - position;

	float magnitudeAB = AB.squaredMagnitude();
	float ABAPproduct = Vec2::Dot( AB, AP );
	float distance = ABAPproduct / magnitudeAB;

	if ( distance < 0 ) {
		return position;
	}
	else if ( distance > 1 ) {
		return direction;
	}
	else {
		return position + (AB * distance);
	}
}

//=====================================================================================================================
// AABB
//=====================================================================================================================

AABB::AABB() {
}

AABB::AABB( Vec2 _center, Vec2 _extents ) {
	center = _center;
	extents = RL_abs(_extents);
}

//=====================================================================================================================
// Circle
//=====================================================================================================================

Circle::Circle() {}

Circle::Circle( Vec2 _center, float _radius ) {
	center = _center;
	radius = RL_abs( _radius );
}

//=====================================================================================================================
// Functions TODO
//=====================================================================================================================

/* TODO: Vec2 GetClosestPointOnRay( Ray ray, Vec2 TestPoint )
f32 GetClosestDistanceToLineSegment (vector3df TestPoint , vector3df LineStart, vector3df LineEnd)

vector3df GetClosestPointOnPlaneFromPoint (vector3df TestPoint , vector3df PlanePos, vector3df PlaneNormal)

f32 GetDistanceToPlaneFromPoint (vector3df TestPoint , vector3df PlanePos, vector3df PlaneNormal)*/
