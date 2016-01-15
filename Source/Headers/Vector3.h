#ifndef __TERMED_VECTOR3_H__
#define __TERMED_VECTOR3_H__

namespace TERMED
{
	class Vector3
	{
	public:
		Vector3( );
		Vector3( const Vector3 &p_Other );
		Vector3( float p_X, float p_Y, float p_Z );
		~Vector3( );

		Vector3 &operator=( const Vector3 &p_Other );

		void Set( float p_X, float p_Y, float p_Z );

	private:
		float m_X, m_Y, m_Z;
	};
}

#endif // __TERMED_VECTOR3_H__
