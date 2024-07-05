#include "Player.h"

Player::Player()
{
	m_fX = 0, m_fY= 0;
	m_cName[0] = 0;
	m_iHp = 100;
	m_iExp = 0;
	m_iLevel = 1;
	m_iLast_move_time = 0;
	m_pState = P_IDLE;
	m_sState = ST_FREE;
}

Player::~Player()
{
}

void Player::send_login_info_packet()
{
	SC_LOGIN_INFO_PACKET p;
	p.id = m_iId;
	p.size = sizeof(SC_LOGIN_INFO_PACKET);
	p.type = SC_LOGIN_INFO;
	p.x = m_fX;
	p.y = m_fY;
	do_send(&p, p.size);
}

void Player::send_login_fail_packet()
{
	SC_LOGIN_FAIL_PACKET p;
	p.size = sizeof(SC_LOGIN_FAIL_PACKET);
	p.type = SC_LOGIN_FAIL;
	do_send(&p, p.size);
}

void Player::send_add_object_packet(Player& player)
{
	SC_ADD_OBJECT_PACKET p;
	p.id = player.m_iId;
	strcpy_s(p.name, player.m_cName);
	p.size = sizeof(SC_ADD_OBJECT_PACKET);
	p.type = SC_ADD_OBJECT;
	p.x = player.m_fX;
	p.y = player.m_fY;
	do_send(&p, p.size);
}

void Player::send_remove_object_packet(int c_id)
{
	SC_REMOVE_OBJECT_PACKET p;
	p.id = c_id;
	p.size = sizeof(SC_REMOVE_OBJECT_PACKET);
	p.type = SC_REMOVE_OBJECT;
	do_send(&p, p.size);
}

void Player::send_move_object_packet(Player& player)
{
	SC_MOVE_OBJECT_PACKET p;
	p.id = player.m_iId;
	p.size = sizeof(SC_MOVE_OBJECT_PACKET);
	p.type = SC_MOVE_OBJECT;
	p.x = player.m_fX;
	p.y = player.m_fY;
	p.move_time = player.m_iLast_move_time;
	do_send(&p, p.size);
}

void Player::send_chat_packet(int c_id, char* mess)
{
	SC_CHAT_PACKET p;
	p.id = c_id;
	strcpy_s(p.mess, mess);
	p.type = SC_CHAT;
	int mess_len = strlen(p.mess);
	p.size = sizeof(SC_CHAT_PACKET)- CHAT_SIZE + mess_len + 1;
	do_send(&p, p.size);
}

void Player::send_state_change_packet()
{

}