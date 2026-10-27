# 项目交接 / HANDOFF

> 更新时间：2026-10-27
> 用途：换设备、新开会话、上下文不足时，先读这个文件。
> 这个文件是“外部记忆”，比聊天记录可靠。

## 1. 我是谁、目标是什么

- 中原工学院，软件学院，软件工程（融媒体方向），大一。
- 目标：2028 年大二下，在郑州找到第一段 C++ 相关实习。
- 竞赛背景：CSP-S 2024 120 分，NOIP 2024 64 分；普及组较稳、提高组入门。
- 已会：C++ 基础语法、数组、递归、DFS/回溯、MySQL 基础、Linux 命令行。
- 还没会/较弱：工程化（头文件、多文件、链接、CMake、Git）、STL 容器、类/对象、调试器。

## 2. 当前项目

- 仓库：`git@github.com:danhuang080123/media-asset-cli.git`
- 本地路径：`~/code/media-asset-cli`（Ubuntu 虚拟机）
- 技术栈：C++17、CMake、MySQL 8.0（Docker）、Git、VS Code Remote-SSH
- 项目目标：融媒体素材管理命令行工具，支持素材的增删改查、标签、检索、CSV 导入、统计。

### 已完成

- 仓库骨架：`README.md`、`CMakeLists.txt`、`.gitignore`、`docs/schema.sql`
- MySQL 三张表：`material`、`tag`、`material_tag`
- `src/db/MySQL.h` / `MySQL.cpp`：连接封装（构造连接、析构关闭）
- `src/main.cpp`：`add`、`list` 命令
- `examples/01-connect.cpp`：最小连接示例
- `examples/mysql_api_demo.cpp`：MySQL C API 示范（连接、查询、插入、删除）
- 洛谷 P1219 八皇后已 AC（代码在 `~/code/Luogu/P1219.cpp`，不一定在仓库里）

### 还没完成

- `delete --id`：删除一行素材
- `update --id --title`：修改标题
- 标签：加标签、给素材挂标签
- 按标签检索
- CSV 导入
- 统计（按类型计数、总大小）
- README 截图/演示视频
- 把 `main.cpp` 里的数据库操作拆到 `MaterialRepository`

## 3. 环境与常用命令

- Windows + Hyper-V，Ubuntu 26.04 虚拟机。
- SSH 配置：`Host ubuntu-vm` → `danhuang-ubuntu.local`，用户 `danhuang`。
- VS Code 用 Remote-SSH 连 `ubuntu-vm`，代码在 Ubuntu 里。
- MySQL 在 Docker：容器 `mysql`，镜像 `mysql:8.0`，端口 `3306`，库 `media_asset`，应用用户 `media`。
- **密码不写进仓库**，本地通过环境变量传：

```bash
export MYSQL_PASSWORD='本地密码'
```

### 编译项目

```bash
cd ~/code/media-asset-cli
cmake -B build
cmake --build build -j
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

## 4. 下一步优先级

1. `delete --id`：`DELETE FROM material WHERE id = ...`，用 `mysql_affected_rows` 判断有没有删到。
2. `update --id --title` 或 `list --type`：二选一。
3. 标签、按标签检索。
4. CSV 导入、统计。
5. 把数据库操作拆到 `src/db/MaterialRepository.h/.cpp`。

学习顺序上：

- 算法：继续洛谷，主刷普及/提高-；力扣 Hot 100 后补。
- 工程：先理解多文件编译、`.o`、链接器，再理解 CMake；不要一次学完。
- 项目：每完成一个小功能就 commit + push。

## 5. 教学偏好（给 AI 的说明）

- 我是**竞赛型 C++**，不是工程型；不要默认我会头文件、多文件、链接器、CMake、Make、Git。
- 不要默认我会 `class`、`STL`、`vector`、`array`；先讲“它是什么”，再给代码。
- 先解释名词，再给命令；一次只讲一个概念。
- 给可运行的小例子；不要一上来贴 200 行。
- 代码 review 顺序：先正确性，再可读性，最后工程化。
- 不要直接给完整项目代码；先让我自己写，再指出哪一行错。
- 我容易在“文件没保存”“路径不对”“大小写”上卡住；遇到报错先让我 `ls -l` / `pwd`。
- 周末全休，不排任务；周一到周五每天 2.5–3 小时。
- 我容易一次塞太多，请提醒我“今天只做一件事”。

## 6. 新会话开场白

新开对话时，把下面这段贴进去：

```text
请先读 docs/HANDOFF.md。

我是中原工学院软件工程（融媒体方向）大一学生，目标 2028 年大二下在郑州找第一段 C++ 实习。
当前项目：media-asset-cli，GitHub: git@github.com:danhuang080123/media-asset-cli.git
环境：Windows + Hyper-V Ubuntu 26.04，VS Code Remote-SSH；MySQL 8.0 在 Docker，端口 3306，库 media_asset。
已完成：仓库骨架、三张表、C++ 连接 MySQL、add/list、examples 下的连接和 C API demo。
还没完成：delete/update、标签检索、CSV、统计。

我是竞赛型 C++：会数组、递归、DFS/回溯；工程化（头文件、多文件、链接、CMake、Git）很弱。
请教我时：先解释名词，再给命令；一次只讲一个概念；不要默认我会 class/STL/CMake；不要直接给完整代码，先让我写再 review。
```

## 7. 重要文件

- `README.md`：项目说明
- `CMakeLists.txt`：构建配置
- `docs/schema.sql`：建表 SQL
- `src/main.cpp`：CLI 入口 + add/list
- `src/db/MySQL.h` / `MySQL.cpp`：连接封装
- `examples/mysql_api_demo.cpp`：MySQL C API 示范

## 8. 安全注意

- 不要把数据库密码、SSH 私钥、`.env` 提交到 Git。
- `~/mysql/docker-compose.yml` 里有本地密码，不要复制到仓库。
- 新设备恢复时，先 `git clone`，再按 `docs/schema.sql` 重建数据库，密码本地重新设置。
