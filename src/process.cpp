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

Process::Process(int pid, std::string user, std::string command, std::string ram, long int uptime, float cpu_utilisation) 
    : pid_(pid), user_(user), command_(command), ram_(ram), uptime_(uptime), cpu_utilisation_(cpu_utilisation){
};

// TODO: Return this process's ID
int Process::Pid() const{ 
    return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    return cpu_utilisation_; }

void Process::SetCpu(float _cpu){
    cpu_utilisation_ = _cpu;
}
// TODO: Return the command that generated this process
string Process::Command() { return command_; }

void Process::SetCommand(std::string _command){
    command_ = _command;
}

// TODO: Return this process's memory utilization
std::string Process::Ram() { return ram_; }
void Process::SetRam(std::string _ram) {
    ram_ = _ram;
}

// TODO: Return the user (name) that generated this process
string Process::User() { return user_; }

void Process::SetUser(std::string _user ) {
    user_ = _user;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return uptime_; }

void Process::SetUptime(long int _uptime) {
    uptime_ = _uptime;
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
    return this->cpu_utilisation_ > a.cpu_utilisation_; 
}