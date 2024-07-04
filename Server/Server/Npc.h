#pragma once
#include "Session.h"
#include "Event.h"

class Npc : public Session
{
public:
	Npc();
	~Npc();

public:
	void Initialize(int id, int tile_map[W_WIDTH][W_HEIGHT]);
	void WakeUpNPC(HANDLE h_iocp, int waker, std::priority_queue<EVENT>& g_event_queue);
	void do_target_move();
	bool can_see(int c_id);

public:
	std::atomic_bool _active;
private:
	int _x, _y;
	int _sector_x, _sector_y;
	char _name[NAME_SIZE];
	std::chrono::system_clock::time_point _rm_time;
	EVENT _event;
	int _id;
};