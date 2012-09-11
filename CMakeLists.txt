#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(opticBench)

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#

set(CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}/cmake/
    ${CMAKE_MODULE_PATH})

find_package(Geant4 REQUIRED ui_all vis_all)
find_package(ROOT REQUIRED)

message("Geant4: ${Geant4_INCLUDE_DIRS}, root: ${ROOT_INCLUDE_DIR}")

include_directories(${Geant4_INCLUDE_DIRS} ${ROOT_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/include)


add_definitions(${Geant4_DEFINITIONS})
set(CMAKE_CXX_FLAGS ${Geant4_CXX_FLAGS})


#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(crystal crystal.cc ${sources})
target_link_libraries(crystal ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build N05. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(crystal_CFGS
  vis.mac
  gps.mac
  crystal.cfg
  run.in
  )

foreach(_script ${crystal_CFGS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
# add_custom_target(opticBench DEPENDS opticBench)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS crystal DESTINATION bin)


