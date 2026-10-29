cmake_minimum_required(VERSION 3.25)

project(FibCalc C)

# set C standard
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

# set compiler flags
add_compile_options(-Wall -Wextra -Wpedantic -O3 -static)

# set build directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# generic source file discovery
file(GLOB SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.c")

# set up the target executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")

# =========================
# Linters and Code Checkers
# =========================

# set up and run clang-tidy
find_program(CLANG_TIDY_BIN clang-tidy)
if(CLANG_TIDY_BIN)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            C_CLANG_TIDY "${CLANG_TIDY_BIN};-checks=bugprone-*;-header-filter=.*"
    )
endif()

# define lint target
add_custom_target(lint COMMENT "Running code linters...")

add_dependencies(${PROJECT_NAME} lint)

# set up and run cppcheck
find_program(CPPCHECK_BIN cppcheck)
if(CPPCHECK_BIN)
    add_custom_command(TARGET lint POST_BUILD
            COMMAND ${CPPCHECK_BIN}
            --enable=warning,style,performance,portability
            --quiet
            --suppress=missingIncludeSystem
            -I "${CMAKE_SOURCE_DIR}/include"
            ${SOURCES}
            COMMENT "Executing cppcheck"
    )
endif()

# set up and run cpplint
find_program(CPPLINT_BIN cpplint)
if(CPPLINT_BIN)
    add_custom_command(TARGET lint POST_BUILD
            COMMAND ${CPPLINT_BIN}
            --verbose=5
            --counting=total
            ${SOURCES} || true
            COMMENT "Executing cpplint"
    )
endif()
