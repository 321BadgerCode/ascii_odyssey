#pragma once

using namespace std;

#ifdef _WIN32
	#include <windows.h>

	void sleep(float seconds){
		Sleep(seconds);
	}
#else
	#include <chrono>
	#include <thread>

	void sleep(float seconds){
		this_thread::sleep_for(chrono::milliseconds((unsigned)(seconds*1000)));
	}
#endif

#ifdef _WIN32
	void clear(){
		system("cls");
	}
#else
	void clear(){
		system("clear");
	}
#endif