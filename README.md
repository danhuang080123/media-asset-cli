# media-asset-cli

融媒体素材管理命令行工具（C++17 + MySQL 8 + CMake）。

## 技术栈
- C++17
- MySQL 8.0（Docker）
- CMake

## 构建
cmake -B build
cmake --build build

## 运行
./build/media_asset_cli

## 目录
- src/：源代码
- docs/：设计文档与 SQL
- tests/：测试

## 进度
- [x] 初始化仓库
- [ ] 建表
- [ ] C++ 连接 MySQL
- [ ] 素材 CRUD
- [ ] 按标签查询
