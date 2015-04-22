option(USE_EXTERNAL_GTEST "" ON)
option(USE_EXTERNAL_OPENGL "" ON)


if(USE_EXTERNAL_GTEST)
    add_subdirectory(gtest)
endif(USE_EXTERNAL_GTEST)

if(USE_EXTERNAL_OPENGL)
    add_subdirectory(opengl)
endif(USE_EXTERNAL_OPENGL)
