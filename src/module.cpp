#include "module.h"

const string monthTable[] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

Module::Module(string _prefix, string _version, string date, string time, string _desc) {
  updateTime = date.substr(7, 4) + "/";
  string sub = date.substr(0, 3);
  for (int i = 0; i < 12; ++i)
    if (monthTable[i] == sub) {
      updateTime += to_string(i+1) + "/";
    }
  updateTime += date.substr(4, 2) + " " + time.substr(0, 5);
  version = _version;
  desc = _desc;
  prefix = _prefix;
}

string Module::help() {
  return "模块名称：" + prefix + " (" + version + ")\n"
        +"构建时间：" + updateTime + "\n"
        +"模块功能：" + desc;
}

