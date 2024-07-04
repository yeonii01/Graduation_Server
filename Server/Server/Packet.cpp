#include "Packet.h"

void Packet::process_packet(int c_id, char* packet, std::array<Player, MAX_USER>& users)
{
	switch (packet[2]) {
	case CS_LOGIN:
	{
		CS_LOGIN_PACKET* p = reinterpret_cast<CS_LOGIN_PACKET*>(packet);
		strcpy_s(users[c_id]._name, p->name);

		if (true/*db->Login(users[c_id]._name, users[c_id])*/)
		{
			users[c_id].send_login_info_packet();
			{
				std::lock_guard<std::mutex> ll{ users[c_id]._s_lock };
				users[c_id]._Sstate = ST_INGAME;
			}

			set_sector(users[c_id]._x, users[c_id]._y, c_id, users);
		}
		else
			users[c_id].send_login_fail_packet();
	}
		break;
	case CS_SIGN_UP:
	{
		//db->add_player
	}
	break;
	case CS_MOVE:
	{
		CS_MOVE_PACKET* p = reinterpret_cast<CS_MOVE_PACKET*>(packet);
		users[c_id]._last_move_time = p->move_time;
		float x = users[c_id]._x;
		float y = users[c_id]._y;
		switch (p->direction) {


		}
		users[c_id]._x = x;
		users[c_id]._y = y;

		set_sector(x, y, c_id, users);

		users[c_id].send_move_object_packet(users[c_id]);
		for (int& id : users[c_id]._near)
		{
			users[c_id].send_move_object_packet(users[id]);
			users[id].send_move_object_packet(users[c_id]);
		}
	}
		break;
		
	case CS_CHAT:
	{
		CS_CHAT_PACKET* p = reinterpret_cast<CS_CHAT_PACKET*>(packet);
		for (auto& pl : users) {
			if (pl._Sstate != ST_INGAME) continue;
			if (pl._id == c_id) continue;
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
			if (pl._Sstate != ST_INGAME) continue;
			if (pl._id == c_id) continue;
			pl.send_char_packet(c_id, p->chartype);
		}
	}
	break;
	case CS_LOGOUT:
		break;
	}
}