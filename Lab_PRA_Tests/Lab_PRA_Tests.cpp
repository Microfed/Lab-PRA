// Lab_PRA_Tests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "gtest/gtest.h"
#include "RegistryReaderTest.h"


int _tmain(int argc, _TCHAR* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

