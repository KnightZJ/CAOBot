#ifndef __PANEL_H__
#define __PANEL_H__

#include <MiraiCP.hpp>
#include <queue>
#include <chrono>
#include <thread>

using namespace MiraiCP;
using namespace std;

struct GroupMsg {
  QQID botId;
  QQID groupId;
  MessageChain mc;
};

class Panel {
public:
  static Panel& instance();
  void addGroupMsg(QQID botId, QQID groupId, MessageChain mc);
  void dealMsg();
private:
  Panel();
  queue<GroupMsg> groupMsg;
};

#endif