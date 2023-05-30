include(${CMAKE_CURRENT_LIST_DIR}/screens/sources.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/buttons/sources.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/widgets/sources.cmake)

list(APPEND rentGame_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/ui.cpp
)
