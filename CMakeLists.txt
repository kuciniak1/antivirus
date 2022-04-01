cmake_minimum_required(VERSION 3.16)
project(antywirus C)

set(CMAKE_C_STANDARD 99)

add_executable(antywirus
        file_handler.c
        file_handler.h
        hashDB_handler.c
        hashDB_handler.h
        hashing.c
        hashing.h
        encrypt.c
        encrypt.h
        main.c
        quarantine.c
        quarantine.h
        queue.c
        queue.h
        tree.c
        tree.h)

find_package(OpenSSL REQUIRED)
target_link_libraries(antywirus OpenSSL::SSL)
target_link_libraries(antywirus OpenSSL::Crypto)
