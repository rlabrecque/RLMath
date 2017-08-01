#include "RLMath.h"

// Constructors

const Matrix4x4& Matrix4x4::zero = Matrix4x4();
const Matrix4x4& Matrix4x4::identity = Matrix4x4(
	Vec4( 1.0f, 0.0f, 0.0f, 0.0f ),
	Vec4( 0.0f, 1.0f, 0.0f, 0.0f ),
	Vec4( 0.0f, 0.0f, 1.0f, 0.0f ),
	Vec4( 0.0f, 0.0f, 0.0f, 1.0f )
);
