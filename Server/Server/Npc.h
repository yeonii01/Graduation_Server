#pragma once
#include "Session.h"
#include "Event.h"

class Npc : public Session
{
public:
	Npc();
	~Npc();

public:
	void Initialize(int id);
	void WakeUpNPC(HANDLE h_iocp, int waker, std::priority_queue<EVENT>& g_event_queue);
	void do_random_move();
	void do_target_move();

public:
	std::atomic_bool						m_bActive;
private:
	float									m_fX, m_fY;
	char									m_cName[NAME_SIZE];
	std::chrono::system_clock::time_point	m_cRm_time;
	EVENT									m_eEvent;
	int										m_iId;
};