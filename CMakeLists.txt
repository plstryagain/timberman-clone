cmake_minimum_required(VERSION 3.27)
project(timberman-clone CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.6.2 COMPONENTS system window graphics network audio REQUIRED PATHS $ENV{SFML_ROOT})
include_directories($ENV{SFML_ROOT}/include)

add_subdirectory(src)

add_executable(${PROJECT_NAME} 
                $<TARGET_OBJECTS:main_obj>
)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} 
                            sfml-system 
                            sfml-window 
                            sfml-graphics 
                            sfml-audio 
                            sfml-network
                            
    )
endif ()