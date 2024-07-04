#pragma once

#include "stdafx.h"
#include "Player.h"
#include "DBConnect.h"

class Packet
{
public:
	void process_packet(int c_id, char* packet, std::array<Player, MAX_USER>& users);
	void set_sector(int x, int y, int c_id, std::array<Player, MAX_USER>& users);

private:
	static const int sector_size = 15;
	static const int sector_w = W_WIDTH / sector_size;
	static const int sector_h = W_HEIGHT / sector_size;
	static const int view_range = 7;
	struct sector {
		std::vector<int> sessions;
		std::mutex mtx;
	};

	sector sectors[sector_w][sector_h];
};