/*
 * Client.cpp
 *
 *  Created on: 11 okt 2017
 *      Author: kaiham-3
 */
#include "Client.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>




#define IP_NUMBER "130.240.40.22"
#define PORT_NUMBER 49152



Client::Client() {


	isConnected = false;
	sockMsg = -1;

	connectToServer();
	sendJoinServer();

}

Client::~Client() {
	// TODO Auto-generated destructor stub
	//shutdownSocket();
}


//Kör run via Thread
void Client::Run() {

	std::cout << "try to run()" << std::endl;
	std::cout << isConnected << std::endl;

	//char recvbuf[256];
	while(isConnected) {

		//isConnected = false;
		std::cout << "In while loop" << std::endl;
		if(recv(SocketFD, (char *) recvbuf, (int) strlen(recvbuf), 0) == -1){
			std::cout << "Error... \n there's nothing from Server" << std::endl;
			break;
		} else {
			std::cout << "Waiting for data..." << std::endl;
			//receiveBuffer();
			receiveFromServer();
			isConnected = false;
		}
		std::cout << "After if statement..." << std::endl;
	}
}

int Client::connectToServer() {


	SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SocketFD == -1) {
		perror("Cannot create socket");
		exit(EXIT_FAILURE);
	}

	memset(&sa, 0, sizeof sa);

	sa.sin_family = AF_INET;
	sa.sin_port = htons(PORT_NUMBER);
	res = inet_pton(AF_INET, IP_NUMBER, &sa.sin_addr);

	if (connect(SocketFD, (struct sockaddr *)&sa, sizeof (sa)) == -1) {
		perror("Connect failed");
		close(SocketFD);
		exit(EXIT_FAILURE);
	}

	isConnected = true;
	std::cout << "SUCCESS" << std::endl;

	sendJoinServer();

	return 0;
}

bool Client::sendData(std::string data) {
	if (send(SocketFD, data.c_str(), (int) strlen(data.c_str()), 0) < 0) {
		perror("Failed to send...");
		return false;
	}
	std::cout << "Data sended" << std::endl;
	isConnected = true;
	return true;
}

void Client::sendJoinServer(){

	joinmsg.head.id = 0;
	joinmsg.head.length = sizeof(joinmsg);
	joinmsg.head.seq_no = currentSeq;
	joinmsg.head.type = Join;

	char sendbuf[sizeof(joinmsg)];

	memcpy((void*)sendbuf, (void*)&joinmsg, sizeof(joinmsg));
	if (send(SocketFD, sendbuf, sizeof(sendbuf) , 0) == -1) {
		perror("Failed to send Join...");
	} else {
		std::cout<<"Join sent Success"<<std::endl;
	}

	while(true) {
		receiveFromServer();
	}
}

void Client::sendLeaveServer(){
	leavemsg.head.id = ID;
	leavemsg.head.length = sizeof(leavemsg);
	//leavemsg.head.seq_no = NULL;
	leavemsg.head.type = Leave;

	char sendbuf[sizeof(leavemsg)];
	memcpy((void*)sendbuf, (void*)&leavemsg, sizeof(leavemsg));
	send(SocketFD, sendbuf, sizeof(sendbuf) , 0);
}

void Client::sendEventServer(int x, int y){

	moveevent.event.head.id = ID;
	moveevent.event.head.length = sizeof(eventmsg);
	moveevent.event.head.seq_no = currentSeq += 1;
	moveevent.event.head.type = Event;
	moveevent.event.type = Move;

	moveevent.pos.x = xCoord + x;
	moveevent.pos.y = yCoord + y;

	moveevent.dir.x = 1;
	moveevent.dir.y = 1;

	char sendbuf[sizeof(moveevent)];
	memcpy((void*) sendbuf, (void*)&moveevent, sizeof (moveevent));
	if(send(SocketFD, sendbuf, sizeof(sendbuf), 0) < 0){
		perror("Failed to send position...");
	}
	std::cout<<"Position sent SUCCESS"<<std::endl;
	receiveFromServer();
}

void Client::receiveFromServer(){

	int Data = recv(SocketFD, recvbuf, sizeof(recvbuf), 0);
	int DataRead = 0;
	std::cout<<"Data Size: "<<Data<<std::endl;
	if ( Data > DataRead ){
		while (Data > DataRead){
			msghead = (MsgHead*)&recvbuf[DataRead];
			std::cout<<"Received data: " <<msghead<<std::endl;
			std::cout<<"ID: "<<msghead->id<<std::endl;
			std::cout<<"Data length: "<<msghead->length<<std::endl;
			std::cout<<"Data sequence: "<<msghead->seq_no<<std::endl;
			std::cout<<"Data type (0 for join, 2 for change): "<<msghead->type<<std::endl;

			receiveBuffer(DataRead);
			DataRead += msghead->length;
			//break;
		}
	} else {
		perror("Failed to receive");
		exit(-1);
	}
}

void Client::receiveBuffer(int counter) {			//read data from server

	switch (msghead -> type) {

		case Join:
			std::cout << "join" << std::endl;
			joinHandler(counter);
			break;

		case Leave:
			std::cout<<"Leaving..."<<std::endl;
			shutdownSocket();
			break;

		case Change:
			std::cout<<"Change"<<std::endl;
			ChangeMsgHandler(counter);
			break;


		case Event:
			std::cout<<"Event"<<std::endl;
			break;

		case TextMessage:
			puts("TextMessage");
			//cout << text[1] <<endl;
			break;

	}
}

void Client::setID(int idNum) {

	if(!idIsSet) {
		ID = idNum;
		idIsSet = true;
	}
}

void Client::joinHandler(int counter) {
	msghead = (MsgHead*)&recvbuf[counter];
	if(!idIsSet){
		setID(msghead->id);
		std::cout << "My ID: " << ID << std::endl;

		std::string msg = "My ID;4;";
		//stringstream convert;
		//convert<<ID;
		//msg = convert.str();
		//cout<<"Test int to string: " << msg << endl;
		//msg = "My ID;" + std::to_string(ID) + ";";
		sendtojava->clientToJava(msg);
	}
}

void Client::ChangeMsgHandler(int counter){

	changemsg = (ChangeMsg*)&recvbuf[counter];
	//coordinate = (Coordinate*)&recvbuf[counter];

	switch(changemsg -> type) {
		std::cout<<"hello im in switch"<<std::endl;

		case NewPlayer:
			std::cout << "New player" << std::endl;
		break;

		case PlayerLeave:
			std::cout << "Player leave" << std::endl;
		break;

		case NewPlayerPosition:
			std::cout << "New player position" << std::endl;
		NewPlayerPositionHandler(counter);
		break;

	}

}

void Client::NewPlayerPositionHandler(int counter){
	newplayerpositionmsg = (NewPlayerPositionMsg*)&recvbuf[counter];
	std::cout<<newplayerpositionmsg->pos.x<<std::endl;
	std::cout<<newplayerpositionmsg->pos.y<<std::endl;
	xCoord = newplayerpositionmsg->pos.x;
	yCoord = newplayerpositionmsg->pos.y;


	//string msgToJava = "New player position;" + std::to_string(ID) + ";" + std::to_string(xCoord) + ";" + std::to_string(yCoord) + ";";
	//sendtojava.clientToJava(msgToJava);

	std::cout<<"Move msg have been sent to Java..."<<std::endl;

	std::cout<<xCoord<<std::endl;
	std::cout<<yCoord<<std::endl;
}


void Client::shutdownSocket() {
	close(SocketFD);
	std::cout << "shutdown and close SUCCESS" << std::endl;
	isConnected = false;
}

