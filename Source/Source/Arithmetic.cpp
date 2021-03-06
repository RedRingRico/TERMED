#include <Arithmetic.h>
#include <cmath>

namespace TERMED
{
	bool IsZero( float p_Value )
	{
		return( fabs( p_Value ) < c_Epsilon );
	}

	float SquareRoot( float p_Value )
	{
		return sqrtf( p_Value );
	}

	bool IsEqual( float p_A, float p_B )
	{
		return IsZero( p_A - p_B );
	}

	void SinCos( const float p_Angle, float &p_Sine, float &p_Cosine )
	{
		p_Sine = sinf( p_Angle );
		p_Cosine = cosf( p_Angle );
	}
}
