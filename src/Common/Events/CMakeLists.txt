message("%% Entering EventPublisher")

####################################################################################################
# Set source files
set(EVENT_PUBLISHER_SOURCE_FILES

    CACHE INTERNAL "EVENT_PUBLISHER_SOURCE_FILES")

####################################################################################################
# Set header files
set(EVENT_PUBLISHER_HEADER_FILES

    ${CMAKE_CURRENT_LIST_DIR}/EventPublisher.hpp

    CACHE INTERNAL "EVENT_PUBLISHER_HEADER_FILES")

####################################################################################################
# Set include dirs
set(EVENT_PUBLISHER_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}

    CACHE INTERNAL "EVENT_PUBLISHER_INCLUDE_DIRS")