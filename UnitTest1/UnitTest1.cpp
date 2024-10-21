#include "pch.h"
#include "CppUnitTest.h"
#include "../PR7.3(rec).cpp"  // включає вашу основну програму

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    TEST_CLASS(UnitTest)
    {
    public:

        TEST_METHOD(TestCountDuplicatesInRow)
        {
            int row[] = { 1, 2, 2, 3, 4, };
            int duplicatesCount = CountDuplicatesInRow(row, 6, 0, 1);
            Assert::AreEqual(2, duplicatesCount);  
        }

        TEST_METHOD(TestFirstNonNegativeCol)
        {
            const int rowCount = 3;
            const int colCount = 3;
            int** a = new int* [rowCount];
            for (int i = 0; i < rowCount; i++)
                a[i] = new int[colCount];

            // Заповнюємо масив
            a[0][0] = -1; a[0][1] = -2; a[0][2] = 3;
            a[1][0] = 4; a[1][1] = -5; a[1][2] = 6;
            a[2][0] = 7; a[2][1] = 8; a[2][2] = 9;

            int firstCol = FirstNonNegativeCol(a, rowCount, colCount, 0);
            Assert::AreEqual(2, firstCol);  

            // Звільняємо пам'ять
            for (int i = 0; i < rowCount; i++)
                delete[] a[i];
            delete[] a;
        }
    };
}
