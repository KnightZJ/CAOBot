#ifndef __MODULE_H__
#define __MODULE_H__

#include <string>
#include <vector>
#include <set>
#include <utility>
#include "panel.h"
#include "utils.h"

using namespace std;
using namespace MiraiCP;

class Module {
public:
  Module(string _prefix, string _version, string date, string time, string _desc);
  void check(ParsedMessage& pm);
  bool processGroupMessage(ParsedMessage& pm);
protected:
  bool help(ParsedMessage& pm);
  bool enable(ParsedMessage& pm);
  bool disable(ParsedMessage& pm);
  bool banlist(ParsedMessage& pm);
protected:
  string version;
  string desc;
  string updateTime;
  string prefix;
  set<QQID> enabledGroups;
  set<QQID> bannedMembers;
  vector<pair<string, bool (Module::*)(ParsedMessage&)>> subcmds;
};

#endif