cmake_minimum_required(VERSION 2.8)
project(controller)

find_package(qibuild)

# Create a executable named controller
# with the source file: main.cpp
qi_create_bin(controller "main.cpp")

# Add a simple test:
qi_create_test(test_controller "test.cpp")
