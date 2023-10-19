add_library(textFinder STATIC
            textFinder.cpp
)
target_link_libraries(textFinder PRIVATE Qt6::Widgets)
target_include_directories(textFinder INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})