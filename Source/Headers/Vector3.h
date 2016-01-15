#ifndef __TERMED_VECTOR3_H__
#define __TERMED_VECTOR3_H__

namespace TERMED
{
	class Vector3
	{
	public:
		Vector3( );
		Vector3( const Vector3 &p_Vector );
		Vector3( float p_X, float p_Y, float p_Z );
		~Vector3( );

		Vector3 &operator=( const Vector3 &p_Vector );

		void Set( float p_X, float p_Y, float p_Z );
		float GetX( ) const;
		float GetY( ) const;
		float GetZ( ) const;

		void Normalise( );

		float Magnitude( ) const;
		float MagnitudeSq( ) const;

		float Distance( const Vector3 &p_Vector ) const;
		float DistanceSq( const Vector3 &p_Vector ) const;

		float Dot( const Vector3 &p_Vector ) const;
		Vector3 Cross( const Vector3 &p_Vector ) const;

		bool operator==( const Vector3 &p_Vector ) const;
		bool operator!=( const Vector3 &p_Vector ) const;

		Vector3 operator+( const Vector3 &p_Vector ) const;
		Vector3 operator-( const Vector3 &p_Vector ) const;
		Vector3 operator*( const Vector3 &p_Vector ) const;
		Vector3 operator/( const float p_Scalar ) const;

		Vector3 &operator+=( const Vector3 &p_Vector );
		Vector3 &operator-=( const Vector3 &p_Vector );
		Vector3 &operator*=( const Vector3 &p_Vector );
		Vector3 &operator/=( const float p_Scalar );		

	private:
		float m_X, m_Y, m_Z;
	};
}

#endif // __TERMED_VECTOR3_H__
