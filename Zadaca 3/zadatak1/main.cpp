#include<iostream>
#include <unordered_map>
#include<stack>
#include <cstdlib> 
#include<queue>
#include"team.hpp"
#include"liga.hpp"
#include"referee.hpp"
#include"game.hpp"


int main()
{
    int choice;
    std::unordered_map<std::string, std::vector<team>> clubs;
    std::unordered_map<std::string, std::vector<ref>> refmap;
    std::unordered_map<std::string, league> league_map;
    std::vector<game*> played_games;


    while(choice != 0)
    {
        std::cout <<'\t' << "MENU:"<<std::endl;
        std::cout << "1: Add new team" << std::endl;
        std::cout << "2: Add new referee" << std::endl;
        std::cout << "3: Add new league"<< std::endl;
        std::cout << "4: Play game in league"<< std::endl;
        std::cout << "5: Delete last played game in league"<< std::endl;
        std::cout << "6: Info about team"<< std::endl;
        std::cout << "7: Standings table"<< std::endl;
        std::cout << "8: Show every game in every league"<< std::endl;
        std::cout << "0: Exit from app" << std::endl;
        std::cin >> choice;
        std::cin.ignore();
        std::cout << std::endl;

        switch (choice)
        {
        case 1:
                {
                    std::string name;
                    std::string state;
                    std::string stadium;
                    std::string city;
                    std::cout << "Enter team name: ";
                    std::getline (std::cin,name);
                    std::cout << std::endl << "Enter team state: ";
                    std::getline (std::cin,state);
                    std::cout << std::endl << "Enter team city: ";
                    std::getline (std::cin,city);
                    std::cout << std::endl << "Enter team stadium: ";
                    std::getline (std::cin,stadium);
                    team input = team(name,state,stadium,city);
                    auto temp = clubs.find(state);
                    bool same = false;
                    if (temp != clubs.end())
                        { 
                            int i = 0;  
                            while(i < temp -> second.size() && !same)
                            {
                                if(temp -> second.at(i) == input)
                                    {
                                        std::cerr << "Cannot insert two teams with the same name in a same city!"<<std::endl;
                                        same = true;
                                    }
                                ++i;
                            }
                            if(same)
                                break;
                            clubs[state].push_back(input);
                        }
                    else
                        {
                            clubs[state].push_back(input);
                            
                        }
                    break;
                }
        case 2:
                {
                    std::string name;
                    std::string surname;
                    std::string state;
                    std::cout << "Enter referee name: ";
                    std::cin >> name;
                    std::cout << std::endl << "Enter referee surname: ";
                    std::cin >> surname;
                    std::cin.ignore();
                    std::cout << std::endl << "Enter referee country: ";
                    std::getline(std::cin,state);
                    ref input = ref(name, surname, state);
                    auto found = refmap.find(state);
                    bool same = false;
                    if(found != refmap.end())
                    {
                        int i = 0;
                        std::vector<ref>& ref_vec = found -> second;
                        while (i < ref_vec.size() && !same )
                        {
                                if(ref_vec.at(i) == input)
                                {
                                    std::cerr << "There is already referee  with that name and surname in this country! " << std::endl;
                                    same = true;
                                }
                                ++i;
                        }
                        if(same)
                            break;
                        ref_vec.push_back(input);
                    }
                    else
                    {
                        refmap[state].push_back(input);
                    }
                    break;
                }
                
        case 3:
                {
                    std::string name;
                    std::string state;
                    std::cout << "Enter league name: ";
                    std::getline(std::cin,name);
                    std::cout << std::endl << "Enter league country: ";
                    std::getline(std::cin,state);
                    auto input = league(name, state);
                    auto team_test = clubs.find(state);
                    if(team_test != clubs.end())
                    {
                        std::vector<team> vec_team = team_test -> second;
                        if(vec_team.size() < 2)
                        {
                            std::cerr << "Inorder to create league you need to add more than one team with the same country !" << std::endl;
                            break;
                        }
                    }
                    else
                    {
                        std::cerr << "No teams to input in this league, please add " << std::endl;
                        break;
                    }
                    auto ref_test = refmap.find(state);
                    if(ref_test != refmap.end())
                    {
                        std::vector<ref> vec_ref = ref_test -> second;
                        if(vec_ref.size() < 2)
                        {
                            std::cerr << "In order to create league you need to add more than one referee with the same country !" << std::endl;
                            break;
                        }
                    }
                    else
                    {
                        std::cerr << "Not referees added for this league, please add" << std::endl;
                        break;
                    }
                    input.add_teams(state, clubs);
                    auto temp = league_map.find(state);
                    if(temp != league_map.end())
                    {
                        std::cerr << "There is already league in this country!";
                        break;
                    }
                    input.make_schedule(refmap,state);
                    league_map[state] = input;
                    break;
                }
        case 4:
                {
                    std::string game_league;
                    std::string result;
                    std::cout << "Enter country from which league is: ";
                    std::getline(std::cin,game_league);
                    auto found = league_map.find(game_league);
                    if(found != league_map.end())
                    {
                        league& searched_league = found -> second;
                        std::deque<game>& game_deque = searched_league.get_schedule();
                        if(game_deque.size() == 0)
                            {
                                std::cout << "There are no teams in this league! ";
                                break;
                            }
                        std::cout << "Insert game outcome for the game in schedule(please insert as \"result_1:result_2\"): " << std::endl;
                        std::cout << game_deque.front();
                        std::cin >> result;
                        game_deque.front().set_result(result);
                        game& resulted_game = game_deque.front();
                        searched_league.game_played();
                        resulted_game.status = "regular game";
                        played_games.push_back(&resulted_game);
                        if(result.at(0) > result.at(2))
                        {
                            team* tm1 = resulted_game.get_team1();
                            tm1->set_win();
                        }
                        else if(result.at(0) == result.at(2))
                        {
                            team* tm1 = resulted_game.get_team1();
                            team* tm2 = resulted_game.get_team2();
                            tm1->set_draw();
                            tm2->set_draw();
                        }
                        else
                        {
                            team* tm2 = resulted_game.get_team2();
                            tm2->set_win();
                        }
                    }
                break;
                }
        case 5:
                {
                  if(played_games.at(played_games.size() - 1)->status == "canceled")
                    {
                        std::cerr << "You have already canceled last played game" << std::endl;
                        break;
                    }
                  else
                   {
                       std::cout << "Game you are canceling: " << *(played_games.at(played_games.size() - 1)) << std::endl;
                       std::string sure;
                       std::cout << "Enter y if you want to cancel, or n if you dont want to cancel this game: ";
                       std::cin >> sure;
                       if(sure == "y")
                       {
                        std::string returned_result = played_games.at(played_games.size() - 1)->get_result();
                        if(returned_result[0] > returned_result[2])
                        {
                          played_games.at(played_games.size() - 1) -> get_team1()->del_points_win();
                        }
                        else if(returned_result[0] == returned_result[2])
                        {
                          played_games.at(played_games.size() - 1) -> get_team1() -> del_points_draw();
                          played_games.at(played_games.size() - 1) -> get_team2() -> del_points_draw();
                        }
                        else
                        {
                            played_games.at(played_games.size() - 1) -> get_team2() ->del_points_win();
                        }
                        played_games.at(played_games.size() - 1)->status="canceled";
                        std::cout << "You have succesfully canceled last played game!" << std::endl;
                       }
                        break;
                    }
                }
        case 6:
                {
                    std::string team_country;
                    std::string team_name;
                    std::cout << "Enter team country: ";
                    std::getline(std::cin,team_country);
                    std::cout << std::endl << "Enter team name: ";
                    std::getline(std::cin,team_name);
                    auto temp = clubs.find(team_country);
                    team found_team;
                    if(temp != clubs.end())
                    {
                        const std::vector<team>& teams = temp -> second;
                        for (int i = 0; i < teams.size(); ++i)
                        {
                            if(teams.at(i) == team_name)
                            {
                                   std::cout << teams.at(i) << std::endl;
                                   found_team = teams.at(i);
                                   break;
                            }
                        }
                        std::cout << "Played games :" << std::endl;
                        for(int i = 0; i < played_games.size(); ++i)
                        {
                            if(*(played_games.at(i) -> get_team1()) == found_team || *(played_games.at(i) -> get_team2()) == found_team)
                            {
                                std::cout << *(played_games.at(i)) << " Status: " << played_games.at(i) -> status << std::endl;
                            }
                        }
                        std::cout << "Unplayed games: " << std::endl;
                        auto league_iter = league_map.find(team_country);
                        league team_league = league_iter -> second;
                        std::deque<game> games_deque = team_league.get_schedule();
                        if(games_deque.size() == 0)
                        {
                            std::cout << "All games played!" << std::endl;
                            break;
                        }
                        for(int i = 0; i < games_deque.size(); ++i)
                        {
                            if(*(games_deque.at(i).get_team1()) == found_team || *(games_deque.at(i).get_team2()) == found_team)
                            {
                                std::cout << games_deque.at(i) << std::endl;
                            }
                        }
                    }
                    else
                    {
                        std::cerr << "There is no team you are looking for!" << std::endl;
                        break;
                    }
                    break;
                }
        case 7:
                {
                    std::string table_league;
                    std::cout << "From which country you want to see league table: ";
                    std::getline(std::cin,table_league);
                    std::cout << std::endl;
                    auto temp = league_map.find(table_league);
                    if(temp != league_map.end())
                    {
                        auto table = temp -> second;
                        table.print_table();
                        break;
                    }
                    else
                    {
                        std::cout << "I cant find league you are looking for !" << std::endl;
                        break;
                    }
                }
        case 8:
                {
                    std::unordered_map<std::string,league>::iterator iter = league_map.begin();
                    std::cout << "Every unplayed game in every league: " << std::endl;
                    for(int i = 0; iter != league_map.end();++i,iter++)
                    {
                        
                        if(iter ->second.get_schedule().size() == 0)
                            continue;    
                        std::cout << iter ->second.get_name() << std::endl;
                        for(int j = 0; j < iter ->second.get_schedule().size(); ++j)
                            std::cout << iter ->second.get_schedule().at(j) << std::endl;
                        
                    }
                    std::cout << "Every played game in every league: " << std::endl;
                    for(int i = 0; i < played_games.size(); ++i)
                    {
                        if(played_games.size() == 0)
                            continue;
                        std::cout << *(played_games.at(i)) << "  Status: " << played_games.at(i)->status << std::endl;
                    }
                   break; 
                }
        case 0:
            break;
        default:
                std::cout << "Wrong menu input, please input only numbers from shown menu!" << std::endl;
            break;
        }
    }
}


    
