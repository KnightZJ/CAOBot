# CAOBOT
> 框架：[MiraiCP](https://github.com/Nambers/MiraiCP)，版本：[![GitHub release (latest SemVer)](https://img.shields.io/github/v/release/Nambers/MiraiCP?include_prereleases)](https://github.com/Nambers/MiraiCP/releases/) 

## TODO:
- [x] Module模块抽象（群消息参数分离、help功能）
- [ ] Module调用限制、黑名单、功能冷却时长
- [ ] Module工厂，通过群消息来管理各个子功能的enable、disable及调用

## 子功能：
- [x] record: 存储群消息至数据库（语音、文件消息额外处理）
- [x] version: 输出当前caobot版本
- [ ] pica: 随机发图

## 依赖：
- [MiraiCP](https://github.com/Nambers/MiraiCP)及其依赖
- [SQLiteCpp](https://github.com/SRombauts/SQLiteCpp)