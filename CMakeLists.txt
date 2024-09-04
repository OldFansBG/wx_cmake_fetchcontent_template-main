cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(wx_cmake_fetchcontent_template LANGUAGES CXX)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "Fetching dependencies...")

# Fetch wxWidgets
FetchContent_Declare(
    wxWidgets
    GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
    GIT_TAG master
    GIT_SHALLOW ON
)

FetchContent_MakeAvailable(wxWidgets)

# Fetch libarchive
FetchContent_Declare(
    libarchive
    GIT_REPOSITORY https://github.com/libarchive/libarchive.git
    GIT_TAG v3.5.2  # You can specify the version or branch
    GIT_SHALLOW ON
)

FetchContent_MakeAvailable(libarchive)

# Define the sources
set(SRCS main.cpp extractor.cpp)

# Add executable
if(APPLE)
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SRCS})
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist)
else()
    add_executable(${PROJECT_NAME} WIN32 ${SRCS})
endif()

# Configure wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base)

include(${wxWidgets_USE_FILE})

# Link wxWidgets and libarchive
target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES} archive)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${wxWidgets_INCLUDE_DIRS}
    ${libarchive_SOURCE_DIR}/libarchive
)

# Set any necessary compiler options
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)