cmake_minimum_required(VERSION 3.1)

project(medInria-visages-plugins)

## #################################################################
## Setup version numbering
## #################################################################

set(${PROJECT_NAME}_VERSION_MAJOR 3 CACHE STRING "${PROJECT_NAME} major
version number.")
set(${PROJECT_NAME}_VERSION_MINOR 0 CACHE STRING "${PROJECT_NAME} minor
version number.")
set(${PROJECT_NAME}_VERSION_BUILD 0 CACHE STRING "${PROJECT_NAME} build
version number." FORCE)
set(${PROJECT_NAME}_VERSION_BUGFIX 0 CACHE STRING "${PROJECT_NAME} bug-fix version number." FORCE)

if (${${PROJECT_NAME}_VERSION_BUGFIX} GREATER 0)
  set(${PROJECT_NAME}_VERSION
    "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_BUILD}-${${PROJECT_NAME}_VERSION_BUGFIX}")
else()
  set(${PROJECT_NAME}_VERSION
    "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_BUILD}")
endif()

mark_as_advanced(${PROJECT_NAME}_VERSION_MAJOR)
mark_as_advanced(${PROJECT_NAME}_VERSION_MINOR)
mark_as_advanced(${PROJECT_NAME}_VERSION_BUILD)
mark_as_advanced(${PROJECT_NAME}_VERSION_BUGFIX)

## #################################################################
## Input
## #################################################################

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MACOSX_RPATH OFF)

## #############################################################################
## enable c++ 17
## #############################################################################

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## #############################################################################
## Qt5
## #############################################################################

find_package(Qt5 COMPONENTS REQUIRED
  Core
  Gui
  Network
  Widgets
)

find_package(dtk REQUIRED)
include_directories(${dtk_INCLUDE_DIRS})

find_package(medInria REQUIRED)

include(list_source_files)
include(list_header_directories_to_include)

option(MEDINRIA_BUILD_QTSHANOIRDATASOURCE_PLUGIN     "Build qtshanoirDataSource plugin" "ON")
option(MEDINRIA_BUILD_ANIMA_SYMMETRYPLANE_PLUGIN     "Build animaSymmetryPlane plugin" "ON")
option(MEDINRIA_BUILD_ANIMA_NONLOCALMEANSFILTER_PLUGIN     "Build anima-NonLocalMeansFilter plugin" "ON")
option(MEDINRIA_BUILD_ANIMA_PYRAMIDALBMREGISTRATION_PLUGIN     "Build anima-PyramidalBMRegistration plugin" "ON")
option(MEDINRIA_BUILD_ANIMA_DENSEBMREGISTRATION_PLUGIN     "Build anima-DenseBMRegistration plugin" "ON")
option(MEDINRIA_BUILD_ANIMA_RELAXOMETRY_PLUGIN     "Build anima-Relaxometry plugin" "ON")
option(MEDINRIA_BUILD_ANIMA_MCMDATAIMAGE_PLUGIN     "Build animaMCMDataImage plugin" "ON")
option(MEDINRIA_BUILD_ANIMA_MCMESTIMATION_PLUGIN     "Build animaMCMEstimation plugin" "ON")
option(MEDINRIA_BUILD_ANIMA_TENSORESTIMATION_PLUGIN     "Build animaTensorEstimation plugin" "ON")

option(BUILD_DOCUMENTATION "Build documentation")
option(BUILD_EXAMPLES "Build examples" OFF)

if (MEDINRIA_BUILD_QTSHANOIRDATASOURCE_PLUGIN)
    add_subdirectory(qtshanoirDataSource)
endif()

if (MEDINRIA_BUILD_ANIMA_SYMMETRYPLANE_PLUGIN)
    add_subdirectory(animaSymmetryPlane)
endif()

if (MEDINRIA_BUILD_ANIMA_NONLOCALMEANSFILTER_PLUGIN)
    add_subdirectory(animaNonLocalMeansFilter)
endif()

if (MEDINRIA_BUILD_ANIMA_PYRAMIDALBMREGISTRATION_PLUGIN)
    add_subdirectory(animaPyramidalBMRegistration)
endif()

if (MEDINRIA_BUILD_ANIMA_DENSEBMREGISTRATION_PLUGIN)
    add_subdirectory(animaDenseBMRegistration)
endif()

if (MEDINRIA_BUILD_ANIMA_MCMDATAIMAGE_PLUGIN)
    add_subdirectory(animaDataMCMImage)
endif()

if (MEDINRIA_BUILD_ANIMA_MCMESTIMATION_PLUGIN)
    add_subdirectory(animaMCMEstimation)
endif()

if (MEDINRIA_BUILD_ANIMA_TENSORESTIMATION_PLUGIN)
    add_subdirectory(animaTensorEstimation)
endif()

if (MEDINRIA_BUILD_ANIMA_RELAXOMETRY_PLUGIN)
    subdirs(animaRelaxometry)
endif()

if (APPLE)
  configure_file(${PROJECT_SOURCE_DIR}/packageScripts/fix_apple_links_and_package.sh.in
                 ${PROJECT_BINARY_DIR}/tmp_fix_apple_links_and_package.sh.in)
  configure_file(${PROJECT_BINARY_DIR}/tmp_fix_apple_links_and_package.sh.in
                 ${PROJECT_BINARY_DIR}/fix_apple_links_and_package.sh)
  configure_file(${PROJECT_SOURCE_DIR}/cmake/ApplePackScript.cmake.in
                 ${PROJECT_BINARY_DIR}/ApplePackScript.cmake)
endif()

if(BUILD_DOCUMENTATION)
  add_subdirectory(doc)
endif(BUILD_DOCUMENTATION)

## #################################################################
## Build settings
## #################################################################

# On Visual Studio 8 MS deprecated C. This removes all 1.276E1265 security warnings
if(WIN32)
  if(NOT BORLAND)
    if(NOT CYGWIN)
      if(NOT MINGW)
        if(NOT ITK_ENABLE_VISUAL_STUDIO_DEPRECATED_C_WARNINGS)
          add_definitions(
            -D_CRT_FAR_MAPPINGS_NO_DEPRECATE
            -D_CRT_IS_WCTYPE_NO_DEPRECATE
            -D_CRT_MANAGED_FP_NO_DEPRECATE
            -D_CRT_NONSTDC_NO_DEPRECATE
            -D_CRT_SECURE_NO_DEPRECATE
            -D_CRT_SECURE_NO_DEPRECATE_GLOBALS
            -D_CRT_SETERRORMODE_BEEP_SLEEP_NO_DEPRECATE
            -D_CRT_TIME_FUNCTIONS_NO_DEPRECATE
            -D_CRT_VCCLRIT_NO_DEPRECATE
            -D_SCL_SECURE_NO_DEPRECATE
            )
        endif(NOT ITK_ENABLE_VISUAL_STUDIO_DEPRECATED_C_WARNINGS)
      endif(NOT MINGW)
    endif(NOT CYGWIN)
  endif(NOT BORLAND)
endif(WIN32)

include(pack)
