#include "DBConnect.h"
#include "Player.h"

thread_local SQLHANDLE DBConnect::m_henv = SQL_NULL_HANDLE;
thread_local SQLHANDLE DBConnect::m_hdbc = SQL_NULL_HANDLE;
thread_local SQLHANDLE DBConnect::m_hstmt = SQL_NULL_HANDLE;
thread_local SQLRETURN DBConnect::m_retcode;

DBConnect::DBConnect()
{
}

DBConnect::~DBConnect()
{
	Clear();
}

void DBConnect::display_error(SQLHANDLE hHandle, SQLSMALLINT hType, RETCODE RetCode)
{
	SQLSMALLINT iRec = 0;
	SQLINTEGER iError;
	WCHAR wszMessage[1000];
	WCHAR wszState[SQL_SQLSTATE_SIZE + 1];
	if (RetCode == SQL_INVALID_HANDLE) {
		fwprintf(stderr, L"Invalid handle!\n");
		return;
	}
	while (SQLGetDiagRec(hType, hHandle, ++iRec, wszState, &iError, wszMessage,
		(SQLSMALLINT)(sizeof(wszMessage) / sizeof(WCHAR)), (SQLSMALLINT*)NULL) == SQL_SUCCESS) {
		// Hide data truncated..
		if (wcsncmp(wszState, L"01004", 5)) {
			fwprintf(stderr, L"[%5.5s] %s (%d)\n", wszState, wszMessage, iError);
		}
	}
}

bool DBConnect::Connect()
{
	setlocale(LC_ALL, "korean");

	m_retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_henv);
	if (m_retcode != SQL_SUCCESS && m_retcode != SQL_SUCCESS_WITH_INFO)
		return false;

	m_retcode = SQLSetEnvAttr(m_henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER*)SQL_OV_ODBC3, 0);
	if (m_retcode != SQL_SUCCESS && m_retcode != SQL_SUCCESS_WITH_INFO)
		return false;

	m_retcode = SQLAllocHandle(SQL_HANDLE_DBC, m_henv, &m_hdbc);
	if (m_retcode != SQL_SUCCESS && m_retcode != SQL_SUCCESS_WITH_INFO)
		return false;

	SQLSetConnectAttr(m_hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);
	m_retcode = SQLConnect(m_hdbc, (SQLWCHAR*)L"GSProject", SQL_NTS, (SQLWCHAR*)NULL, 0, NULL, 0);
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);

	m_retcode = SQLExecDirect(m_hstmt, (SQLWCHAR*)L"", SQL_NTS);					//tw
	if (m_retcode == SQL_SUCCESS || m_retcode == SQL_SUCCESS_WITH_INFO)
		return true;

	else {
		display_error(m_hstmt, SQL_HANDLE_STMT, m_retcode);
		return false;
	}
}

void DBConnect::Clear()
{
	if (m_hstmt != SQL_NULL_HANDLE)
	{
		SQLCancel(m_hstmt);
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
		m_hstmt = SQL_NULL_HANDLE;
	}
	if (m_hdbc != SQL_NULL_HANDLE)
	{
		SQLDisconnect(m_hdbc);
		SQLFreeHandle(SQL_HANDLE_DBC, m_hdbc);
	}
	SQLFreeHandle(SQL_HANDLE_ENV, m_henv);
}

void DBConnect::Fetch()
{
	for (int i = 0; ; i++) {
		m_retcode = SQLFetch(m_hstmt);
		if (m_retcode == SQL_ERROR)
			std::cout << "Error" << std::endl;
		else if (m_retcode == SQL_SUCCESS || m_retcode == SQL_SUCCESS_WITH_INFO)
			continue;
		else
			break;
	}
	std::cout << "Finish" << std::endl;
	SQLFreeStmt(m_hstmt, SQL_CLOSE);
}

bool DBConnect::BindCol()
{
	//tw
	//_retcode = SQLBindCol(_hstmt, 1, SQL_C_CHAR, u_name, sizeof(u_name), &l_name);
	//_retcode = SQLBindCol(_hstmt, 2, SQL_C_SHORT, &u_exp, 0, &l_exp);
	//_retcode = SQLBindCol(_hstmt, 3, SQL_C_SHORT, &u_hp, 0, &l_hp);
	//_retcode = SQLBindCol(_hstmt, 4, SQL_C_SHORT, &u_level, 0, &l_level);
	//_retcode = SQLBindCol(_hstmt, 5, SQL_C_SHORT, &u_posX, 0, &l_posX);
	//_retcode = SQLBindCol(_hstmt, 6, SQL_C_SHORT, &u_posY, 0, &l_posY);
	if (m_retcode != SQL_SUCCESS && m_retcode != SQL_SUCCESS_WITH_INFO)
		return false;
	return true;
}

void DBConnect::PrintInfo(int num)
{
	//tw
	/*printf("%d: %20s %3d %3d %3d %3d\n",
		num+1, u_name, u_hp, u_level, u_posX, u_posY);*/
}

bool DBConnect::Login(char* name, Player& player)
{
	//tw
	//_retcode = SQLExecDirect(_hstmt, (SQLWCHAR*)L"SELECT _name, _exp, _hp, _level, _posx, _posy FROM [GameServerTermProject].[dbo].[user_table]",SQL_NTS);

	if (m_retcode != SQL_SUCCESS && m_retcode != SQL_SUCCESS_WITH_INFO){
		display_error(m_hstmt, SQL_HANDLE_STMT, m_retcode);
		return false;
	}

	if (!BindCol())
		return false;

	while ((m_retcode = SQLFetch(m_hstmt)) != SQL_NO_DATA)
	{
		for (int i = 0; i < NAME_SIZE; ++i)
			if (m_uName[i] == ' ')
				m_uName[i] = '\0';

		if (std::strcmp(name, (char*)m_uName) == 0)
		{
			player.m_iHp = m_uHp;
			player.m_iExp = m_uExp;
			player.m_fX = m_uPosX;
			player.m_fY = m_uPosY;
			player.m_iLevel = m_uLevel;
			SQLFreeStmt(m_hstmt, SQL_CLOSE);
			return true;
		}
	}
	SQLFreeStmt(m_hstmt, SQL_CLOSE);
	return false;
}

bool DBConnect::AddPlayer(Player& player)
{
	WCHAR query[512];
	//swprintf(query, sizeof(query) / sizeof(WCHAR),
	//	L"INSERT INTO [GameServerTermProject].[dbo].[user_table] (_name, _exp, _hp, _level, _posx, _posy) VALUES (N'%S', %d, %d, %d, %d, %d)",
	//	player._name, player._exp, player._hp, player._level, player._x, player._y);

	m_retcode = SQLExecDirect(m_hstmt, (SQLWCHAR*)query, SQL_NTS);

	if (m_retcode != SQL_SUCCESS && m_retcode != SQL_SUCCESS_WITH_INFO) {
		display_error(m_hstmt, SQL_HANDLE_STMT, m_retcode);
		SQLFreeStmt(m_hstmt, SQL_CLOSE);
		return false;
	}

	SQLFreeStmt(m_hstmt, SQL_CLOSE);
	return true;
}
