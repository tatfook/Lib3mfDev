# Author: leio
# Date: 2018.1.15
# Desc: 

cmake_minimum_required(VERSION 2.6)
project (Exporter3mf)

set (BoostRoot_DIR "$ENV{BOOST_ROOT}")
set(NPLRuntime_DIR "../NPLRuntime" CACHE STRING "")
set (NPLRuntime_Absolutely_DIR "${PROJECT_SOURCE_DIR}/${NPLRuntime_DIR}")

set( OUTPUT_BIN_DIR "${NPLRuntime_Absolutely_DIR}/ParaWorld/bin32/libs_3mf" )

IF (WIN32)
      set(libs_3mf lib3MF.lib)
ELSE ()
      set(lib3MF.so)
ENDIF()



SET(Exporter3mf_Source_files "")
file (GLOB src_files ${PROJECT_SOURCE_DIR}/src/*.*)
SOURCE_GROUP("src" FILES ${src_files}) 
list(APPEND Exporter3mf_Source_files ${src_files})

include_directories("${PROJECT_SOURCE_DIR}/deps/include")
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${NPLRuntime_Absolutely_DIR}/Client/trunk/ParaEngineClient")
include_directories("${NPLRuntime_Absolutely_DIR}/Client/trunk/ParaEngineClient/Core")
include_directories("${NPLRuntime_Absolutely_DIR}/Client/trunk/ParaEngineClient/renderer")
include_directories("${NPLRuntime_Absolutely_DIR}/Client/trunk/ParaEngineClient/math")
include_directories("${NPLRuntime_Absolutely_DIR}/Client/trunk/ParaEngineClient/util")
include_directories("${NPLRuntime_Absolutely_DIR}/Client/trunk/ParaEngineClient/IO")
include_directories("${BoostRoot_DIR}")
IF(MSVC)
	# statically link MSVC to reduce dependancies
	foreach(flag_var CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)
	 	if(${flag_var} MATCHES "/MD")
			string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
	 	endif(${flag_var} MATCHES "/MD")
	 	if(${flag_var} MATCHES "/MDd")
	 		string(REGEX REPLACE "/MDd" "/MTd" ${flag_var} "${${flag_var}}")
		endif(${flag_var} MATCHES "/MDd")
	endforeach(flag_var)
	
	# /GR- Remove RTTI to miminize the executable size
	SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GR-")

  # generate program database (PDB symbol files even in release build)
	SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
	SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /Zi")
ENDIF()


SET(CMAKE_DEBUG_POSTFIX "_d")

link_directories(${PROJECT_SOURCE_DIR}/deps/bin)

 

add_library(Exporter3mf SHARED ${Exporter3mf_Source_files})
target_link_libraries(Exporter3mf ${libs_3mf})

file(GLOB  libs_3mf_files "${PROJECT_SOURCE_DIR}/deps/bin/*.dll")

ADD_CUSTOM_COMMAND(
   TARGET Exporter3mf
   POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_BIN_DIR}
   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Exporter3mf> ${OUTPUT_BIN_DIR}
   COMMAND ${CMAKE_COMMAND} -E copy ${libs_3mf_files} ${OUTPUT_BIN_DIR}
)