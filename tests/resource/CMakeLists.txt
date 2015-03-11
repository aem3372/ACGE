file(MAKE_DIRECTORY ${ACGE_TESTS_DIR}/resource)

file(COPY resource/libdevice-gdiplus.dll 
	DESTINATION ${ACGE_TESTS_DIR}/resource)