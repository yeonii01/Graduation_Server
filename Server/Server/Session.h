#pragma once
#include "EXP_Over.h"
class Session
{
public:
	Session();
	~Session();

public:
	void do_recv();
	void do_send(void* packet, int packet_size);

public:
	int					m_iId;
	SOCKET				m_sClient;
	int					m_iRemain_data;
	Exp_Over			m_eExp_over;
};