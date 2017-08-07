#include "pch.h"
#include "Color.h"

static float HUE2RGB( float p, float q, float t ) {
	if ( t < 0.0f ) t += 1.0f;
	if ( t > 1.0f ) t -= 1.0f;
	if ( t < 1.0f / 6.0f ) return p + (q - p) * 6.0f * t;
	if ( t < 1.0f / 2.0f ) return q;
	if ( t < 2.0f / 3.0f ) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
	return p;
}

Vec4 Color::HSL2RGB( const float h, const float s, const float l ) {
	if ( s == 0.0f ) {
		return Vec4( l, l, l, 1 ); // achromatic
	}

	Vec4 rgb;
	float q = (l < 0.5f) ? (l * (1.0f + s)) : (l + s - l * s);
	float p = 2 * l - q;
	rgb[0] = HUE2RGB( p, q, h + 1.0f / 3.0f );
	rgb[1] = HUE2RGB( p, q, h );
	rgb[2] = HUE2RGB( p, q, h - 1.0f / 3.0f );
	rgb[3] = 1.0f;
	
	return rgb;
}

/*Vec4 Color::RGB2HSL( Vec4 rgb ) {
	return Vec4();
}*/
