# Define library. Only source files here!
project(librecon VERSION 0.1 LANGUAGES CXX)

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
	src/version.cpp
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
	src/libraryinfo.h
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
	pcl 
	unittestpp)

# 'make install' to the correct location
install(TARGETS librecon
    ARCHIVE  DESTINATION lib
    LIBRARY  DESTINATION lib
    RUNTIME  DESTINATION bin)  # This is for Windows
install(DIRECTORY include/ DESTINATION include)

# This makes the project importable from the build directory
export(TARGETS librecon FILE LibConfig.cmake)

# Every library has unit tests, of course
add_executable(testlibrecon
    test/main.cpp
	test/sanity_check.cpp
	test/test.h)

target_link_libraries(testlibrecon
    librecon 
#	boost-datetime 
	boost-filesystem 
	boost-system 
	boost-chrono
	boost-iostreams
	boost-serialization
	boost-thread
	unittestpp 
	pcl)

add_test(testlibrecon testlibrecon)