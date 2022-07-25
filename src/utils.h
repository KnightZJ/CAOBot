#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include <ctime>
#include <MiraiCP.hpp>

using namespace std;
using namespace MiraiCP;

struct ParsedMessage {
  ParsedMessage(GroupMessageEvent &e);
  string miraiCode;
  vector<Member> mentionedMembers;
  vector<Image> images;
  vector<string> cmds;
  bool atAll;
  optional<OnlineAudio> audioMsg;
  optional<RemoteFile> fileMsg;
  optional<OnlineForwardedMessage> forwardMsg;
  Member sender;
  Group group;
  time_t timestamp;
};

string timeToString(time_t time);

#endif