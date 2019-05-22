#include<iostream>
#include<string>
#include<fstream>
#include<functional>
#include "Station.h"


std::vector<std::string> read (std::string& grad)
{
    std::vector<std::string> input;
    std::string grad_;
    grad_ = grad + ".csv";
    std::ifstream infile(grad_);
    std::string  row;
    while (getline(infile, row))
    {
        input.push_back(row);
    }
    return input;
}

std::vector<station> input_stations()
{
    std::vector<std::string> data;
    std::ifstream infile("stations.csv");
    std::string row;
    while(getline(infile, row))
    {
        data.push_back(row);
    }
    std::vector<station> finalstat;
    auto it_begin = data.begin();
    auto it_end = data.end();
    ++ it_begin;
    while (it_begin != it_end)
    {
        std::string beg = *it_begin;
        int i = 0;
        std::string id;
        std::string name;
        double lattitude;
        double longitude;
        int elevation;
        while(beg[i] != ',')
        {
            id.push_back(beg[i]);
            ++i;
        }
        ++i;
        std::string lat;
        while (beg[i] != ',')
        {
            lat.push_back(beg[i]);
            ++i;
        }
        ++i;
        lattitude = atof(lat.c_str());
        std::string lon;
        while(beg[i] != ',')
        {
            lon.push_back(beg[i]);
            ++i;
        }
        ++i;

        longitude = atof(lon.c_str());
        std::string el;

        while(beg[i] != ',')
        {
            el.push_back(beg[i]);
            ++i;
        }

        ++i;
        elevation = atoi(el.c_str());

        while(beg[i] != ',')
        {
            name.push_back(beg[i]);
            ++i;
        }

        station temp (id, name, lattitude, longitude, elevation);
        finalstat.push_back(temp);
        ++it_begin;
    }
    return finalstat;
}

std::vector<time> pars (std::vector<std::string>& input)
{
    std::vector<std::string> temp;
    temp = input_stations();
    std::vector<time> temprature;
    auto it_begin = input.begin();
    auto it_end = input.end();
    ++it_begin;
    while(it_begin != it_end)
    {
        std::string parsing = *it_begin;
        std::string stat;
        station fstation;
        int year;
        int month;
        double temp_max;
        double temp_min;
        int i = 0;
        while (parsing[i] != ',')
        {
            stat.push_back(parsing[i]);
            ++i;
        }
        ++i;
        std::string y;
        while(parsing[i] != ',')
        {
            y.push_back(parsing[i]);
            ++i;
        }
        ++i;
        year = atoi(y.c_str());

        std::string m;
        while (parsing[i] != ',')
        {
            m.push_back(parsing[i]);
            ++i;
        }
        ++i;

        month = atoi(y.c_str());

        std::string tmpmx;

        while(parsing[i] != ',');
        {
            tmpmx.push_back(parsing[i]);
            ++i;
        }
        ++i;

        temp_max = atof(tmpmx.c_str());

        std::string tmpmn;

        while(parsing[i] != ' ')
        {
            tmpmn.push_back(parsing[i]);
            ++i;
        }
        ++i;

        temp_min = atof(tmpmn.c_str());

        auto iter = find_if(temp.begin(), temp.end(), [stat](station a){return a.Id() == stat;});
        fstation = (*iter);
        time tempo {fstation, year, month, temp_min, temp_max};
        temprature.push_back(tempo);
        ++it_begin;
    } 
    return temprature;
}

std::vector<std::vector<time>> input()
{
    std::vector<std::vector<time>> vec;
    std::string tz = "Tuzla";
    std::string bg = "Belgrade";
    std::string bjel = "Bjelasnica";
    std::string mos = "Mostar";
    std::string neum = "Neum";
    std::string bl = "BanjaLuka";
    std::string zg = "Zagreb";

    auto tz_ = read(tz);
    std::vector<time> temp = pars(tz_);
    vec.push_back(temp);
    auto bg_ = read(bg);
    std::vector<time> temp1 = pars(bg_);
    vec.push_back(temp1);
    auto bjel_ = read(bjel);
    std::vector<time> temp2 = pars(bjel_);
    vec.push_back(temp2);
    auto mos_ = read(mos);
    std::vector<time> temp3 = pars(mos_);
    vec.push_back(temp3);
    auto neum_ = read(neum);
    std::vector<time> temp4 = pars(neum_);
    vec.push_back(temp4);
    auto bl_ = read(bl);
    std::vector<time> temp5 = pars(bl_);
    vec.push_back(temp5);
    auto zg_ = read(zg);
    std::vector<time> temp6 = pars(zg_);
    vec.push_back(temp6);

    return vec;
}


int menu(std::vector<std::vector<time>>& vek)
{
    std::string stars (50,'*');
    std::cout << stars << "Historical temperature information" << stars << std::endl;
    std::cout<<"1.Get information for entire year"<<std::endl;
    std::cout<<"2.Get information for specific mont" << std::endl;
    std::cout<<"3.Insert new historical informatio" << std::endl;
    std::cout << std::endl;
    std::cout <<"4. End" << std::endl;

    int option;

    std::cout << "Your choice : ";
    std::cin >> option;
    std::cout << stars + stars << std::endl;

    switch (option)
    {
    case 1:
            {
                std::cout << "Enter location where station is placed: ";
                std::string city;
                std::cin >> city;

                auto iter = find(vek.begin(), vek.end(), [city](std::vector<time>a) {return ((a[1]).gStat()).Id() == city;});
                std::vector<time> vec;
                vec = *iter;
                std::cout << "StationID: " << vec[1].gStat().Id() << std::endl;
                std::cout << "Lattitude: " << vec[1].gStat().Lattitude() << std::endl;
                std::cout << "Longitude: " << vec[1].gStat().Longitude() << std::endl;
                std::cout << "Elevation: " << vec[1].gStat().Elevation() << std::endl;
                std:cout << std::endl;
                std::cout << "Enter a year: ";
                int year;
                std::cin >> year;
                auto iter2 = find(vek.begin(), vek.end(), [year](time a){return a.gYear == year;});
                std::vector<time> vec1;
                while((*iter2).gYear() == year)
                {
                    vec1.push_back(*iter2);
                    ++iter2;
                }
            }
        break;
    
    default:
        break;
    }

}