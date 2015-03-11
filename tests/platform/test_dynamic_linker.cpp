#include "platform/dynamic_linker.h"
#include "gtest/gtest.h"

TEST(DynamicLinkerTest, DeviceMoudle) {
	DynamicLinker* linker = DynamicLinker::getInstance();

	// should check the file(DLL) existed. (not realization)

	ASSERT_TRUE(
		linker->loadLibrary("device-gdiplus", "resource\\libdevice-gdiplus.dll"));
	ASSERT_NE(0,
		(int)linker->getProcAddress("device-gdiplus", "createInstance"));
	ASSERT_TRUE(
		linker->freeLibrary("device-gdiplus"));
}
