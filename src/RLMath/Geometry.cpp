#include "RLMath.h"

Vec2 GetClosestPointOnRay( Ray ray, Vec2 point ) {
	Vec2 AP = point - ray.position;
	Vec2 AB = ray.direction - ray.position;

	float magnitudeAB = AB.squaredMagnitude();
	float ABAPproduct = Vec2::Dot( AP, AB );
	float distance = ABAPproduct / magnitudeAB;

	if ( distance < 0 ) {
		return ray.position;
	}
	else if ( distance > 1 ) {
		return ray.direction;
	}
	else {
		return ray.position + (AB * distance);
	}
}

/* TODO: Vec2 GetClosestPointOnRay( Ray ray, Vec2 TestPoint )
f32 GetClosestDistanceToLineSegment (vector3df TestPoint , vector3df LineStart, vector3df LineEnd)

vector3df GetClosestPointOnPlaneFromPoint (vector3df TestPoint , vector3df PlanePos, vector3df PlaneNormal)

f32 GetDistanceToPlaneFromPoint (vector3df TestPoint , vector3df PlanePos, vector3df PlaneNormal)*/
