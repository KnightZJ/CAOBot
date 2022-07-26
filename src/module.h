#ifndef __MODULE_H__
#define __MODULE_H__

#include <string>
#include <vector>
#include "utils.h"

using namespace std;
using namespace MiraiCP;

class Module {
public:
  Module(string _prefix, string _version, string date, string time, string _desc);
  bool processGroupMessage(ParsedMessage& pm);
protected:
  string help();
protected:
  string version;
  string desc;
  string updateTime;
  string prefix;
};

#endif