#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          break;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel >> version;
  }
  return version;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  float value, used_memory;
  std::map<std::string, int> mmap;
  std::string line, word;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if(filestream.is_open())
  {
    while(std::getline(filestream, line))
    {
      //std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> word >> value;
      mmap[word] = value;
    }
    used_memory = mmap["MemTotal:"] - mmap["MemFree:"];
  }
  return used_memory / mmap["MemTotal:"]; }
 
// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  std::string line;
  long first;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if(filestream.is_open())
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> first;
  }
  return first; 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  std::string line, cpu_;
  long total, first, second, third, fourth, fifth, sixth, seventh, eighth, ninth, tenth;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open())
  {
    std::getline(filestream,line);
    std::istringstream linestream(line);
    linestream >> cpu_ >> first >> second >> third >>fourth >> fifth >> sixth >> seventh >> eighth >> ninth >> tenth ;
    total = (first + second + third + fourth + fifth + sixth + seventh + eighth + ninth + tenth);    
  }
  return total; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  std::string line, cpu_;
  long active_total, first, second, third;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open())
  {
    std::getline(filestream,line);
    std::istringstream linestream(line);
    linestream >> cpu_ >> first >> second >> third;
    active_total = first + second + third;
  }
  return active_total; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  std::string line, cpu_;
  long first, second, third, fourth, fifth;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open())
  {
    std::getline(filestream,line);
    std::istringstream linestream(line);
    linestream >> cpu_ >> first >> second >> third >> fourth >> fifth;
  }
  return fourth + fifth; }

// TODO: Read and return CPU utilization
float LinuxParser::CpuUtilization() { 
  std::string line, cpu_;
  float cpu_utilisation;
  long total_seconds;
  total_seconds = Jiffies() / sysconf(_SC_CLK_TCK);
  cpu_utilisation = ((float)(total_seconds - (IdleJiffies() / sysconf(_SC_CLK_TCK))) / total_seconds);
  return cpu_utilisation;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  std::string line, key;
  int value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open())
  {
    while(std::getline(filestream, line))
    {
      std::istringstream linestream(line);
      linestream >> key;
      if(key == "processes")
      {
        linestream >> value;
        break;
      }
    }
  }
  return value;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  std::string line, key;
  int value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open())
  {
    while(std::getline(filestream, line))
    {
      std::istringstream linestream(line);
      linestream >> key;
      if(key == "procs_running")
      {
        linestream >> value;
        break;
      }
    }
  }
  return value;
}

// TODO: Read and return the command associated with a process
string LinuxParser::Command(int pid) { 
  std::string line;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if(filestream.is_open())
    std::getline(filestream, line);
  return line; 
}

float LinuxParser::CpuUtilization(int pid)
{
  std::string line, word;
  std::string first, second , third, fourth, fifth, sixth, seventh, eighth, ninth, tenth, eleven, twelve, thirteen, fourteen, 
              fifteen, sixteen, seventen, eighteen, nineteen, twenty, twentyone, twentytwo;
  long total_time, seconds; 
  float cpu_usage;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if(filestream.is_open())
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> first >> second >> third >> fourth >> fifth >> sixth >> seventh >> eighth >> ninth >> tenth >> eleven >> twelve >>
    thirteen >> fourteen >> fifteen >> sixteen >> seventen >> eighteen >> nineteen >> twenty >> twentyone >> twentytwo ;

    total_time = std::stol(fourteen) + std::stol(fifteen) + std::stol(sixteen) + std::stol(seventen);
    seconds = LinuxParser::UpTime() - (std::stol(twentytwo) / sysconf(_SC_CLK_TCK));
    cpu_usage = ((float)(total_time / sysconf(_SC_CLK_TCK)) / seconds );   
  }
  return cpu_usage;
}

// TODO: Read and return the memory used by a process
std::string LinuxParser::Ram(int pid) { 
  std::string line, key, value;
  int memsize;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if(filestream.is_open())
  {
    while(std::getline(filestream, line))
    {
      std::istringstream linestream(line);
      linestream >> key;
      if(key == "VmSize:")
      {
        linestream >> value;
        memsize = std::stoi(value) / 1000;
        value = std::to_string(memsize);
        break;
      }
    }
  }
  return value;
}

// TODO: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) { 
  std::string line, key, value;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if(filestream.is_open())
  {
      std::getline(filestream, line);
      std::istringstream linestream(line);
      linestream >> key ;
      if(key == "Uid:")
      {
        linestream >> value;
      }
  }
  return value;
 }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string line, uname, x, uid;
  std::ifstream filestream(kPasswordPath);
  std::string current_uid = LinuxParser::Uid(pid);
  if(filestream.is_open())
  {
    while(std::getline(filestream, line))
    {
      std::replace(line.begin(),line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> uname >> x >> uid ;
      if(current_uid == uid)
      {
        return uname;
      }
    }
  }
  return uname; 
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long int LinuxParser::UpTime(int pid) { 
  std::string line;
  long int uptime, value;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if(filestream.is_open())
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    for(int i = 1 ; i <= 22; i++)
    {
      if(i == 22)
        linestream >> value;
    }
    uptime = value / sysconf(_SC_CLK_TCK);
  }
  return uptime; 
}
