#pragma once

#include <iostream>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <MSWSock.h>

#include <tchar.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <memory>
#include <thread>
#include <mutex>
#include <vector>
#include <array>
#include <unordered_map>
#include <windows.h>  
#include <clocale>
#include <sqlext.h> 
#include <wchar.h>
#include <new>
#include <fstream>
#include <sstream>
#include <queue>

#include "protocol.h"

#pragma comment(lib, "ws2_32")
#pragma comment(lib, "MSWSock.lib")
#pragma comment(lib, "lua54.lib")

using namespace std::chrono;

static const int sector_size = 15;
static const int sector_w = W_WIDTH / sector_size;
static const int sector_h = W_HEIGHT / sector_size;
static const int view_range = 7;