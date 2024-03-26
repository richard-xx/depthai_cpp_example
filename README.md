
> 推荐使用 cmake 3.21 以上版本

# 1.安装依赖


## 1.2 使用预编译包

前往 [depthai-core](https://gitee.com/oakchina/depthai-core/releases) 下载 `depthai-core` 预编译文件

+ depthai_{version}_amd64.deb
+ depthai_{version}_armhf.deb
+ depthai_{version}_arm64.deb
+ depthai-{version}-Linux-amd64.tar.xz
+ depthai-{version}-Linux-armhf.tar.xz
+ depthai-{version}-Linux-arm64.tar.xz
+ depthai-core-v{version}-win64.zip
+ depthai-core-v{version}-win32-no-opencv.zip
+ depthai-core-v{version}.tar.gz

### Ubuntu 16+ / Debian 9+

```shell
sudo apt update
sudo apt install -y libusb-1.0-0-dev libopencv-dev 
# sudo apt install <path>/depthai_{version}_$(dpkg --print-architecture).deb
# 例如
sudo apt install ~/Downloads/depthai_2.15.3_amd64.deb
```

#### PPA

> 支持架构：amd64(x86_64) arm64(aarch64) armhf(arm32)

```shell
sudo wget -O - https://richard-xx.github.io/ppa/depthai/richard_depthai.gpg | sudo tee /etc/apt/trusted.gpg.d/richard_depthai.gpg
sudo wget -O /etc/apt/sources.list.d/depthai-ppa.list https://richard-xx.github.io/ppa/depthai/depthai-ppa.list
sudo apt update
sudo apt install depthai
```

### Windows

前往 https://opencv.org/releases/ 下载 `OpenCV` 安装包 并安装

解压对应 `depthai-core` 压缩包即可

----

## 1.2 从源码编译

根据 [depthai-core](https://github.com/luxonis/depthai-core) 仓库，编译 deptahi

### 依赖项

+ CMake >= 3.10
+ C/C++14 compiler _GCC 5+ / Clang 3.4_
+ OpenCV 4
  > Ubuntu 可通过 _[Kitware APT Repository](https://apt.kitware.com/)_ 安装最新 CMake
  或者通过 [pip](https://pypi.org/project/cmake/) 安装
  >
  >_[GCC 5](https://gcc.gnu.org/projects/cxx-status.html#cxx14)
  或 [Clang 3.4](https://clang.llvm.org/cxx_status.html#cxx14)_ 以上版本 支持 C/C++14
  >
  > 推荐使用 gcc 7 以上

>

```shell
git clone --recursive https://github.com/luxonis/depthai-core.git --branch main --depth 1
cmake -Hdepthai-core -Bdepthai-core/build -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=/usr/local
cmake --build depthai-core/build --target install
```

# 2. 编译
## 2.1 下载
可使用 git clone
```shell
git clone https://github.com/richard-xx/depthai_cpp_example.git 
```

或直接下载 zip

## 2.2 目录结构
`depthai_cpp_example`
```shell

.
├── cmake
├── CMakeLists.txt
├── examples
├── get_network_info
├── README.md
└── utility
```

## 2.3 编译

### Linux

```shell
cd <path>/depthai_cpp_example
mkdir build 
cmake -S. -Bbuild 
cmake --build build 
# cmake --build build --target ...
```

### Windows

```shell
cd <path>/depthai_cpp_example
cmake -S. -Bbuild -D"depthai_DIR=<path>/depthai-core-v{version}-win64/lib/cmake/depthai" -D"OpenCV_DIR=<path>/opencv/build"
cmake --build build
# cmake --build build --target ...
```

> Tips:
>
> + `-D"depthai_DIR=<path>"`: 手动指定 `depthai` 路径，目录结构参考下方 `注` 内容
> + `-D"OpenCV_DIR=<path>"`: 手动指定 `OpenCV` 路径，目录结构参考下方 `注` 内容
> + `-DCMAKE_BUILD_TYPE=Release/Debug/...`: 指定 CMAKE 构建类型
> + `-DUSE_NETWORK_SOURCE=ON` 使用 hunter 下载资源文件
> + `-DUSE_NETWORK_SOURCE=OFF` 手动将 [models.zip](https://github.com/richard-xx/depthai_cpp_example/releases/) 文件下载解压后放到 examples/models 文件夹下

## 2.4 编译完成后

可在 `build/bin` 目录下看到编译的结果，可双击执行或在命令行中执行。

例如：

```shell
cd build/bin
./rgb_preview
```
> 注： 
> 
> `OpenCV_DIR=<path>/opencv/build` 目录结构：
>
>     ```shell
>     ├───bin
>     ├───etc
>     ├───include
>     ├───java
>     ├───python
>     ├───x64
>     ├───LICENSE
>     ├───OpenCVConfig.cmake
>     ├───OpenCVConfig-version.cmake
>     └───setup_vars_opencv4.cmd
>     ```
>
> `depthai_DIR=<path>/depthai-core-v{version}-win64/lib/cmake/depthai` 目录结构：
>
>     ```shell
>     ├── dependencies
>     ├── depthaiConfig.cmake
>     ├── depthaiConfigVersion.cmake
>     ├── depthaiDependencies.cmake
>     ├── depthaiTargets.cmake
>     └── depthaiTargets-release.cmake
>     ```