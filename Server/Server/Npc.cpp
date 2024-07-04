#include "Npc.h"

Npc::Npc()
{
	_active = false;
	_rm_time = std::chrono::system_clock::now();
}

Npc::~Npc()
{
}

void Npc::Initialize(int id, int tile_map[W_WIDTH][W_HEIGHT])
{
	while (true)
	{
		_x = rand() % W_WIDTH;
		_y = rand() % W_HEIGHT;
		if (tile_map[_x][_y] != 1)
			break;
	}
	_sector_x = _x / sector_size;
	_sector_y = _x / sector_size;

	_id = id;
	sprintf_s(_name, "N%d", id);
}

void Npc::WakeUpNPC(HANDLE h_iocp, int waker, std::priority_queue<EVENT>& g_event_queue)
{
	Exp_Over* over = new Exp_Over;
	over->_comp_type = C_TARGET_MOVE;
	over->_ai_target_obj = waker;
	PostQueuedCompletionStatus(h_iocp, 1, _id, &over->_over);

	if (_active) return;
	bool old_state = false;
	if (false == atomic_compare_exchange_strong(&_active, &old_state, true))
		return;
	EVENT ev{ _id, std::chrono::system_clock::now(), EV_TARGET_MOVE, 0 };
	g_event_queue.push(ev);
}

void Npc::do_target_move()
{
}

bool Npc::can_see(int c_id)
{
	return false;
}

