/*
 * sendToJava.h
 *
 *  Created on: 15 okt 2017
 *      Author: kaiham-3
 */

#ifndef SENDTOJAVA_H_
#define SENDTOJAVA_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "Client.h"



class sendToJava {

public:



	void clientToJava(std::string msg);

	sendToJava();
	virtual ~sendToJava();

private:

	struct sockaddr_in sa;
	int res;
	bool isConnectedToJava;
	char* ipAddress;
	int port;
	int connectionStatus;
	bool socketIsActive;
	int sockToJava;

	void ConnectToJava();
	void setUpSocket();


};



 /* namespace std */
#endif /* SENDTOJAVA_H_ */
