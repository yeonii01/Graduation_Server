#include "Npc.h"

Npc::Npc()
{
	m_bActive = false;
	m_cRm_time = std::chrono::system_clock::now();
}

Npc::~Npc()
{
}

void Npc::Initialize(int id)
{
	m_iId = id;
	sprintf_s(m_cName, "N%d", id);
}

void Npc::WakeUpNPC(HANDLE h_iocp, int waker, std::priority_queue<EVENT>& g_event_queue)
{
	Exp_Over* over = new Exp_Over;
	over->m_cType = C_TARGET_MOVE;
	over->m_iTarget_obj = waker;
	PostQueuedCompletionStatus(h_iocp, 1, m_iId, &over->m_wOver);

	if (m_bActive) return;
	bool old_state = false;
	if (false == atomic_compare_exchange_strong(&m_bActive, &old_state, true))
		return;
	EVENT ev{ m_iId, std::chrono::system_clock::now(), EV_TARGET_MOVE, 0 };
	g_event_queue.push(ev);
}

void Npc::do_random_move()
{
}

void Npc::do_target_move()
{
}