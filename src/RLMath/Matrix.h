#pragma once
#include <utility>

//=====================================================================================================================
// Matrix
//=====================================================================================================================

struct Matrix4x4 {
	float data[4][4];

	// Constructors

	static const Matrix4x4& identity;
	static const Matrix4x4& zero;

	// Overrides
	inline float& operator[]( const int index );
	inline const float& operator[]( const int index ) const;
	inline float& operator[]( const std::pair<int, int>& index );
	inline const float& operator[]( const std::pair<int, int>& index ) const;

	inline Matrix4x4 operator* ( const Matrix4x4 other ) const;
	inline Matrix4x4& operator*=( const Matrix4x4 other );
	inline Vec4 Matrix4x4::operator*( const Vec4 v ) const;

	// Custom
	inline const char* ToString() const;
	inline float determinant() const;
	inline bool isIdentity( const float epsilon ) const;
	inline Matrix4x4 inverse() const;
	inline Matrix4x4& Inverse();
	inline Matrix4x4 transpose() const;
	inline Matrix4x4& Transpose();
	inline Vec4 GetRow( const int index ) const;
	inline Vec4 GetColumn( const int index ) const;
	inline void SetRow( const int index, const Vec4 row );
	inline void SetColumn( const int index, const Vec4 column );

	inline Vec2 MultiplyPoint2x4( Vec2 point ) const;
	inline Vec3 MultiplyPoint3x4( Vec3 point ) const;

	// Static functions
	static inline Matrix4x4 Translate( Vec2 v );
	static inline Matrix4x4 Translate( Vec3 v );
	static inline Matrix4x4 Rotate( Vec3 v );
	static inline Matrix4x4 Scale( Vec2 v );
	static inline Matrix4x4 Scale( Vec3 v );
	static inline Matrix4x4 TRS( Vec3 translate, Vec3 rotate, Vec3 scale );
};

#include "Matrix.inl"
