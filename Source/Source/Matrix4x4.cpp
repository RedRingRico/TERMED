#include <Matrix4x4.h>
#include <Arithmetic.h>
#include <cstring>

namespace TERMED
{
	Matrix4x4::Matrix4x4( )
	{
		this->SetAsIdentity( );
	}

	Matrix4x4::Matrix4x4( const Matrix4x4 &p_Matrix )
	{
		memcpy( m_M, p_Matrix.m_M, sizeof( m_M ) );
	}

	Matrix4x4::~Matrix4x4( )
	{
	}

	void Matrix4x4::SetAsIdentity( )
	{
		m_M[ 0 ] = m_M[ 5 ] = m_M[ 10 ] = m_M[ 15 ] = 1.0f;
		m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 4 ] =
			m_M[ 6 ] = m_M[ 7 ] = m_M[ 8 ] = m_M[ 9 ] =
			m_M[ 11 ] = m_M[ 12 ] = m_M[ 13 ] = m_M[ 14 ] = 0.0f;
	}

	Matrix4x4 &Matrix4x4::CreateTranslation( const Vector3 &p_Translate )
	{
		m_M[ 0 ] = 1.0f;
		m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 4 ] = 0.0f;
		m_M[ 5 ] = 1.0f;
		m_M[ 6 ] = m_M[ 7 ] = m_M[ 8 ] = m_M[ 9 ] = 0.0f;
		m_M[ 10 ] = 1.0f;
		m_M[ 12 ] = p_Translate.GetX( );
		m_M[ 13 ] = p_Translate.GetY( );
		m_M[ 14 ] = p_Translate.GetZ( );
		m_M[ 15 ] = 1.0f;

		return *this;
	}

	Matrix4x4 &Matrix4x4::CreateRotation( float p_Angle, const Vector3 &p_Axis )
	{
		float Cos, Sin;
		float X = p_Axis.GetX( );
		float Y = p_Axis.GetY( );
		float Z = p_Axis.GetZ( );		

		float XX = X*X;
		float XY = X*Y;
		float XZ = X*Z;

		float YY = Y*Y;
		float YZ = Y*Z;
		
		float ZZ = Z*Z;

		TERMED::SinCos( p_Angle, Sin, Cos );

		m_M[ 0 ] = XX * ( 1.0f - Cos ) + Cos;
		m_M[ 1 ] = XY * ( 1.0f - Cos ) + X * Sin;
		m_M[ 2 ] = XZ * ( 1.0f - Cos ) - Y * Sin;
		m_M[ 3 ] = 0.0f;

		m_M[ 4 ] = XY * ( 1.0f - Cos ) - Z * Sin;
		m_M[ 5 ] = YY * ( 1.0f - Cos ) * Cos;
		m_M[ 6 ] = YZ * ( 1.0f - Cos ) + X * Sin;
		m_M[ 7 ] = 0.0f;

		m_M[ 8 ] = XZ * ( 1.0f - Cos ) + Y * Sin;
		m_M[ 9 ] = YZ * ( 1.0f - Cos ) - X * Sin;
		m_M[ 10 ] = ZZ * ( 1.0f - Cos ) + Cos;

		m_M[ 12 ] = m_M[ 13 ] = m_M[ 14 ] = 0.0f;
		m_M[ 15 ] = 1.0f;

		return *this;
	}

	Matrix4x4 &Matrix4x4::CreateRotationX( float p_X )
	{
		float Sin, Cos;
		TERMED::SinCos( p_X, Sin, Cos );

		m_M[ 0 ] = 1.0f;
		m_M[ 1 ] = 0.0f;
		m_M[ 2 ] = 0.0f;
		m_M[ 3 ] = 0.0f;
		
		m_M[ 4 ] = 0.0f;
		m_M[ 5 ] = Cos;
		m_M[ 6 ] = Sin;
		m_M[ 7 ] = 0.0f;

		m_M[ 8 ] = 0.0f;
		m_M[ 9 ] = -Sin;
		m_M[ 10 ] = Cos;
		m_M[ 11 ] = 0.0f;

		m_M[ 12 ] = 0.0f;
		m_M[ 13 ] = 0.0f;
		m_M[ 14 ] = 0.0f;
		m_M[ 15 ] = 1.0f;

		return *this;
	}

	Matrix4x4 &Matrix4x4::CreateRotationY( float p_Y )
	{
		float Sin, Cos;

		TERMED::SinCos( p_Y, Sin, Cos );

		m_M[ 0 ] = Cos;
		m_M[ 1 ] = 0.0f;
		m_M[ 2 ] = -Sin;
		m_M[ 3 ] = 0.0f;
		
		m_M[ 4 ] = 0.0f;
		m_M[ 5 ] = 1.0f;
		m_M[ 6 ] = 0.0f;
		m_M[ 7 ] = 0.0f;

		m_M[ 8 ] = Sin;
		m_M[ 9 ] = 0.0f;
		m_M[ 10 ] = Cos;
		m_M[ 11 ] = 0.0f;

		m_M[ 12 ] = 0.0f;
		m_M[ 13 ] = 0.0f;
		m_M[ 14 ] = 0.0f;
		m_M[ 15 ] = 1.0f;

		return *this;
	}

	Matrix4x4 &Matrix4x4::CreateRotationZ( float p_Z )
	{
		float Sin, Cos;

		TERMED::SinCos( p_Z, Sin, Cos );

		m_M[ 0 ] = Cos;
		m_M[ 1 ] = Sin;
		m_M[ 2 ] = 0.0f;
		m_M[ 3 ] = 0.0f;
		
		m_M[ 4 ] = -Sin;
		m_M[ 5 ] = Cos;
		m_M[ 6 ] = 0.0f;
		m_M[ 7 ] = 0.0f;

		m_M[ 8 ] = 0.0f;
		m_M[ 9 ] = 0.0f;
		m_M[ 10 ] = 1.0f;
		m_M[ 11 ] = 0.0f;

		m_M[ 12 ] = 0.0f;
		m_M[ 13 ] = 0.0f;
		m_M[ 14 ] = 0.0f;
		m_M[ 15 ] = 1.0f;

		return *this;
	}

	Matrix4x4 &Matrix4x4::CreateScale( float p_Scale )
	{
		m_M[ 0 ] = m_M[ 5 ] = m_M[ 10 ] = p_Scale;
		m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 4 ] =
			m_M[ 6 ] = m_M[ 7 ] = m_M[ 8 ] = m_M[ 9 ] =
			m_M[ 11 ] = m_M[ 12 ] = m_M[ 13 ] = m_M[ 14 ] = 0.0f;
		m_M[ 15 ] = 1.0f;


		return *this;
	}

	Matrix4x4 &Matrix4x4::CreateScale( const Vector3 &p_Scale )
	{
		m_M[ 0 ] = p_Scale.GetX( );
		m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 4 ] = 0.0f;
		m_M[ 5 ] = p_Scale.GetY( );
		m_M[ 6 ] = m_M[ 7 ] = m_M[ 8 ] = m_M[ 9 ] = 0.0f;
		m_M[ 10 ] = p_Scale.GetZ( );
		m_M[ 11 ] = m_M[ 12 ] = m_M[ 13 ] = m_M[ 14 ] = 0.0f;
		m_M[ 15 ] = 1.0f;

		return *this;
	}

	Matrix4x4 &Matrix4x4::CreateScaleX( float p_X )
	{
		m_M[ 0 ] = p_X;
		m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 4 ] = 0.0f;
		m_M[ 5 ] = 1.0f;
		m_M[ 6 ] = m_M[ 7 ] = m_M[ 8 ] = m_M[ 9 ] = 0.0f;
		m_M[ 10 ] = 1.0f;
		m_M[ 11 ] = m_M[ 12 ] = m_M[ 13 ] = m_M[ 14 ] = 0.0f;
		m_M[ 15 ] = 1.0f;

		return *this;
	}

	Matrix4x4 &Matrix4x4::CreateScaleY( float p_Y )
	{
		m_M[ 0 ] = 1.0f;
		m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 4 ] = 0.0f;
		m_M[ 5 ] = p_Y;
		m_M[ 6 ] = m_M[ 7 ] = m_M[ 8 ] = m_M[ 9 ] = 0.0f;
		m_M[ 10 ] = 1.0f;
		m_M[ 11 ] = m_M[ 12 ] = m_M[ 13 ] = m_M[ 14 ] = 0.0f;
		m_M[ 15 ] = 1.0f;

		return *this;
	}

	Matrix4x4 &Matrix4x4::CreateScaleZ( float p_Z )
	{
		m_M[ 0 ] = 1.0f;
		m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 4 ] = 0.0f;
		m_M[ 5 ] = 1.0f;
		m_M[ 6 ] = m_M[ 7 ] = m_M[ 8 ] = m_M[ 9 ] = 0.0f;
		m_M[ 10 ] = p_Z;
		m_M[ 11 ] = m_M[ 12 ] = m_M[ 13 ] = m_M[ 14 ] = 0.0f;
		m_M[ 15 ] = 1.0f;

		return *this;
	}

	bool Matrix4x4::IsZero( ) const
	{
		for( size_t i = 0; i < 16; ++i )
		{
			if( !TERMED::IsZero( m_M[ i ] ) )
			{
				return false;
			}
		}

		return true;
	}

	bool Matrix4x4::IsIdentity( ) const
	{
		if(
			( m_M[ 0 ] == 1.0f ) &&
			( m_M[ 1 ] == 0.0f ) &&
			( m_M[ 2 ] == 0.0f ) &&
			( m_M[ 3 ] == 0.0f ) &&
			( m_M[ 4 ] == 0.0f ) &&
			( m_M[ 5 ] == 1.0f ) &&
			( m_M[ 6 ] == 0.0f ) &&
			( m_M[ 7 ] == 0.0f ) &&
			( m_M[ 8 ] == 0.0f ) &&
			( m_M[ 9 ] == 0.0f ) &&
			( m_M[ 10 ] == 1.0f ) &&
			( m_M[ 11 ] == 0.0f ) &&
			( m_M[ 12 ] == 0.0f ) &&
			( m_M[ 13 ] == 0.0f ) &&
			( m_M[ 14 ] == 0.0f ) &&
			( m_M[ 15 ] == 1.0f ) )
		{
			return true;
		}

		return false;
	}

	void Matrix4x4::CopyToFloatArray( float *p_pMatrix ) const
	{
		memcpy( p_pMatrix, m_M, sizeof( m_M ) );
	}

	void Matrix4x4::Clean( )
	{
		for( size_t i = 0; i < 16; ++i )
		{
			if( TERMED::IsZero( m_M[ i ] ) )
			{
				m_M[ i ] = 0.0f;
			}
		}
	}

	Matrix4x4 &Matrix4x4::Transpose( )
	{
		float Temp = m_M[ 1 ];
		m_M[ 1 ] = m_M[ 4 ];
		m_M[ 4 ] = Temp;

		Temp = m_M[ 2 ];
		m_M[ 2 ] = m_M[ 8 ];
		m_M[ 8 ] = Temp;

		Temp = m_M[ 3 ];
		m_M[ 3 ] = m_M[ 12 ];
		m_M[ 12 ] = Temp;

		Temp = m_M[ 6 ];
		m_M[ 6 ] = m_M[ 9 ];
		m_M[ 9 ] = Temp;

		Temp = m_M[ 7 ];
		m_M[ 7 ] = m_M[ 13 ];
		m_M[ 13 ] = Temp;

		Temp = m_M[ 11 ];
		m_M[ 11 ] = m_M[ 14 ];
		m_M[ 14 ] = Temp;

		return *this;
	}

	void Matrix4x4::Transpose( Matrix4x4 &p_Matrix ) const
	{
		p_Matrix = *this;

		p_Matrix.Transpose( );
	}

	Matrix4x4 &Matrix4x4::CreateTransposeFrom( const Matrix4x4 &p_Matrix )
	{
		*this = p_Matrix;
		this->Transpose( );

		return *this;
	}

	float Matrix4x4::GetTrace( ) const
	{
		return m_M[ 0 ] + m_M[ 5 ] + m_M[ 10 ] + m_M[ 15 ];
	}

	Matrix4x4 Matrix4x4::operator*( const Matrix4x4 &p_Matrix ) const
	{
		Matrix4x4 Multiply;

		/*Multiply.m_M[ 0 ] =	m_M[ 0 ] * p_Matrix.m_M[ 0 ] +
							m_M[ 1 ] * p_Matrix.m_M[ 4 ] +
							m_M[ 2 ] * p_Matrix.m_M[ 8 ] +
							m_M[ 3 ] * p_Matrix.m_M[ 12 ];
		Multiply.m_M[ 1 ] =	m_M[ 0 ] * p_Matrix.m_M[ 1 ] +
							m_M[ 1 ] * p_Matrix.m_M[ 5 ] +
							m_M[ 2 ] * p_Matrix.m_M[ 9 ] +
							m_M[ 3 ] * p_Matrix.m_M[ 13 ];
		Multiply.m_M[ 2 ] =	m_M[ 0 ] * p_Matrix.m_M[ 2 ] +
							m_M[ 1 ] * p_Matrix.m_M[ 6 ] +
							m_M[ 2 ] * p_Matrix.m_M[ 10 ] +
							m_M[ 3 ] * p_Matrix.m_M[ 14 ];
		Multiply.m_M[ 3 ] =	m_M[ 0 ] * p_Matrix.m_M[ 3 ] +
							m_M[ 1 ] * p_Matrix.m_M[ 7 ] +
							m_M[ 2 ] * p_Matrix.m_M[ 11 ] +
							m_M[ 3 ] * p_Matrix.m_M[ 15 ];

		Multiply.m_M[ 4 ] =	m_M[ 4 ] * p_Matrix.m_M[ 0 ] +
							m_M[ 5 ] * p_Matrix.m_M[ 4 ] +
							m_M[ 6 ] * p_Matrix.m_M[ 8 ] +
							m_M[ 7 ] * p_Matrix.m_M[ 12 ];
		Multiply.m_M[ 5 ] =	m_M[ 4 ] * p_Matrix.m_M[ 1 ] +
							m_M[ 5 ] * p_Matrix.m_M[ 5 ] +
							m_M[ 6 ] * p_Matrix.m_M[ 9 ] +
							m_M[ 7 ] * p_Matrix.m_M[ 13 ];
		Multiply.m_M[ 6 ] =	m_M[ 4 ] * p_Matrix.m_M[ 2 ] +
							m_M[ 5 ] * p_Matrix.m_M[ 6 ] +
							m_M[ 6 ] * p_Matrix.m_M[ 10 ] +
							m_M[ 7 ] * p_Matrix.m_M[ 14 ];
		Multiply.m_M[ 7 ] =	m_M[ 4 ] * p_Matrix.m_M[ 3 ] +
							m_M[ 5 ] * p_Matrix.m_M[ 7 ] +
							m_M[ 6 ] * p_Matrix.m_M[ 11 ] +
							m_M[ 7 ] * p_Matrix.m_M[ 15 ];

		Multiply.m_M[ 8 ] =	m_M[ 8 ] * p_Matrix.m_M[ 0 ] +
							m_M[ 9 ] * p_Matrix.m_M[ 4 ] +
							m_M[ 10 ] * p_Matrix.m_M[ 8 ] +
							m_M[ 11 ] * p_Matrix.m_M[ 12 ];
		Multiply.m_M[ 9 ] =	m_M[ 8 ] * p_Matrix.m_M[ 1 ] +
							m_M[ 9 ] * p_Matrix.m_M[ 5 ] +
							m_M[ 10 ] * p_Matrix.m_M[ 9 ] +
							m_M[ 11 ] * p_Matrix.m_M[ 13 ];
		Multiply.m_M[ 10 ] =	m_M[ 8 ] * p_Matrix.m_M[ 2 ] +
								m_M[ 9 ] * p_Matrix.m_M[ 6 ] +
								m_M[ 10 ] * p_Matrix.m_M[ 10 ] +
								m_M[ 11 ] * p_Matrix.m_M[ 14 ];
		Multiply.m_M[ 11 ] =	m_M[ 8 ] * p_Matrix.m_M[ 3 ] +
								m_M[ 9 ] * p_Matrix.m_M[ 7 ] +
								m_M[ 10 ] * p_Matrix.m_M[ 11 ] +
								m_M[ 11 ] * p_Matrix.m_M[ 15 ];

		Multiply.m_M[ 12 ] =	m_M[ 12 ] * p_Matrix.m_M[ 0 ] +
								m_M[ 13 ] * p_Matrix.m_M[ 4 ] +
								m_M[ 14 ] * p_Matrix.m_M[ 8 ] +
								m_M[ 15 ] * p_Matrix.m_M[ 12 ];
		Multiply.m_M[ 13 ] =	m_M[ 12 ] * p_Matrix.m_M[ 1 ] +
								m_M[ 13 ] * p_Matrix.m_M[ 5 ] +
								m_M[ 14 ] * p_Matrix.m_M[ 9 ] +
								m_M[ 15 ] * p_Matrix.m_M[ 13 ];
		Multiply.m_M[ 14 ] =	m_M[ 12 ] * p_Matrix.m_M[ 2 ] +
								m_M[ 13 ] * p_Matrix.m_M[ 6 ] +
								m_M[ 14 ] * p_Matrix.m_M[ 10 ] +
								m_M[ 15 ] * p_Matrix.m_M[ 14 ];
		Multiply.m_M[ 15 ] =	m_M[ 12 ] * p_Matrix.m_M[ 3 ] +
								m_M[ 13 ] * p_Matrix.m_M[ 7 ] +
								m_M[ 14 ] * p_Matrix.m_M[ 11 ] +
								m_M[ 15 ] * p_Matrix.m_M[ 15 ];*/

		Multiply.m_M[ 0 ] = m_M[ 0 ] * p_Matrix.m_M[ 0 ] +
							m_M[ 4 ] * p_Matrix.m_M[ 1 ] +
							m_M[ 8 ] * p_Matrix.m_M[ 2 ] +
							m_M[ 12 ] * p_Matrix.m_M[ 3 ];
		Multiply.m_M[ 4 ] = m_M[ 0 ] * p_Matrix.m_M[ 4 ] +
							m_M[ 4 ] * p_Matrix.m_M[ 5 ] +
							m_M[ 8 ] * p_Matrix.m_M[ 6 ] +
							m_M[ 12 ] * p_Matrix.m_M[ 7 ];
		Multiply.m_M[ 8 ] = m_M[ 0 ] * p_Matrix.m_M[ 8 ] +
							m_M[ 4 ] * p_Matrix.m_M[ 9 ] +
							m_M[ 8 ] * p_Matrix.m_M[ 10 ] +
							m_M[ 12 ] * p_Matrix.m_M[ 11 ];
		Multiply.m_M[ 12 ] = m_M[ 0 ] * p_Matrix.m_M[ 12 ] +
							m_M[ 4 ] * p_Matrix.m_M[ 13 ] +
							m_M[ 8 ] * p_Matrix.m_M[ 14 ] +
							m_M[ 12 ] * p_Matrix.m_M[ 15 ];

		Multiply.m_M[ 1 ] = m_M[ 1 ] * p_Matrix.m_M[ 0 ] +
							m_M[ 5 ] * p_Matrix.m_M[ 1 ] +
							m_M[ 9 ] * p_Matrix.m_M[ 2 ] +
							m_M[ 13 ] * p_Matrix.m_M[ 3 ];
		Multiply.m_M[ 5 ] = m_M[ 1 ] * p_Matrix.m_M[ 4 ] +
							m_M[ 5 ] * p_Matrix.m_M[ 5 ] +
							m_M[ 9 ] * p_Matrix.m_M[ 6 ] +
							m_M[ 13 ] * p_Matrix.m_M[ 7 ];
		Multiply.m_M[ 9 ] = m_M[ 1 ] * p_Matrix.m_M[ 8 ] +
							m_M[ 5 ] * p_Matrix.m_M[ 9 ] +
							m_M[ 9 ] * p_Matrix.m_M[ 10 ] +
							m_M[ 13 ] * p_Matrix.m_M[ 11 ];
		Multiply.m_M[ 13 ] = m_M[ 1 ] * p_Matrix.m_M[ 12 ] +
							m_M[ 5 ] * p_Matrix.m_M[ 13 ] +
							m_M[ 9 ] * p_Matrix.m_M[ 14 ] +
							m_M[ 13 ] * p_Matrix.m_M[ 15 ];

		Multiply.m_M[ 2 ] = m_M[ 2 ] * p_Matrix.m_M[ 0 ] +
							m_M[ 6 ] * p_Matrix.m_M[ 1 ] +
							m_M[ 10 ] * p_Matrix.m_M[ 2 ] +
							m_M[ 14 ] * p_Matrix.m_M[ 3 ];
		Multiply.m_M[ 6 ] = m_M[ 2 ] * p_Matrix.m_M[ 4 ] +
							m_M[ 6 ] * p_Matrix.m_M[ 5 ] +
							m_M[ 10 ] * p_Matrix.m_M[ 6 ] +
							m_M[ 14 ] * p_Matrix.m_M[ 7 ];
		Multiply.m_M[ 10 ] = m_M[ 2 ] * p_Matrix.m_M[ 8 ] +
							m_M[ 6 ] * p_Matrix.m_M[ 9 ] +
							m_M[ 10 ] * p_Matrix.m_M[ 10 ] +
							m_M[ 14 ] * p_Matrix.m_M[ 11 ];
		Multiply.m_M[ 14 ] = m_M[ 2 ] * p_Matrix.m_M[ 12 ] +
							m_M[ 6 ] * p_Matrix.m_M[ 13 ] +
							m_M[ 10 ] * p_Matrix.m_M[ 14 ] +
							m_M[ 14 ] * p_Matrix.m_M[ 15 ];

		Multiply.m_M[ 3 ] = m_M[ 3 ] * p_Matrix.m_M[ 0 ] +
							m_M[ 7 ] * p_Matrix.m_M[ 1 ] +
							m_M[ 11 ] * p_Matrix.m_M[ 2 ] +
							m_M[ 15 ] * p_Matrix.m_M[ 3 ];
		Multiply.m_M[ 7 ] = m_M[ 3 ] * p_Matrix.m_M[ 4 ] +
							m_M[ 7 ] * p_Matrix.m_M[ 5 ] +
							m_M[ 11 ] * p_Matrix.m_M[ 6 ] +
							m_M[ 15 ] * p_Matrix.m_M[ 7 ];
		Multiply.m_M[ 11 ] = m_M[ 3 ] * p_Matrix.m_M[ 8 ] +
							m_M[ 7 ] * p_Matrix.m_M[ 9 ] +
							m_M[ 11 ] * p_Matrix.m_M[ 10 ] +
							m_M[ 15 ] * p_Matrix.m_M[ 11 ];
		Multiply.m_M[ 15 ] = m_M[ 3 ] * p_Matrix.m_M[ 12 ] +
							m_M[ 7 ] * p_Matrix.m_M[ 13 ] +
							m_M[ 11 ] * p_Matrix.m_M[ 14 ] +
							m_M[ 15 ] * p_Matrix.m_M[ 15 ];

		return Multiply;
	}

	Matrix4x4 &Matrix4x4::operator=( const Matrix4x4 &p_Matrix )
	{
		memcpy( m_M, p_Matrix.m_M, sizeof( m_M ) );

		return *this;
	}

	float &Matrix4x4::operator( )( size_t p_Row, size_t p_Column )
	{
		return m_M[ p_Row + ( 4 * p_Column ) ];
	}
}
