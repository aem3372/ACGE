option(USE_EXTERNAL_GTEST "" ON)

if(USE_EXTERNAL_GTEST)
	add_subdirectory(gtest)
endif(USE_EXTERNAL_GTEST)
