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
  : sender(e.sender), group(e.group) {
  for (auto at: e.message.filter<At>())
    mentionedMembers.push_back(e.group.getMember(at.target));
  for (auto audio: e.message.filter<OnlineAudio>())
    audios.push_back(audio);
  images = e.message.filter<Image>();
  for (auto text: e.message.filter<PlainText>()) {
    string s = text.content;
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