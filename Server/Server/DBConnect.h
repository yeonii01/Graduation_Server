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
	static thread_local SQLHENV			m_henv;
	static thread_local SQLHDBC			m_hdbc;
	static thread_local SQLRETURN		m_retcode;
	static thread_local SQLHSTMT		m_hstmt;

	SQLCHAR					m_uName[20];
	SQLSMALLINT				m_uLevel;
	SQLSMALLINT				m_uHp;
	SQLSMALLINT				m_uExp;
	SQLSMALLINT				m_uPosX;
	SQLSMALLINT				m_uPosY;

	SQLLEN					m_lName;
	SQLLEN					m_lLevel;
	SQLLEN					m_lHp;
	SQLLEN					m_lExp;
	SQLLEN					m_lPosX;
	SQLLEN					m_lPosY;
};

