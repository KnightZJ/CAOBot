#include "record.h"
#include <cstdio>

Record::Record(): Module(
  "record",
  "v1.0",
  __DATE__,
  __TIME__,
  "存储群聊历史记录") {  
}

bool Record::processGroupMessage(ParsedMessage& pm) {
  int fileId = 0, audioId = 0;
  if (pm.fileMsg != nullopt) {
    string name = pm.fileMsg.value().name;
    int64_t size = pm.fileMsg.value().size;
    string url = pm.fileMsg.value().dinfo->url;
    fileId = Sql::instance().saveFileMsg(name, size, url);
  }
  if (pm.audioMsg != nullopt) {
    string name = pm.audioMsg.value().filename;
    int size = pm.audioMsg.value().size;
    int length = pm.audioMsg.value().length;
    string url = pm.audioMsg.value().url;
    audioId = Sql::instance().saveAudioMsg(name, size, length, url);
  }
  Sql::instance().saveGroupMsg(pm.group.id(), pm.sender.id(), pm.miraiCode, pm.timestamp, fileId, audioId);
  return true;
}
