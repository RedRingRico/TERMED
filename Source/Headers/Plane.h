#ifndef __TERMED_PLANE_H__
#define __TERMED_PLANE_H__

#include <Vector3.h>

namespace TERMED
{
	class Plane
	{
	public:
		Plane( );
		Plane( const Plane &p_Plane );
		Plane( const Vector3 &p_Normal, const Vector3 &p_Point );
		~Plane( );

	private:
		Vector3	m_Normal;
		Vector3	m_Point;
		float	m_Distance;
	};
}

#endif // __TERMED_PLANE_H__
