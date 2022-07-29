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
  int saveGroupMsg(int64_t groupId, int64_t senderId, string source, time_t timestamp, int type);
  bool saveFileMsg(int msgId, string name, int64_t size, string url);
  bool saveAudioMsg(int msgId, string name, int size, int length, string url);
  bool savePlainMsg(int msgId, string content);
  bool saveImageMsg(int msgId, string id, string url);
  bool updateGroupConfig(int64_t groupId, int64_t config);
  int64_t getGroupConfig(int64_t groupId);
  vector<string> getGroupMsg(int64_t groupId, int64_t senderId, int count);
private:
  Sql();
private:
  Database db;
};

#endif