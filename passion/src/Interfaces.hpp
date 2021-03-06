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

#ifndef PASSION_INTERFACE_HPP
#define PASSION_INTERFACE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <Passion/Render.hpp>
#include <Passion/Input.hpp>
#include <Passion/Scripting.hpp>
#include <Passion/Network.hpp>

////////////////////////////////////////////////////////////
// Globals
////////////////////////////////////////////////////////////

extern Passion::IBaseRender*		g_Render;
extern Passion::IBaseInput*			g_Input;

extern Passion::IBaseScripting*		g_Scripting;
extern Passion::BaseScriptState*	g_Lua;

extern Passion::IBaseNetwork*		g_Network;

////////////////////////////////////////////////////////////
// Miscellaneous
////////////////////////////////////////////////////////////

using Passion::BaseScriptValue;

////////////////////////////////////////////////////////////
// Type parsing
////////////////////////////////////////////////////////////

inline Passion::Vector GetVector( int index )
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	std::auto_ptr<BaseScriptValue> vec = g_Lua->Get( index );

	if ( vec->IsTable() && vec->GetMetaTable()->Equals( g_Lua->Registry()->GetMember( "Vector" ) ) )
	{
		x = vec->GetMember( "x" )->GetFloat();
		y = vec->GetMember( "y" )->GetFloat();
		z = vec->GetMember( "z" )->GetFloat();
	} else {
		g_Lua->Error( index, "Vector" );
	}

	return Passion::Vector( x, y, z );
}

inline Passion::Color GetColor( int index )
{
	float r, g, b, a;

	std::auto_ptr<BaseScriptValue> col = g_Lua->Get( index );

	if ( col->IsTable() )
	{
		r = col->GetMember( "r" )->GetFloat() / 255.0f;
		g = col->GetMember( "g" )->GetFloat() / 255.0f;
		b = col->GetMember( "b" )->GetFloat() / 255.0f;
		a = col->GetMember( "a" )->GetFloat() / 255.0f;
	} else {
		g_Lua->Error( index, "Color" );
	}

	return Passion::Color( r, g, b, a );
}

inline Passion::Vertex GetVertex( int index )
{
	Passion::Vertex vtx;

	std::auto_ptr<BaseScriptValue> vertex = g_Lua->Get( index );

	if ( vertex->IsTable() )
	{
		vertex->GetMember( "pos" )->Push();
		Passion::Vector pos = GetVector( -1 );
		g_Lua->Pop( 1 );
		
		vertex->GetMember( "color" )->Push();
		Passion::Color color = GetColor( -1 );
		g_Lua->Pop( 1 );

		vtx.x = pos.x; vtx.y = pos.y; vtx.z = pos.z;
		vtx.r = color.R; vtx.g = color.G; vtx.b = color.B; vtx.a = color.A;

		vtx.u = vertex->GetMember( "u" )->GetFloat();
		vtx.v = vertex->GetMember( "v" )->GetFloat();
	} else {
		g_Lua->Error( index, "Vertex" );
	}

	return vtx;
}

#endif
