message("%% Entering Events")

####################################################################################################
# Set source files
set(EVENTS_SOURCE_FILES

    CACHE INTERNAL "EVENTS_SOURCE_FILES")

####################################################################################################
# Set header files
set(EVENTS_HEADER_FILES

    ${CMAKE_CURRENT_LIST_DIR}/EventPublisher.hpp
    ${CMAKE_CURRENT_LIST_DIR}/EventTypes.hpp

    CACHE INTERNAL "EVENTS_HEADER_FILES")

####################################################################################################
# Set include dirs
set(EVENTS_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}

    CACHE INTERNAL "EVENTS_INCLUDE_DIRS")