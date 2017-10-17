/*
 * protocol.h
 *
 *  Created on: 11 okt 2017
 *      Author: kaiham-3
 */

#ifndef PROTOCOL_H_
#define PROTOCOL_H_

//using namespace std;

class protocol {
public:
	protocol();
	virtual ~protocol();
};


#endif /* PROTOCOL_H_ */

#define MAXNAMELEN 32

enum ObjectDesc
	{
		Human,
		NonHuman,
		Vehicle,
		StaticObject
	};

	enum ObjectForm
	{
		Cube,
		Sphere,
		Pyramid,
		Cone
	};

	struct Coordinate
	{
		int x;
		int y;
	};

	enum MsgType
	{
		Join,			//Client joining game at server
		Leave,			//CLient leaving game
		Change,			//Information to clients
		Event,			//Information from clients to server
		TextMessage		//Send text messages to one or all
	};

	//Included first in all messages

	struct MsgHead
	{
		unsigned int length;	//Total length for whole message
		unsigned int seq_no;	//Sequence number
		unsigned int id;		//Client ID or 0
		MsgType type;			//Type of message
	};

	//Message type Join (Client -> Server)

	struct JoinMsg
	{
		MsgHead		head;
		ObjectDesc	desc;
		ObjectForm	form;
		char		name[MAXNAMELEN];
	};

	//Message type Leave (Client -> Server)

	struct LeaveMsg
	{
		MsgHead		head;
	};

	//Message type Change (Server -> Client)

	enum ChangeType
	{
		NewPlayer,
		PlayerLeave,
		NewPlayerPosition
	};

	//Included first in all Change message

	struct ChangeMsg
	{
		MsgHead		head;
		ChangeType	type;
	};

	//variations of ChangeMsg

	struct NewPlayerMsg
	{
		ChangeMsg	msg;				//Change message header with new client id
		ObjectDesc	desc;
		ObjectForm	form;
		char		name[MAXNAMELEN];	//nullterminated!, or emtyp
	};

	struct PlayerLeaveMsg
	{
		ChangeMsg	msg;				//Change message header with new client id
	};

	struct NewPlayerPositionMsg
	{
		ChangeMsg	msg;				//Change message header
		Coordinate	pos;				//New object position
		Coordinate	dir;				//New object direction
	};

	//Messages of type Event (Client -> Server)

	enum EventType
	{
		Move
	};

	//Included first in all Event messages

	struct EventMsg
	{
		MsgHead		head;
		EventType	type;
	};

	//Variantions of EventMsg

	struct MoveEvent
	{
		EventMsg	event;
		Coordinate	pos;				//New object position
		Coordinate	dir;				//New object direction
	};

	//Messages of type TextMessage

	struct TextMessageMsg				//Optional at client side!!!
	{
		MsgHead		head;
		char		text[1];			//NULL-terminerad arry av char.
	};

