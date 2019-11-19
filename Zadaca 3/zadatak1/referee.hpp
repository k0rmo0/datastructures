#ifndef _REFEREE_
#define _REFEREE_
#include<iostream>
#include<map>
class ref
{
    private:
    std::string name_;
    std::string surname_;
    std::string state_;
    public:
    ref(std::string nm, std::string surnm, std::string st) : name_ {nm}, surname_{surnm}, state_{st} {}
    friend std::istream& operator>>(std::istream& in, const ref& man);
    friend bool operator==(const ref& rf1, const ref& rf2);
    friend std::ostream& operator<<(std::ostream& out, const ref& rf);
};

bool operator==(const ref& rf1, const ref& rf2)
{
    return(rf1.name_ == rf2.name_ && rf1.surname_ == rf2.surname_ && rf1.state_ == rf2.state_);
}

std::ostream& operator<<(std::ostream& out, const ref& rf)
{
    out << rf.name_ << " " << rf.surname_;
    return out;
}
#endif