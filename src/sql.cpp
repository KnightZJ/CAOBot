#include "sql.h"

Sql::Sql()
 : db("caobot.db", OPEN_READWRITE | OPEN_CREATE) {
  if (!db.tableExists("GroupMsg"))
    db.exec("CREATE TABLE GroupMsg("\
            "msgId       INTEGER   PRIMARY KEY,"\
            "groupId     INT8      NOT NULL,"\
            "senderId    INT8      NOT NULL,"\
            "source      TEXT      NOT NULL,"\
            "timestamp   INTEGER   NOT NULL,"\
            "type        INTEGER   NOT NULL)");
  if (!db.tableExists("FileMsg"))
    db.exec("CREATE TABLE FileMsg("\
            "fileId      INTEGER   PRIMARY KEY,"\
            "msgId       INTEGER   NOT NULL,"\
            "fileName    TEXT      NOT NULL,"\
            "fileSize    INT8      NOT NULL,"\
            "fileUrl     TEXT      NOT NULL)");
  if (!db.tableExists("ImageMsg"))
    db.exec("CREATE TABLE ImageMsg("\
            "imageId      INTEGER   PRIMARY KEY,"\
            "msgId       INTEGER   NOT NULL,"\
            "imageName    TEXT      NOT NULL,"\
            "imageUrl     TEXT      NOT NULL)");
  if (!db.tableExists("PlainMsg"))
    db.exec("CREATE TABLE PlainMsg("\
            "plainMsgId  INTEGER   PRIMARY KEY,"\
            "msgId       INTEGER   NOT NULL,"\
            "content     TEXT      NOT NULL)");
  if (!db.tableExists("AudioMsg"))
    db.exec("CREATE TABLE AudioMsg("\
            "audioId     INTEGER   PRIMARY KEY,"\
            "msgId       INTEGER   NOT NULL,"\
            "audioName   TEXT      NOT NULL,"\
            "audioSize   INTEGER   NOT NULL,"\
            "audioLength INTEGER   NOT NULL,"\
            "audioUrl    TEXT      NOT NULL)");
}

Sql& Sql::instance() {
  static Sql sql;
  return sql;
}

int Sql::saveGroupMsg(int64_t groupId, int64_t senderId, string source, time_t timestamp, int type) {
  Statement query(db, 
      "INSERT INTO GroupMsg "\
      "(msgId, groupId, senderId, source, timestamp, type) "\
      "VALUES (NULL, ?, ?, ?, ?, ?)");
  query.bind(1, groupId);
  query.bind(2, senderId);
  query.bind(3, source);
  query.bind(4, timestamp);
  query.bind(5, type);
  query.exec();
  return db.execAndGet("SELECT max(msgId) FROM GroupMsg").getInt();
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

bool Sql::saveFileMsg(int msgId, string name, int64_t size, string url) {
  Statement query(db, 
      "INSERT INTO FileMsg "\
      "(fileId, msgId, fileName, fileSize, fileUrl) "\
      "VALUES (NULL, ?, ?, ?, ?)");
  query.bind(1, msgId);
  query.bind(2, name);
  query.bind(3, size);
  query.bind(4, url);
  query.exec();
  return true;
}

bool Sql::saveAudioMsg(int msgId, string name, int size, int length, string url) {
  Statement query(db, 
      "INSERT INTO AudioMsg "\
      "(audioId, msgId, audioName, audioSize, audioLength, audioUrl) "\
      "VALUES (NULL, ?, ?, ?, ?, ?)");
  query.bind(1, msgId);
  query.bind(2, name);
  query.bind(3, size);
  query.bind(4, length);
  query.bind(5, url);
  query.exec();
  return true;
}

bool Sql::saveImageMsg(int msgId, string id, string url) {
  Statement query(db, 
      "INSERT INTO ImageMsg "\
      "(imageId, msgId, imageName, imageUrl) "\
      "VALUES (NULL, ?, ?, ?)");
  query.bind(1, msgId);
  query.bind(2, id);
  query.bind(3, url);
  query.exec();
  return true;
}

bool Sql::savePlainMsg(int msgId, string content) {
  Statement query(db, 
      "INSERT INTO PlainMsg "\
      "(plainMsgId, msgId, content) "\
      "VALUES (NULL, ?, ?)");
  query.bind(1, msgId);
  query.bind(2, content);
  query.exec();
  return true;
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
