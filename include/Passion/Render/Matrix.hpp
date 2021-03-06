////////////////////////////////////////////////////////////
//
//  Copyright (C) 2010 Alexander Overvoorde (overv161@gmail.com)
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//  2. Altered source versions must be plainly marked as such, and must not be
//     misrepresented as being the original software.
//  3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef PASSION_MATRIX_HPP
#define PASSION_MATRIX_HPP

#include <cmath>

namespace Passion
{
	class Matrix
	{
	public:
		Matrix();
		Matrix( float* m );

		Vector operator*( Vector v );
		Matrix operator*( Matrix m );
		void operator*=( Matrix m );

		operator float*();

		void Translate( Vector v );
		void Scale( Vector v );

		void RotateX( float ang );
		void RotateY( float ang );
		void RotateZ( float ang );

		void Orthogonal( float left, float right, float bottom, float top, float znear = -1.0f, float zfar = 1.0f );
		void Perspective( float fov, float aspectRatio, float znear, float zfar );
		void LookAt( Vector pos, Vector target, Vector up );

		bool Invert();
		
		float m[16];
	};

	inline Matrix::Matrix()
	{
		for ( int i = 0; i < 16; i++ ) m[i] = 0;
		m[0] = 1;
		m[5] = 1;
		m[10] = 1;
		m[15] = 1;
	}

	inline Matrix::Matrix( float* v )
	{
		for ( int i = 0; i < 16; i++ )
			m[i] = v[i];
	}

	inline Vector Matrix::operator*( Vector v )
	{
		float x = v.x * m[0] + v.y * m[1] + v.z * m[2] + m[3];
		float y = v.x * m[4] + v.y * m[5] + v.z * m[6] + m[7];
		float z = v.x * m[8] + v.y * m[9] + v.z * m[10] + m[11];

		return Vector( x, y, z );
	}

	inline Matrix Matrix::operator*( Matrix mat )
	{
		Matrix res;

		res.m[0] = m[0]*mat.m[0] + m[1]*mat.m[4] + m[2]*mat.m[8] + m[3]*mat.m[12];
		res.m[1] = m[0]*mat.m[1] + m[1]*mat.m[5] + m[2]*mat.m[9] + m[3]*mat.m[13];
		res.m[2] = m[0]*mat.m[2] + m[1]*mat.m[6] + m[2]*mat.m[10] + m[3]*mat.m[14];
		res.m[3] = m[0]*mat.m[3] + m[1]*mat.m[7] + m[2]*mat.m[11] + m[3]*mat.m[15];
		res.m[4] = m[4]*mat.m[0] + m[5]*mat.m[4] + m[6]*mat.m[8] + m[7]*mat.m[12];
		res.m[5] = m[4]*mat.m[1] + m[5]*mat.m[5] + m[6]*mat.m[9] + m[7]*mat.m[13];
		res.m[6] = m[4]*mat.m[2] + m[5]*mat.m[6] + m[6]*mat.m[10] + m[7]*mat.m[14];
		res.m[7] = m[4]*mat.m[3] + m[5]*mat.m[7] + m[6]*mat.m[11] + m[7]*mat.m[15];
		res.m[8] = m[8]*mat.m[0] + m[9]*mat.m[4] + m[10]*mat.m[8] + m[11]*mat.m[12];
		res.m[9] = m[8]*mat.m[1] + m[9]*mat.m[5] + m[10]*mat.m[9] + m[11]*mat.m[13];
		res.m[10] = m[8]*mat.m[2] + m[9]*mat.m[6] + m[10]*mat.m[10] + m[11]*mat.m[14];
		res.m[11] = m[8]*mat.m[3] + m[9]*mat.m[7] + m[10]*mat.m[11] + m[11]*mat.m[15];
		res.m[12] = m[12]*mat.m[0] + m[13]*mat.m[4] + m[14]*mat.m[8] + m[15]*mat.m[12];
		res.m[13] = m[12]*mat.m[1] + m[13]*mat.m[5] + m[14]*mat.m[9] + m[15]*mat.m[13];
		res.m[14] = m[12]*mat.m[2] + m[13]*mat.m[6] + m[14]*mat.m[10] + m[15]*mat.m[14];
		res.m[15] = m[12]*mat.m[3] + m[13]*mat.m[7] + m[14]*mat.m[11] + m[15]*mat.m[15];
		
		return res;
	}

	inline void Matrix::operator*=( Matrix m )
	{
		*this = *this * m;
	}

	inline Matrix::operator float*()
	{
		return (float*)this;
	}

	inline void Matrix::Translate( Vector v )
	{
		float mat[] = {
			1, 0, 0, v.x,
			0, 1, 0, v.y,
			0, 0, 1, v.z,
			0, 0, 0, 1
		};
		*this *= Matrix( mat );
	}

	inline void Matrix::Scale( Vector v )
	{
		float mat[] = {
			v.x, 0, 0, 0,
			0, v.y, 0, 0,
			0, 0, v.z, 0,
			0, 0, 0, 1
		};
		*this *= Matrix( mat );
	}

	inline void Matrix::RotateX( float ang )
	{
		float mat[] = {
			1, 0, 0, 0,
			0, cos( ang ), -sin( ang ), 0,
			0, sin( ang ), cos( ang ), 0,
			0, 0, 0, 1
		};
		*this *= Matrix( mat );
	}

	inline void Matrix::RotateY( float ang )
	{
		float mat[] = {
			cos( ang ), 0, sin( ang ), 0,
			0, 1, 0, 0,
			-sin( ang ), 0, cos( ang ), 0,
			0, 0, 0, 1
		};
		*this *= Matrix( mat );
	}

	inline void Matrix::RotateZ( float ang )
	{
		float mat[] = {
			cos( ang ), sin( ang ), 0, 0,
			-sin( ang ), cos( ang ), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
		*this *= Matrix( mat );
	}

	inline Vector Vector::operator*( Matrix m )
	{
		return m.operator*( *this );
	}

	inline void Matrix::Orthogonal( float left, float right, float bottom, float top, float znear, float zfar )
	{
		float mat[] = {
			2/(right-left), 0, 0, -(right+left)/(right-left),
			0, 2/(top-bottom), 0, -(top+bottom)/(top-bottom),
			0, 0, -2/(zfar-znear), -(zfar+znear)/(zfar-znear),
			0, 0, 0, 1
		};
		*this *= Matrix( mat );
	}

	inline void Matrix::Perspective( float fov, float aspectRatio, float znear, float zfar )
	{
		float f = 1.0f / tan( fov / 2.0f );
		
		float mat[] = {
			f/aspectRatio, 0, 0, 0,
			0, f, 0, 0,
			0, 0, (zfar+znear)/(znear-zfar), (2.0f*zfar*znear)/(znear-zfar),
			0, 0, -1, 0
		};
		*this *= Matrix( mat );
	}

	inline void Matrix::LookAt( Vector pos, Vector target, Vector up )
	{
		Vector f = ( target - pos ).Normal();
		up = up.Normal();

		Vector s = f.Cross( up );
		Vector u = s.Cross( f );
		
		float mat[] = {
			s.x, s.y, s.z, 0,
			u.x, u.y, u.z, 0,
			-f.x, -f.y, -f.z, 0,
			0, 0, 0, 1
		};

		*this *= Matrix( mat );
		Translate( -pos );
	}

	inline bool Matrix::Invert()
	{
		float inv[16], det;
		int i;

		inv[0] =   m[5]*m[10]*m[15] - m[5]*m[11]*m[14] - m[9]*m[6]*m[15]
		+ m[9]*m[7]*m[14] + m[13]*m[6]*m[11] - m[13]*m[7]*m[10];
		inv[4] =  -m[4]*m[10]*m[15] + m[4]*m[11]*m[14] + m[8]*m[6]*m[15]
		- m[8]*m[7]*m[14] - m[12]*m[6]*m[11] + m[12]*m[7]*m[10];
		inv[8] =   m[4]*m[9]*m[15] - m[4]*m[11]*m[13] - m[8]*m[5]*m[15]
		+ m[8]*m[7]*m[13] + m[12]*m[5]*m[11] - m[12]*m[7]*m[9];
		inv[12] = -m[4]*m[9]*m[14] + m[4]*m[10]*m[13] + m[8]*m[5]*m[14]
		- m[8]*m[6]*m[13] - m[12]*m[5]*m[10] + m[12]*m[6]*m[9];
		inv[1] =  -m[1]*m[10]*m[15] + m[1]*m[11]*m[14] + m[9]*m[2]*m[15]
		- m[9]*m[3]*m[14] - m[13]*m[2]*m[11] + m[13]*m[3]*m[10];
		inv[5] =   m[0]*m[10]*m[15] - m[0]*m[11]*m[14] - m[8]*m[2]*m[15]
		+ m[8]*m[3]*m[14] + m[12]*m[2]*m[11] - m[12]*m[3]*m[10];
		inv[9] =  -m[0]*m[9]*m[15] + m[0]*m[11]*m[13] + m[8]*m[1]*m[15]
		- m[8]*m[3]*m[13] - m[12]*m[1]*m[11] + m[12]*m[3]*m[9];
		inv[13] =  m[0]*m[9]*m[14] - m[0]*m[10]*m[13] - m[8]*m[1]*m[14]
		+ m[8]*m[2]*m[13] + m[12]*m[1]*m[10] - m[12]*m[2]*m[9];
		inv[2] =   m[1]*m[6]*m[15] - m[1]*m[7]*m[14] - m[5]*m[2]*m[15]
		+ m[5]*m[3]*m[14] + m[13]*m[2]*m[7] - m[13]*m[3]*m[6];
		inv[6] =  -m[0]*m[6]*m[15] + m[0]*m[7]*m[14] + m[4]*m[2]*m[15]
		- m[4]*m[3]*m[14] - m[12]*m[2]*m[7] + m[12]*m[3]*m[6];
		inv[10] =  m[0]*m[5]*m[15] - m[0]*m[7]*m[13] - m[4]*m[1]*m[15]
		+ m[4]*m[3]*m[13] + m[12]*m[1]*m[7] - m[12]*m[3]*m[5];
		inv[14] = -m[0]*m[5]*m[14] + m[0]*m[6]*m[13] + m[4]*m[1]*m[14]
		- m[4]*m[2]*m[13] - m[12]*m[1]*m[6] + m[12]*m[2]*m[5];
		inv[3] =  -m[1]*m[6]*m[11] + m[1]*m[7]*m[10] + m[5]*m[2]*m[11]
		- m[5]*m[3]*m[10] - m[9]*m[2]*m[7] + m[9]*m[3]*m[6];
		inv[7] =   m[0]*m[6]*m[11] - m[0]*m[7]*m[10] - m[4]*m[2]*m[11]
		+ m[4]*m[3]*m[10] + m[8]*m[2]*m[7] - m[8]*m[3]*m[6];
		inv[11] = -m[0]*m[5]*m[11] + m[0]*m[7]*m[9] + m[4]*m[1]*m[11]
		- m[4]*m[3]*m[9] - m[8]*m[1]*m[7] + m[8]*m[3]*m[5];
		inv[15] =  m[0]*m[5]*m[10] - m[0]*m[6]*m[9] - m[4]*m[1]*m[10]
		+ m[4]*m[2]*m[9] + m[8]*m[1]*m[6] - m[8]*m[2]*m[5];

		det = m[0]*inv[0] + m[1]*inv[4] + m[2]*inv[8] + m[3]*inv[12];
		if ( det == 0 )
			return false;

		det = 1.0f / det;

		for ( i = 0; i < 16; i++ )
			m[i] = inv[i] * det;

		return true;
	}
}

#endif
