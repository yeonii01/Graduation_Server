#include "DBConnect.h"
#include "Player.h"

thread_local SQLHANDLE DBConnect::_henv = SQL_NULL_HANDLE;
thread_local SQLHANDLE DBConnect::_hdbc = SQL_NULL_HANDLE;
thread_local SQLHANDLE DBConnect::_hstmt = SQL_NULL_HANDLE;
thread_local SQLRETURN DBConnect::_retcode;

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

	_retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &_henv);
	if (_retcode != SQL_SUCCESS && _retcode != SQL_SUCCESS_WITH_INFO)
		return false;

	_retcode = SQLSetEnvAttr(_henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER*)SQL_OV_ODBC3, 0);
	if (_retcode != SQL_SUCCESS && _retcode != SQL_SUCCESS_WITH_INFO)
		return false;

	_retcode = SQLAllocHandle(SQL_HANDLE_DBC, _henv, &_hdbc);
	if (_retcode != SQL_SUCCESS && _retcode != SQL_SUCCESS_WITH_INFO)
		return false;

	SQLSetConnectAttr(_hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);
	_retcode = SQLConnect(_hdbc, (SQLWCHAR*)L"GSProject", SQL_NTS, (SQLWCHAR*)NULL, 0, NULL, 0);
	_retcode = SQLAllocHandle(SQL_HANDLE_STMT, _hdbc, &_hstmt);

	_retcode = SQLExecDirect(_hstmt, (SQLWCHAR*)L"", SQL_NTS);					//tw
	if (_retcode == SQL_SUCCESS || _retcode == SQL_SUCCESS_WITH_INFO)
		return true;

	else {
		display_error(_hstmt, SQL_HANDLE_STMT, _retcode);
		return false;
	}
}

void DBConnect::Clear()
{
	if (_hstmt != SQL_NULL_HANDLE)
	{
		SQLCancel(_hstmt);
		SQLFreeHandle(SQL_HANDLE_STMT, _hstmt);
		_hstmt = SQL_NULL_HANDLE;
	}
	if (_hdbc != SQL_NULL_HANDLE)
	{
		SQLDisconnect(_hdbc);
		SQLFreeHandle(SQL_HANDLE_DBC, _hdbc);
	}
	SQLFreeHandle(SQL_HANDLE_ENV, _henv);
}

void DBConnect::Fetch()
{
	for (int i = 0; ; i++) {
		_retcode = SQLFetch(_hstmt);
		if (_retcode == SQL_ERROR)
			std::cout << "Error" << std::endl;
		else if (_retcode == SQL_SUCCESS || _retcode == SQL_SUCCESS_WITH_INFO)
			continue;
		else
			break;
	}
	std::cout << "Finish" << std::endl;
	SQLFreeStmt(_hstmt, SQL_CLOSE);
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
	if (_retcode != SQL_SUCCESS && _retcode != SQL_SUCCESS_WITH_INFO)
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

	if (_retcode != SQL_SUCCESS && _retcode != SQL_SUCCESS_WITH_INFO){
		display_error(_hstmt, SQL_HANDLE_STMT, _retcode);
		return false;
	}

	if (!BindCol())
		return false;

	while ((_retcode = SQLFetch(_hstmt)) != SQL_NO_DATA)
	{
		for (int i = 0; i < NAME_SIZE; ++i)
			if (u_name[i] == ' ')
				u_name[i] = '\0';

		if (std::strcmp(name, (char*)u_name) == 0)
		{
			player._hp = u_hp;
			player._exp = u_exp;
			player._x = u_posX;
			player._y = u_posY;
			player._level = u_level;
			SQLFreeStmt(_hstmt, SQL_CLOSE);
			return true;
		}
	}
	SQLFreeStmt(_hstmt, SQL_CLOSE);
	return false;
}

bool DBConnect::AddPlayer(Player& player)
{
	WCHAR query[512];
	//swprintf(query, sizeof(query) / sizeof(WCHAR),
	//	L"INSERT INTO [GameServerTermProject].[dbo].[user_table] (_name, _exp, _hp, _level, _posx, _posy) VALUES (N'%S', %d, %d, %d, %d, %d)",
	//	player._name, player._exp, player._hp, player._level, player._x, player._y);

	_retcode = SQLExecDirect(_hstmt, (SQLWCHAR*)query, SQL_NTS);

	if (_retcode != SQL_SUCCESS && _retcode != SQL_SUCCESS_WITH_INFO) {
		display_error(_hstmt, SQL_HANDLE_STMT, _retcode);
		SQLFreeStmt(_hstmt, SQL_CLOSE);
		return false;
	}

	SQLFreeStmt(_hstmt, SQL_CLOSE);
	return true;
}
