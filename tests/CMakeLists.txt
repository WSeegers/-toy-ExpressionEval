
add_executable(basicTest basic_test.cpp)
target_include_directories(basicTest PRIVATE "$(PROJECT_SOURCE_DIR)/include")
add_test("Basic Test" basicTest)