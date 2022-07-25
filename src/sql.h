#ifndef __SQL_H__
#define __SQL_H__

#include <SQLiteCpp/SQLiteCpp.h>
#include <string>
#include <vector>

using namespace std;
using namespace SQLite;

class Sql {
public:
  static Sql* instance();
  bool saveGroupMsg(int64_t groupId, int64_t senderId, string miraiCode, time_t timestamp);
  vector<string> getGroupMsg(int64_t groupId, int64_t senderId, int count);
  void quit();
private:
  Sql();
  bool init();
private:
  Database db;
};

#endif