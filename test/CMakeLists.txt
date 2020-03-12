# 指定项目名
project(test)

# 添加可执行文件
add_executable(${PROJECT_NAME} 
               src/main.cpp # 添加源文件，建议在此逐个列出而不是使用变量
)

# 搜索第三方包
enable_testing()
find_package(GTest REQUIRED)

# 添加头文件目录
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${GTEST_INCLUDE_DIR}
)


# 添加链接文件
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    ${GTEST_LIBRARIES}
    ${GTEST_MAIN_LIBRARIES}
    lib::fac
    dll::fib
)
# 要将 add_executable 的声明放到设置库文件的 target_link_libraries 之前

# 指定安装地址
install (TARGETS ${PROJECT_NAME}
         DESTINATION bin)
         
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include 
        DESTINATION include)

install (TARGETS ${PROJECT_NAME}
         LIBRARY DESTINATION lib
         RUNTIME DESTINATION bin)