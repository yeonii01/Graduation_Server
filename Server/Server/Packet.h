#pragma once

#include "stdafx.h"
#include "Player.h"
#include "DBConnect.h"

class Packet
{
public:
	void process_packet(int c_id, char* packet, std::array<Player, MAX_USER>& users);
};