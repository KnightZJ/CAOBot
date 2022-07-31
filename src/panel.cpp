#include "panel.h"

Panel::Panel() {
}

Panel& Panel::instance() {
  static Panel panel;
  return panel;
}

void Panel::addGroupMsg(QQID botId, QQID groupId, MessageChain mc) {
  groupMsg.push({botId, groupId, mc});
}

void Panel::dealMsg() {
  while(!groupMsg.empty()) {
    auto front = groupMsg.front();
    Group(front.groupId, front.botId).sendMessage(front.mc);
    groupMsg.pop();
    this_thread::sleep_for(chrono::milliseconds(500));

  }
}
