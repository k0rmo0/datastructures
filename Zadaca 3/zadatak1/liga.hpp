#ifndef _LEAGUE_
#define _LEAGUE_
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<deque>
#include<cstdlib>
#include"date.hpp"
#include"game.hpp"
#include"team.hpp"

class league
{
    private:
    std::string name_;
    std::string state_;
    std::vector<team*> league_teams;
    std::deque<game> league_games;
    public:
    league() = default;
    league(std::string name, std::string country) : name_{name}, state_{country} {}
    void add_teams(const std::string& country, std::unordered_map<std::string,std::vector<team>>& cont);
    void print_table();
    void make_schedule(std::unordered_map<std::string, std::vector<ref>>& ref_map, const std::string& state);
    std::deque<game>& get_schedule(){return league_games;}
    std::string get_name(){return name_;}
    void game_played(){league_games.pop_front();}
    friend std::ostream& operator<<(std::ostream& out, const league& leag);
    friend bool operator==(const league& lg1, const league& lg2);
    
};

bool operator==(const league& lg1,const league& lg2)
{
    return(lg1.name_ == lg2.name_ && lg1.state_ == lg2.state_);
}


void league::add_teams(const std::string& country, std::unordered_map<std::string,std::vector<team>>& cont)
{
    auto temp = cont.find(country);
    if(temp != cont.end())
    {
        std::vector<team>& teams = temp -> second;
        for(int i = 0; i < teams.size(); ++i)
        {
            league_teams.push_back(&teams.at(i));
        }
    }
    else
    {
        std::cout << "There are no teams in this league!" << std::endl;
    }
}

void league::print_table() 
{
    std::sort(league_teams.begin(), league_teams.end(),[](team* a,  team* b){return a->points > b->points;});
    int j = 1;
    std::cout << "\t TABLE AND STANDINGS" << std::endl;
    std::cout << "Name" << "\t \t" << "Points" << std::endl;
    for(int i = 0; i < league_teams.size(); ++i)
    {
        std::cout << j << "." << league_teams.at(i)->name() <<"\t" << league_teams.at(i)->points << std::endl;
        ++j;
    }
}

void league::make_schedule(std::unordered_map<std::string, std::vector<ref>>& ref_map, const std::string& state)
{
    date game_day;
    game_day.day = 1;
    game_day.month = 6;
    game_day.year = 2019;
    int random_ref1;
    int random_ref2;
    auto temp1 = ref_map.find(state);
    std::vector<ref>& vec_ref = temp1 -> second;
    for (int i = 0; i < league_teams.size(); ++i)
    {
        for(int j = 0; j < league_teams.size(); ++j)
        {
            if(*(league_teams.at(i)) == *(league_teams.at(j)))
                continue;
            random_ref1 = rand() % vec_ref.size();
            random_ref2 = rand() % vec_ref.size();
            if(random_ref1 == random_ref2)
            {
                while(random_ref1 == random_ref2)
                   random_ref2 = rand() % vec_ref.size();
            }
            league_games.push_back(game(league_teams.at(i), league_teams.at(j), &vec_ref.at(random_ref1), &vec_ref.at(random_ref2), game_day));
            if(league_games.size() % 4 == 0)
                {
                    game_day.day ++;
                    if (game_day.day == 30)
                        game_day.month ++;
                }
        }
    }
}

#endif









