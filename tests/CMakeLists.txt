set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Now simply link against gtest or gtest_main as needed. Eg
add_executable(testmodel model_test.cpp ../model.hpp ../model.cpp ../dateManager.hpp ../dateManager.cpp)
add_executable(testview view_test.cpp ../model.hpp ../model.cpp ../dateManager.hpp ../dateManager.cpp ../view.hpp ../view.cpp)

include_directories(..)

target_link_libraries(testmodel gtest_main)
target_link_libraries(testview gtest_main)
