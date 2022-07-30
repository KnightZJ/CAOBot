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
    marketfaceMsg(e.message.first<MarketFace>()),
    faceMsg(e.message.filter<Face>()),
    plainMsg(e.message.filter<PlainText>()),
    atMsg(e.message.filter<At>()),
    timestamp(time(0)),
    type(0) {
  if (audioMsg != nullopt)
    type |= AUDIO_MSG;
  if (fileMsg != nullopt)
    type |= FILE_MSG;
  if (forwardedMsg != nullopt)
    type |= FORWARDED_MSG;
  if (flashImageMsg != nullopt)
    type |= FLASHIMAGE_MSG;
  if (marketfaceMsg != nullopt)
    type |= MARKETFACE_MSG;
  if (!atMsg.empty())
    type |= AT_MSG;
  if (!faceMsg.empty())
    type |= FACE_MSG;
  if (!plainMsg.empty())
    type |= PLAIN_MSG;
  if (!imageMsg.empty())
    type |= IMAGE_MSG;
  atAll = e.message.first<AtAll>() != nullopt;
  for (int i = 0; i < plainMsg.size(); ++i) {
    string s = plainMsg[i].content;
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