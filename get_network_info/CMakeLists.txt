get_directory_property(has_parent PARENT_DIRECTORY)
if (NOT has_parent)
    project("GetNetworkInfo")
    find_package(depthai CONFIG REQUIRED)
endif ()

add_executable(GetNetworkInfo get_network_info.cpp)
target_link_libraries(GetNetworkInfo PRIVATE depthai::core)

if (WIN32)
    add_custom_command(TARGET GetNetworkInfo
            # 在目标中的所有其他规则都已执行后运行
            POST_BUILD
            # 指定要在构建时执行的命令行
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:GetNetworkInfo> $<TARGET_FILE_DIR:GetNetworkInfo>
            # 参数中的列表COMMAND将被扩展, 包括那些用生成器表达式创建的列表
            COMMAND_EXPAND_LISTS
            )
endif ()

if(NOT MSVC)
    target_compile_options(${example_name} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-Werror=return-type>)
endif()

install(TARGETS GetNetworkInfo RUNTIME_DEPENDENCY_SET runtime_set)
