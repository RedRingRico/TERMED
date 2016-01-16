#ifndef __TERMED_ARITHMETIC_H__
#define __TERMED_ARITHMETIC_H__

namespace TERMED
{
	const float c_Epsilon = 1.0e-10f;
	const float c_HalfEpsilon = 1.0e-5f;
	const float c_Pi = 3.1415926535897932384626433832795f;
	const float c_PiOver360 = c_Pi / 360.0f;

	bool IsZero( float p_Value );
	float SquareRoot( float p_Value );
	bool IsEqual( float p_A, float p_B );
	void SinCos( const float p_Angle, float &p_Sine, float &p_Cosine );
}

#endif // __TERMED_ARITHMETIC_H__
