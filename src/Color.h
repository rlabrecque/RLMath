#pragma once

struct Vec4;

struct Color {
	static Vec4 HSL2RGB( const float h, const float s, const float l );
	//static Vec4 RGB2HSL( Vec4 rgb );
};
