#pragma once
#include "stdafx.h"

enum COMP_TYPE { C_ACCEPT, C_RECV, C_SEND, C_TARGET_MOVE};
class Exp_Over
{
public:
	Exp_Over();
	Exp_Over(unsigned char* packet, int packet_size);

public:
	WSAOVERLAPPED _over;
	WSABUF _wsabuf;
	char _buf[CHAT_SIZE];
	COMP_TYPE _comp_type;
	int _ai_target_obj;
};
