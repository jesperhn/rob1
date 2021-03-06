#
# Test CMake version
#
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

# The name of the project.
PROJECT(RobVis1Plugin2013NoCV)
MESSAGE(${PROJECT_NAME})

# Used to resolve absolute path names
SET(ROOT ${CMAKE_CURRENT_SOURCE_DIR})

# Set the RobWork root (edit this if necessary)
SET(RW_ROOT "/home/jesperhn/RWPROJECTROOT/RobWork")

# Set the RobWorkStudio root (edit this if necessary)
SET(RWSTUDIO_ROOT "/home/jesperhn/RWPROJECTROOT/RobWorkStudio")

# Set the level of verbosity when running make.
set(CMAKE_VERBOSE_MAKEFILE False)

# If not the -DCMAKE_BUILD_TYPE option is given when running CMake, use Release as default.
IF( NOT DEFINED CMAKE_BUILD_TYPE )
    SET(CMAKE_BUILD_TYPE Release)
ENDIF()
MESSAGE("-- Build type: " ${CMAKE_BUILD_TYPE})

# Use RobWork
SET(RobWork_DIR "~/RWPROJECTROOT/RobWork/cmake") 
FIND_PACKAGE(RobWork REQUIRED)
INCLUDE_DIRECTORIES( ${ROBWORK_INCLUDE_DIRS} )
LINK_DIRECTORIES( ${ROBWORK_LIBRARY_DIRS} )
MESSAGE("-- RobWork found: " ${RW_ROOT})

# Use RobWorkStudio
SET(RobWorkStudio_DIR "~/RWPROJECTROOT/RobWorkStudio/cmake")
FIND_PACKAGE(RobWorkStudio REQUIRED)
INCLUDE_DIRECTORIES( ${ROBWORKSTUDIO_INCLUDE_DIRS} )
LINK_DIRECTORIES( ${ROBWORKSTUDIO_LIBRARY_DIRS} )
MESSAGE("-- RobWorkStudio found: " ${RWSTUDIO_ROOT})

# Set the output dir for generated libraries and binaries
IF(MSVC)
	SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${ROOT}/bin" CACHE PATH "Runtime directory" FORCE)
	SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${ROOT}/libs" CACHE PATH "Library directory" FORCE)
	SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${ROOT}/libs" CACHE PATH "Archive directory" FORCE)
ELSE()
	SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${ROOT}/bin/${CMAKE_BUILD_TYPE}" CACHE PATH "Runtime directory" FORCE)
	SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${ROOT}/libs/${CMAKE_BUILD_TYPE}" CACHE PATH "Library directory" FORCE)
	SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${ROOT}/libs/${CMAKE_BUILD_TYPE}" CACHE PATH "Archive directory" FORCE)
ENDIF()

# If we want to use ui files add them here
RWS_QT4_WRAP_UI(UIS_OUT_H SamplePlugin.ui)

# Moc
QT4_WRAP_CPP(MocSrcFiles SamplePlugin.hpp)

# Rcc the files:
QT4_ADD_RESOURCES(RccSrcFiles resources.qrc)

# Add the source files to build (besides the Qt generated source files)
SET(SrcFiles SamplePlugin.cpp)

# The shared library to build:
ADD_LIBRARY(SamplePlugin MODULE ${SrcFiles} ${UIS_OUT_H} ${MocSrcFiles} ${RccSrcFiles})
TARGET_LINK_LIBRARIES(SamplePlugin ${ROBWORK_LIBRARIES} ${ROBWORKSTUDIO_LIBRARIES})

MESSAGE("-- " ${PROJECT_NAME} " done!")
