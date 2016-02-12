#include <Plane.h>

namespace TERMED
{
	Plane::Plane( ) :
		m_Normal( 0.0f, 0.0f, 1.0f ),
		m_Point( 0.0f, 0.0f, 0.0f ),
		m_Distance( 0.0f )
	{
	}

	Plane::Plane( const Plane &p_Plane ) :
		m_Normal( p_Plane.m_Normal ),
		m_Point( p_Plane.m_Point ),
		m_Distance( p_Plane.m_Distance )
	{
	}

	Plane::Plane( const Vector3 &p_Normal, const Vector3 &p_Point ) :
		m_Normal( p_Normal ),
		m_Point( p_Point )		
	{
		m_Distance = -m_Normal.Dot( m_Point );
	}

	Plane::~Plane( )
	{
	}
}
