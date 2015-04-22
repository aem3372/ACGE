#include "tools/DynamicLinker.h"
#include "../mock/mock_object.h"
#include "gtest/gtest.h"

TEST(DynamicLinkerTest, DeviceMoudle) {
	DynamicLinker* linker = DynamicLinker::getInstance();

	// should check the file(DLL) existed. (not realization)

	ASSERT_TRUE(
		linker->loadLibrary("MockObject", "mock_object.dll"));
	ASSERT_NE(0,
		(int)linker->getProcAddress("MockObject", "createInstance"));
	ASSERT_TRUE(
		linker->freeLibrary("MockObject"));
}
