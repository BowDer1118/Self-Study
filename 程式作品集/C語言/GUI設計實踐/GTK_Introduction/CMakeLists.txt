cmake_minimum_required(VERSION 3.24)
project(GTK_Introduction C)

set(CMAKE_C_STANDARD 11)

#尋找PkgConfig
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

#設定函數庫與動態連結庫位置
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})


ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

#產生執行檔案
add_executable(GTK_Introduction hello_world.c)
add_executable(Xml_Layout xml_layout.c)
add_executable(Load_CSS load_css.c)

#鏈結庫到工程中
target_link_libraries(GTK_Introduction ${GTK3_LIBRARIES})
target_link_libraries(Xml_Layout ${GTK3_LIBRARIES})
target_link_libraries(Load_CSS ${GTK3_LIBRARIES})
