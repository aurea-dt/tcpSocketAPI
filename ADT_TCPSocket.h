////////////////////////////////////////////////////////////////////////////////
// ADT_TCPSocket.h
// Mario Chirinos Colunga
// Áurea Desarrollo Tecnológico
// 2012/05/11
//------------------------------------------------------------------------------
// Notes:
//	Berkeley sockets
//
////////////////////////////////////////////////////////////////////////////////

#ifndef ADT_TCPSOCKET_H
#define ADT_TCPSOCKET_H

// your public header include
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <glib.h>

#include <arpa/inet.h>
#include <unistd.h>

using namespace std;
//------------------------------------------------------------------------------
// The declaration of your class...
#define	CONNQUEUE	1 // connection backlog queue
#define	BUFFERSIZE	255
//------------------------------------------------------------------------------
class ADT_TCPSocket
{
 private:
 	int rxid;
 	GIOChannel* serverChannel;
 	GIOChannel* clientChannel;
 
 	int serverSocketFd;
	struct sockaddr_in server_addr;
	
 	int clientSocketFd;
	struct sockaddr_in client_addr;
	
	int sendData(int fd, const unsigned char *data,  int length) const;
	int sendToServer(const unsigned char* data, unsigned int length) const;
// 	const char* sendToServer(const char *server, int port, const char *data,  int length) const;// send and wait for response.
 	
	virtual void onGetData(struct sockaddr_in client);
	
	static int listen_callback(GIOChannel *source, GIOCondition condition, void *data);
	static int tcp_callback(GIOChannel *source, GIOCondition condition, void *data);
	
 protected:
  	unsigned char* buffer;
  	int bufferLength;
  	
 public: 
 	int connectToServer(const char *_server, int portno);
 	int sendData(const unsigned char* data, unsigned int length) const;
 	int sendData(const char* data, unsigned int length) const;
 	int sendData(const char *address, int port, const char *data,  int length) const;
 	int sendData(const char *address, int port, const unsigned char *data,  int length) const;
 	//int sendToClient(const unsigned char* data, unsigned int length) const;

 	ADT_TCPSocket(int port);		// port to allow clients to communicate with the tcp server.
	~ADT_TCPSocket();
};
//------------------------------------------------------------------------------
#endif
