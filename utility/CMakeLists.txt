# 创建 utility 库
add_library(utility STATIC utility.cpp)
target_include_directories(utility PUBLIC ".")
target_link_libraries(utility FP16::fp16 opencv_highgui)
if (WIN32)
    install(TARGETS utility RUNTIME_DEPENDENCY_SET runtime_set)
else ()
    install(TARGETS utility)
endif ()