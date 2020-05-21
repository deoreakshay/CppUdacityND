#include <string>
#include <iomanip>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    int hours = seconds / 3600;
    seconds = seconds % 3600;
    int minutes = seconds / 60;
    seconds = seconds % 60; 

    std::string hh{"00"}, mm{"00"}, ss{"00"};

    hh = std::to_string(hours);    
    if(std::stoi(hh) < 10)
        hh = "0" + hh;
    
    mm = std::to_string(minutes);
    if(std::stoi(mm) < 10)
        mm = "0" + mm;
    
    ss = std::to_string(seconds);
    if(std::stoi(ss) < 10)
        ss = "0" + ss;

    return  hh +  ":" + mm + ":" + ss; 
}