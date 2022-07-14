# 创建 utility 库
add_library(utility STATIC utility.cpp)
target_include_directories(utility PUBLIC ".")
target_link_libraries(utility FP16::fp16 ${OpenCV_LIBS})
