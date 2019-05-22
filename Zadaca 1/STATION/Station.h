#ifndef _STAT_
#define _STAT_

#include<iostream>


class station
{
    private:
    std::string id_;
    std::string name_;
    double lattitude_;
    double longitude_;
    int elevation_;

    public:

    station() = default;
    station(std::string id, std::string name, double lat, double lon, int ele ) : id_{id}, name_{name}, lattitude_{lat}, longitude_{lon} {}
    ~station() {}
    friend std::ostream& operator<<(std::ostream& out, const station& st)
    {
        out << st.id_ << " " << st.name_ << " " << st.lattitude_ << " " << st.longitude_ << " " << st.elevation_;
        return out; 
    }
    
    std::string Id () {return id_;}
    std::string Name () {return name_;}
    double Lattitude () {return lattitude_;}
    double Longitude () {return longitude_;}
    int Elevation () {return elevation_;}
};

class time
{
    private:
    station stat_;
    int year_ = 0;
    int month_ = 0;
    double temp_min_ = 0;
    double temp_max_ = 0;

    public:
    time() = default;
    time (station stat, int year, int month, double temp_min, double temp_max) : stat_{stat}, year_{year}, month_{month}, temp_min_{temp_min}, temp_max_{temp_max} {}
    ~time() {}
    station gStat() {return stat_;}
    int gYear() {return year_;}
    int gMonth() {return month_;}
    double gMin() {return temp_min_;}
    double gMax () {return temp_max_;}

    void stTempMax (int temp) {temp_max_ = temp;}
    void stTempMin (int temp) {temp_min_ = temp;}
    friend std::ostream& operator <<(std::ostream out, const time& tm)
    {
        out << tm.stat_ << " " << tm.year_ << " " << tm.month_ << " " << tm.temp_max_ << " " << tm.temp_min_;
        return out; 
    }
};
#endif