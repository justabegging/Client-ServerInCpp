/*
 * sendToJava.cpp
 *
 *  Created on: 14 okt 2017
 *      Author: kaiham-3
 */

#include "sendToJava.h"



sendToJava::sendToJava() {
	// TODO Auto-generated constructor stub
	ipAddress = "130.240.40.22";
	port = 9876;
	isConnectedToJava = false;
	connectionStatus = 0;
	socketIsActive = false;


	setUpSocket();
	ConnectToJava();
}

sendToJava::~sendToJava() {
	// TODO Auto-generated destructor stub
}

void sendToJava::setUpSocket() {

	sockToJava = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockToJava == -1) {
		std::cout << "Socket to Java failed to create..." << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cout << "Socket to Java created SUCCESS" << std::endl;
	socketIsActive = true;

}

void sendToJava::ConnectToJava() {

	std::cout << "Trying to connect..." << std::endl;
	if(socketIsActive){
		memset(&sa, 0, sizeof(sa));
		sa.sin_family = AF_INET;
		sa.sin_port = htons(port);
		sa.sin_addr.s_addr = inet_addr(ipAddress);

		connectionStatus = connect(sockToJava, (sockaddr *) &sa, sizeof(sa));

		if (connectionStatus < 0) {
			perror("Connection Failed...");
			close(sockToJava);
			exit(EXIT_FAILURE);
		}
		std::cout << "Connected to Java" << std::endl;
	}
}

void sendToJava::clientToJava(std::string msg) {
	send(sockToJava, msg.data(), msg.size(), 0);
	std::cout << "Sent Success!" << std::endl;
}

