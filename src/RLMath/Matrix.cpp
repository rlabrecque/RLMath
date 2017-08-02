#include "pch.h"

// Constructors
static constexpr float identity_matrix[4][4] = {
	{ 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f }
};

const Matrix4x4& Matrix4x4::zero = Matrix4x4();
const Matrix4x4& Matrix4x4::identity = Matrix4x4( identity_matrix );
