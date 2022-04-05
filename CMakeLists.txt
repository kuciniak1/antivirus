cmake_minimum_required(VERSION 3.16)
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
<<<<<<< HEAD
        cipher.c
        cipher.h
=======
        encrypt.c
        encrypt.h
>>>>>>> 3d6e4558b47ca3cb67ed5c1bf7e034ac18ec4eed
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
