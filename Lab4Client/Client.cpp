/*
 * Client.cpp
 *
 *  Created on: 11 okt 2017
 *      Author: kaiham-3
 */
#include "Client.h"

Client::Client() {
    guiclient = new ClientToJava(&conn, &xCord, &yCord, &clientid);
    connectToHost();
}

void Client::connectToHost(){
    conn = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //for c++ server
    if(conn == -1){
        std::cout << "Socket failed to create(C++)" << std::endl;
        exit(EXIT_FAILURE);
    }
    memset(&sa, 0, sizeof sa);  // initialize all undeclared to 0
    sa.sin_family = AF_INET;    // Set family to AF_INET
    sa.sin_port = htons(49152); // port to connect to.
    res = inet_pton(AF_INET, "130.240.40.22", &sa.sin_addr); // puts the string of IP to binary form for AF_INET.
    if (connect(conn, (struct sockaddr *)&sa, sizeof sa) == -1) { //checks if connect succeeds or not
        perror("connect failed");
        close(conn);
        exit(EXIT_FAILURE);
    }
    cout << "Connected!" << endl;
    sendJoinMsg();
    while(true){
        recieveMessage();
    }
}

void Client::threadStart(){
}

void Client::recieveMessage(){
    int dataSize = recv(conn, recvBuf, sizeof(recvBuf), 0);
    int bytesRead = 0;
    if(dataSize == -1){
        cout << "Failed to recieve a message";
    }else{
        while(dataSize > bytesRead){
            msghead = (MsgHead*)&recvBuf[bytesRead];
            cout << "Recieved a message, size: "<< dataSize << ", read: " << bytesRead << ", bytes read now: "<< msghead->length << endl;
            cout << "id: " << msghead->id << "\n";
            /*cout << "length: " << msghead->length << "\n";
            cout << "seq_no: " << msghead->seq_no << "\n";*/
            currentSeq = msghead->seq_no;                // get current seq_no
            cout << "type: " << msghead->type << endl;
            translateMessage(bytesRead);
            bytesRead += msghead->length;
        }
    }
}

void Client::translateMessage(int bytesRead){
    msghead = (MsgHead*)&recvBuf[bytesRead];
    switch(msghead->type){
        case(Join): {
            cout << "this was a join message"<< endl << endl << endl;
            if(!gotID){
                std::string sendMsg = "MyId;"+std::to_string(msghead->id)+";";
                guiclient->sendToJava(sendMsg);
                clientid = msghead->id;
                gotID = true;
            }
            break;
        }
        case(Leave): {
            cout << "This was a leave message" << endl << endl << endl;
            break;
        }
        case(Change): {
            changeMessageHandler(bytesRead);
            break;
        }
        case(Event): {
            cout << "This was a event message" << endl << endl << endl;
            break;
        }
        case(TextMessage): {
            cout << "This was a text message" << endl << endl << endl;
            break;
        }
    }
}

void Client::changeMessageHandler(int bytesRead){
    changemsg = (ChangeMsg*)&recvBuf[bytesRead];
    switch(changemsg->type){
        case(NewPlayer): {
            newplayermsg = (NewPlayerMsg*)&recvBuf[bytesRead];
            cout << "Change: new player message, name: "<< newplayermsg->name << endl << endl << endl;
            // dont know if this is needed to java
            break;
        }
        case(PlayerLeave): {
            leavemsg = (LeaveMsg*)&recvBuf[bytesRead];
            cout << "Change: player left message!" << endl << endl << endl;
            std::string sendMsg = "PlayerLeave;"+std::to_string(leavemsg->head.id)+";";
            guiclient->sendToJava(sendMsg);
            break;
        }
        case(NewPlayerPosition): {
            newplayerpos = (NewPlayerPositionMsg*)&recvBuf[bytesRead];
            cout << "Change: new player position message: (" << newplayerpos->pos.x << "," << newplayerpos->pos.y << ")";
            cout << ", (" << newplayerpos->dir.x << "," << newplayerpos->dir.y << ")" << endl << endl << endl;
            std::string sendMsg = "NewPlayerPosition;"+std::to_string(newplayerpos->msg.head.id)+";"+std::to_string(newplayerpos->pos.x)+";"+std::to_string(newplayerpos->pos.y)+";";
            guiclient->sendToJava(sendMsg);
            if(msghead->id == clientid){
                xCord = newplayerpos->pos.x;
                yCord = newplayerpos->pos.y;
            }
            break;
        }
    }
}

void Client::sendJoinMsg(){
    joinmsg.head.id = 0;
    joinmsg.head.length = sizeof(joinmsg);
    joinmsg.head.seq_no = 0;
    joinmsg.head.type = Join;
    char sendBuf[sizeof(joinmsg)];
    memcpy((void*)sendBuf, (void*)&joinmsg, sizeof(sendBuf));
    if(send(conn, sendBuf, sizeof(sendBuf), 0) == -1){
        cout << "Failed to send message";
        exit(EXIT_FAILURE);
    }else{
        cout << "Sent the join message!" << endl;
    }
}

/*char * Client::sendMoveMsg(int x){
    moveevent.event.head.id = clientid;
    moveevent.event.head.length = sizeof(moveevent);
    moveevent.event.head.seq_no = currentSeq + 1;
    moveevent.event.head.type = Event;
    moveevent.event.type = Move;
    moveevent.pos.x = 100;
    moveevent.pos.y = 100+x;
    moveevent.dir.x = 1;
    moveevent.dir.y = 1;
    char sendBuf[sizeof(joinmsg)];
    memcpy((void*)sendBuf, (void*)&moveevent, sizeof(sendBuf));
    //return &moveevent;
    if(send(conn, sendBuf, sizeof(sendBuf), 0) == -1){
        cout << "Failed to send message";
        exit(EXIT_FAILURE);
    }else{
        cout << "Sent the move message!" << endl;
    }

}*/

void Client::closeSocket(){
    cout << "Closing socket...";
    close(conn);                    //closes the socket.
    cout << "Socket closed!";
}

Client::~Client() {
    // TODO Auto-generated destructor stub
}
