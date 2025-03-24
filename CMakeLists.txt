cmake_minimum_required(VERSION 3.10)
project(BlinkDB)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include header files
include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/include/stx)


# Add source files explicitly
set(SOURCES
    src/main.cpp   # ✅ Add this to fix "undefined reference to main"
    src/Server.cpp
    src/KeyValueStore.cpp
    src/PersistentKeyValueStore.cpp  # ✅ Ensure it's included
    src/REPL.cpp      
    src/BloomFilter.cpp  # ✅ Add this to fix "undefined reference to BloomFilter"
)

# Create executable
add_executable(BlinkDB ${SOURCES})

# Link necessary libraries
target_link_libraries(BlinkDB pthread)
