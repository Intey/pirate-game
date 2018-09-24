set(TEST_CORE_SRC
    test_core.h
    test_core.cpp
    )

add_library(test_core
    ${TEST_CORE_SRC}
    )
target_include_directories(test_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(craft_test
    craft_test.cpp
    )
target_link_libraries(craft_test game_core test_core)

add_executable(reward_test
    reward_test.cpp
    )
target_link_libraries(reward_test game_core test_core)
