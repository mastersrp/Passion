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

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <Passion/Input/IInput.hpp>

namespace Passion
{
	void IInput::SetWindow( Window* window )
	{
		m_window = (RenderWindow*)window;
	}

	bool IInput::GetEvents()
	{
		return m_window->GetEvents();
	}

	int IInput::GetMouseX()
	{
		return m_window->MouseX();
	}

	int IInput::GetMouseY()
	{
		return m_window->MouseY();
	}

	int IInput::GetMouseWheel()
	{
		return m_window->MouseWheel();
	}

	bool IInput::IsMouseDown( MouseButton button )
	{
		return m_window->IsMouseDown( button );
	}

	bool IInput::IsKeyDown( Key key )
	{
		return m_window->IsKeyDown( key );
	}

	void IInput::ShowMouseCursor( bool show )
	{
		m_window->ShowMouseCursor( show );
	}

	void IInput::SetMousePos( int x, int y )
	{
		m_window->SetMousePos( x, y );
	}
}