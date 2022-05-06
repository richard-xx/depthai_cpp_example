# 安装依赖
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

## Debian/Ubuntu 
```shell
sudo apt update
sudo apt install -y libusb-1.0-0-dev libopencv-dev 
# sudo apt install depthai_{version}_$(dpkg --print-architecture).deb
# 例如
sudo apt install depthai_2.15.3_amd64.deb
```
## Windows
前往 https://opencv.org/releases/ 下载 `OpenCV` 安装包 并安装

解压对应 `depthai-core` 压缩包即可

# 编译
## Linux
```shell
mkdir build 
cmake -S . -B build 
cmake --build build
```

## Windows
```shell
cmake -S . -B build -D"depthai_DIR=<path>/depthai-core-v{version}-win64/lib/cmake" -D"OpenCV_DIR=<path>/opencv/build"
cmake --build build
```

> Tips:
> + `-D"depthai_DIR=<path>"`: 手动指定 `depthai` 路径
> + `-D"OpenCV_DIR=<path>"`: 手动指定 `OpenCV` 路径
> + `-DCMAKE_BUILD_TYPE=Release/Debug/...`: 指定 CMAKE 构建类型

`OpenCV_DIR=<path>/opencv/build` 目录结构： 
``` 
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