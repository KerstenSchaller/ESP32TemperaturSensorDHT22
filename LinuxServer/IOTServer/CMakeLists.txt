FIND_PACKAGE( Boost 1.40 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(IOTServer
main.cpp
)

target_link_libraries(IOTServer
    ${Boost_LIBRARIES}
    Threads::Threads
    )