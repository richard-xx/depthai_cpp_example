- [安装依赖](#%E5%AE%89%E8%A3%85%E4%BE%9D%E8%B5%96)
    - [使用预编译包](#%E4%BD%BF%E7%94%A8%E9%A2%84%E7%BC%96%E8%AF%91%E5%8C%85)
        - [Ubuntu 16+](#ubuntu-16--debian-9)
            - [PPA](#ppa)
        - [Windows](#windows)
    - [从源码编译](#%E4%BB%8E%E6%BA%90%E7%A0%81%E7%BC%96%E8%AF%91)
        - [依赖项](#%E4%BE%9D%E8%B5%96%E9%A1%B9)
- [编译](#%E7%BC%96%E8%AF%91)
    - [Linux](#linux)
    - [Windows](#windows-1)

> 推荐使用 cmake 3.21 以上版本

# 安装依赖

## 使用预编译包

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
# sudo apt install depthai_{version}_$(dpkg --print-architecture).deb
# 例如
sudo apt install depthai_2.15.3_amd64.deb
```

#### PPA

> 支持架构 ： amd64(x86_64) arm64(aarch64) armhf(arm32)

```shell
sudo wget -O - https://richard-xx.github.io/ppa/depthai/richard_depthai.gpg | sudo tee /etc/apt/trusted.gpg.d/richard_depthai.gpg
sudo wget -O /etc/apt/sources.list.d/depthai-ppa.list https://richard-xx.github.io/ppa/depthai/depthai-ppa.list
sudo apt update
sudo apt install depthai
```

### Windows

前往 https://opencv.org/releases/ 下载 `OpenCV` 安装包 并安装

解压对应 `depthai-core` 压缩包即可

## 从源码编译

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

# 编译

## Linux

```shell
mkdir build 
cmake -S . -B build 
cmake --build build 
# cmake --build build --target ...
```

## Windows

```shell
cmake -S . -B build -D"depthai_DIR=<path>/depthai-core-v{version}-win64/lib/cmake/depthai" -D"OpenCV_DIR=<path>/opencv/build"
cmake --build build
# cmake --build build --target ...
```

> Tips:
>
> + `-D"depthai_DIR=<path>"`: 手动指定 `depthai` 路径
> + `-D"OpenCV_DIR=<path>"`: 手动指定 `OpenCV` 路径
> + `-DCMAKE_BUILD_TYPE=Release/Debug/...`: 指定 CMAKE 构建类型
> + `-DUSE_NETWORK_SOURCE=ON/OFF`: 是否 不使用 release 中文件

`OpenCV_DIR=<path>/opencv/build` 目录结构：

```shell
├───bin
├───etc
├───include
├───java
├───python
├───x64
├───LICENSE
├───OpenCVConfig.cmake
├───OpenCVConfig-version.cmake
└───setup_vars_opencv4.cmd
```

`depthai_DIR=<path>/depthai-core-v{version}-win64/lib/cmake/depthai` 目录结构：

```shell
├── dependencies
├── depthaiConfig.cmake
├── depthaiConfigVersion.cmake
├── depthaiDependencies.cmake
├── depthaiTargets.cmake
└── depthaiTargets-release.cmake
```