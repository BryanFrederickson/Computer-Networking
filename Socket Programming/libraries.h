#pragma once // Preprocessor directive to include header file one during program compilation //

#define _CRT_SECURE_NO_WARNINGS // Disables warnings related to buffer overflow //
#include <stdlib.h> // Standard C library //
#include <stdio.h> // Standard Input/Output C library //
#include <time.h> // Time library for C //
#include <string.h> // String-based (char*) functions //
#include <WinSock2.h> // Socket library for C //
#include <ws2tcpip.h> // Additional socket functions //

#pragma comment(lib, "Ws2_32.lib") // Linker instruction for Ws2_32.lib library, necessity for WinSock2 functions //

#define SERVERPORT 8080 // Using virtual port 8080 for non-administrative privileges & commonly known development port //

