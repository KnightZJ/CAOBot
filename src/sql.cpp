#include "sql.h"
#include <cstdio>

Sql* sql = nullptr;

Sql::Sql()
 : db("caobot.db", OPEN_READWRITE | OPEN_CREATE) {
  init();
}

Sql* Sql::instance() {
  if (sql == nullptr)
    sql = new Sql();
  return sql;
}

bool Sql::init() {
  if (!db.tableExists("GroupMsg"))
    db.exec("CREATE TABLE GroupMsg("\
            "groupId     INT8             NOT NULL,"\
            "senderId    INT8             NOT NULL,"\
            "msgContent  TEXT             NOT NULL,"\
            "timestamp   INTEGER          NOT NULL)");
  if (!db.tableExists("FriendMsg"))
    db.exec("CREATE TABLE FriendMsg("\
                  "msgId       INT8 PRIMARY KEY NOT NULL,"\
                  "friendId    INT8             NOT NULL,"\
                  "msgContent  TEXT             NOT NULL,"\
                  "timestamp   INTEGER          NOT NULL)");
  return true;
}

bool Sql::saveGroupMsg(int64_t groupId, int64_t senderId, string miraiCode, time_t timestamp) {
  Statement query(db, 
      "INSERT INTO GroupMsg "\
      "(groupId, senderId, msgContent, timestamp) "\
      "VALUES (?, ?, ?, ?)");
  query.bind(1, groupId);
  query.bind(2, senderId);
  query.bind(3, miraiCode);
  query.bind(4, timestamp);
  query.exec();
  return true;
}

vector<string> Sql::getGroupMsg(int64_t groupId, int64_t senderId, int count) {
  vector<string> res;
  Statement query(db, 
      "SELECT msgContent FROM GroupMsg "\
      "WHERE groupId = ? AND senderId = ? "\
      "ORDER BY timestamp DESC "\
      "LIMIT ?");
  query.bind(1, groupId);
  query.bind(2, senderId);
  query.bind(3, count);
  while (query.executeStep())
    res.push_back(query.getColumn(0));
  return res;
}

void Sql::quit() {
  delete sql;
  sql = nullptr;
}
