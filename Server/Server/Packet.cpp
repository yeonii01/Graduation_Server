#include "Packet.h"

void Packet::process_packet(int c_id, char* packet, std::array<Player, MAX_USER>& users)
{
	switch (packet[2]) {
	case CS_LOGIN:
	{
		CS_LOGIN_PACKET* p = reinterpret_cast<CS_LOGIN_PACKET*>(packet);
		strcpy_s(users[c_id].m_cName, p->name);

		if (true/*db->Login(users[c_id]._name, users[c_id])*/)
		{
			users[c_id].send_login_info_packet();
			{
				std::lock_guard<std::mutex> ll{ users[c_id].m_sLock };
				users[c_id].m_sState = ST_INGAME;
			}
		}
		else
			users[c_id].send_login_fail_packet();
	}
		break;
	case CS_SIGN_UP:
	{
		CS_SIGN_UP_PACKET* p = reinterpret_cast<CS_SIGN_UP_PACKET*>(packet);
		//db->add_player
	}
	break;
	case CS_MOVE:
	{
		CS_MOVE_PACKET* p = reinterpret_cast<CS_MOVE_PACKET*>(packet);
		users[c_id].m_iLast_move_time = p->move_time;
		float x = users[c_id].m_fX;
		float y = users[c_id].m_fY;
		switch (p->direction) {


		}
		users[c_id].m_fX = x;
		users[c_id].m_fY = y;

		users[c_id].send_move_object_packet(users[c_id]);
		for (auto& pl : users) {
			users[c_id].send_move_object_packet(users[pl.m_iId]);
			users[pl.m_iId].send_move_object_packet(users[c_id]);
		}
	}
		break;
		
	case CS_CHAT:
	{
		CS_CHAT_PACKET* p = reinterpret_cast<CS_CHAT_PACKET*>(packet);
		for (auto& pl : users) {
			if (pl.m_sState != ST_INGAME) continue;
			if (pl.m_iId == c_id) continue;
			pl.send_chat_packet(c_id, p->mess);
		}
	}
		break;

	case CS_ATTACK:
		break;
	case CS_CHAR_SELECT:
	{
		CS_CHAR_SELECT_PACKET* p = reinterpret_cast<CS_CHAR_SELECT_PACKET*>(packet);
		for (auto& pl : users) {
			if (pl.m_sState != ST_INGAME) continue;
			if (pl.m_iId == c_id) continue;
			//pl.send_add_object_packet();
		}
	}
	break;

	case CS_LOGOUT:
		break;
	
	case CS_ANIMATION:
		break;

	case CS_LOOK_DIRECTION:
		break;
	}
}