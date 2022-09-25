add_library(recursive INTERFACE)

target_sources(recursive
INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/detail/arity.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/detail/array.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/detail/parallel_evaluation.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/detail/span.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/aliases.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/general.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/minimisation.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/primitive_functions.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/primitive.hpp
)

target_include_directories(recursive
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
