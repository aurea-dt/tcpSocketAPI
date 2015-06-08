////////////////////////////////////////////////////////////////////////////////
// ADT_TCPSocket.cpp
// Mario Chirinos Colunga
// Áurea Desarrollo Tecnológico
// 2012/05/11
//------------------------------------------------------------------------------
// Notes:
//	Berkeley sockets
//
////////////////////////////////////////////////////////////////////////////////
#include "ADT_TCPSocket.h"
using namespace std;
//------------------------------------------------------------------------------
ADT_TCPSocket::ADT_TCPSocket(int port)
{
	cout << "ADT_TCPSocket(int port) constructor..." << endl;

	buffer = new unsigned char[BUFFERSIZE];
	
	// creates a new socket. AF_INET = Internet domain; SOCK_STREAM=TCP
	serverSocketFd = socket(AF_INET, SOCK_STREAM, 0);
	if(serverSocketFd < 0) 
	{
		cerr << "ERROR opening socket";
		exit(1);
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);	
     	
	//binds a socket to an address
	if (bind(serverSocketFd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) 
	{
		cerr << "ERROR on binding";
		exit(1);
	}       
	
	listen(serverSocketFd, CONNQUEUE);
	GIOChannel* channel = g_io_channel_unix_new (serverSocketFd);
	g_io_add_watch(channel, G_IO_IN, &listen_callback, this);
	g_io_channel_unref(channel);
}
//------------------------------------------------------------------------------
ADT_TCPSocket::~ADT_TCPSocket()
{
	close(clientSocketFd);
	close(serverSocketFd);
	delete[] buffer;
}
//------------------------------------------------------------------------------
int ADT_TCPSocket::listen_callback(GIOChannel *source, GIOCondition condition, void *data)
{cout << "listen_callback" << endl;

	socklen_t clilen = sizeof(((ADT_TCPSocket*)data)->client_addr);
 	((ADT_TCPSocket*)data)->clientSocketFd = accept(g_io_channel_unix_get_fd(source), (struct sockaddr *) &((ADT_TCPSocket*)data)->client_addr, &clilen);
 		
	if(((ADT_TCPSocket*)data)->clientSocketFd < 0) 
        	cerr << "ERROR on accept" << endl;

       	GIOChannel* channel = g_io_channel_unix_new (((ADT_TCPSocket*)data)->clientSocketFd);
	((ADT_TCPSocket*)data)->rxid = g_io_add_watch(channel, (GIOCondition)(G_IO_IN | G_IO_HUP), &tcp_callback, data);
	g_io_channel_unref(channel);
	return true;
}
//------------------------------------------------------------------------------
int ADT_TCPSocket::tcp_callback(GIOChannel *source, GIOCondition condition, void *data)
{

	cout << "tcpcallback: " << endl;
	
	if(condition == G_IO_IN)
	{
		cout << "G_IO_IN" << endl;
	}
	if(condition == G_IO_HUP)
	{
		cout << "G_IO_HUP" << endl;
	}

	bzero(((ADT_TCPSocket*)data)->buffer,BUFFERSIZE);
	((ADT_TCPSocket*)data)->bufferLength = recv(g_io_channel_unix_get_fd(source),((ADT_TCPSocket*)data)->buffer,BUFFERSIZE, 0);
	if (((ADT_TCPSocket*)data)->bufferLength <= 0) 
	{
		cout << "ERROR reading from socket (tcp_callback): " << ((ADT_TCPSocket*)data)->bufferLength << endl;  
		g_io_channel_shutdown(source, true, NULL);
		return false;  	
	}   	

	((ADT_TCPSocket*)data)->onGetData(((ADT_TCPSocket*)data)->client_addr);
	return true;
//cout << "END tcpcallback" << endl;
}
//------------------------------------------------------------------------------
//	Send *data to fd Socket
int ADT_TCPSocket::sendData(int fd, const unsigned char *data, int length) const
{
	if(send(fd, data, length, 0) < 0)
	{
		cerr << "ERROR writing to socket" << endl;
		return false;
	}
 return true;
}
//------------------------------------------------------------------------------
int ADT_TCPSocket::sendData(const unsigned char* data, unsigned int length) const
{
	sendData(clientSocketFd, data, length);
}
//------------------------------------------------------------------------------
int ADT_TCPSocket::sendData(const char* data, unsigned int length) const
{
	sendData(clientSocketFd, (unsigned char *)data, length);
}
//------------------------------------------------------------------------------
int ADT_TCPSocket::connectToServer(const char *_server, int portno)
{
	struct hostent *server;
	struct sockaddr_in serv_addr;
	
	clientSocketFd = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocketFd < 0)
	{
		cerr << "ERROR opening socket" << endl;
		return false;
	}
	server = gethostbyname(_server);
	if (server == NULL)
	{
		cerr << "ERROR, no such host\n" << endl;
		return false;
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	
	if (connect(clientSocketFd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
	{
		cout << "ERROR connecting" << endl;
		return false;
	}
	GIOChannel* channel = g_io_channel_unix_new (clientSocketFd);
	g_io_add_watch(channel, (GIOCondition)(G_IO_IN | G_IO_HUP), &tcp_callback, this);
	g_io_channel_unref(channel);
	return true;
}
//------------------------------------------------------------------------------
// Send data as client
//------------------------------------------------------------------------------
int ADT_TCPSocket::sendData(const char *_server, int portno, const unsigned char *data,  int length) const
{
	sendData(_server, portno, (const char *)data, length);
}
//------------------------------------------------------------------------------
int ADT_TCPSocket::sendData(const char *_server, int portno, const char *data,  int length) const
{
	int sockfd;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		cerr << "ERROR opening socket" << endl;
		return false;
	}
	server = gethostbyname(_server);
	if (server == NULL)
	{
		cerr << "ERROR, no such host\n" << endl;
		return false;
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
	{
		cout << "ERROR connecting" << endl;
		return false;
	}
//	char* databuffer = new char[BUFFERSIZE];
	sendData(sockfd, (unsigned char *)data, length);
//	bzero(databuffer,256);
//	if (read(sockfd,databuffer,255) < 0) 
//		cout << "ERROR reading from socket" << endl;
//	printf("%s\n",databuffer);
	close(sockfd);
 return 0;
}
//------------------------------------------------------------------------------
//	call back function activated when data is recived
void ADT_TCPSocket::onGetData(struct sockaddr_in client)
{	cout << "onGetData()" << endl;
	cout << "From: " << inet_ntoa(client.sin_addr) << endl;
     	cout << "Message: " << buffer << endl;
}
//------------------------------------------------------------------------------
