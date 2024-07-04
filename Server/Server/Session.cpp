#include "Session.h"
#include "GameServer.h"

Session::Session()
{
	_id = -1;
	_client = INVALID_SOCKET;
	_remain_data = 0;
}

Session::~Session()
{
}

void Session::do_recv()
{
	DWORD recv_flag = 0;
	ZeroMemory(&_exp_over._over, sizeof(OVERLAPPED));
	_exp_over._wsabuf.len = CHAT_SIZE -_remain_data;	//���ۻ����ŭ? ó���ϰ� ���� ��Ŷ ������ ���ۿ� ��������� �װ� ���� �޾ƾߵ�
	_exp_over._wsabuf.buf = _exp_over._buf + _remain_data; //���� ����� ������ �߸� ���� �ں��� �޾ƾߵ�
	int res = WSARecv(_client, &_exp_over._wsabuf, 1, 0, &recv_flag,
		&_exp_over._over, 0);
	if (0 != res) {
		int err_no = WSAGetLastError();
		if (WSA_IO_PENDING != err_no)
			GameServer::Print_Error("WSARecv", WSAGetLastError());
	}
}

void Session::do_send(void* packet, int packet_size)
{
	Exp_Over* data = new Exp_Over{ reinterpret_cast<unsigned char*>(packet),packet_size };
	WSASend(_client, &data->_wsabuf, 1, 0, 0, &data->_over, 0);
}