cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

################### Variables. ####################
# Change if you want modify path or other values. #
###################################################

set(PROJECT_NAME insertion_map)
# Output Variables
set(OUTPUT_UNIX_DEBUG debug_bin_unix)
set(OUTPUT_UNIX_RELEASE bin_unix)
set(OUTPUT_WIN32 bin_win32)
# Folders files
set(SOURCE_DIR ./src)
set(HEADER_DIR ./include)


############## CMake Project ################
#        The main options of project        #
#############################################

project(${PROJECT_NAME} C CXX)

# Define Release by default.
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
	message(STATUS "Build type not specified: Use Release by default.")
endif(NOT CMAKE_BUILD_TYPE)

# Definition of Macros
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions(		
	   -D_CONSOLE 
	   -DUNICODE
	   -D_UNICODE
	)
else()
	add_definitions(
		-DNDEBUG
		-D_CONSOLE 
		-DUNICODE
		-D_UNICODE
	)
endif()

############## Artefacts Output #################
# Defines outputs , depending Debug or Release. #
#################################################

# on UNIX there is no Debug nor Release subfolder so I specify a different for each configuration
if (UNIX)
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${OUTPUT_UNIX_DEBUG})
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${OUTPUT_UNIX_DEBUG})
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${OUTPUT_UNIX_DEBUG})
	else()
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${OUTPUT_UNIX_RELEASE})
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${OUTPUT_UNIX_RELEASE})
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${OUTPUT_UNIX_RELEASE})
	endif()
# on WIN32 Debug and Release folders are created automatically
elseif (WIN32)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${OUTPUT_WIN32})
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${OUTPUT_WIN32})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${OUTPUT_WIN32})
	set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${OUTPUT_WIN32})
else()
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
endif()

# Include directories 
include_directories(${HEADER_DIR})

################# Flags ################
# Defines Flags for Windows and Linux. #

if(MSVC)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W3 /MD /Od /Zi /EHsc")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /W3 /GL /Od /Oi /Gy /Zi /EHsc")
	
	set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
	set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
endif(MSVC)
if(NOT MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	   set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
	endif()
endif(NOT MSVC)

################ Files ################
#   --   Add files to project.   --   #
#

# include files
include_directories(./include)

# Add executable to build.
add_executable(${PROJECT_NAME} ${SOURCE_DIR}/main.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX d)
