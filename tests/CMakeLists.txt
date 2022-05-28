set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Now simply link against gtest or gtest_main as needed. Eg
add_executable(testmodel test_model.cpp ../model.hpp ../model.cpp ../dateManager.hpp ../dateManager.cpp)
add_executable(testview test_view.cpp ../model.hpp ../model.cpp ../dateManager.hpp ../dateManager.cpp ../view.hpp ../view.cpp)
add_executable(testcontroller test_controller.cpp ../model.hpp ../model.cpp ../dateManager.hpp ../dateManager.cpp ../view.hpp ../view.cpp ../controller.hpp ../controller.cpp)

include_directories(..)

target_link_libraries(testmodel gtest_main)
target_link_libraries(testview gtest_main)
target_link_libraries(testcontroller gtest_main gmock_main)