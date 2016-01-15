#include <Vector3.h>
#include <Arithmetic.h>

namespace TERMED
{
	Vector3::Vector3( ) :
		m_X( 0.0f ),
		m_Y( 0.0f ),
		m_Z( 0.0f )
	{
	}

	Vector3::Vector3( const Vector3 &p_Vector ) :
		m_X( p_Vector.m_X ),
		m_Y( p_Vector.m_Y ),
		m_Z( p_Vector.m_Z )
	{
	}

	Vector3::Vector3( float p_X, float p_Y, float p_Z ) :
		m_X( p_X ),
		m_Y( p_Y ),
		m_Z( p_Z )
	{
	}

	Vector3::~Vector3( )
	{
	}

	void Vector3::Set( float p_X, float p_Y, float p_Z )
	{
		m_X = p_X;
		m_Y = p_Y;
		m_Z = p_Z;
	}

	float Vector3::GetX( ) const
	{
		return m_X;
	}

	float Vector3::GetY( ) const
	{
		return m_Y;
	}
	
	float Vector3::GetZ( ) const
	{
		return m_Z;
	}

	void Vector3::Normalise( )
	{
		float Squared = ( m_X * m_X ) + ( m_Y * m_Y ) + ( m_Z * m_Z );

		if( TERMED::IsZero( Squared ) )
		{
			return;
		}

		float Factor = 1.0f / TERMED::SquareRoot( Squared );

		m_X *= Factor;
		m_Y *= Factor;
		m_Z *= Factor;
	}

	float Vector3::Magnitude( ) const
	{
		return TERMED::SquareRoot( ( m_X * m_X ) + ( m_Y * m_Y ) +
			( m_Z * m_Z ) );
	}

	float Vector3::MagnitudeSq( ) const
	{
		return ( ( m_X * m_X ) + ( m_Y * m_Y ) + ( m_Z * m_Z ) );
	}

	float Vector3::Distance( const Vector3 &p_Vector ) const
	{
		float X = m_X - p_Vector.m_X;
		float Y = m_Y - p_Vector.m_Y;
		float Z = m_Z - p_Vector.m_Z;

		return TERMED::SquareRoot( ( X * X ) + ( Y * Y ) + ( Z * Z ) );
	}

	float Vector3::DistanceSq( const Vector3 &p_Vector ) const
	{
		float X = m_X - p_Vector.m_X;
		float Y = m_Y - p_Vector.m_Y;
		float Z = m_Z - p_Vector.m_Z;

		return ( ( X * X ) + ( Y * Y ) + ( Z * Z ) );
	}

	float Vector3::Dot( const Vector3 &p_Vector ) const
	{
		return ( ( m_X * p_Vector.m_X ) + ( m_Y * p_Vector.m_Y ) +
			( m_Z * p_Vector.m_Z ) );
	}

	Vector3 Vector3::Cross( const Vector3 &p_Vector ) const
	{
		return Vector3(
			( m_Y * p_Vector.m_Z ) - ( m_Z * p_Vector.m_Y ),
			( m_Z * p_Vector.m_X ) - ( m_X * p_Vector.m_Z ),
			( m_X * p_Vector.m_Y ) - ( m_Y * p_Vector.m_X ) );
	}
	
	bool Vector3::operator ==( const Vector3 &p_Vector ) const
	{
		return( TERMED::IsEqual( m_X, p_Vector.m_X ) &&
			TERMED::IsEqual( m_Y, p_Vector.m_Y ) &&
			TERMED::IsEqual( m_Z, p_Vector.m_Z ) );
	}

	bool Vector3::operator !=( const Vector3 &p_Vector ) const
	{
		return( !TERMED::IsEqual( m_X, p_Vector.m_X ) ||
			!TERMED::IsEqual( m_Y, p_Vector.m_Y ) ||
			!TERMED::IsEqual( m_Z, p_Vector.m_Z ) );
	}

	Vector3 Vector3::operator+( const Vector3 &p_Vector ) const
	{
		return Vector3( m_X + p_Vector.m_X, m_Y + p_Vector.m_Y,
			m_Z + p_Vector.m_Z );
	}

	Vector3 Vector3::operator-( const Vector3 &p_Vector ) const
	{
		return Vector3( m_X - p_Vector.m_X, m_Y - p_Vector.m_Y,
			m_Z - p_Vector.m_Z );
	}

	Vector3 Vector3::operator*( const Vector3 &p_Vector ) const
	{
		return Vector3( m_X * p_Vector.m_X, m_Y * p_Vector.m_Y,
			m_Z * p_Vector.m_Z );
	}

	Vector3 Vector3::operator/( const float p_Scalar ) const
	{
		return Vector3( m_X / p_Scalar, m_Y / p_Scalar, m_Z / p_Scalar );
	}

	Vector3 &Vector3::operator+=( const Vector3 &p_Vector )
	{
		m_X += p_Vector.m_X;
		m_Y += p_Vector.m_Y;
		m_Z += p_Vector.m_Z;

		return *this;
	}

	Vector3 &Vector3::operator-=( const Vector3 &p_Vector )
	{
		m_X -= p_Vector.m_X;
		m_Y -= p_Vector.m_Y;
		m_Z -= p_Vector.m_Z;

		return *this;
	}

	Vector3 &Vector3::operator*=( const Vector3 &p_Vector )
	{
		m_X *= p_Vector.m_X;
		m_Y *= p_Vector.m_Y;
		m_Z *= p_Vector.m_Z;

		return *this;
	}

	Vector3 &Vector3::operator/=( const float p_Scalar )
	{
		m_X /= p_Scalar;
		m_Y /= p_Scalar;
		m_Z /= p_Scalar;

		return *this;
	}
}
