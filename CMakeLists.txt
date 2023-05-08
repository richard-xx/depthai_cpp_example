cmake_minimum_required(VERSION 3.10)

option(USE_NETWORK_SOURCE "Use hunters to download resource files, such as models" ON)
if (USE_NETWORK_SOURCE)
    include("cmake/HunterGate.cmake")
    HunterGate(
            URL "https://github.com/cpp-pm/hunter/archive/v0.24.16.tar.gz"
            SHA1 "09668c254f01afeca1b3d3d2e4692ed5e0e39dcc"
            # LOCAL
    )
endif ()


project("DepthaiExample")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
if (NOT WIN32)
    # 是否在 macOS 和 iOS 上使用 rpaths。
    set(CMAKE_MACOSX_RPATH ON)
    # 如果此变量设置为 true，则软件始终在没有 RPATH 的情况下构建。
    set(CMAKE_SKIP_BUILD_RPATH OFF)
    # 如果此变量设置为 true，则始终使用 RPATH 的安装路径构建软件，并且在安装时不需要重新链接。
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    # 将路径添加到链接器搜索和安装的 rpath。
    # 如果设置为 True，则将项目外部位于链接器搜索路径中或包含链接库文件的任何目录附加到已安装二进制文件的运行时搜索路径 (rpath) 中。
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif ()

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Installation Directory" FORCE)
endif ()

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif ()

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR} CACHE PATH "Installation directory for libraries")
set(INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR} CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR} CACHE PATH "Installation directory for header files")
if (WIN32 AND NOT CYGWIN)
    set(DEF_INSTALL_CMAKEDIR CMake)
else ()
    set(DEF_INSTALL_CMAKEDIR share/cmake/${PROJECT_NAME})
endif ()

set(INSTALL_CMAKEDIR ${DEF_INSTALL_CMAKEDIR} CACHE PATH "Installation directory for CMake files")

# Report to user
foreach (p LIB BIN INCLUDE CMAKE)
    file(TO_NATIVE_PATH ${CMAKE_INSTALL_PREFIX}/${INSTALL_${p}DIR} _path)
    message(STATUS "Installing ${p} components to ${_path}")
    unset(_path)
endforeach ()

# 用于添加新示例
function(dai_add_example example_name example_src)

    # parse the rest of the arguments
    set(arguments ${ARGV})
    list(REMOVE_AT arguments 0 1)

    # 添加示例
    add_executable(${example_name} ${example_src})
    target_link_libraries(${example_name} PRIVATE utility depthai::opencv usb-1.0 Threads::Threads ${arguments})
    if (WIN32)
        # Copy dlls to target directory - Windows only
        # TARGET_RUNTIME_DLLS generator expression available since CMake 3.21
        if (CMAKE_VERSION VERSION_LESS "3.21")
            file(GLOB depthai_dll_libraries "${depthai_DIR}/dependencies/bin/*.dll")
        else ()
            set(depthai_dll_libraries "$<TARGET_RUNTIME_DLLS:${example_name}>")
        endif ()

        add_custom_command(TARGET ${example_name}
                # 在目标中的所有其他规则都已执行后运行
                POST_BUILD
                # 指定要在构建时执行的命令行
                COMMAND ${CMAKE_COMMAND} -E copy_if_different ${depthai_dll_libraries} $<TARGET_FILE_DIR:${example_name}>
                # 参数中的列表 COMMAND 将被扩展, 包括那些用生成器表达式创建的列表
                COMMAND_EXPAND_LISTS
                )

        if (CMAKE_VERSION VERSION_LESS "3.21")
            install(TARGETS ${example_name})
            install(FILES ${depthai_dll_libraries} TYPE LIB )
        else ()
            install(TARGETS ${example_name} RUNTIME_DEPENDENCY_SET runtime_set)
        endif ()
    else ()
        install(TARGETS ${example_name})
    endif ()

    if (NOT MSVC)
        target_compile_options(${example_name} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-Werror=return-type>)
    endif ()


endfunction()


message(CHECK_START "Finding depthai")
find_package(depthai CONFIG QUIET)
if (NOT depthai_FOUND)
    set(depthai_DIR ${depthai_DIR_CACHE})
    find_package(depthai CONFIG REQUIRED)
endif ()
if (depthai_FOUND)
    message(CHECK_PASS "${depthai_DIR} (version: ${depthai_VERSION})")
    set(depthai_DIR_CACHE ${depthai_DIR} CACHE PATH "The directory containing a CMake configuration file for depthai.")
    set(_CMAKE_PREFIX_PATH_ORIGINAL ${CMAKE_PREFIX_PATH})
    set(CMAKE_PREFIX_PATH "${depthai_DIR}/dependencies;${CMAKE_PREFIX_PATH}")

    # BZip2 (for bspatch)
    message(CHECK_START "Finding BZip2")
    find_package(BZip2 CONFIG REQUIRED QUIET)
    message(CHECK_PASS "${BZip2_DIR} (version: ${BZip2_VERSION})")

    # FP16 for conversions
    message(CHECK_START "Finding FP16")
    find_package(FP16 CONFIG REQUIRED QUIET)
    message(CHECK_PASS "${FP16_DIR} (version: ${FP16_VERSION})")

    # libarchive for firmware packages
    message(CHECK_START "Finding archive_static")
    find_package(archive_static CONFIG REQUIRED QUIET)
    message(CHECK_PASS "${archive_static_DIR} (version: ${archive_static_VERSION})")

    message(CHECK_START "Finding lzma")
    find_package(lzma CONFIG REQUIRED QUIET)
    message(CHECK_PASS "${lzma_DIR} (version: ${lzma_VERSION})")
    # ZLIB for compressing Apps
    message(CHECK_START "Finding ZLIB")
    find_package(ZLIB CONFIG REQUIRED QUIET)
    message(CHECK_PASS "${ZLIB_DIR} (version: ${ZLIB_VERSION})")

    # spdlog for library and device logging
    message(CHECK_START "Finding spdlog")
    find_package(spdlog CONFIG REQUIRED QUIET)
    message(CHECK_PASS "${spdlog_DIR} (version: ${spdlog_VERSION})")

    # Backward
    if (DEPTHAI_ENABLE_BACKWARD)
        # Disable automatic check for additional stack unwinding libraries
        # Just use the default compiler one
        set(STACK_DETAILS_AUTO_DETECT FALSE)
        message(CHECK_START "Finding Backward")
        find_package(Backward CONFIG REQUIRED QUIET)
        message(CHECK_PASS "${Backward_DIR} (version: ${Backward_VERSION})")
        set(STACK_DETAILS_AUTO_DETECT)
    endif ()

    set(CMAKE_PREFIX_PATH ${_CMAKE_PREFIX_PATH_ORIGINAL})
endif ()

message(CHECK_START "Finding OpenCV")
if (NOT OpenCV_FOUND)
    set(OpenCV_DIR ${OpenCV_DIR_CACHE})
    find_package(OpenCV CONFIG QUIET)
endif ()
if (OpenCV_FOUND)
    message(CHECK_PASS "${OpenCV_DIR} (version: ${OpenCV_VERSION})")
    set(OpenCV_DIR_CACHE ${OpenCV_DIR} CACHE PATH "The directory containing a CMake configuration file for OpenCV.")
else ()
    message(CHECK_FAIL "not found")
endif ()

if (OpenCV_FOUND)
    add_subdirectory(utility)
    add_subdirectory(examples)
endif ()

add_subdirectory(get_network_info)
add_subdirectory(mine)

if (WIN32)
    if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.21")
        # https://cmake.org/cmake/help/latest/command/file.html#get-runtime-dependencies
        # https://cmake.org/cmake/help/latest/command/install.html#installing-runtime-dependencies
        # 安装运行时依赖项
        install(RUNTIME_DEPENDENCY_SET runtime_set
                # 预包含正则表达式列表，通过这些正则表达式过滤尚未解决的依赖项的名称。
                PRE_EXCLUDE_REGEXES "api-ms-" "ext-ms-"
                # 用于过滤已解析依赖项名称的排除后正则表达式列表。
                POST_EXCLUDE_REGEXES ".*system32/.*\\.dll"
                )
    endif ()
endif ()
