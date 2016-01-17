#ifndef __TERMED_MATRIX4X4_H__
#define __TERMED_MATRIX4X4_H__

#include <Vector3.h>

namespace TERMED
{
	class Matrix4x4
	{
	public:
		Matrix4x4( );
		Matrix4x4( const Matrix4x4 &p_Matrix );
		~Matrix4x4( );

		void SetAsIdentity( );

		Matrix4x4 &CreateTranslation( const Vector3 &p_Translate );

		Matrix4x4 &CreateRotation( float p_Angle, const Vector3 &p_Axis );
		Matrix4x4 &CreateRotation( float p_Roll, float p_Pitch, float p_Yaw );

		Matrix4x4 &CreateRotationX( float p_X );
		Matrix4x4 &CreateRotationY( float p_Y );
		Matrix4x4 &CreateRotationZ( float p_Z );

		Matrix4x4 &CreateScale( float p_Scale );
		Matrix4x4 &CreateScale( const Vector3 &p_Scale );

		Matrix4x4 &CreateScaleX( float p_X );
		Matrix4x4 &CreateScaleY( float p_Z );
		Matrix4x4 &CreateScaleZ( float p_Y );

		bool IsZero( ) const;
		bool IsIdentity( ) const;

		void CopyToFloatArray( float *p_pMatrix ) const;

		void Clean( );

		Matrix4x4 &Transpose( );
		void Transpose( Matrix4x4 &p_Matrix ) const;
		Matrix4x4 &CreateTransposeFrom( const Matrix4x4 &p_Matrix );

		Matrix4x4 &AffineInverse( );
		void AffineInverse( Matrix4x4 &p_Matrix ) const;
		Matrix4x4 &CreateAffineInverseFrom( const Matrix4x4 &p_Matrix );

		float GetTrace( ) const;

		Matrix4x4 operator*( const Matrix4x4 &p_Matrix ) const;

		Matrix4x4 &operator=( const Matrix4x4 &p_Matrix );

		float &operator( )( size_t p_Row, size_t p_Column );
		float operator( )( size_t p_Row, size_t p_Column ) const;

		float &operator[ ]( size_t p_Index );
		float operator[ ]( size_t p_Index ) const;

	private:
		// 0 4  8 12
		// 1 5  9 13
		// 2 6 10 14
		// 3 7 11 15
		float m_M[ 16 ];
	};
}

#endif // __TERMED_MATRIX4X4_H__
