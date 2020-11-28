# A380 Systems build script.
#
# Thanks to https://github.com/sparker256 for the whole build system!
#
# Useful command line flags:
#   * -DCMAKE_BUILD_TYPE=XXX, where XXX is one of Debug, Release,
#     RelWithDebInfo and MinSizeRel. Default is Release.
#   * -DCREATECOMPLETEEDITION=XXX, where XXX is true or false. Default is true.

cmake_minimum_required(VERSION 3.9)
project(A380Systems VERSION 1.0 DESCRIPTION "J-PRO A380 Systems X-Plane plugin")

# By default, use optimized release configuration.
if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif ()

set(CMAKE_CXX_STANDARD 14)

# Set include directories used by our code and dependencies.
include_directories("${CMAKE_SOURCE_DIR}/../include/XPSDK303/CHeaders/Widgets")
include_directories("${CMAKE_SOURCE_DIR}/../include/XPSDK303/CHeaders/Wrappers")
include_directories("${CMAKE_SOURCE_DIR}/../include/XPSDK303/CHeaders/XPLM")


# Specify library search locations.
if (WIN32)
    list(APPEND CMAKE_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/../include/XPSDK303/Libraries/Win")
elseif (APPLE)
    list(APPEND CMAKE_FRAMEWORK_PATH "${CMAKE_SOURCE_DIR}/../include/XPSDK303/Libraries/Mac")
elseif (UNIX)

endif ()

# message (STATUS "CMAKE_LIBRARY_PATH" = ${CMAKE_LIBRARY_PATH})

# Enable all X-Plane SDK APIs up to the newest version.
add_definitions(-DXPLM200=1 -DXPLM210=1 -DXPLM300=1 -DXPLM301=1)
# Define platform macros.
add_definitions(-DAPL=$<BOOL:${APPLE}> -DIBM=$<BOOL:${WIN32}> -DLIN=$<AND:$<BOOL:${UNIX}>,$<NOT:$<BOOL:${APPLE}>>>)



# Force-enable exception support. This is most likely redundant, although for C
# code the default is the opposite. Since we are mixing C++ and C libraries,
# safer to set it on?
add_compile_options(-fexceptions)
# On UNIX systems this makes symbols non-exported by default. On Windows this
# option is simply ignored, since symbol visibility works differently there.
add_compile_options(-fvisibility=hidden)

# Enable stricter warnings and then disable some we are not interested in.
add_compile_options(-Wall -Wpedantic -Wshadow -Wfloat-equal -Wextra)
add_compile_options(-Wno-unused)

# Always use position-independent code and highest optimization level (FPS!).
add_compile_options(-O3 -fPIC)

# X-Plane plugin
# FIXME: Split this into individual targets.
list(APPEND A380SYS_SRCS main.cpp
        FUEL/PhysicalFuelSystem/FuelSystem.cpp FUEL/PhysicalFuelSystem/FuelSystem.h FUEL/PhysicalFuelSystem/FuelTank.cpp FUEL/PhysicalFuelSystem/FuelTank.h FUEL/PhysicalFuelSystem/FuelPump.cpp FUEL/PhysicalFuelSystem/FuelPump.h FUEL/PhysicalFuelSystem/FuelTankValve.cpp FUEL/PhysicalFuelSystem/FuelTankValve.h FUEL/PhysicalFuelSystem/FuelBus.cpp FUEL/PhysicalFuelSystem/FuelBus.h FUEL/PhysicalFuelSystem/FuelBusValve.cpp FUEL/PhysicalFuelSystem/FuelBusValve.h FUEL/PhysicalFuelSystem/FuelConsumer.cpp FUEL/PhysicalFuelSystem/FuelConsumer.h FUEL/PhysicalFuelSystem/EmergTransValve.cpp
        FUEL/PlaneFuelSystem/Tables/Tables.h FUEL/PlaneFuelSystem/Tables/Table0.cpp FUEL/PlaneFuelSystem/Tables/Table1.cpp FUEL/PlaneFuelSystem/Tables/Table2.cpp FUEL/PlaneFuelSystem/Tables/Table3.cpp FUEL/PlaneFuelSystem/DistributionTables.h FUEL/PlaneFuelSystem/DistributionTables.cpp FUEL/PlaneFuelSystem/FuelDistributor.h FUEL/PlaneFuelSystem/FuelDistributor.cpp FUEL/PlaneFuelSystem/FQDC.cpp FUEL/PlaneFuelSystem/FQDC.h FUEL/PlaneFuelSystem/FQMS.cpp FUEL/PlaneFuelSystem/FQMS.h FUEL/SystemControl.cpp
        FUEL/SystemControl.h FUEL/PlaneFuelSystem/Templates/Template.h FUEL/PlaneFuelSystem/Templates/TemplateGetter.cpp FUEL/PlaneFuelSystem/Templates/TemplateGetter.h FUEL/PlaneFuelSystem/Templates/InnerFeed14.cpp FUEL/PlaneFuelSystem/Templates/InnerFeed14.h FUEL/PlaneFuelSystem/Templates/TrimFeeds.cpp FUEL/PlaneFuelSystem/Templates/TrimFeeds.h FUEL/PlaneFuelSystem/Templates/InnerOuter.cpp FUEL/PlaneFuelSystem/Templates/InnerOuter.h
        FUEL/PlaneFuelSystem/Templates/InnerFeed23.cpp FUEL/PlaneFuelSystem/Templates/InnerFeed23.h FUEL/PlaneFuelSystem/Templates/MidFeed14.cpp FUEL/PlaneFuelSystem/Templates/MidFeed14.h FUEL/PlaneFuelSystem/Templates/MidFeed23.cpp FUEL/PlaneFuelSystem/Templates/MidFeed23.h FUEL/PlaneFuelSystem/Templates/MidFeeds.cpp FUEL/PlaneFuelSystem/Templates/MidFeeds.h FUEL/PlaneFuelSystem/Templates/MidOuter.cpp FUEL/PlaneFuelSystem/Templates/MidOuter.h FUEL/PlaneFuelSystem/Templates/OutFeeds.cpp
        FUEL/PlaneFuelSystem/Templates/OutFeeds.h FUEL/PlaneFuelSystem/Templates/OutInner.cpp FUEL/PlaneFuelSystem/Templates/OutInner.h FUEL/PlaneFuelSystem/Templates/OutMid.cpp FUEL/PlaneFuelSystem/Templates/OutMid.h FUEL/PlaneFuelSystem/Templates/TrimInner.cpp FUEL/PlaneFuelSystem/Templates/TrimInner.h FUEL/PlaneFuelSystem/Templates/TrimMid.cpp FUEL/PlaneFuelSystem/Templates/TrimMid.h FUEL/FuelSystemFrontend.cpp FUEL/FuelSystemFrontend.h FUEL/PlaneFuelSystem/Templates/InnerFeeds.cpp FUEL/PlaneFuelSystem/Templates/InnerFeeds.h FUEL/PlaneFuelSystem/FQMSFailuresDetect.cpp

        ECAM/ECAMSystemControl.cpp ECAM/ECAMSystemControl.h ECAM/FuelMonitor.cpp ECAM/FuelMonitor.h ECAM/ECAMFrontend.cpp ECAM/ECAMFrontend.h ECAM/ECAMDataCache.cpp ECAM/ECAMDataCache.h

        PluginControl/PlaneSystemsFrontends.h PluginControl/SimulatorData.cpp PluginControl/SimulatorData.h PluginControl/PlaneSystemsRefs.h PluginControl/SystemsControl.cpp PluginControl/SystemsControl.h  PluginControl/PluginControl.cpp PluginControl/PluginControl.h
        PluginControl/DatarefHandlers/XPLANE_DataHandlers.cpp PluginControl/DatarefHandlers/XPLANE_DataHandlers.h PluginControl/DatarefHandlers/COCKPIT_DataHandlers.cpp PluginControl/DatarefHandlers/COCKPIT_DataHandlers.h PluginControl/DatarefHandlers/ECAM_DataHandlers.cpp PluginControl/DatarefHandlers/ECAM_DataHandlers.h PluginControl/DatarefHandlers/FUEL_DataHandlers.cpp PluginControl/DatarefHandlers/FUEL_DataHandlers.h

        COCKPIT/CockpitControls.cpp COCKPIT/CockpitControls.h)


add_library(A380Systems SHARED ${A380SYS_SRCS} )

target_compile_features(A380Systems PUBLIC cxx_std_11)

if (APPLE)
    # X-Plane supports OS X 10.10+, so this should ensure FlyWithLua can run on
    # all supported versions.
    target_compile_options(A380Systems PUBLIC -mmacosx-version-min=10.10)
    target_link_libraries(A380Systems -mmacosx-version-min=10.10)
endif ()

# Link OpenGL and OpenAL related libraries.
find_package(OpenGL REQUIRED)  # apt install freeglut3-dev
find_library(OPENAL_LIBRARY NAMES openal OpenAL OpenAL32)  # apt install libopenal-dev
find_library(GLUT_LIBRARY NAMES glut GLUT glut64)  # apt install freeglut3-dev
# target_link_libraries(A380Systems ${OPENGL_LIBRARIES} ${OPENAL_LIBRARY} ${GLUT_LIBRARY})


# Link X-Plane plugin system libraries. They are only provided for OS X and Windows.
if (WIN32 OR APPLE)
    # if (WIN32)
    find_library(XPLM_LIBRARY NAMES XPLM XPLM_64.lib)
    find_library(XPWIDGETS_LIBRARY NAMES XPWidgets XPWidgets_64.lib)
    target_link_libraries(A380Systems ${XPLM_LIBRARY} ${XPWIDGETS_LIBRARY})
endif ()


# Link library for dynamic loading of shared objects on UNIX systems.
if (UNIX)
    find_library(DL_LIBRARY dl)
    target_link_libraries(A380Systems ${DL_LIBRARY})
endif ()

# Link OS X core system libraries.
if (APPLE)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(CORE_FOUNDATION_LIBRARY CoreFoundation)
    find_library(GLUT_LIBRARY GLUT)
    find_library(OpenGL_LIBRARY OpenGL)
    find_library(Cocoa_LIBRARY Cocoa)

    target_link_libraries(A380Systems ${IOKIT_LIBRARY} ${CORE_FOUNDATION_LIBRARY} ${GLUT_LIBRARY})
    target_link_libraries(A380Systems ${OpenGL_LIBRARY} ${Cocoa_LIBRARY})
endif ()

if (WIN32)
    # Unlike OS X and Linux we build standard libraries statically since X-Plane does not provide them.
    target_link_libraries(A380Systems -static-libgcc -static-libstdc++ opengl32)
    # MSYS2 for some reason always links against winpthread, so we have to work around it by statically linking the
    # entire plugin. This allows building the plugin nativaly on Windows.
    target_link_libraries(A380Systems -static)
elseif (APPLE)
    # Restrict set of symbols exported from the plugin. This reduces changes of
    # conflict with other plugins, in particular ones with Lua interpreter
    # embedded.
    target_link_libraries(A380Systems "-exported_symbols_list ${CMAKE_SOURCE_DIR}/A380Systems.sym_mac")
    target_link_libraries(A380Systems "-framework XPLM -framework XPWidgets -ldl")
elseif (UNIX)
    # Specify additional runtime search laths for dynamically-linked libraries.
    # Restrict set of symbols exported from the plugin. This reduces changes of
    # conflict with other plugins, in particular ones with Lua interpreter
    # embedded.
    target_link_libraries(A380Systems -Wl,--version-script -Wl,${CMAKE_SOURCE_DIR}/A380Systems.sym)
endif ()


# set_target_properties(A380Systems PROPERTIES PREFIX "")
# if (WIN32)
#    set_target_properties(A380Systems PROPERTIES OUTPUT_NAME "win")
# elseif (APPLE)
#    set_target_properties(A380Systems PROPERTIES OUTPUT_NAME "mac")
# elseif (UNIX)
#    set_target_properties(A380Systems PROPERTIES OUTPUT_NAME "lin")
# endif ()
# set_target_properties(A380Systems PROPERTIES SUFFIX ".xpl")


set_target_properties(A380Systems PROPERTIES PREFIX "")
set_target_properties(A380Systems PROPERTIES OUTPUT_NAME "A380Systems")
set_target_properties(A380Systems PROPERTIES SUFFIX ".xpl")




