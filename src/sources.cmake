include(${CMAKE_CURRENT_LIST_DIR}/display/sources.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/logic/sources.cmake)

list(APPEND rentGame_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/game.cpp
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)
