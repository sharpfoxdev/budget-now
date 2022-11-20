cmake_minimum_required(VERSION 3.16.3)
project(BudgetNow)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")
add_executable(budgetApp src/main.cpp src/controller.cpp src/model.cpp src/view.cpp src/controller.hpp src/model.hpp src/view.hpp src/dataClasses.hpp src/json.hpp src/date.h src/dateManager.hpp src/dateManager.cpp)

include_directories(src)

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
add_subdirectory(tests)
