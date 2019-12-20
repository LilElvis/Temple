#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <vector>

enum Colours
{
	Red = 12,
	Grey = 7,
	DarkGrey = 8
};

enum GameState
{
	MENUSTATE,
	PLAYSTATE,
	EVENTSTATE,
	GAMEOVER,
	WINNINGSTATE,
	ENDSTATE
};

struct Room
{
	bool northDoor;
	bool southDoor;
	bool eastDoor;
	bool westDoor;

	bool inEvent = true;
	std::string description;
	int location;
};