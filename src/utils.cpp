#include "utils.h"
#include <iomanip>
#include <sstream>

string timeToString(time_t time, string format) {
  tm tm = *localtime(&time);
  ostringstream oss;
  oss << put_time(&tm, format.c_str());
  return oss.str();
}

ParsedMessage::ParsedMessage(GroupMessageEvent &e)
  : senderId(e.sender.id()),
    groupId(e.group.id()),
    source(e.message.source.value().source),
    audioMsg(e.message.first<OnlineAudio>()),
    fileMsg(e.message.first<RemoteFile>()),
    forwardedMsg(e.message.first<OnlineForwardedMessage>()),
    imageMsg(e.message.filter<Image>()),
    flashImageMsg(e.message.first<FlashImage>()),
    timestamp(time(0)),
    type(0) {
  if (audioMsg != nullopt)
    type |= AUDIO_MSG;
  else if (fileMsg != nullopt)
    type |= FILE_MSG;
  else if (forwardedMsg != nullopt)
    type |= FORWARDED_MSG;
  else if (flashImageMsg != nullopt)
    type |= FLASHIMAGE_MSG;
  else
    type |= NORMAL_MSG;
  for (auto at: e.message.filter<At>())
   atTargets.push_back(at.target);
  atAll = e.message.first<AtAll>() != nullopt;
  auto v = e.message.filter<PlainText>();
  for (int i = 0; i < v.size(); ++i) {
    string s = v[i].content;
    text += s+(i == v.size() - 1 ? "" : "\n");
    int pos = 0;
    bool word = false;
    for (int i = 0; i < s.length(); ++i) {
      if (s[i] == ' ' || s[i] == '\n') {
        if (word) {
          cmds.push_back(s.substr(pos, i - pos));
          word = false;
        }
      } else {
        if (!word) {
          word = true;
          pos = i;
        }
      }
    }
    if (word)
      cmds.push_back(s.substr(pos));
  }
}