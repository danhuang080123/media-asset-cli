# 项目交接 / HANDOFF

> 更新时间：2026-10-28
> 用途：换设备、新开会话、上下文不足时，先读这个文件。
> 这个文件是“外部记忆”，比聊天记录可靠。

## 0. 先看这一句

我以后把对话分成两种：

1. **规划对话**：只负责目标、周计划、优先级、复盘、资源选择、投递节奏；不展开讲语法，不贴完整代码。
2. **执行对话**：具体写某个功能、某个报错、某个知识点；一次只解决一个具体问题。

这份文件主要给“规划对话”用；执行对话只需要看当前任务那一节。

## 1. 我是谁、目标是什么

- 中原工学院，软件学院，软件工程（融媒体方向），大一。
- 目标：2028 年大二下，在郑州找到第一段 C++ 相关实习。
- 竞赛背景：CSP-S 2024 120 分，NOIP 2024 64 分；普及组较稳、提高组入门。
- 已会：C++ 基础语法、数组、递归、DFS/回溯、MySQL 基础、Linux 命令行。
- 工程化还在补：头文件、多文件、链接器、CMake、Git 都只能算入门。

## 2. 当前项目

- 仓库：`git@github.com:danhuang080123/media-asset-cli.git`
- 本地路径：`~/code/media-asset-cli`（Ubuntu 虚拟机）
- 最新提交：`8909db1 feat: add delete command with --id`
- 技术栈：C++17、CMake、MySQL 8.0（Docker）、Git、VS Code Remote-SSH
- 项目目标：融媒体素材管理命令行工具，支持素材的增删改查、标签、检索、CSV 导入、统计。

### 已完成

- 仓库骨架：`README.md`、`CMakeLists.txt`、`.gitignore`、`docs/schema.sql`
- MySQL 三张表：`material`、`tag`、`material_tag`
- `src/db/MySQL.h` / `MySQL.cpp`：连接封装（构造连接、析构关闭）
- `src/main.cpp`：`add`、`list`、`delete --id`
- `examples/01-connect.cpp`：最小连接示例
- `examples/mysql_api_demo.cpp`：MySQL C API 示范（连接、查询、插入、删除）
- 洛谷 P1219 八皇后已 AC（代码在 `~/code/Luogu/P1219.cpp`）
- VS Code 全局构建：打开 `~/code` 作为工作区时，`Ctrl+Shift+B` 编译当前文件到同目录 `bin/`
- `HANDOFF.md` 已提交到仓库

### 还没完成

- `update --id --title`：修改标题
- `list --type`：按类型过滤
- 标签：加标签、给素材挂标签
- 按标签检索
- CSV 导入
- 统计（按类型计数、总大小）
- README 截图/演示视频
- 把 `main.cpp` 里的数据库操作拆到 `MaterialRepository`

## 3. 我已经理解的内容（不用再从零讲）

- `MySQL.h` 的每一行：`#pragma once`、`class`、构造/析构、`= delete`、`get()`、`conn_`
- `MYSQL*` 是连接句柄；`mysql_init` 返回指针
- 构造函数 = 对象创建时自动连接；析构函数 = 对象销毁时自动关闭
- 为什么禁止拷贝：两个对象共用 `conn_` 会重复 `mysql_close`
- `host.c_str()`：`std::string` → `const char*`，给 C API 用
- `try/catch`、`throw`、`std::exception`、`e.what()`、切片
- 多文件编译、`.o`、链接器、CMake 的 configure/build
- 指针、引用、`const`、`nullptr` 的基本用法

## 4. 还比较弱、需要从零讲的内容

- `std::vector`、`std::array`、`std::string` 的常用操作
- `class` 的继承、多态、虚函数
- CMake 的变量、`target_link_libraries`、库的查找
- Git 分支、回滚、冲突处理
- gdb 调试、断点、backtrace
- Qt、FFmpeg、网络编程（还没开始）
- 多文件项目的分层：`model` / `db` / `service`

## 5. 环境与常用命令

- Windows + Hyper-V，Ubuntu 26.04 虚拟机。
- SSH 配置：`Host ubuntu-vm` → `danhuang-ubuntu.local`，用户 `danhuang`。
- VS Code 用 Remote-SSH 连 `ubuntu-vm`，代码在 Ubuntu 里。
- MySQL 在 Docker：容器 `mysql`，镜像 `mysql:8.0`，端口 `3306`，库 `media_asset`，应用用户 `media`。
- **密码不写进仓库**，本地通过环境变量传：

```bash
export MYSQL_USER=media
export MYSQL_PASSWORD='本地密码'
export MYSQL_DATABASE=media_asset
```

### 编译项目

```bash
cd ~/code/media-asset-cli
cmake -B build
cmake --build build -j
./build/media_asset_cli list
```

### 运行 delete

```bash
./build/media_asset_cli delete --id 2
./build/media_asset_cli list
```

### 单独编译一个文件

```bash
g++ -std=c++17 examples/mysql_api_demo.cpp -o /tmp/demo \
    $(pkg-config --cflags --libs mysqlclient)
```

### 启动 MySQL（如果容器没开）

```bash
cd ~/mysql
docker compose up -d
docker ps
```

### Git

```bash
git status
git add .
git commit -m "说明"
git push
```

## 6. 下一步优先级

1. `update --id --title`：改标题，练 `UPDATE` 和 `mysql_affected_rows`。
2. `list --type`：加过滤条件，练 `WHERE`。
3. 标签、按标签检索。
4. CSV 导入、统计。
5. 把数据库操作拆到 `src/db/MaterialRepository.h/.cpp`。

学习顺序上：

- 算法：继续洛谷，主刷普及/提高-；力扣 Hot 100 后补。
- 工程：先理解多文件编译、`.o`、链接器，再理解 CMake；不要一次学完。
- 项目：每完成一个小功能就 commit + push。

## 7. 规划对话的规则（给 AI）

如果你是“规划对话”的 AI：

- 只负责：目标、周计划、优先级、复盘、资源选择、投递节奏。
- 不要展开讲 C++ 语法、不要贴完整代码；那属于“执行对话”。
- 每次最多给我 3 件事，按优先级排。
- 先问我这周实际可用时间，再排计划。
- 周一到周五学习，周六周日全休；每天 2.5–3 小时。
- 我容易一次塞太多，请提醒我“今天只做一件事”。
- 我容易在“文件没保存”“路径不对”“大小写”上卡住；遇到报错先让我 `ls -l` / `pwd`。

## 8. 执行对话的规则（给 AI）

如果你是“执行对话”的 AI：

- 一次只解决一个具体问题：一个函数、一个报错、一个知识点。
- 顺序：先解释名词 → 给最小步骤 → 让我自己写 → 只指出错误行。
- 不要直接给完整实现，除非我明确说“直接帮我改”。
- 先让我跑 `git status`、`cmake --build build -j`，把第一行报错发你。
- 不要默认我会 `class`、`STL`、`CMake`、`Git`。

## 9. 新会话开场白

### 规划对话（复制这段）

```text
你是我的学习规划教练，不是代码陪练。先读 docs/HANDOFF.md。

我是中原工学院软件工程（融媒体方向）大一学生，目标 2028 年大二下在郑州找第一段 C++ 实习。
当前项目：media-asset-cli，已完成 add/list/delete --id；下一步 update、list --type、标签、CSV、统计。
我周一到周五每天 2.5–3 小时，周六周日全休。

请只负责：本周计划、优先级、复盘、资源选择、投递节奏。
不要展开讲语法，不要贴完整代码；具体学习我会另开“执行对话”。
每次最多给我 3 件事，先问我这周实际可用时间。
```

### 执行对话（复制这段）

```text
我在做 media-asset-cli 的某个具体任务，遇到一个具体问题。
先读 docs/HANDOFF.md 的第 2、3、4 节即可。

请按这个顺序：
1. 先解释我不懂的名词；
2. 给最小步骤；
3. 让我自己写；
4. 只指出我哪一行错，不要直接给完整实现。

我的水平：竞赛型 C++，会数组/递归/DFS；工程化（class、STL、CMake、Git）很弱。
```

## 10. 重要文件

- `README.md`：项目说明
- `CMakeLists.txt`：构建配置
- `docs/schema.sql`：建表 SQL
- `src/main.cpp`：CLI 入口 + add/list/delete
- `src/db/MySQL.h` / `MySQL.cpp`：连接封装
- `examples/mysql_api_demo.cpp`：MySQL C API 示范
- `docs/HANDOFF.md`：本文件

## 11. 安全注意

- 不要把数据库密码、SSH 私钥、`.env` 提交到 Git。
- `~/mysql/docker-compose.yml` 里有本地密码，不要复制到仓库。
- 新设备恢复时，先 `git clone`，再按 `docs/schema.sql` 重建数据库，密码本地重新设置。
