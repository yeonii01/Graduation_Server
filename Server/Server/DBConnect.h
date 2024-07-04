#pragma once
#include "Player.h"
#include "stdafx.h"
class DBConnect
{
public:
	DBConnect();
	~DBConnect();

public:
	void			display_error(SQLHANDLE hHandle, SQLSMALLINT hType, RETCODE RetCode);

	bool			Connect();
	void			Clear();

	bool			BindCol();
	void			Fetch();
	void			PrintInfo(int num);

public:
	bool			Login(char* Name, Player& player);
	bool			AddPlayer(Player& player);
private:
	static thread_local SQLHENV			_henv;
	static thread_local SQLHDBC			_hdbc;
	static thread_local SQLRETURN		_retcode;
	static thread_local SQLHSTMT		_hstmt;

	SQLCHAR					u_name[20];
	SQLSMALLINT				u_level;
	SQLSMALLINT				u_hp;
	SQLSMALLINT				u_exp;
	SQLSMALLINT				u_posX;
	SQLSMALLINT				u_posY;

	SQLLEN					l_name;
	SQLLEN					l_level;
	SQLLEN					l_hp;
	SQLLEN					l_exp;
	SQLLEN					l_posX;
	SQLLEN					l_posY;
};

