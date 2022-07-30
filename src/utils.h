#ifndef __UTILS_H__
#define __UTILS_H__

#define AUDIO_MSG 0x2
#define FILE_MSG  0x4
#define FORWARDED_MSG 0x8
#define FLASHIMAGE_MSG 0x10
#define AT_MSG 0x20
#define MARKETFACE_MSG 0x40
#define FACE_MSG 0x80
#define IMAGE_MSG 0x100
#define PLAIN_MSG 0x200

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
  optional<OnlineAudio>     audioMsg;
  optional<RemoteFile>      fileMsg;
  optional<OnlineForwardedMessage> forwardedMsg;
  optional<FlashImage>      flashImageMsg;
  optional<MarketFace>      marketfaceMsg;
  vector<Image>  imageMsg;
  vector<At>     atMsg;
  vector<Face>   faceMsg;
  vector<PlainText> plainMsg;
  vector<string> cmds;
  int type;
  time_t timestamp;
};

string timeToString(time_t time);

#endif