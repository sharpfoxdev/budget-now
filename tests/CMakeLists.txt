set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

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