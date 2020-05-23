#ifndef PROCESS_H
#define PROCESS_H

#include <string>

#include "linux_parser.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid, std::string user, std::string command, std::string ram, long int uptime, float cpu_utilisation);
  int Pid() const;                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  void SetCpu(float _cpu);
  void SetUser(std::string _user );
  void SetUptime(long int _uptime);
  void SetCommand(std::string _command);
  void SetRam(std::string _ram);

  // TODO: Declare any necessary private members
 private:
    int pid_{0};
    std::string user_{};
    std::string command_{};
    std::string ram_{};
    long int uptime_{0};
    float cpu_utilisation_{0.0};
};

#endif