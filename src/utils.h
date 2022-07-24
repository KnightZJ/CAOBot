#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include <ctime>
#include <MiraiCP.hpp>

using namespace std;
using namespace MiraiCP;

struct ParsedMessage {
  ParsedMessage(GroupMessageEvent &e);
  vector<Member> mentionedMembers;
  vector<Image> images;
  vector<OnlineAudio> audios;
  vector<string> cmds;
  Member sender;
  Group group;
};

string timeToString(time_t time);

#endif