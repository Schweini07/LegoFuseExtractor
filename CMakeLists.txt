cmake_minimum_required(VERSION 3.10)
project (FUSEExtractor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

add_executable(FUSEExtractor src/main.cpp
src/fuse.cpp
src/util/FileSystemDirectoryHandler.cpp
)