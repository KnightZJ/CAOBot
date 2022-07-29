#ifndef __UTILS_H__
#define __UTILS_H__

#define NORMAL_MSG 0x1
#define AUDIO_MSG 0x2
#define FILE_MSG  0x4
#define FORWARDED_MSG 0x8
#define FLASHIMAGE_MSG 0x10

#include <string>
#include <ctime>
#include <MiraiCP.hpp>

using namespace std;
using namespace MiraiCP;

struct ParsedMessage {
  ParsedMessage(GroupMessageEvent &e);
  string source;
  QQID senderId;
  QQID groupId;
  bool atAll;
  optional<OnlineAudio> audioMsg;
  optional<RemoteFile>  fileMsg;
  optional<OnlineForwardedMessage> forwardedMsg;
  optional<FlashImage> flashImageMsg;
  vector<Image> imageMsg;
  vector<QQID>  atTargets;
  vector<string> cmds;
  int type;
  string text;
  time_t timestamp;
};

string timeToString(time_t time);

#endif