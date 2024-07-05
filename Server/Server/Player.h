#pragma once
#include "Session.h"

#include "stdafx.h"

enum P_STATE {P_IDLE, P_MOVE, P_ATTACK, P_DIE};
enum S_STATE { ST_FREE, ST_ALLOC, ST_INGAME };
class Player : public Session
{
public:
	Player();
	~Player();

public:
	void send_login_info_packet();
	void send_login_fail_packet();
	void send_add_object_packet(Player& player);
	void send_remove_object_packet(int c_id);
	void send_move_object_packet(Player& player);
	void send_chat_packet(int c_id, char* mess);
	void send_state_change_packet();
public:
	float				m_fX, m_fY;
	char				m_cName[NAME_SIZE];
	int					m_iHp;
	int					m_iExp;
	int					m_iLevel;
	int					m_iLast_move_time;
	P_STATE				m_pState;
	S_STATE				m_sState;
	std::mutex			m_sLock;
};