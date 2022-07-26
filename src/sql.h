#ifndef __SQL_H__
#define __SQL_H__

#include <SQLiteCpp/SQLiteCpp.h>
#include <string>
#include <vector>

using namespace std;
using namespace SQLite;

class Sql {
public:
  static Sql& instance();
  bool saveGroupMsg(int64_t groupId, int64_t senderId, string miraiCode, time_t timestamp, int fileId, int audioId);
  int saveFileMsg(string name, int64_t size, string url);
  int saveAudioMsg(string name, int size, int length, string url);
  vector<string> getGroupMsg(int64_t groupId, int64_t senderId, int count);
private:
  Sql();
private:
  Database db;
};

#endif