#include "module.h"

const string monthTable[] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

Module::Module(string _prefix, string _version, string date, string time, string _desc) {
  updateTime = date.substr(7, 4) + "/";
  string sub = date.substr(0, 3);
  for (int i = 0; i < 12; ++i)
    if (monthTable[i] == sub) {
      updateTime += to_string(i+1) + "/";
    }
  updateTime += date.substr(4, 2) + " " + time.substr(0, 5);
  version = _version;
  desc = _desc;
  prefix = _prefix;
  subcmds.push_back({"help", &Module::help});
  subcmds.push_back({"enable", &Module::enable});
  subcmds.push_back({"disable", &Module::disable});
  subcmds.push_back({"banlist", &Module::banlist});
}

bool Module::help(ParsedMessage& pm) {
  Panel::instance().addGroupMsg(pm.botId, pm.group.id(),
      MessageChain(PlainText("模块名称：" + prefix + " (" + version + ")\n"
        +"构建时间：" + updateTime + "\n"
        +"模块功能：" + desc)));
  return true;
}

bool Module::processGroupMessage(ParsedMessage& pm) {
  if (bannedMembers.find(pm.sender.id()) == bannedMembers.end() && pm.cmds.size() >= 1 && pm.cmds[0] == "/" + prefix) {
    if (pm.cmds.size() >= 2) {
      for (auto& sub: subcmds) {
        if (pm.cmds[1] == sub.first) {
          (*this.*sub.second)(pm);
        }
      }
    }
  }
  return true;
}
bool Module::enable(ParsedMessage& pm) {
  if (pm.sender.permission >= 1) {
    if (enabledGroups.find(pm.group.id()) == enabledGroups.end()) {
      enabledGroups.insert(pm.group.id());
      Panel::instance().addGroupMsg(pm.botId, pm.group.id(), MessageChain(PlainText("指令/"+prefix+"已启用。")));
      return true;
    } else {
      Panel::instance().addGroupMsg(pm.botId, pm.group.id(), MessageChain(PlainText("指令/"+prefix+"已经启用！")));
      return false;
    }
  }
  Panel::instance().addGroupMsg(pm.botId, pm.group.id(), MessageChain(PlainText("你权限不足！")));
  return false;
}

bool Module::disable(ParsedMessage& pm) {
  if (pm.sender.permission >= 1) {
    if (enabledGroups.find(pm.group.id()) != enabledGroups.end()) {
      enabledGroups.erase(pm.group.id());
      Panel::instance().addGroupMsg(pm.botId, pm.group.id(), MessageChain(PlainText("指令/"+prefix+"已禁用。")));
      return true;
    } else {
      Panel::instance().addGroupMsg(pm.botId, pm.group.id(), MessageChain(PlainText("指令/"+prefix+"已经禁用！")));
      return false;
    }
  }
  Panel::instance().addGroupMsg(pm.botId, pm.group.id(), MessageChain(PlainText("你权限不足！")));
  return false;
}

bool Module::banlist(ParsedMessage& pm) {
  if (pm.sender.permission >= 1) {
    if (pm.cmds.size() >= 3) {
      if (pm.cmds[2] == "add" && pm.atMsg.size() >= 1) {
        int success = 0;
        for (auto at: pm.atMsg) {
          if (bannedMembers.find(at.target) == bannedMembers.end()) {
            bannedMembers.insert(at.target);
            ++success;
          }
        }
        if (success > 0) {
          Panel::instance().addGroupMsg(pm.botId, pm.group.id(), 
              MessageChain(PlainText("成功新增"+to_string(success)+"人至指令/"+prefix+"黑名单。")));
          return true;
        } else {
          Panel::instance().addGroupMsg(pm.botId, pm.group.id(), 
              MessageChain(PlainText("添加失败。所艾特成员已在/"+prefix+"黑名单中！")));
          return false;
        }
      }
      else if (pm.cmds[2] == "remove" && pm.atMsg.size() >= 1) {
        int success = 0;
        for (auto at: pm.atMsg) {
          if (bannedMembers.find(at.target) != bannedMembers.end()) {
            bannedMembers.erase(at.target);
            ++success;
          }
        }
        if (success > 0) {
          Panel::instance().addGroupMsg(pm.botId, pm.group.id(), 
              MessageChain(PlainText("成功将"+to_string(success)+"人移出指令/"+prefix+"黑名单。")));
          return true;
        } else {
          Panel::instance().addGroupMsg(pm.botId, pm.group.id(), 
              MessageChain(PlainText("移除失败。所艾特成员不在/"+prefix+"黑名单中！")));
          return false;
        }
      }
      else if (pm.cmds[2] == "print") {
        string s = "指令/"+prefix+"的黑名单有"+to_string(bannedMembers.size())+"人";
        if (bannedMembers.size() == 0)
          s += "。";
        else {
          s += ": ";
          int i = 1;
          for (auto id: bannedMembers)
            s += "\n" + to_string(i++) + ": @"+Member(id, pm.group.id(), pm.botId).nickOrNameCard();
        }
        Panel::instance().addGroupMsg(pm.botId, pm.group.id(), MessageChain(PlainText(s)));
        return true;
      }
    }
    Panel::instance().addGroupMsg(pm.botId, pm.group.id(), 
          MessageChain(PlainText("参数不正确！")));
    return false;
  }
  Panel::instance().addGroupMsg(pm.botId, pm.group.id(), 
          MessageChain(PlainText("你权限不足！")));
  return false;
}
