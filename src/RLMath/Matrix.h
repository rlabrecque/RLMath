#pragma once
#include <utility>

//=====================================================================================================================
// Matrix
//=====================================================================================================================

struct Matrix4x4 {
	float data[4][4];

	// Constructors
	constexpr Matrix4x4();
	constexpr explicit Matrix4x4( Vec4 row1, Vec4 row2, Vec4 row3, Vec4 row4 );

	static const Matrix4x4& identity;
	static const Matrix4x4& zero;

	// Overrides
	inline float& operator[]( const int index );
	inline const float& operator[]( const int index ) const;

	inline float& operator[]( const std::pair<int, int>& index );
	inline const float& operator[]( const std::pair<int, int>& index ) const;

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

	inline Vec3 MultiplyPoint3x4( Vec3 point ) const;
	inline Vec2 MultiplyPoint2x3( Vec2 point ) const;

	// Static functions
	static inline Matrix4x4 Translate( Vec2 v );
	static inline Matrix4x4 Translate( Vec3 v );
	static inline Matrix4x4 Scale( Vec2 v );
	static inline Matrix4x4 Scale( Vec3 v );
};

// Constructors
constexpr Matrix4x4::Matrix4x4() : data{ 0 } {}
constexpr Matrix4x4::Matrix4x4( Vec4 row1, Vec4 row2, Vec4 row3, Vec4 row4 ) :
	data{
		row1.x, row1.y, row1.z, row1.w,
		row2.x, row2.y, row2.z, row2.w,
		row3.x, row3.y, row3.z, row3.w,
		row4.x, row4.y, row4.z, row4.w } {}

// Overrides
inline float& Matrix4x4::operator[]( const int index ) {
	const int first = index % 4;
	const int second = index / 4;
	return data[first][second];
}

inline const float& Matrix4x4::operator[]( const int index ) const {
	const int first = index % 4;
	const int second = index / 4;
	return data[first][second];
}

inline float& Matrix4x4::operator[]( const std::pair<int, int>& index ) {
	return data[index.first][index.second];
}

inline const float& Matrix4x4::operator[]( const std::pair<int, int>& index ) const {
	return data[index.first][index.second];
}

// Custom
inline const char* Matrix4x4::ToString() const {
	constexpr int maxSize =
		FLOAT_MAX_PRINT_LENGTH * (sizeof( Matrix4x4 ) / sizeof( float )) // Maximum length of all the floats
		+ 24 // ", "
		+ 8 // Spacing up front
		+ 3 // \n
		+ 2 // Brackets
		+ 1; // NUL
	static char str[maxSize];
	snprintf( str, maxSize,
		"[ %f, %f, %f, %f\n"
		"  %f, %f, %f, %f\n"
		"  %f, %f, %f, %f\n"
		"  %f, %f, %f, %f ]",
		data[0][0], data[0][1],  data[0][2], data[0][3],
		data[1][0], data[1][1], data[1][2], data[1][3], 
		data[2][0], data[2][1], data[2][2], data[2][3], 
		data[3][0], data[3][1], data[3][2], data[3][3] );

	return str;
}

inline float Matrix4x4::determinant() const {
	return
		data[0][3] * data[1][2] * data[2][1] * data[3][0] - data[0][2] * data[1][3] * data[2][1] * data[3][0] -
		data[0][3] * data[1][1] * data[2][2] * data[3][0] + data[0][1] * data[1][3] * data[2][2] * data[3][0] +
		data[0][2] * data[1][1] * data[2][3] * data[3][0] - data[0][1] * data[1][2] * data[2][3] * data[3][0] -
		data[0][3] * data[1][2] * data[2][0] * data[3][1] + data[0][2] * data[1][3] * data[2][0] * data[3][1] +
		data[0][3] * data[1][0] * data[2][2] * data[3][1] - data[0][0] * data[1][3] * data[2][2] * data[3][1] -
		data[0][2] * data[1][0] * data[2][3] * data[3][1] + data[0][0] * data[1][2] * data[2][3] * data[3][1] +
		data[0][3] * data[1][1] * data[2][0] * data[3][2] - data[0][1] * data[1][3] * data[2][0] * data[3][2] -
		data[0][3] * data[1][0] * data[2][1] * data[3][2] + data[0][0] * data[1][3] * data[2][1] * data[3][2] +
		data[0][1] * data[1][0] * data[2][3] * data[3][2] - data[0][0] * data[1][1] * data[2][3] * data[3][2] -
		data[0][2] * data[1][1] * data[2][0] * data[3][3] + data[0][1] * data[1][2] * data[2][0] * data[3][3] +
		data[0][2] * data[1][0] * data[2][1] * data[3][3] - data[0][0] * data[1][2] * data[2][1] * data[3][3] -
		data[0][1] * data[1][0] * data[2][2] * data[3][3] + data[0][0] * data[1][1] * data[2][2] * data[3][3];
}

inline bool Matrix4x4::isIdentity( const float epsilon = 0.0003f ) const {
	for ( int i = 0; i < 4; ++i ) {
		for ( int j = 0; j < 4; ++j ) {
			if ( i == j ) {
				if ( RL_abs( data[i][j] - 1 ) > epsilon )
					return false;
			}
			else {
				if ( RL_abs( data[i][j] ) > epsilon )
					return false;
			}
		}
	}

	return true;
}

inline Matrix4x4 Matrix4x4::transpose() const {
	return Matrix4x4( *this ).Transpose();
}

inline Matrix4x4& Matrix4x4::Transpose() {
	Vec4 row0 = GetRow( 0 );
	Vec4 row1 = GetRow( 1 );
	Vec4 row2 = GetRow( 2 );
	Vec4 row3 = GetRow( 3 );
	SetColumn( 0, row0 );
	SetColumn( 1, row1 );
	SetColumn( 2, row2 );
	SetColumn( 3, row3 );
	
	return *this;
}

inline Matrix4x4 Matrix4x4::inverse() const {
	return Matrix4x4( *this ).Inverse();
}

inline Matrix4x4& Matrix4x4::Inverse() {
	const float A2323 = data[2][2] * data[3][3] - data[2][3] * data[3][2];
	const float A1323 = data[2][1] * data[3][3] - data[2][3] * data[3][1];
	const float A1223 = data[2][1] * data[3][2] - data[2][2] * data[3][1];
	const float A0323 = data[2][0] * data[3][3] - data[2][3] * data[3][0];
	const float A0223 = data[2][0] * data[3][2] - data[2][2] * data[3][0];
	const float A0123 = data[2][0] * data[3][1] - data[2][1] * data[3][0];
	const float A2313 = data[1][2] * data[3][3] - data[1][3] * data[3][2];
	const float A1313 = data[1][1] * data[3][3] - data[1][3] * data[3][1];
	const float A1213 = data[1][1] * data[3][2] - data[1][2] * data[3][1];
	const float A2312 = data[1][2] * data[2][3] - data[1][3] * data[2][2];
	const float A1312 = data[1][1] * data[2][3] - data[1][3] * data[2][1];
	const float A1212 = data[1][1] * data[2][2] - data[1][2] * data[2][1];
	const float A0313 = data[1][0] * data[3][3] - data[1][3] * data[3][0];
	const float A0213 = data[1][0] * data[3][2] - data[1][2] * data[3][0];
	const float A0312 = data[1][0] * data[2][3] - data[1][3] * data[2][0];
	const float A0212 = data[1][0] * data[2][2] - data[1][2] * data[2][0];
	const float A0113 = data[1][0] * data[3][1] - data[1][1] * data[3][0];
	const float A0112 = data[1][0] * data[2][1] - data[1][1] * data[2][0];

	const float det = 1 / (data[0][0] * (data[1][1] * A2323 - data[1][2] * A1323 + data[1][3] * A1223)
		- data[0][1] * (data[1][0] * A2323 - data[1][2] * A0323 + data[1][3] * A0223)
		+ data[0][2] * (data[1][0] * A1323 - data[1][1] * A0323 + data[1][3] * A0123)
		- data[0][3] * (data[1][0] * A1223 - data[1][1] * A0223 + data[1][2] * A0123));

	data[0][0] = det *   (data[1][1] * A2323 - data[1][2] * A1323 + data[1][3] * A1223);
	data[0][1] = det * -(data[0][1] * A2323 - data[0][2] * A1323 + data[0][3] * A1223);
	data[0][2] = det *   (data[0][1] * A2313 - data[0][2] * A1313 + data[0][3] * A1213);
	data[0][3] = det * -(data[0][1] * A2312 - data[0][2] * A1312 + data[0][3] * A1212);
	data[1][0] = det * -(data[1][0] * A2323 - data[1][2] * A0323 + data[1][3] * A0223);
	data[1][1] = det *   (data[0][0] * A2323 - data[0][2] * A0323 + data[0][3] * A0223);
	data[1][2] = det * -(data[0][0] * A2313 - data[0][2] * A0313 + data[0][3] * A0213);
	data[1][3] = det *   (data[0][0] * A2312 - data[0][2] * A0312 + data[0][3] * A0212);
	data[2][0] = det *   (data[1][0] * A1323 - data[1][1] * A0323 + data[1][3] * A0123);
	data[2][1] = det * -(data[0][0] * A1323 - data[0][1] * A0323 + data[0][3] * A0123);
	data[2][2] = det *   (data[0][0] * A1313 - data[0][1] * A0313 + data[0][3] * A0113);
	data[2][3] = det * -(data[0][0] * A1312 - data[0][1] * A0312 + data[0][3] * A0112);
	data[3][0] = det * -(data[1][0] * A1223 - data[1][1] * A0223 + data[1][2] * A0123);
	data[3][1] = det *   (data[0][0] * A1223 - data[0][1] * A0223 + data[0][2] * A0123);
	data[3][2] = det * -(data[0][0] * A1213 - data[0][1] * A0213 + data[0][2] * A0113);
	data[3][3] = det *   (data[0][0] * A1212 - data[0][1] * A0212 + data[0][2] * A0112);

	return *this;
}

inline Vec4 Matrix4x4::GetRow( const int index ) const {
	return Vec4( data[index][0], data[index][1], data[index][2], data[index][3] );
}

inline Vec4 Matrix4x4::GetColumn( const int index ) const {
	return Vec4( data[0][index], data[1][index], data[2][index], data[3][index] );
}

inline void Matrix4x4::SetRow( const int index, const Vec4 row ) {
	data[index][0] = row.x;
	data[index][1] = row.y;
	data[index][2] = row.z;
	data[index][3] = row.w;
}

inline void Matrix4x4::SetColumn( const int index, const Vec4 column ) {
	data[0][index] = column.x;
	data[1][index] = column.y;
	data[2][index] = column.z;
	data[3][index] = column.w;
}

inline Vec3 Matrix4x4::MultiplyPoint3x4( Vec3 point ) const {
	Vec3 result;
	result.x = data[0][0] * point.x + data[0][1] * point.y + data[0][2] * point.z + data[0][3];
	result.y = data[1][0] * point.x + data[1][1] * point.y + data[1][2] * point.z + data[1][3];
	result.z = data[2][0] * point.x + data[2][1] * point.y + data[2][2] * point.z + data[2][3];
	return result;
}

inline Vec2 Matrix4x4::MultiplyPoint2x3( Vec2 point ) const {
	Vec2 result;
	result.x = data[0][0] * point.x + data[0][1] * point.y + data[0][2];
	result.y = data[1][0] * point.x + data[1][1] * point.y + data[1][2];
	return result;
}

// Static functions
inline Matrix4x4 Matrix4x4::Scale( Vec2 v ) {
	Matrix4x4 ret = Matrix4x4::identity;
	ret[{0, 0}] = v.x;
	ret[{1, 1}] = v.y;
	return ret;
}

inline Matrix4x4 Matrix4x4::Scale( Vec3 v ) {
	Matrix4x4 ret = Matrix4x4::identity;
	ret[{0, 0}] = v.x;
	ret[{1, 1}] = v.y;
	ret[{2, 2}] = v.z;
	return ret;
}

inline Matrix4x4 Matrix4x4::Translate( Vec2 v ) {
	Matrix4x4 ret = Matrix4x4::identity;
	ret[{0, 3}] = v.x;
	ret[{1, 3}] = v.y;
	return ret;
}

inline Matrix4x4 Matrix4x4::Translate( Vec3 v ) {
	Matrix4x4 ret = Matrix4x4::identity;
	ret[{0, 3}] = v.x;
	ret[{1, 3}] = v.y;
	ret[{2, 3}] = v.z;
	return ret;
}

