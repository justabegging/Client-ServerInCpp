/*
 * protocol.h
 *
 *  Created on: 11 okt 2017
 *      Author: kaiham-3
 */

#pragma once
#ifndef PROTOCOL_H_
#define PROTOCOL_H_
#define MAXNAMELEN 32

#include <iostream>
#include "string.h"

    enum ObjectDesc{
        Human,
        NonHuman,
        Vehicle,
        StaticObject
    };

    enum ObjectForm{
        Cube,
        Sphere,
        Pyramid,
        Cone
    };

    enum MsgType{
        Join,
        Leave,
        Change,
        Event,
        TextMessage
    };

    enum EventType{
        Move
    };

    enum ChangeType{
        NewPlayer,
        PlayerLeave,
        NewPlayerPosition
    };

    struct Coordinate{
        int x;
        int y;
    };

    struct MsgHead{
        unsigned int length;
        unsigned int seq_no;
        unsigned int id;
        MsgType type;
    };

    struct ChangeMsg{
        MsgHead head;
        ChangeType type;
    };

    struct EventMsg{
        MsgHead head;
        EventType type;
    };

    struct LeaveMsg{
        MsgHead head;
    };

    struct MoveEvent{
        EventMsg event;
        Coordinate pos;
        Coordinate dir;
    };

    struct JoinMsg{
        MsgHead head;
        ObjectDesc desc;
        ObjectForm form;
        char name[MAXNAMELEN];
    };

    struct NewPlayerMsg{
        ChangeMsg msg;
        ObjectDesc desc;
        ObjectForm form;
        char name[MAXNAMELEN];
    };

    struct PlayerLeaveMsg{
        ChangeMsg msg;
    };

    struct NewPlayerPositionMsg{
        ChangeMsg msg;
        Coordinate pos;
        Coordinate dir;
    };

class Protocol {

private:

public:
    void getJoinMsg();
    Protocol();
    virtual ~Protocol();
};

#endif /* PROTOCOL_H_ */
