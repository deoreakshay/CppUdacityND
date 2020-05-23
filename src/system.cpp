#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { 
    return cpu_; 
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    vector<int> _pids{LinuxParser::Pids()};
    processes_.clear();

    for(int pid : _pids)
    {
        std::string command = LinuxParser::Command(pid);
        std::string user = LinuxParser::User(pid);
        long int uptime = LinuxParser::UpTime(pid);
        std::string ram = LinuxParser::Ram(pid);
        float cpu_utilisation = LinuxParser::CpuUtilization(pid);
    
        //processes_.emplace_back(pid, user, command, ram, uptime, cpu_utilisation);
        auto result = std::find_if(processes_.begin(), processes_.end(), [&pid](const auto &iter)-> bool{ return pid == iter.Pid();});
        if(result != processes_.end())
        {
            result->SetCommand(command);
            result->SetUser(user);
            result->SetUptime(uptime);
            result->SetRam(ram);
            result->SetCpu(cpu_utilisation);
        }
        else
        {
            processes_.emplace_back(pid, user, command, ram, uptime, cpu_utilisation);
        }
    }  
    std::sort(processes_.begin(), processes_.end());
    return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
    long int time = LinuxParser::UpTime() ;
    return time; 
}