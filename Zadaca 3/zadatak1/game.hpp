#ifndef _GAME_
#define _GAME_
#include<iostream>
#include"date.hpp"
#include"team.hpp"
#include"referee.hpp"
class date;


class game
{
    private:
    team* team1;
    team* team2;
    ref* boss;
    ref* line_ref;
    public:
    std::string result;
    date date_game;
    std::string status;
    game(team* t1, team* t2, ref* rf1, ref* rf2, date dt) : team1{t1}, team2{t2}, boss{rf1}, line_ref{rf2}, date_game{dt} {}
    void set_result(const std::string& res);
    team* get_team1() {return team1;}
    team* get_team2() {return team2;}
    friend std::ostream& operator<<(std::ostream& out, const game& gm)
    {
    if(gm.result.size() != 0)
    {
        out << gm.date_game << gm.team1 -> name() << " | " << gm.result <<  " | " << gm.team2 -> name() << "| Referee: " << *(gm.boss) << "| Line referee: " << *(gm.line_ref) << std::endl;
        return out;
    }
    else
    {
        out << gm.date_game << gm.team1 -> name() << " vs. " << gm.team2 -> name() << "| Referee: " << *(gm.boss) << "| Line referee: " << *(gm.line_ref) << std::endl;
        return out;
    }
}
    std::string get_result(){return result;}
};

void game::set_result(const std::string& res)
{
    result = res;
}

#endif
     