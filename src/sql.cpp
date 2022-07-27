#include "sql.h"

Sql::Sql()
 : db("caobot.db", OPEN_READWRITE | OPEN_CREATE) {
  if (!db.tableExists("GroupMsg"))
    db.exec("CREATE TABLE GroupMsg("\
            "msgId       INTEGER   PRIMARY KEY,"\
            "groupId     INT8      NOT NULL,"\
            "senderId    INT8      NOT NULL,"\
            "miraiCode   TEXT      NOT NULL,"\
            "timestamp   INTEGER   NOT NULL,"\
            "fileId      INTEGER   DEFAULT 0,"\
            "audioId     INTEGER   DEFAULT 0)");
  if (!db.tableExists("FriendMsg"))
    db.exec("CREATE TABLE FriendMsg("\
            "msgId       INTEGER   PRIMARY KEY,"\
            "friendId    INT8      NOT NULL,"\
            "miraiCode  TEXT      NOT NULL,"\
            "timestamp   INTEGER   NOT NULL)");
  if (!db.tableExists("FileMsg"))
    db.exec("CREATE TABLE FileMsg("\
            "fileId      INTEGER   PRIMARY KEY,"\
            "fileName    TEXT      NOT NULL,"\
            "fileSize    INT8      NOT NULL,"\
            "fileUrl     TEXT      NOT NULL)");
  if (!db.tableExists("AudioMsg"))
    db.exec("CREATE TABLE AudioMsg("\
            "audioId     INTEGER   PRIMARY KEY,"\
            "audioName   TEXT      NOT NULL,"\
            "audioSize   INTEGER   NOT NULL,"\
            "audioLength INTEGER   NOT NULL,"\
            "audioUrl    TEXT      NOT NULL)");
  if (!db.tableExists("GroupConfig"))
    db.exec("CREATE TABLE GroupConfig("\
            "groupId     INT8   PRIMARY KEY,"\
            "config      INT8   DEFAULT 0)");
}

Sql& Sql::instance() {
  static Sql sql;
  return sql;
}

bool Sql::saveGroupMsg(int64_t groupId, int64_t senderId, string miraiCode, time_t timestamp, int fileId, int audioId) {
  Statement query(db, 
      "INSERT INTO GroupMsg "\
      "(msgId, groupId, senderId, miraiCode, timestamp, fileId, audioId) "\
      "VALUES (NULL, ?, ?, ?, ?, ?, ?)");
  query.bind(1, groupId);
  query.bind(2, senderId);
  query.bind(3, miraiCode);
  query.bind(4, timestamp);
  query.bind(5, fileId);
  query.bind(6, audioId);
  query.exec();
  return true;
}

vector<string> Sql::getGroupMsg(int64_t groupId, int64_t senderId, int count) {
  vector<string> res;
  Statement query(db, 
      "SELECT miraiCode FROM GroupMsg "\
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

int Sql::saveFileMsg(string name, int64_t size, string url) {
  Statement query(db, 
      "INSERT INTO FileMsg "\
      "(fileId, fileName, fileSize, fileUrl) "\
      "VALUES (NULL, ?, ?, ?)");
  query.bind(1, name);
  query.bind(2, size);
  query.bind(3, url);
  query.exec();
  return db.execAndGet("SELECT max(fileId) FROM FileMsg").getInt();
}

int Sql::saveAudioMsg(string name, int size, int length, string url) {
  Statement query(db, 
      "INSERT INTO AudioMsg "\
      "(audioId, audioName, audioSize, audioLength, audioUrl) "\
      "VALUES (NULL, ?, ?, ?, ?)");
  query.bind(1, name);
  query.bind(2, size);
  query.bind(3, length);
  query.bind(4, url);
  query.exec();
  return db.execAndGet("SELECT max(audioId) FROM AudioMsg").getInt();
}

bool Sql::updateGroupConfig(int64_t groupId, int64_t config) {
  Statement q1(db, 
      "INSERT OR IGNORE INTO GroupConfig VALUES(?, ?)");
  q1.bind(1, groupId);
  q1.bind(2, config);
  q1.exec();
  Statement q2(db,
      "UPDATE GroupConfig SET config = ? WHERE groupId = ?");
  q2.bind(1, config);
  q2.bind(2, groupId);
  q2.exec();
  return true;
}

int64_t Sql::getGroupConfig(int64_t groupId) {
  Statement query(db,
      "SELECT config FROM GroupConfig WHERE groupId = ?");
  query.bind(1, groupId);
  if (query.executeStep())
    return query.getColumn(0);
  return 0;
}
