cmake_minimum_required(VERSION 2.5)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
SET(CMAKE_C_COMPILER mpicc)
SET(CMAKE_CXX_COMPILER mpicxx)
SET(CMAKE_CXX_FLAGS "-g -Wall -DDEBUG")

set(HDRS
        utility.h
	fermatfactor.h
	quadraticsieve.h
    )
set(SRC
	utility.cc
	fermatfactor.cc
	quadraticsieve.cc	
	main.cc
    ) 

add_executable(mpisieve-0.0.2 ${HDRS} ${SRC})
target_link_libraries(mpisieve-0.0.2 gmp mpi)
