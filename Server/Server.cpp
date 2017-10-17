/*
 * Server.cpp
 *
 *  Created on: 17 okt 2017
 *      Author: kaiham-3
 */

#include "Server.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

#define SERVERADDRESS "130.240.40.22"
#define PORTNUMBER 50000


Server::Server() {
	// TODO Auto-generated constructor stub

	createSocket();
}

Server::~Server() {
	// TODO Auto-generated destructor stub
}

void Server::debugString() {
	std::cout<<"Wello Horld\n";
}
void Server::createSocket() {
	serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == -1) {
		perror("Cannot create socket");
		exit(EXIT_FAILURE);
	}
	std::cout<<"Socket created succes..."<<std::endl;

	//prep of the server's local address
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORTNUMBER);
	res = inet_addr(SERVERADDRESS);
	memset(&serverSocket, 0, sizeof(serverSocket));

	std::cout<<"Try to Bind..."<<std::endl;
	bindSocket();
}

void Server::bindSocket() {
	netCodeop = bind(serverSocket, (struct sockaddr*) &server_addr, sizeof(server_addr));
	if (serverSocket == -1) {
		perror("Cannot binding Socket...");
		exit(-1);
	}
	std::cout<<"Bind Success...\n";
	std::cout<<"Try to listen...\n";
	listenSocket();
}

void Server::listenSocket() {
	netCodeop = listen(serverSocket, 10);
	if (netCodeop == -1) {
		perror("Listen Failed...");
		exit(-1);
	}
	std::cout<<"Listen Success...\n";
	printf("Server ready... \nbind Ok! \nPort Numer: %d", PORTNUMBER, "IP Address: %d", SERVERADDRESS);

	std::cout<<"Waiting for Connection...\n";
	//Waiting for connection
	while(true) {
		connectSocket();
	}
}

void Server::connectSocket(){
	client_addr_len = sizeof(client_addr);
	connect_Socket = accept(serverSocket, (struct sockaddr *) &client_addr, &client_addr_len);
	if (connect_Socket == -1) {
		perror("Connection Failed...\n");
		exit(-1);
	}
	std::cout<<"Connection Success...\n";

	client_address = inet_ntoa(client_addr.sin_addr);
	printf("\nClient @ %s connects on socket %d\n", client_address, serverSocket);
	receiveFromClient();
}

void Server::receiveFromClient() {
	netCodeop = recv(serverSocket, buffer, MAXBUF, 0);
	while (netCodeop > 0) {
		buffer[netCodeop] = '\0';
		printf(">> %s: %s\n, client_address, buffer");
	}
	close(serverSocket);
}
