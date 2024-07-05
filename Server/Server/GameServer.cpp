#include "GameServer.h"

void GameServer::Init()
{
	std::wcout.imbue(std::locale("korean"));	//오류 한글로 설정

	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 2), &WSAData);
}

void GameServer::Clear()
{
	WSACleanup();
}

void GameServer::Print_Error(const char* msg, int err_no)
{
	WCHAR* msg_buf = nullptr;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, err_no,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPWSTR>(&msg_buf), 0, NULL);
	std::cout << msg;
	std::wcout << L": 에러 : " << msg_buf;
	while (true);
	LocalFree(msg_buf);
}

SOCKET GameServer::CreateSocket()
{
	return WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
}

void GameServer::BindAnyAddress(SOCKET socket)
{
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT_NUM);

	int res = bind(socket, reinterpret_cast<SOCKADDR*>(&addr), sizeof(addr));
	if (res != 0)
	{
		Print_Error("Bind", res);
	}
}

void GameServer::Listen(SOCKET socket)
{
	int res = listen(socket, SOMAXCONN);
	if (res != 0)
	{
		Print_Error("Listen", res);
	}
}

void GameServer::DisConnect(int id)
{
}

void GameServer::CloseSocket(SOCKET& socket)
{
	if (socket != INVALID_SOCKET)
	{
		closesocket(socket);
		socket = INVALID_SOCKET;
	}
}

HANDLE GameServer::CreateHandle()
{
	return CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
}

void GameServer::RegisterSocket(HANDLE& iocp, SOCKET& socket, int id)
{
	CreateIoCompletionPort(reinterpret_cast<HANDLE>(socket), iocp, id, 0);
}

bool GameServer::DBInit(DBConnect* db)
{
	if(!db->Connect()) return false;
	if (!db->BindCol()) return false;
	db->Fetch();
	return true;
}

void GameServer::LoadMap()
{

}

void GameServer::InitNpc(std::array<Npc, MAX_NPC>& npcs)
{
	for (int i = 0; i < MAX_NPC; ++i)
	{
		npcs[i].Initialize(i);
	}
}