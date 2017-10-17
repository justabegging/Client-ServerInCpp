/*
 * ClientToJava.cpp
 *
 *  Created on: 17 okt 2017
 *      Author: kaiham-3
 */

#include "ClientToJava.h"

namespace std {

ClientToJava::ClientToJava(int * clientConn, int * x, int * y, int * clientid) {
	// TODO Auto-generated constructor stub
	socketptr = clientConn;
	xptr = x;
	yptr = y;
	idptr = clientid;
	setupSocket();
}

void ClientToJava::setupSocket(){
    conn = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); // for JAVA server
    if(conn == -1){
        std::cout << "Socket failed to create (Java)" << std::endl;
        exit(EXIT_FAILURE);
    }
    memset(&sa, 0, sizeof sa);  // initialize all undeclared to 0
        sa.sin_family = AF_INET;    // Set family to AF_INET
        sa.sin_port = htons(6543);  // port to connect to.
        res = inet_pton(AF_INET, "130.240.40.22", &sa.sin_addr); // puts the string of IP to binary form for AF_INET.
        if (connect(conn, (struct sockaddr *)&sa, sizeof sa) == -1) { //checks if connect succeeds or not
            perror("connect failed");
            close(conn);
            exit(EXIT_FAILURE);
        }
        cout << "Connected!" << endl;
        std::thread * t1 = new std::thread(&ClientToJava::threadFunc, this);
        //std::thread t1()
        //std::string str = "join;5;13;14;";
        //sendToJava(str);
}

void ClientToJava::sendToJava(std::string msg){
    send(conn, msg.data(), msg.size(), 0);
    //send(*socketptr, msg.data(), msg.size(), 0);
    cout << "Sent the messages!" << endl;
}

void * ClientToJava::threadFunc(){
    while(true){
        int recvSize = recv(conn, javaRecvBuf, sizeof(javaRecvBuf), 0);
        if(recvSize == -1){
            cout << "Error\n";
            exit(EXIT_FAILURE);
        }else{
            cout << "buf: " << javaRecvBuf << endl;
            int key = *javaRecvBuf - '0';
            if(key == 1){
                sendMoveMsg(0, -1);
            }else if(key == 2){
                sendMoveMsg(-1,0);
            }else if(key == 3){
                sendMoveMsg(0, 1);
            }else if(key == 4){
                sendMoveMsg(1, 0);
            }
        //sendbuf = classptr->sendMoveMsg(-1);
        //send(*socketptr, sendbuf, sizeof(sendbuf), 0);
        }
    }
}

void ClientToJava::sendMoveMsg(int x, int y){
    moveevent.event.head.id = *idptr;
    moveevent.event.head.length = sizeof(moveevent);
    moveevent.event.head.seq_no = 1;
    moveevent.event.head.type = Event;
    moveevent.event.type = Move;
    moveevent.pos.x = *xptr + x;
    moveevent.pos.y = *yptr + y;
    moveevent.dir.x = 1;
    moveevent.dir.y = 1;
    char sendbuf[sizeof(moveevent)];
    memcpy((void*)sendbuf, (void*)&moveevent, sizeof(sendbuf));
    if(send(*socketptr, sendbuf, sizeof(sendbuf), 0) == -1){
        cout << "Failed to send message";
        exit(EXIT_FAILURE);
    }else{
        cout << "Sent the move message!" << endl;
    }

}
ClientToJava::~ClientToJava() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
