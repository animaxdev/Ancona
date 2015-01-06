# Script used to find all libraries needed by the build process

#Include the external project module to build dependencies
#include(ExternalProject)

set(Download_Dir ${CMAKE_SOURCE_DIR}/lib/SFML)
# TODO: pull required libraries off of git

# TODO: build required libraries

#Download and build SFML
#set(Ancona_SFML_Dir ${Download_Dir}/SFML)
#set(Ancona_SFML_Bin ${Ancona_SFML_Dir}/build/${Ancona_Platform})
#execute_process(COMMAND ./BuildTools/Scripts/get_depend.py ${CMAKE_SOURCE_DIR} Debian)

#ExternalProject_Add(SFML_Project
#    DOWNLOAD_DIR ${Ancona_SFML_Dir} 
#    GIT_REPOSITORY http://github.com/LaurentGomila/SFML
#    GIT_TAG 2.2
#    SOURCE_DIR ${Ancona_SFML_Dir}
#    BINARY_DIR ${Ancona_SFML_Dir}/build/${Ancona_Platform}
#    )
include_directories(${CMAKE_SOURCE_DIR}/lib/SFML/include)
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${CMAKE_SOURCE_DIR}/lib/SFML/build/${Ancona_Platform})

#Add SFML to the project
#include(CMake/Modules/FindSFML.cmake)
#set(SFML_ROOT ${Ancona_SFML_Dir}/build)
#find_package(SFML COMPONENTS system window graphics network audio main)


# Add all projects to the include

# Set up Library variables
