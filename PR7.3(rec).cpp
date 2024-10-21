#include <iostream>
#include <iomanip>
using namespace std;

void InputRow(int** a, const int rowNo, const int colCount, int colNo);
void InputRows(int** a, const int rowCount, const int colCount, int rowNo);
void PrintRow(int** a, const int rowNo, const int colCount, int colNo);
void PrintRows(int** a, const int rowCount, const int colCount, int rowNo);
int CountDuplicatesInRow(int* row, const int colCount, int index1, int index2);
void SortByRowDuplicates(int** a, const int rowCount, const int colCount, int index1, int index2);
int FirstNonNegativeCol(int** a, const int rowCount, const int colCount, int colNo); // ѕараметри без значенн€ за замовчуванн€м
int FirstNonNegativeColHelper(int** a, const int rowCount, const int colCount, int colNo, int rowNo); // ƒодаткова функц≥€

int main() {
    int rowCount, colCount;
    cout << "rowCount = "; cin >> rowCount;
    cout << "colCount = "; cin >> colCount;

    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    InputRows(a, rowCount, colCount, 0);
    PrintRows(a, rowCount, colCount, 0);

    // ¬пор€дкувати р€дки за к≥льк≥стю однакових елемент≥в
    SortByRowDuplicates(a, rowCount, colCount, 0, rowCount - 1);
    cout << "After sorting by duplicate elements:" << endl;
    PrintRows(a, rowCount, colCount, 0);

    // «найти перший стовпець без в≥д'Їмних елемент≥в
    int firstCol = FirstNonNegativeCol(a, rowCount, colCount, 0); 
    if (firstCol == -1)
        cout << "No column without negative elements found." << endl;
    else
        cout << "First column without negative elements: " << firstCol + 1 << endl;

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

void InputRow(int** a, const int rowNo, const int colCount, int colNo) {
    cout << "a[" << rowNo << "][" << colNo << "] = ";
    cin >> a[rowNo][colNo];
    if (colNo < colCount - 1)
        InputRow(a, rowNo, colCount, colNo + 1);
}

void InputRows(int** a, const int rowCount, const int colCount, int rowNo) {
    if (rowNo < rowCount) {
        InputRow(a, rowNo, colCount, 0);
        InputRows(a, rowCount, colCount, rowNo + 1);
    }
}

void PrintRow(int** a, const int rowNo, const int colCount, int colNo) {
    cout << setw(4) << a[rowNo][colNo];
    if (colNo < colCount - 1)
        PrintRow(a, rowNo, colCount, colNo + 1);
    else
        cout << endl;
}

void PrintRows(int** a, const int rowCount, const int colCount, int rowNo) {
    if (rowNo < rowCount) {
        PrintRow(a, rowNo, colCount, 0);
        PrintRows(a, rowCount, colCount, rowNo + 1);
    }
}

int CountDuplicatesInRow(int* row, const int colCount, int index1, int index2) {
    if (index1 >= colCount)
        return 0;

    if (row[index1] == row[index2]) {
        return 1 + CountDuplicatesInRow(row, colCount, index1 + 1, index2);
    }
    else {
        return CountDuplicatesInRow(row, colCount, index1 + 1, index2);
    }
}

void SortByRowDuplicates(int** a, const int rowCount, const int colCount, int index1, int index2) {
    if (index1 >= index2)
        return;

    if (CountDuplicatesInRow(a[index1], colCount, 0, 1) > CountDuplicatesInRow(a[index2], colCount, 0, 1)) {
        int* temp = a[index1];
        a[index1] = a[index2];
        a[index2] = temp;
    }
    SortByRowDuplicates(a, rowCount, colCount, index1, index2 - 1);
    SortByRowDuplicates(a, rowCount, colCount, index1 + 1, index2);
}

int FirstNonNegativeCol(int** a, const int rowCount, const int colCount, int colNo) {
    return FirstNonNegativeColHelper(a, rowCount, colCount, colNo, 0);
}

int FirstNonNegativeColHelper(int** a, const int rowCount, const int colCount, int colNo, int rowNo) {
    if (colNo >= colCount) // якщо перев≥рен≥ вс≥ стовпц≥
        return -1;

    if (rowNo < rowCount) { // ѕерев≥р€Їмо вс≥ р€дки в поточному стовпц≥
        if (a[rowNo][colNo] < 0) { // якщо в≥д'Їмний елемент
            return FirstNonNegativeColHelper(a, rowCount, colCount, colNo + 1, 0); // ѕереходимо до наступного стовпц€
        }
        else {
            return FirstNonNegativeColHelper(a, rowCount, colCount, colNo, rowNo + 1); // ѕереходимо до наступного р€дка
        }
    }

    // якщо вс≥ елементи в стовпц≥ нев≥д'Їмн≥
    return colNo; // ѕовертаЇмо номер стовпц€, €кщо в≥н нев≥д'Їмний
}
