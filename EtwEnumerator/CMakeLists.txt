add_library(EtwEnumeratorStatic STATIC
    EtwEnumerator.cpp
    EtwEnumeratorCallbacks.cpp
    EtwEnumerator_DefaultConstruct.cpp
    EtwEnumerator_Format.cpp
    EtwEnumerator_Export.cpp
)

target_include_directories(EtwEnumeratorStatic PUBLIC ".")

target_precompile_headers(EtwEnumeratorStatic PRIVATE stdafx.h)

target_link_libraries(EtwEnumeratorStatic INTERFACE Tdh)

# Set linker properties to generate PDB
set_target_properties(EtwEnumeratorStatic PROPERTIES 
    COMPILE_PDB_NAME "EtwEnumeratorStatic"
    COMPILE_PDB_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)

# .NET AOT does not work with the Debug MSVC runtime library
set_property(TARGET EtwEnumeratorStatic PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:>")

add_library(EtwEnumerator SHARED
    EtwEnumerator_DllMain.cpp
    EtwEnumerator.def
)

target_link_libraries(EtwEnumerator PRIVATE EtwEnumeratorStatic)

add_executable(EtwEnumeratorExec main.cpp)

target_link_libraries(EtwEnumeratorExec PRIVATE EtwEnumeratorStatic)
