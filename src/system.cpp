#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

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
    vector<int> pid{LinuxParser::Pids()};

    std::set<int> unique_pid;
    for(Process &process : processes_)
    {
        unique_pid.insert(process.Pid());
    }

    for(int i : pid)
    {
        std::string command = LinuxParser::Command(pid[i]);
        std::string user = LinuxParser::User(pid[i]);
        long uptime = LinuxParser::UpTime(pid[i]);
        std::string ram = LinuxParser::Ram(pid[i]);
        float cpu_utilisation = LinuxParser::CpuUtilization(pid[i]);
        Process proc(pid[i], command, user, uptime, ram, cpu_utilisation);
        if(unique_pid.find(pid[i]) == unique_pid.end())             // C++20 provides set::contains()
            processes_.emplace_back(proc);
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
    long int time = LinuxParser::UpTime() / sysconf(_SC_CLK_TCK) ;
    return time; 
}