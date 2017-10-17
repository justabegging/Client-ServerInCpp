/*
 * Server.h
 *
 *  Created on: 17 okt 2017
 *      Author: kaiham-3
 */

#ifndef SERVER_H_
#define SERVER_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

#include "Protocol.h"
#include "ServerMain.h"

#define MAXBUF 128

class Server {

public:
	Server();

	virtual ~Server();


private:
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_addr_len;
	char buffer[MAXBUF];
	int serverSocket, netCodeop, res, connect_Socket;
	char * client_address;

	int main();

	void createSocket();
	void bindSocket();
	void listenSocket();
	void connectSocket();
	void receiveFromClient();
	void debugString();

};
#endif /* SERVER_H_ */
