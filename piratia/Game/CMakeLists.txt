
set(GAME_SOURCE)
list(APPEND GAME_SOURCE
     ArmorBody.cpp
     CraftAbility.cpp
     FindPairGame.cpp
     Inventory.cpp
     Item.cpp
     Player.cpp
     Reciepe.cpp
     Resource.cpp
     Weapon.cpp
     )

set(GAME_HEADER)
list(APPEND GAME_HEADER
     ArmorBody.h
     CraftAbility.h
     FindPairGame.h
     Inventory.h
     Item.h
     Player.h
     Reciepe.cpp
     Resource.h
     structures.h
     Weapon.h
     )

add_library(game_core
  ${GAME_SOURCE}
  ${GAME_HEADER})

include(GenerateExportHeader)
generate_export_header(game_core)
target_include_directories(game_core PUBLIC ${CMAKE_BINARY_DIR}/Game)

add_subdirectory(tests)
