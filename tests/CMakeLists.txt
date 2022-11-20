set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(testmodel test_model.cpp ../src/model.hpp ../src/model.cpp ../src/dateManager.hpp ../src/dateManager.cpp)
add_executable(testview test_view.cpp ../src/model.hpp ../src/model.cpp ../src/dateManager.hpp ../src/dateManager.cpp ../src/view.hpp ../src/view.cpp)
add_executable(testcontroller test_controller.cpp ../src/model.hpp ../src/model.cpp ../src/dateManager.hpp ../src/dateManager.cpp ../src/view.hpp ../src/view.cpp ../src/controller.hpp ../src/controller.cpp)

include_directories(../src)

target_link_libraries(testmodel gtest_main)
target_link_libraries(testview gtest_main)
target_link_libraries(testcontroller gtest_main gmock_main)

# Used for running ctest
include(GoogleTest)
gtest_discover_tests(testmodel ./test)
gtest_discover_tests(testview ./test)
gtest_discover_tests(testcontroller ./test)