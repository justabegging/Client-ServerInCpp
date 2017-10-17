/*
 * Client.h
 *
 *	CONTROLLER
 *
 *  Created on: 11 okt 2017
 *      Author: kaiham-3
 */

#ifndef CLIENT_H_
#define CLIENT_H_
#include "protocol.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "sendToJava.h"

#define DEFAULT_BUFLEN	512 //Maybe need bigger...

//using namespace std;

class sendToJava;

class Client {

private:
	struct sockaddr_in sa;
	struct JoinMsg joinmsg;
	struct MsgHead* msghead;
	struct LeaveMsg leavemsg;

	//Change
	struct ChangeMsg* changemsg;
	struct NewPlayerMsg newplayermsg;
	struct PlayerLeaveMsg* playerleavemsg;
	struct NewPlayerPositionMsg* newplayerpositionmsg;

	//Event
	struct EventMsg eventmsg;
	struct MoveEvent moveevent;

	//Coordinates
	struct Coordinate* coordinate;

	sendToJava* sendtojava;


	int res;
	int SocketFD;
	char sendbuf[DEFAULT_BUFLEN];
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	bool isConnected;
	int sockMsg;
	int ID;
	int idNum;
	std::string data;
	int currentSeq = 0;

	int xCoord;
	int yCoord;

	int sockToJava;
	bool isConnectedToJava = false;
	bool idIsSet = false;

	int main();

	void setID(int idNum);
	int connectToServer();

	bool sendData(std::string data);

	void sendLeaveServer();
	void sendEventServer(int xCoord, int yCoord);
	void shutdownSocket();
	void sendNewCoordinate();
	void NewPlayerPositionHandler(int counter);
	void setUpSocket();
	void receiveBuffer(int counter);
	void ChangeMsgHandler(int counter);
	void Run();
	void sendJoinServer();
	void receiveFromServer();
	void joinHandler(int counter);

	void clientToJava(std::string msg);

public:

	Client();



	virtual ~Client();



};

#endif /* CLIENT_H_ */
