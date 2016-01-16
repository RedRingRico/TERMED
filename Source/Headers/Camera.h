#ifndef __TERMED_CAMERA_H__
#define __TERMED_CAMERA_H__

#include <Vector3.h>
#include <Matrix4x4.h>

namespace TERMED
{
	enum PROJECTION_MODE
	{
		PROJECTION_MODE_ORTHOGRAPHIC = 0,
		PROJECTION_MODE_PERSPECTIVE
	};

	class Camera
	{
	public:
		Camera( );
		Camera( const Camera &p_Other );
		~Camera( );

		Camera &operator=( const Camera &p_Camera );

		void SetPosition( float p_X, float p_Y, float p_Z );
		void SetPosition( const Vector3 &p_Position );
		void GetPosition( Vector3 &p_Position ) const;

		void SetDimensions( float p_Width, float p_Height );
		void GetDimensions( float &p_Width, float &p_Height ) const;

		void SetLookPoint( float p_X, float p_Y, float p_Z );
		void SetLookPoint( const Vector3 &p_LookPoint );
		void GetLookPoint( Vector3 &p_LookPoint ) const;

		void SetWorldUp( float p_X, float p_Y, float p_Z );
		void SetWorldUp( const Vector3 &p_WorldUp );
		void GetWorldUp( Vector3 &p_WorldUp ) const;

		void SetClippingPlanes( float p_Near, float p_Far );
		void GetClippingPlanes( float &p_Near, float &p_Far ) const;

		void SetAspectRatio( float p_AspectRatio );
		float GetAspectRatio( ) const;

		void GetProjectionMatrix( Matrix4x4 &p_Matrix ) const;
		void GetViewMatrix( Matrix4x4 &p_Matrix ) const;

		int CalculateProjectionMatrix( );
		int CalculateViewMatrix( );
		
	private:
		Vector3			m_Position;
		Vector3			m_WorldUp;
		Vector3			m_LookPoint;
		Matrix4x4		m_Projection;
		Matrix4x4		m_View;
		float			m_Near;
		float			m_Far;
		float			m_AspectRatio;
		float			m_FieldOfView;
		float			m_Width;
		float			m_Height;
		PROJECTION_MODE	m_ProjectionMode;
	};
}

#endif // __TERMED_CAMERA_H__
