cmake_minimum_required( VERSION 2.8 FATAL_ERROR )
set( CMAKE_VERBOSE_MAKEFILE ON )

project( HelloCinder )


set(CINDER_PATH $ENV{CINDER_PATH})
get_filename_component( APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE )

include( "${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )

ci_make_app(
        SOURCES     ${APP_PATH}/src/ParticlesApp.cpp
                    ${APP_PATH}/src/Particle.cpp
                    ${APP_PATH}/src/ParticleController.cpp
        CINDER_PATH ${CINDER_PATH}
)