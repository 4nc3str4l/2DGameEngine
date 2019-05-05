#pragma once

#include <iostream>
#include <string>
#ifdef _WIN64
#include <windows.h>
#endif

namespace le {

#define ENGINE_SPECIAL_COLOR 14
#define ENGINE_INFO_COLOR 9
#define ENGINE_REGULAR_COLOR 15
#define ENGINE_ERROR_COLOR 12
#define ENGINE_CORRECT_COLOR 2

template <typename T>
static void SPECIAL(T t)
{
	std::cout << t << " ";
}

template <typename T, typename... Args>
static void SPECIAL(T t, Args... _specialMessage)
{
	std::cout << t << " ";
	SPECIAL(_specialMessage...);
}

template <typename T>
static void MESSAGE(T t)
{
	std::cout << t << " ";
}

template <typename T, typename... Args>
static void MESSAGE(T t, Args... _message)
{
	std::cout << t << " ";
	MESSAGE(_message...);
}

static void SetLogType(int t)
{
#ifdef _WIN64
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), t);
#endif
}

static void EndLog()
{
	std::cout << "\n";
#ifdef _WIN64
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_REGULAR_COLOR);
#endif
}

#define LOG_SPECIAL(...) SetLogType(ENGINE_SPECIAL_COLOR); SPECIAL(__VA_ARGS__); EndLog()
#define LOG_INFO(...) SetLogType(ENGINE_INFO_COLOR); MESSAGE(__VA_ARGS__); EndLog()
#define LOG_CORRECT(...) SetLogType(ENGINE_CORRECT_COLOR); MESSAGE(__VA_ARGS__); EndLog()
#define LOG_MESSAGE(...) SetLogType(ENGINE_REGULAR_COLOR); MESSAGE(__VA_ARGS__); EndLog()
#define LOG_FAIL(...) SetLogType(ENGINE_ERROR_COLOR); MESSAGE(__VA_ARGS__); EndLog()
}