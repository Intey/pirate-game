
set(GAME_SOURCE)
list(APPEND GAME_SOURCE
     ArmorBody.cpp
     CraftAbility.cpp
     FindPairGame.cpp
     Inventory.cpp
     Item.cpp
     Ore.cpp
     Player.cpp
     Recipe.cpp
     Resource.cpp
     Reward.cpp
     Weapon.cpp
     )

set(GAME_HEADER)
list(APPEND GAME_HEADER
     ArmorBody.h
     CraftAbility.h
     FindPairGame.h
     Inventory.h
     Item.h
     Ore.h
     Player.h
     Recipe.h
     Resource.h
     Reward.h
     structures.h
     Weapon.h
     )

add_library(game_core
  ${GAME_SOURCE}
  ${GAME_HEADER})

include(GenerateExportHeader)
generate_export_header(game_core)
target_include_directories(game_core PUBLIC ${CMAKE_BINARY_DIR}/Game ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(tests)
