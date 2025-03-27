#ifndef TESTCASES_H
#define TESTCASES_H

#include "app/inventory.h" 
#include "list/DLinkedList.h"
#include "list/XArrayList.h"
#include "util/Point.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <functional>
#include <iomanip>

using namespace std;

// Định nghĩa kiểu hàm testcase
using TestCaseFunc = function<void(ostream&)>;

// Lớp quản lý testcase
class TestCaseRegistry {
private:
    static vector<pair<string, TestCaseFunc>>& getRegistry() {
        static vector<pair<string, TestCaseFunc>> registry;
        return registry;
    }

public:
    static void registerTestCase(const string& name, TestCaseFunc func) {
        getRegistry().emplace_back(name, func);
    }

    static const vector<pair<string, TestCaseFunc>>& getTestCases() {
        return getRegistry();
    }
};

// Macro để định nghĩa và đăng ký testcase tự động
#define REGISTER_TESTCASE(name) \
    void name(ostream& os); \
    namespace { \
        struct AutoRegister_##name { \
            AutoRegister_##name() { \
                TestCaseRegistry::registerTestCase(#name, name); \
            } \
        }; \
        AutoRegister_##name autoRegister_##name; \
    } \
    void name(ostream& os)

// Testcase cho InventoryManager

REGISTER_TESTCASE(tc_inventory1001) {
    int arr[] = {1, 2, 3, 4, 5};
    List1D<int> list1D(arr, 5);
    os << list1D.toString() << endl;
}

REGISTER_TESTCASE(tc_inventory1002) {
    int row0[] = {1, 2, 3};
    int row1[] = {4, 5, 6};
    int row2[] = {7, 8, 9};
    List1D<int> arr2D[] = { List1D<int>(row0, 3), List1D<int>(row1, 3), List1D<int>(row2, 3) };
    List2D<int> matrix(arr2D, 3);
    os << matrix.toString() << endl;
}

REGISTER_TESTCASE(tc_inventory1003) {
    InventoryAttribute attrA1("weight", 10);
    InventoryAttribute attrA2("height", 156);
    InventoryAttribute arrA[] = { attrA1, attrA2 };
    int numAttrA = sizeof(arrA) / sizeof(arrA[0]);
    List1D<InventoryAttribute> listAttrA(arrA, numAttrA);

    InventoryAttribute attrB1("weight", 20);
    InventoryAttribute attrB2("depth", 24);
    InventoryAttribute attrB3("height", 100);
    InventoryAttribute arrB[] = { attrB1, attrB2, attrB3 };
    int numAttrB = sizeof(arrB) / sizeof(arrB[0]);
    List1D<InventoryAttribute> listAttrB(arrB, numAttrB);

    InventoryAttribute attrD1("weight", 22);
    InventoryAttribute attrD2("depth", 24);
    InventoryAttribute attrD3("height", 100);
    InventoryAttribute arrD[] = { attrD1, attrD2, attrD3 };
    int numAttrD = sizeof(arrD) / sizeof(arrD[0]);
    List1D<InventoryAttribute> listAttrD(arrD, numAttrD);

    InventoryAttribute attrE1("weight", 22);
    InventoryAttribute attrE2("depth", 24);
    InventoryAttribute attrE3("height", 100);
    InventoryAttribute arrE[] = { attrE1, attrE2, attrE3 };
    int numAttrE = sizeof(arrE) / sizeof(arrD[0]);
    List1D<InventoryAttribute> listAttrE(arrE, numAttrE);

    InventoryAttribute attrC1("color", 2);
    InventoryAttribute arrC[] = { attrC1 };
    int numAttrC = sizeof(arrC) / sizeof(arrC[0]);
    List1D<InventoryAttribute> listAttrC(arrC, numAttrC);

    List1D<InventoryAttribute> attributesArray[5] = { listAttrA, listAttrB, listAttrC, listAttrD, listAttrE };
    List2D<InventoryAttribute> attributesMatrix(attributesArray, 5);

    string namesArray[] = { "Product A", "Product B", "Product C", "Product D", "Product E" };
    List1D<string> productNames(namesArray, 5);
    int quantitiesArray[] = { 50, 30, 20, 10, 10 };
    List1D<int> quantities(quantitiesArray, 5);

    InventoryManager inventory(attributesMatrix, productNames, quantities);
    os << inventory.toString() << endl;

    os << inventory.query("weight", 10, 30, 10, false)<< endl;
}

REGISTER_TESTCASE(tc_inventory1004) {
    InventoryAttribute attrA1("weight", 10);
    InventoryAttribute attrA2("height", 156);
    InventoryAttribute arrA[] = { attrA1, attrA2 };
    int numAttrA = sizeof(arrA) / sizeof(arrA[0]);
    List1D<InventoryAttribute> listAttrA(arrA, numAttrA);

    InventoryAttribute attrB1("weight", 20);
    InventoryAttribute attrB2("depth", 24);
    InventoryAttribute attrB3("height", 100);
    InventoryAttribute arrB[] = { attrB1, attrB2, attrB3 };
    int numAttrB = sizeof(arrB) / sizeof(arrB[0]);
    List1D<InventoryAttribute> listAttrB(arrB, numAttrB);

    InventoryAttribute attrD1("weight", 10);
    InventoryAttribute attrD2("height", 156);

    InventoryAttribute arrD[] = { attrD1, attrD2};
    int numAttrD = sizeof(arrD) / sizeof(arrD[0]);
    List1D<InventoryAttribute> listAttrD(arrD, numAttrD);

    InventoryAttribute attrE1("weight", 10);
    InventoryAttribute attrE2("height", 156);

    InventoryAttribute arrE[] = { attrE1, attrE2 };
    int numAttrE = sizeof(arrE) / sizeof(arrD[0]);
    List1D<InventoryAttribute> listAttrE(arrE, numAttrE);

    InventoryAttribute attrC1("color", 2);
    InventoryAttribute arrC[] = { attrC1 };
    int numAttrC = sizeof(arrC) / sizeof(arrC[0]);
    List1D<InventoryAttribute> listAttrC(arrC, numAttrC);

    List1D<InventoryAttribute> attributesArray[5] = { listAttrA, listAttrB, listAttrC, listAttrD, listAttrE };
    List2D<InventoryAttribute> attributesMatrix(attributesArray, 5);

    string namesArray[] = { "Product A", "Product B", "Product C", "Product A", "Product A" };
    List1D<string> productNames(namesArray, 5);
    int quantitiesArray[] = { 50, 30, 20, 10, 10 };
    List1D<int> quantities(quantitiesArray, 5);

    InventoryManager inventory(attributesMatrix, productNames, quantities);
    os << inventory.toString() << endl;

    inventory.removeDuplicates();
    os << inventory.toString();
}



REGISTER_TESTCASE(tc_inventory1005) {
    InventoryAttribute attrA1("weight", 10);
    InventoryAttribute attrA2("height", 156);
    InventoryAttribute arrA[] = { attrA1, attrA2 };
    int numAttrA = sizeof(arrA) / sizeof(arrA[0]);
    List1D<InventoryAttribute> listAttrA(arrA, numAttrA);

    InventoryAttribute attrB1("weight", 20);
    InventoryAttribute attrB2("depth", 24);
    InventoryAttribute attrB3("height", 100);
    InventoryAttribute arrB[] = { attrB1, attrB2, attrB3 };
    int numAttrB = sizeof(arrB) / sizeof(arrB[0]);
    List1D<InventoryAttribute> listAttrB(arrB, numAttrB);

    InventoryAttribute attrD1("weight", 10);
    InventoryAttribute attrD2("height", 156);

    InventoryAttribute arrD[] = { attrD1, attrD2};
    int numAttrD = sizeof(arrD) / sizeof(arrD[0]);
    List1D<InventoryAttribute> listAttrD(arrD, numAttrD);

    InventoryAttribute attrE1("weight", 10);
    InventoryAttribute attrE2("height", 156);

    InventoryAttribute arrE[] = { attrE1, attrE2 };
    int numAttrE = sizeof(arrE) / sizeof(arrD[0]);
    List1D<InventoryAttribute> listAttrE(arrE, numAttrE);

    InventoryAttribute attrC1("color", 2);
    InventoryAttribute arrC[] = { attrC1 };
    int numAttrC = sizeof(arrC) / sizeof(arrC[0]);
    List1D<InventoryAttribute> listAttrC(arrC, numAttrC);

    List1D<InventoryAttribute> attributesArray1[3] = { listAttrA, listAttrB, listAttrC};
    List1D<InventoryAttribute> attributesArray2[2] = { listAttrD, listAttrE };
    List2D<InventoryAttribute> attributesMatrix1(attributesArray1, 3);
    List2D<InventoryAttribute> attributesMatrix2(attributesArray2, 2);

    string namesArray1[] = { "Product A", "Product B", "Product C" };
    string namesArray2[] = { "Product A", "Product A" };

    List1D<string> productNames1(namesArray1, 3);
    List1D<string> productNames2(namesArray2, 2);

    int quantitiesArray1[] = { 50, 30, 20};
    int quantitiesArray2[] = {  10, 15 };
    List1D<int> quantities1(quantitiesArray1, 3);
    List1D<int> quantities2(quantitiesArray2, 2);

    InventoryManager inventory1(attributesMatrix1, productNames1, quantities1);
    InventoryManager inventory2(attributesMatrix2, productNames2, quantities2);

    os << inventory1.toString() << endl;
    os << inventory2.toString() << endl;

    // inventory.removeDuplicates();
    InventoryManager newinven;
    newinven = InventoryManager::merge(inventory1,inventory2);
    os << newinven.toString();
}
#endif /* TESTCASES_H */