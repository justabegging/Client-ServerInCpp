/*
 * ClientToJava.h
 *
 *  Created on: 17 okt 2017
 *      Author: kaiham-3
 */

#ifndef CLIENTTOJAVA_H_
#define CLIENTTOJAVA_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <pthread.h>
#include "Client.h"
#include "Protocol.h"
#define DEFAULT_BUFLEN 512

using namespace std;

class ClientToJava {

private:
	Client * classptr;
	int * socketptr, * xptr, * yptr, * idptr;
	int conn, res;
	void setupSocket();
	std::string recvStr;
	struct MoveEvent moveevent;
	char sendbuf[56];
	char javaRecvBuf[DEFAULT_BUFLEN];
	struct sockaddr_in sa;
public:

	void * threadFunc();
	void sendToJava(std::string msg);
	void sendMoveMsg(int x, int y);
	ClientToJava(int * sock, int * x, int * y, int * id);
	virtual ~ClientToJava();
};


#endif /* CLIENTTOJAVA_H_ */
