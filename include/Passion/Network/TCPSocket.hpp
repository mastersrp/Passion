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

#ifndef PASSION_TCPSOCKET_HPP
#define PASSION_TCPSOCKET_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <Passion/Network/BaseTCPSocket.hpp>

#ifdef WIN32
	#include <winsock2.h>
#endif

namespace Passion
{
	class TCPSocket : public BaseTCPSocket
	{
	public:
		TCPSocket();
		~TCPSocket();

		void Connect( const char* host, unsigned short port );
		void Disconnect();

		void Send( const char* data, size_t length );
		unsigned int Receive( char* buffer, size_t length );

		bool IsConnected();
		bool Available();
	private:
#ifdef WIN32
		SOCKET m_socket;
#endif
		bool m_connected;
	};
}

#endif