cmake_minimum_required(VERSION 2.8)
project(arqSoft)

set (CMAKE_CXX_FLAGS " -std=c++0x")
set (TARGET arqSoft)

# set this variable to specify a common place where CMake should put all executable files
# (instead of CMAKE_CURRENT_BINARY_DIR)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

include_directories ("${PROJECT_SOURCE_DIR}/src/jsoncpp")
include_directories ("${PROJECT_SOURCE_DIR}/src/Mongoose")
include_directories ("${PROJECT_SOURCE_DIR}/src/leveldb/db")
include_directories ("${PROJECT_SOURCE_DIR}/src/leveldb/include")
include_directories ("${PROJECT_SOURCE_DIR}/src/leveldb/leveldb/util")
include_directories ("${PROJECT_SOURCE_DIR}/src/leveldb/leveldb/port")


link_directories("${CMAKE_BINARY_DIR}/lib")


add_subdirectory(src/leveldb)
add_subdirectory(src/Mongoose)
add_subdirectory(src/jsoncpp)
add_subdirectory(src/googletest)

set(SOURCE_FILES
        src/main.cpp
        src/api/handler/WebHandler.h
        src/api/handler/WebHandler.cpp
        src/api/Response.cpp
        src/api/handler/Handler.h
        src/api/handler/Handler.cpp
        src/api/Response.h
        src/DB/DBWrapper.h
        src/DB/DBWrapper.cpp
    src/Mongoose/mongoose.c
    src/Mongoose/mongoose.h src/api/handler/MateriasHandler.cpp src/api/handler/MateriasHandler.h src/Managers/MateriaManager.cpp src/Managers/MateriaManager.h src/Exceptions/MateriaInexistenteException.cpp src/Exceptions/MateriaInexistenteException.h src/Exceptions/InvalidRequestException.cpp src/Exceptions/InvalidRequestException.h src/DOM/Curso.cpp src/DOM/Curso.h src/DOM/Dia.cpp src/DOM/Dia.h src/Managers/Manager.cpp src/Managers/Manager.h src/DOM/Materia.cpp src/DOM/Materia.h src/api/handler/InscriptosHandler.cpp src/api/handler/InscriptosHandler.h src/DOM/Alumno.cpp src/DOM/Alumno.h src/Exceptions/CursoInexistenteException.cpp src/Exceptions/CursoInexistenteException.h src/Exceptions/MateriaYaExisteException.cpp src/Exceptions/MateriaYaExisteException.h src/DB/DbBuilder.cpp src/DB/DbBuilder.h)

add_executable(arqSoft ${SOURCE_FILES})

target_link_libraries (${TARGET} Mongoose)
target_link_libraries (${TARGET} JsonCpp)
target_link_libraries (${TARGET} leveldb)
