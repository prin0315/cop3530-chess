#pragma once
using namespace std;

struct Game
{
    string event;
    string whiteID;
    string blackID;
    string winner;
    string date;
    string time;
    string whiteElo;
    string blackElo;
    string whiteRatingDiff;
    string blackRatingDiff;
    string eco;
    string opening;
    string timeControl;
    string termination;
    string an;

    unsigned int getDateTime()
    {
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));
        int hour = stoi(time.substr(0, 2));
        int minute = stoi(time.substr(3, 2));
        int second = stoi(time.substr(6, 2));
        return second + 60 * minute + 3600 * hour + 86400 * day + 2592000 * month + 31104000 * year;
    }
};
