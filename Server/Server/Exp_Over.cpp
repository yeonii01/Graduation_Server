#include "Exp_Over.h"

Exp_Over::Exp_Over()
{
	m_wBuf.len = CHAT_SIZE;
	m_wBuf.buf = m_cBuf;
	m_cType = C_RECV;
	memset(m_cBuf, 0, sizeof(m_cBuf));
	ZeroMemory(&m_wOver, sizeof(m_wOver));
}

Exp_Over::Exp_Over(unsigned char* packet, int packet_size)
{
	m_wBuf.len = packet_size;
	m_wBuf.buf = m_cBuf;
	ZeroMemory(&m_wOver, sizeof(m_wOver));
	m_cType = C_SEND;
	memcpy(m_cBuf, packet, packet_size);
}
