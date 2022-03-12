cmake_minimum_required(VERSION 3.0.0)
project(sql VERSION 0.1.0)


set(
    SOURCES
    ${PROJECT_SOURCE_DIR}/main.cxx
    ${PROJECT_SOURCE_DIR}/src/string.cxx
)

# add the executable
add_executable(${PROJECT_NAME} ${SOURCES})
