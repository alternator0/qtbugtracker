project(bugtracker VERSION 0.1 LANGUAGES CXX)

set(PostgreSQL_ROOT "C:/Program Files/PostgreSQL/16")
set(BUILD_SHARED_LIBS OFF)

add_subdirectory(${CMAKE_SOURCE_DIR}/deps/libpqxx/ build-pqxx)
