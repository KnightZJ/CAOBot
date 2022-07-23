#ifndef __MODULE_H__
#define __MODULE_H__

#include <string>

using namespace std;

class Module {
public:
  Module(string _prefix, string _version, string date, string time, string _desc);
  string help();
protected:
  string version;
  string desc;
  string updateTime;
  string prefix;
};

#endif