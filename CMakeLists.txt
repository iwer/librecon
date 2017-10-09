# Define library. Only source files here!
project(librecon LANGUAGES CXX)
SET (APPLICATION_NAME "Reconstruction Library")
SET (APPLICATION_CODENAME "${PROJECT_NAME}")
SET (APPLICATION_COPYRIGHT_YEARS "2013-2016")
SET (APPLICATION_VERSION_MAJOR 1)
SET (APPLICATION_VERSION_MINOR 0)
SET (APPLICATION_VERSION_PATCH 0)
SET (APPLICATION_VERSION_TYPE "-snapshot")
SET (APPLICATION_VERSION_STRING "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}.${APPLICATION_VERSION_PATCH}-${APPLICATION_VERSION_TYPE}")
SET (APPLICATION_VENDOR_ID "de.haw-hamburg.informatik.i2e")
SET (APPLICATION_VENDOR_NAME "Interactive Immersive Environments")
SET (APPLICATION_VENDOR_URL "i2e.informatik.haw-hamburg.de")
SET (APPLICATION_ID "${APPLICATION_VENDOR_ID}.${PROJECT_NAME}")

#
# Configure Files
#
#FILE (GLOB_RECURSE CONFIGINPUTS1 include/*.in.h.cmake)
#FILE (GLOB_RECURSE CONFIGINPUTS2 include/*.h.in.cmake)
#FILE (GLOB_RECURSE CONFIGINPUTS3 src/*.in.h.cmake)
#FILE (GLOB_RECURSE CONFIGINPUTS4 src/*.h.in.cmake)
#FILE (GLOB_RECURSE CONFIGINPUTS5 test/*.in.h.cmake)
#FILE (GLOB_RECURSE CONFIGINPUTS6 test/*.h.in.cmake)
#LIST (APPEND CONFIGINPUTS "${CONFIGINPUTS1}")
#LIST (APPEND CONFIGINPUTS "${CONFIGINPUTS2}")
#LIST (APPEND CONFIGINPUTS "${CONFIGINPUTS3}")
#LIST (APPEND CONFIGINPUTS "${CONFIGINPUTS4}")
#LIST (APPEND CONFIGINPUTS "${CONFIGINPUTS5}")
#LIST (APPEND CONFIGINPUTS "${CONFIGINPUTS6}")
#FOREACH (CONFIGINPUT ${CONFIGINPUTS})
#    STRING (REPLACE ".in.h.cmake" ".h" CONFIGOUTPUT1 "${CONFIGINPUT}")
#    STRING (REPLACE ".h.in.cmake" ".h" CONFIGOUTPUT2 "${CONFIGOUTPUT1}")
#    CONFIGURE_FILE ("${CONFIGINPUT}" "${CONFIGOUTPUT2}")
#ENDFOREACH (CONFIGINPUT ${CONFIGINPUTS})



add_library(librecon
    # Source files
	src/AbstractMeshProcessor.cpp
	src/AbstractPointCloudGenerator.cpp
	src/AbstractPointProcessor.cpp
	src/AbstractProcessingPipeline.cpp
	src/AbstractSensor.cpp
	src/CameraExtrinsics.cpp
	src/CameraIntrinsics.cpp
	src/DepthFilePointCloudGenerator.cpp
	src/DepthThreshold.cpp
	src/DummySensor.cpp
	src/FilePointCloudGenerator.cpp
	src/Frame.cpp
	src/GreedyProjectionMeshProcessor.cpp
	src/OpenNI2Sensor.cpp
	src/OrganizedFastMeshProcessor.cpp
	src/PclOpenNI2Grabber.cpp
	src/Pipeline01.cpp
	src/Pipeline02.cpp
	src/PointCloudSampler.cpp
	src/PointCloudSmoother.cpp
	src/SensorFactory.cpp
	src/SimulatedOpenNI2Sensor.cpp
	src/StaticBackgroundRemover.cpp
#	src/version.cpp
	# Header files (to be able to edit in VS et. al.)
	include/recon/AbstractMeshProcessor.h
	include/recon/AbstractPointCloudGenerator.h
	include/recon/AbstractPointProcessor.h
	include/recon/AbstractProcessingPipeline.h
	include/recon/AbstractSensor.h
	include/recon/CameraExtrinsics.h
	include/recon/CameraIntrinsics.h
	include/recon/DepthFilePointCloudGenerator.h
	include/recon/DepthThreshold.h
	include/recon/DummySensor.h
	include/recon/FilePointCloudGenerator.h
	include/recon/Frame.h
	include/recon/GreedyProjectionMeshProcessor.h
	include/recon/libraryinfo.h
	include/recon/OpenNI2Sensor.h
	include/recon/OrganizedFastMeshProcessor.h
	include/recon/PclOpenNI2Grabber.h
	include/recon/Pipeline01.h
	include/recon/Pipeline02.h
	include/recon/PointCloudSampler.h
	include/recon/PointCloudSmoother.h
	include/recon/recon.h
	include/recon/SensorFactory.h
	include/recon/SimulatedOpenNI2Sensor.h
	include/recon/StaticBackgroundRemover.h
	include/recon/typedefs.h
	include/recon/version.h
	include/recon/libraryinfo.h
	)


# generate version using cmake tools
file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build-number BUILDNO_FILE)
file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/last-buildno LAST_BUILDNO_FILE)

file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include/recon/version.h.in.cmake CONFIG_FILE)
file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include/recon/version.h VERSION_HEADER)


add_custom_target(
        librecon_version
        ${CMAKE_COMMAND} -D SRC=${CONFIG_FILE}
        -D DST=${VERSION_HEADER}
        -D VERFILE=${BUILDNO_FILE}
        -D LASTVERFILE=${LAST_BUILDNO_FILE}
        -D APPLICATION_VERSION_MAJOR=${APPLICATION_VERSION_MAJOR}
        -D APPLICATION_VERSION_MINOR=${APPLICATION_VERSION_MINOR}
        -D APPLICATION_VERSION_PATCH=${APPLICATION_VERSION_PATCH}
        -D APPLICATION_VERSION_TYPE=${APPLICATION_VERSION_TYPE}
        -P ${CMAKE_CUSTOM_MODULE_PATH}/version.cmake
)
add_dependencies(librecon librecon_version)

#increment build-number post-build
add_custom_command(TARGET librecon
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND}
        -D VERFILE=${BUILDNO_FILE}
        -D LASTVERFILE=${LAST_BUILDNO_FILE}
        -P ${CMAKE_CUSTOM_MODULE_PATH}/increment_version.cmake
        )






# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(librecon PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

# If we have compiler requirements for this library, list them
# here
target_compile_features(librecon
    PUBLIC cxx_auto_type
    PRIVATE cxx_variadic_templates)

# Depend on a library that we defined in the top-level file
target_link_libraries(librecon
	boost-datetime 
	boost-filesystem 
	boost-system 
	boost-chrono
	boost-iostreams
	boost-serialization
	boost-thread
	pcl-common 
	pcl-search
	pcl-io
	pcl-filters
	pcl-surface)

# 'make install' to the correct location
install(TARGETS librecon
    ARCHIVE  DESTINATION lib
    LIBRARY  DESTINATION lib
    RUNTIME  DESTINATION bin)  # This is for Windows
install(DIRECTORY include/ DESTINATION include)

# This makes the project importable from the build directory
export(TARGETS librecon FILE ReconConfig.cmake)

# Every library has unit tests, of course
add_executable(testlibrecon
    test/main.cpp
	test/sanity_check.cpp
	test/test.h)

target_link_libraries(testlibrecon
    librecon 
	UnitTest++)

add_test(testlibrecon testlibrecon)