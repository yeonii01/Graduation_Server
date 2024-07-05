#pragma once
#include "stdafx.h"

enum COMP_TYPE { C_ACCEPT, C_RECV, C_SEND, C_RANDOM_MOVE, C_TARGET_MOVE};
class Exp_Over
{
public:
	Exp_Over();
	Exp_Over(unsigned char* packet, int packet_size);

public:
	WSAOVERLAPPED m_wOver;
	WSABUF m_wBuf;
	char m_cBuf[CHAT_SIZE];
	COMP_TYPE m_cType;
	int m_iTarget_obj;
};
