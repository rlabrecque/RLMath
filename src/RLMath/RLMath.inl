#pragma once

//=================
// abs
//=================
inline Vec2 RL_abs( const Vec2 vec ) {
	return Vec2( RL_abs( vec.x ), RL_abs( vec.y ) );
}

inline Vec3 RL_abs( const Vec3 vec ) {
	return Vec3( RL_abs( vec.x ), RL_abs( vec.y ), RL_abs( vec.z ) );
}

inline Vec4 RL_abs( const Vec4 vec ) {
	return Vec4( RL_abs( vec.x ), RL_abs( vec.y ), RL_abs( vec.z ), RL_abs( vec.w ) );
}

//=================
// sqrt
//=================
float RL_sqrt( const float f ) {
	return sqrtf( f );
}

inline Vec2 RL_sqrt( const Vec2 vec ) {
	return Vec2( RL_sqrt( vec.x ), RL_sqrt( vec.y ) );
}

inline Vec3 RL_sqrt( const Vec3 vec ) {
	return Vec3( RL_sqrt( vec.x ), RL_sqrt( vec.y ), RL_sqrt( vec.z ) );
}

inline Vec4 RL_sqrt( const Vec4 vec ) {
	return Vec4( RL_sqrt( vec.x ), RL_sqrt( vec.y ), RL_sqrt( vec.z ), RL_sqrt( vec.w ) );
}

//=================
// sin
//=================
float RL_sin( const float f ) {
	return sinf( f );
}

inline Vec2 RL_sin( const Vec2 vec ) {
	return Vec2( RL_sin( vec.x ), RL_sin( vec.y ) );
}

inline Vec3 RL_sin( const Vec3 vec ) {
	return Vec3( RL_sin( vec.x ), RL_sin( vec.y ), RL_sin( vec.z ) );
}

inline Vec4 RL_sin( const Vec4 vec ) {
	return Vec4( RL_sin( vec.x ), RL_sin( vec.y ), RL_sin( vec.z ), RL_sin( vec.w ) );
}


//=================
// cos
//=================
float RL_cos( const float f ) {
	return cosf( f );
}

inline Vec2 RL_cos( const Vec2 vec ) {
	return Vec2( RL_cos( vec.x ), RL_cos( vec.y ) );
}

inline Vec3 RL_cos( const Vec3 vec ) {
	return Vec3( RL_cos( vec.x ), RL_cos( vec.y ), RL_cos( vec.z ) );
}

inline Vec4 RL_cos( const Vec4 vec ) {
	return Vec4( RL_cos( vec.x ), RL_cos( vec.y ), RL_cos( vec.z ), RL_cos( vec.w ) );
}
