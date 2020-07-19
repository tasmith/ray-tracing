add_executable(ray main.cpp)
target_link_libraries(ray docopt.cpp::docopt.cpp fmt::fmt spdlog::spdlog)
