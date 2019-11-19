#ifndef _TEAM_
#define _TEAM_
#include<iostream>
#include<vector>
class game;


class team
{
    private:
    std::string team_name;
    std::string state_;
    std::string city_;
    std::string stadium_;
    public:
    int points = 0;
    team() = default;
    team(std::string tmname, std::string st, std::string stad, std::string cty) : team_name{tmname}, state_{st}, stadium_{stad}, city_{cty} {}
    std::string name() {return team_name;}
    void set_win(){points +=3; }
    void set_draw(){points +=1; }
    void del_points_win(){points -=3;}
    void del_points_draw(){points -=1;}
    friend std::ostream& operator<<(std::ostream& out, const team& clb);
    friend bool operator==(const team& t1, const team& t2);
    friend bool operator==(const team& t1, const std::string& t2);

};


std::ostream& operator<<(std::ostream& out, const team& clb)
{
    out<< "Team name: " << clb.team_name << '\t' << "Country: " << clb.state_ << '\t' << "City: " << clb.city_ << '\t' << "Stadium: " << clb.stadium_ << std::endl;
    return out;
}

bool operator==(const team& t1, const team& t2)
{
    return(t1.team_name == t2.team_name && t1.city_ == t2.city_);
}

bool operator==(const team& t1, const std::string& t2)
{
    return(t1.team_name == t2);
}

#endif

