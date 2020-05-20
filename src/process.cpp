#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid, std::string command, std::string user, long uptime, std::string ram, float cpu_utilisation) 
    : pid_(pid), command_(command), user_(user), uptime_(uptime), ram_(ram), cpu_utilisation_(cpu_utilisation){
};

// TODO: Return this process's ID
int Process::Pid() { 
    return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    return cpu_utilisation_; }

// TODO: Return the command that generated this process
string Process::Command() { return command_; }

// TODO: Return this process's memory utilization
std::string Process::Ram() { return ram_; }

// TODO: Return the user (name) that generated this process
string Process::User() { return user_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return uptime_; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
    return this->cpu_utilisation_ > a.cpu_utilisation_; 
}