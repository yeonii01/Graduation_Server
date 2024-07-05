#include "Session.h"
#include "GameServer.h"

Session::Session()
{
	m_iId = -1;
	m_sClient = INVALID_SOCKET;
	m_iRemain_data = 0;
}

Session::~Session()
{
}

void Session::do_recv()
{
	DWORD recv_flag = 0;
	ZeroMemory(&m_eExp_over.m_wOver, sizeof(OVERLAPPED));
	m_eExp_over.m_wBuf.len = CHAT_SIZE -m_iRemain_data;	//���ۻ����ŭ? ó���ϰ� ���� ��Ŷ ������ ���ۿ� ��������� �װ� ���� �޾ƾߵ�
	m_eExp_over.m_wBuf.buf = m_eExp_over.m_cBuf + m_iRemain_data; //���� ����� ������ �߸� ���� �ں��� �޾ƾߵ�
	int res = WSARecv(m_sClient, &m_eExp_over.m_wBuf, 1, 0, &recv_flag,
		&m_eExp_over.m_wOver, 0);
	if (0 != res) {
		int err_no = WSAGetLastError();
		if (WSA_IO_PENDING != err_no)
			GameServer::Print_Error("WSARecv", WSAGetLastError());
	}
}

void Session::do_send(void* packet, int packet_size)
{
	Exp_Over* data = new Exp_Over{ reinterpret_cast<unsigned char*>(packet),packet_size };
	WSASend(m_sClient, &data->m_wBuf, 1, 0, 0, &data->m_wOver, 0);
}