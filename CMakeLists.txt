cmake_minimum_required(VERSION 2.8)
project(MST)

#Added to detect compiler support for C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
endif()

option(CYLINDRICAL_SHIELD "Enabling CYLINDRICAL shape shielding layers, Default is Cuboidal" OFF)
if(CYLINDRICAL_SHIELD)
add_definitions(-DCYLINDRICAL_SHIELD)
endif(CYLINDRICAL_SHIELD)

option(ENABLE_OPTICAL_PHYSICS "Enabling OPTICAL Physics, Default is OFF " OFF)
if(ENABLE_OPTICAL_PHYSICS)
add_definitions(-DENABLE_OPTICAL_PHYSICS)
endif(ENABLE_OPTICAL_PHYSICS)

option(INSPECT_SOURCE "Inspect Particle source, default is OFF " OFF)
if(INSPECT_SOURCE)
add_definitions(-DINSPECT_SOURCE)
endif(INSPECT_SOURCE)

option(FILL_COLOUR "Assign default color to detector components, default is OFF " OFF)
if(FILL_COLOUR)
add_definitions(-DFILL_COLOUR)
endif(FILL_COLOUR)

option(TRACK_ONLY_PRIMARY "Enabling OPTICAL Physics, Default is OFF " OFF)
if(TRACK_ONLY_PRIMARY)
add_definitions(-DTRACK_ONLY_PRIMARY)
endif(TRACK_ONLY_PRIMARY)

option(USE_RANECU_RANDOM "Enabling RANECU random number generator, Required CLHEP, Default is OFF " OFF)
if(USE_RANECU_RANDOM)
add_definitions(-DUSE_RANECU_RANDOM)
find_package(CLHEP REQUIRED)
message(STATUS ${CLHEP_INCLUDE_DIR})
message(STATUS ${CLHEP_LIBRARIES})
include_directories(${CLHEP_INCLUDE_DIR})
#set(REQLIBS ${REQLIBS} ${CLHEP_LIBRARIES} )
endif(USE_RANECU_RANDOM)


#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
file(GLOB MAC_FILES ${PROJECT_SOURCE_DIR}/MacFiles/*)
message(STATUS ${MAC_FILES})
#file(COPY ${MAC_FILES} DESTINATION ${PROJECT_SOURCE_DIR}/build)
file(COPY ${MAC_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/inc)
include_directories(../..)

find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIRS})
#set(REQLIBS ${REQLIBS} ${ROOT_LIBRARIES} )

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/inc/*.h ${PROJECT_SOURCE_DIR}/inc/*.hh ../../base/Vector3D.h) 

add_executable(main main.cpp ${sources} ${headers})
if(USE_RANECU_RANDOM)
target_link_libraries(main ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ${CLHEP_LIBRARIES})
else()
target_link_libraries(main ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
endif()

add_executable(TestBoolean coreTest/TestBoolean.cpp)
target_link_libraries(TestBoolean ${Geant4_LIBRARIES})

add_executable(TestG4Units coreTest/TestG4Units.cpp)
target_link_libraries(TestG4Units ${Geant4_LIBRARIES})

#target_link_libraries(main ${Geant4_LIBRARIES} Tomo)
