project(TP_BD)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++11 -DHAVE_NULLPTR")

set(REQUIRED_LIBRARIES
        pq
        thevoid
        boost_system
        boost_thread
        swarm
        )

find_path(THEVOID_INCLUDE_DIRS NAMES thevoid/rapidjson/document.h)
INCLUDE_DIRECTORIES(BEFORE ${THEVOID_INCLUDE_DIRS}/thevoid)

find_path(PQ_INCLUDE_DIRS postgresql/libpq-fe.h)
set(PQ_INCLUDE_DIRS ${PQ_INCLUDE_DIRS}/postgresql)

aux_source_directory(. SRC_LIST)
aux_source_directory(./handlers HANDLERS_LIST)
aux_source_directory(./models MODELS_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${HANDLERS_LIST} ${MODELS_LIST})

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBRARIES})

