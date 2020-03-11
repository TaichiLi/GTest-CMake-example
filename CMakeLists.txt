cmake_minimum_required(VERSION 3.5) # 指定能够支持本文件的 CMake 最低版本

# 添加自定义 CMake 命令行宏，运行 CMake 时以 "-DGTEST_VERSION=1.7.0" 的形式调用
add_compile_definitions(COMPILER=${COMPILER})
add_compile_definitions(GTEST_VERSION=${GTEST_VERSION})
add_compile_definitions(GTEST_BITS=${GTEST_BITS})

# 对之后的 target 设置编译器，因此必须在添加 target 之前设置，最好用命令行指定（这里嫌命令行麻烦）
if (${COMPILER} STREQUAL "clang") # CMake 字符串比较不区分大小写
    SET (CMAKE_C_COMPILER   "clang")
    SET (CMAKE_CXX_COMPILER "clang++")
elseif (${COMPILER} STREQUAL "gcc")
    SET (CMAKE_C_COMPILER   "gcc")
    SET (CMAKE_CXX_COMPILER "g++")
endif()

# 指定项目名
project(gtest_test)

# set (CMAKE_GENERATOR "MinGW Makefiles")

# 添加可执行文件
add_executable(gtest_test 
               src/main.cpp # 添加源文件，建议在此逐个列出而不是使用变量
)

# 添加静态库
add_library(fac_library STATIC
            src/fac.cpp
)

# 添加动态库
add_library(fib_library SHARED
            src/fib.cpp
)

# 设置 "make VERBOSE=1"，获取 make 过程的详细输出
set (CMAKE_VERBOSE_MAKEFILE ON)

# 为 target 添加编译特性
# target_compile_features(gtest_test PUBLIC cxx_std_17 cxx_long_long_type)

# 打印所有已知的编译特性
# message("List of compile features: ${CMAKE_CXX_COMPILE_FEATURES}")

if (${GTEST_BITS} STREQUAL "x86") # CMake字符串操作符必须大写
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        message(FATAL_ERROR "FATAL: When use Clang, the option \"GTEST_BITS\" can only be \"x64\"!")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set (GTEST_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/${GTEST_VERSION})
        set (GTEST_LIBRARY ${PROJECT_SOURCE_DIR}/lib/${GTEST_VERSION}/${GTEST_BITS}/libgtest.a)
        set (GTEST_MAIN_LIBRARY ${PROJECT_SOURCE_DIR}/lib/${GTEST_VERSION}/${GTEST_BITS}/libgtest_main.a)
        message(STATUS "STATUS: Using GCC!")
    else ()
        message(FATAL_ERROR "FATAL: Only support Clang and GCC!")
    endif()
    # add_compile_options(-m32)
    # target_compile_options 为特定 target 添加编译参数，该函数必须出现在 add_executable 或 add_library 后
    target_compile_options(gtest_test PRIVATE ${CMAKE_CXX_FLAGS} -m32)
    target_link_options(gtest_test PRIVATE ${CMAKE_EXE_LINKER_FLAGS} -m32)
    target_compile_options(fac_library PRIVATE ${CMAKE_CXX_FLAGS} -m32)
    target_link_options(fac_library PRIVATE ${CMAKE_EXE_LINKER_FLAGS} -m32)
    target_compile_options(fib_library PRIVATE ${CMAKE_CXX_FLAGS} -m32)
    target_link_options(fib_library PRIVATE ${CMAKE_EXE_LINKER_FLAGS} -m32)    
    # set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
    # set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
    message(STATUS "OPTIONAL: -m32")
elseif (${GTEST_BITS} STREQUAL "x64")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set (GTEST_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/${GTEST_VERSION})
        set (GTEST_LIBRARY ${PROJECT_SOURCE_DIR}/lib/${GTEST_VERSION}/clang/libgtest.a)
        set (GTEST_MAIN_LIBRARY ${PROJECT_SOURCE_DIR}/lib/${GTEST_VERSION}/clang/libgtest_main.a)
        target_compile_options(gtest_test PRIVATE ${CMAKE_CXX_FLAGS} -fsjlj-exceptions)
        target_link_options(gtest_test PRIVATE ${CMAKE_EXE_LINKER_FLAGS} -pthread)    
        target_compile_options(fac_library PRIVATE ${CMAKE_CXX_FLAGS} -fsjlj-exceptions)
        target_link_options(fac_library PRIVATE ${CMAKE_EXE_LINKER_FLAGS} -pthread)
        target_compile_options(fib_library PRIVATE ${CMAKE_CXX_FLAGS} -fsjlj-exceptions)
        target_link_options(fib_library PRIVATE ${CMAKE_EXE_LINKER_FLAGS} -pthread)
        message(STATUS "STATUS: Using Clang!")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set (GTEST_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/${GTEST_VERSION})
        set (GTEST_LIBRARY ${PROJECT_SOURCE_DIR}/lib/${GTEST_VERSION}/${GTEST_BITS}/libgtest.a)
        set (GTEST_MAIN_LIBRARY ${PROJECT_SOURCE_DIR}/lib/${GTEST_VERSION}/${GTEST_BITS}/libgtest_main.a)
        message(STATUS "STATUS: Using GCC!")
    else ()
        message(FATAL_ERROR "FATAL: Only support Clang and GCC!")
    endif()
    # add_compile_options(-m64)
    target_compile_options(gtest_test PRIVATE ${CMAKE_CXX_FLAGS} -m64)
    target_link_options(gtest_test PRIVATE ${CMAKE_EXE_LINKER_FLAGS} -m64)    
    target_compile_options(fac_library PRIVATE ${CMAKE_CXX_FLAGS} -m64)
    target_link_options(fac_library PRIVATE ${CMAKE_EXE_LINKER_FLAGS} -m64)
    target_compile_options(fib_library PRIVATE ${CMAKE_CXX_FLAGS} -m64)
    target_link_options(fib_library PRIVATE ${CMAKE_EXE_LINKER_FLAGS} -m64)
    # set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64")
    # set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
    message(STATUS "OPTIONAL: -m64")
else ()
    message(FATAL_ERROR "FATAL: The option \"GTEST_BITS\" can only be \"x86\" or \"x64\"!")
endif ()

# 搜索第三方包
enable_testing()
find_package(GTest REQUIRED)

# 为 target 添加包含文件目录
target_include_directories(gtest_test
                           PUBLIC
                           ${GTEST_INCLUDE_DIR}
)

target_include_directories(fac_library
                           PUBLIC 
                           ${PROJECT_SOURCE_DIR}/include
)

# 设置别名
add_library(fib::library ALIAS fib_library)

target_include_directories(fib_library
                           PUBLIC 
                           ${PROJECT_SOURCE_DIR}/include
)

# 为 target 指定链接文件
target_link_libraries(gtest_test
                      PRIVATE
                      ${GTEST_LIBRARIES}
                      ${GTEST_MAIN_LIBRARIES}
                      fac_library
                      fib::library
)
# 要将 add_executable 的声明放到设置库文件的 target_link_libraries 之前

# 指定安装地址
install (TARGETS gtest_test
         DESTINATION bin)
         
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include 
        DESTINATION include)

install (TARGETS gtest_test
         LIBRARY DESTINATION lib
         RUNTIME DESTINATION bin)