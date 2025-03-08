add_library(mcp9808 STATIC)

target_sources(mcp9808 PRIVATE 
    "mcp9808.cpp"
)

target_include_directories(mcp9808 PUBLIC 
    "."
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(mcp9808 PRIVATE
    utility
    stm32cubemx
)

target_compile_options(mcp9808 PUBLIC
    -std=c++23
    -Wall
    -Wextra
    -Wconversion
    -Wshadow
    -Wpedantic
    -Wnarrowing
    -Waddress
    -pedantic
    -Wdeprecated
    -Wsign-conversion
    -Wduplicated-cond
    -Wduplicated-branches
    -Wlogical-op
    -Wnull-dereference
    -Wdouble-promotion
    -Wimplicit-fallthrough
    -Wcast-align
    -fconcepts
)
