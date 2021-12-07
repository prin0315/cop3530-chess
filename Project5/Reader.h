#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "Game.h"

class Reader
{
private:
	string file_location;
	ifstream file;
public:
	Reader(string file_location);
	Game read();
};

Reader::Reader(string file_location)
{
	this->file_location = file_location;
	file.open(file_location);
}

Game Reader::read()
{
	Game game;
	if (file.is_open())
	{
		string headers;
		getline(file, headers);
        getline(file, game.event, ',');
        getline(file, game.whiteID, ',');
        getline(file, game.blackID, ',');
        getline(file, game.winner, ',');
        getline(file, game.date, ',');
        getline(file, game.time, ',');
        getline(file, game.whiteElo, ',');
        getline(file, game.blackElo, ',');
        getline(file, game.whiteRatingDiff, ',');
        getline(file, game.blackRatingDiff, ',');
        getline(file, game.eco, ',');
        getline(file, game.opening, ',');
        getline(file, game.timeControl, ',');
        getline(file, game.termination, ',');
        getline(file, game.an, '\n');
	}
    return game;
}