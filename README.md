# ktm-lua

### 安装依赖

#### ktm库

```shell
git clone https://github.com/YGXXD/ktm.git
cd ktm
cmake -S . -B ./build
cmake --install build --config Release
```

#### ntr库

```shell
git clone https://github.com/YGXXD/ntr.git
cd ntr
cmake -S . -B ./build
cmake --build build --config Release
cmake --install build --config Release
```

#### lua解释器
```shell
# macos
brew install lua

# linux
apt-get install lua5.4 liblua5.4-dev

# windows
scoop install lua
```

### 编译运行

#### 构建ktm-lua库
```shell
cmake -S . -B ./build
cmake --build build --config Release
```

#### 测试ktm-lua库
```lua
-- test.lua
package.cpath = './build/?.so;./build/?.dylib;./build/?.dll;'..package.cpath
local ktm = require("ktm")
local vec0 = ktm.fvec3.create(1, 2, 3)
local vec1 = ktm.fvec3.create(4, 5, 6)
print(vec0 + vec1)
```

### 许可证

ktm-lua使用MIT许可证，详细信息请参见[LICENSE](LICENSE)文件。
