cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra -Wall" CACHE STRING "Default C options" FORCE)
project(antivirus C)
project(quarantine_handler C)

set(CMAKE_C_STANDARD 99)

add_executable(antivirus
        file_handler.c
        file_handler.h
        hashDB_handler.c
        hashDB_handler.h
        hashing.c
        hashing.h
        cipher.c
        cipher.h
        main.c
        quarantine.c
        quarantine.h
        queue.c
        queue.h
        tree.c
        tree.h)


add_executable(quarantine_handler
	quarantine_handler.c
	cipher.c
	cipher.h)
	
find_package(OpenSSL REQUIRED)
target_link_libraries(antivirus OpenSSL::SSL)
target_link_libraries(antivirus OpenSSL::Crypto)

target_link_libraries(quarantine_handler OpenSSL::SSL)
target_link_libraries(quarantine_handler OpenSSL::Crypto)
target_link_libraries(quarantine_handler m)

