#include <Camera.h>
#include <Arithmetic.h>
#include <cmath>

namespace TERMED
{
	Camera::Camera( ) :
		m_Position( 0.0f, 0.0f, 0.0f ),
		m_WorldUp( 0.0f, 1.0f, 0.0f ),
		m_LookPoint( 0.0f, 0.0f, -1.0f ),
		m_Near( 1.0f ),
		m_Far( 1000.0f ),
		m_AspectRatio( 1.0f ),
		m_FieldOfView( 45.0f ),
		m_Width( 0.0f ),
		m_Height( 0.0f ),
		m_ProjectionMode( PROJECTION_MODE_PERSPECTIVE )
	{
	}

	Camera::~Camera( )
	{
	}

	Camera::Camera( const Camera &p_Camera ) :
		m_Position( p_Camera.m_Position ),
		m_WorldUp( p_Camera.m_WorldUp ),
		m_LookPoint( p_Camera.m_LookPoint ),
		m_Near( p_Camera.m_Near ),
		m_Far( p_Camera.m_Far ),
		m_AspectRatio( p_Camera.m_AspectRatio ),
		m_FieldOfView( p_Camera.m_FieldOfView ),
		m_Width( p_Camera.m_Width ),
		m_Height( p_Camera.m_Height ),
		m_ProjectionMode( p_Camera.m_ProjectionMode )
	{
	}

	void Camera::SetPosition( float p_X, float p_Y, float p_Z )
	{
		m_Position.Set( p_X, p_Y, p_Z );
	}

	void Camera::SetPosition( const Vector3 &p_Position )
	{
		m_Position = p_Position;
	}

	void Camera::GetPosition( Vector3 &p_Position ) const
	{
		p_Position = m_Position;
	}

	void Camera::SetDimensions( float p_Width, float p_Height )
	{
		m_Width = p_Width;
		m_Height = p_Height;
	}

	void Camera::SetLookPoint( float p_X, float p_Y, float p_Z )
	{
		m_LookPoint.Set( p_X, p_Y, p_Z );
	}

	void Camera::SetWorldUp( float p_X, float p_Y, float p_Z )
	{
		m_WorldUp.Set( p_X, p_Y, p_Z );
	}

	void Camera::SetClippingPlanes( float p_Near, float p_Far )
	{
		m_Near = p_Near;
		m_Far = p_Far;
	}

	void Camera::Pan( float p_X, float p_Y )
	{
	}

	void Camera::SetAspectRatio( float p_AspectRatio )
	{
		m_AspectRatio = p_AspectRatio;
	}

	void Camera::SetProjectionMode( PROJECTION_MODE p_ProjectionMode )
	{
		m_ProjectionMode = p_ProjectionMode;
	}

	int Camera::CalculateProjectionMatrix( )
	{
		switch( m_ProjectionMode )
		{
		case PROJECTION_MODE_ORTHOGRAPHIC:
			{
				m_Projection.SetAsIdentity( );

				m_Projection( 0, 0 ) = 2.0f / ( m_Width );
				m_Projection( 1, 1 ) = 2.0f / ( m_Height );

				m_Projection( 2, 2 ) = -2.0f / ( m_Far - m_Near );
				m_Projection( 2, 3 ) = -( m_Far + m_Near ) /
					( m_Far - m_Near );

				break;
			}
		case PROJECTION_MODE_PERSPECTIVE:
			{
				if( TERMED::IsZero( m_Far - m_Near ) )
				{
					return 1;
				}

				float D = 1.0f / tanf( ( m_FieldOfView * c_PiOver360 ) / 2.0f );

				m_Projection.SetAsIdentity( );

				m_Projection( 0, 0 ) = D / m_AspectRatio;
				m_Projection( 1, 1 ) = D;
				m_Projection( 2, 2 ) = -( m_Far + m_Near ) /
					( m_Far - m_Near );
				m_Projection( 2, 3 ) = ( -2.0f * m_Near * m_Far ) /
					( m_Far - m_Near );
				m_Projection( 3, 2 ) = -1.0f;
				m_Projection( 3, 3 ) = 0.0f;

				break;
			}
		default:
			{
				return 1;
			}
		}

		return 0;
	}

	int Camera::CalculateViewMatrix( )
	{
		Vector3 Direction = ( m_Position - m_LookPoint );
		Direction.Normalise( );

		Vector3 Right = m_WorldUp.Cross( Direction );
		Right.Normalise( );

		Vector3 Up = Direction.Cross( Right );
		Up.Normalise( );

		float PositionX, PositionY, PositionZ;
		PositionX = -Right.Dot( m_Position );
		PositionY = -Up.Dot( m_Position );
		PositionZ = -Direction.Dot( m_Position );

		m_View( 3, 0 ) = m_View( 3, 1 ) = m_View( 3, 2 ) = 0.0f;
		m_View( 3, 3 ) = 1.0f;

		m_View( 0, 0 ) = Right.GetX( );
		m_View( 1, 0 ) = Right.GetY( );
		m_View( 2, 0 ) = Right.GetZ( );

		m_View( 0, 1 ) = Up.GetX( );
		m_View( 1, 1 ) = Up.GetY( );
		m_View( 2, 1 ) = Up.GetZ( );

		m_View( 0, 2 ) = Direction.GetX( );
		m_View( 1, 2 ) = Direction.GetY( );
		m_View( 2, 2 ) = Direction.GetZ( );

		m_View( 0, 3 ) = PositionX;
		m_View( 1, 3 ) = PositionY;
		m_View( 2, 3 ) = PositionZ;

		return 0;
	}

	void Camera::GetProjectionMatrix( Matrix4x4 &p_Matrix ) const
	{
		p_Matrix = m_Projection;
	}

	void Camera::GetViewMatrix( Matrix4x4 &p_Matrix ) const
	{
		p_Matrix = m_View;
	}
}
