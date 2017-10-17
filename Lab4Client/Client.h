/*
 * Client.h
 *
 *	CONTROLLER
 *
 *  Created on: 11 okt 2017
 *      Author: kaiham-3
 */
#pragma once
#ifndef CLIENT_H_
#define CLIENT_H_
#define DEFAULT_BUFLEN 512
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include "Protocol.h"
#include "Client.h"
#include "ClientToJava.h"
#include <pthread.h>
#include <thread>

using namespace std;

class ClientToJava;

class Client {

private:
    //Client klient;
    struct JoinMsg joinmsg;
    struct MoveEvent moveevent;
    struct MsgHead* msghead;
    struct ChangeMsg* changemsg;
    struct NewPlayerMsg* newplayermsg;
    struct NewPlayerPositionMsg* newplayerpos;
    struct LeaveMsg* leavemsg;
    struct sockaddr_in sa;
    char recvBuf[DEFAULT_BUFLEN];
    char sendBuf[DEFAULT_BUFLEN];
    char * charptr[56];
    unsigned int res, currentSeq;
    signed int conn2, xCord, yCord;
    bool gotID = false;
    ClientToJava *guiclient;
    void connectToHost();
    void translateMessage(int bytesRead);
    void changeMessageHandler(int bytesRead);
    void closeSocket();
public:
    int conn, clientid;
    void recieveMessage();
    Client();
    virtual ~Client();
    void sendJoinMsg();
    static void threadStart();
    //void sendMoveMsg(int x, int y);
    char * sendMoveMsg(int x);
};

#endif /* CLIENT_H_ */
