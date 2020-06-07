
# Public header files
set(HEADER_FOLDER "${PROJECT_SOURCE_DIR}/include/tree-container")
set(HEADER_LIST
    "${HEADER_FOLDER}/binary_tree.h"
)

# Public template "source" files
set(TEMPLATE_SOURCE_FOLDER "${PROJECT_SOURCE_DIR}/include/tree-container")
set(TEMPLATE_SOURCE_LIST
    "${TEMPLATE_SOURCE_FOLDER}/binary_tree.tpp"
)


# Make an automatic library - will be static or dynamic based on user setting
add_library(${LIBRARY_NAME} INTERFACE)

# Headers will not show up in IDEs unless they are listed here
target_sources(${LIBRARY_NAME}
            INTERFACE
            ${HEADER_LIST}
            ${TEMPLATE_SOURCE_LIST}
)

# Since this is a header-only library, only users of our library will need this directory
target_include_directories(${LIBRARY_NAME} INTERFACE "${PROJECT_SOURCE_DIR}/include")

# All users of this library will need at least C++11
target_compile_features(${LIBRARY_NAME} INTERFACE cxx_std_11)

# IDEs should put the headers in a nice place
# (This might not work as intended)
# source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})