constexpr int PORT_NUM = 4000;
constexpr int NAME_SIZE = 20;
constexpr int CHAT_SIZE = 300;

constexpr int MAX_USER = 10000;				//tw
constexpr int MAX_NPC = 200000;				//tw

constexpr int W_WIDTH = 2000;				//tw
constexpr int W_HEIGHT = 2000;				//tw

// Packet ID
constexpr char CS_LOGIN = 0;
constexpr char CS_SIGN_UP = 1;
constexpr char CS_MOVE = 2;
constexpr char CS_CHAT = 3;
constexpr char CS_ATTACK = 4;			
constexpr char CS_CHAR_SELECT = 5;
constexpr char CS_LOGOUT = 6;			

constexpr char SC_LOGIN_INFO = 7;
constexpr char SC_LOGIN_FAIL = 8;
constexpr char SC_ADD_OBJECT = 9;
constexpr char SC_REMOVE_OBJECT = 10;
constexpr char SC_MOVE_OBJECT = 11;
constexpr char SC_CHAT = 12;
constexpr char SC_STAT_CHANGE = 13;

#pragma pack (push, 1)
struct CS_LOGIN_PACKET {				//Try login
	char	size;
	char	type;
	char	name[NAME_SIZE];
};

struct CS_SIGN_UP_PACKET {				//Sign up
	char	size;
	char	type;
	char	name[NAME_SIZE];
};

struct CS_MOVE_PACKET {					//Move
	char		size;
	char		type;
	char		direction;
	unsigned	move_time;
};

struct CS_CHAT_PACKET {					//Chat
	char	size;
	char	type;
	char	mess[CHAT_SIZE];
};

struct CS_CHAR_SELECT_PACKET {			//Character Select
	char	size;
	char	type;
	char	chartype;
};

struct CS_LOGOUT_PACKET {				//Logout
	char	size;
	char	type;
};

struct SC_LOGIN_INFO_PACKET {			//Login Success
	char size;
	char	type;
	int		id;
	int		hp;
	int		max_hp;
	int		exp;
	int		level;
	float	x, y, z;
};

struct SC_LOGIN_FAIL_PACKET {			//Login Fail
	char	size;
	char	type;
};

struct SC_ADD_OBJECT_PACKET {			//NPC, Player Add
	char	size;
	char	type;
	int		id;
	float	x, y, z;
	char	name[NAME_SIZE];
};

struct SC_REMOVE_OBJECT_PACKET {		//NPC, Player Remove
	char	size;
	char	type;
	int		id;
};

struct SC_MOVE_OBJECT_PACKET {			//NPC, Player Move
	char	size;
	char	type;
	int		id;
	float	x, y, z;
	unsigned int move_time;
};

struct SC_CHAT_PACKET {					//Player Chat
	char	size;
	char	type;
	int		id;
	char	mess[CHAT_SIZE];
};

struct SC_STAT_CHANGE_PACKET {			//Chat
	char	size;
	char	type;
	int		hp;
	int		max_hp;
	int		exp;
	int		level;
};

#pragma pack (pop)