# 设置项目名
project (factorial)

# 添加静态库
add_library(${PROJECT_NAME} STATIC src/fac.cpp)
add_library(lib::fac ALIAS ${PROJECT_NAME})

# 添加头文件目录
target_include_directories (
    ${PROJECT_NAME}
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
)

# 指定安装地址
install (TARGETS ${PROJECT_NAME}
         DESTINATION bin)
         
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include 
        DESTINATION include)

install (TARGETS ${PROJECT_NAME}
         LIBRARY DESTINATION lib
         RUNTIME DESTINATION bin)