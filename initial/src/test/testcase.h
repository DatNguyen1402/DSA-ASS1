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
    int quantitiesArray[] = { 50, 30, 20, 10, 15 };
    List1D<int> quantities(quantitiesArray, 5);

    InventoryManager inventory(attributesMatrix, productNames, quantities);
    os << inventory.toString() << endl;

    os << inventory.query("weight", 10, 30, 10, true);
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

    InventoryAttribute attrC1("color", 2);
    InventoryAttribute arrC[] = { attrC1 };
    int numAttrC = sizeof(arrC) / sizeof(arrC[0]);
    List1D<InventoryAttribute> listAttrC(arrC, numAttrC);

    List1D<InventoryAttribute> attributesArray[3] = { listAttrA, listAttrB, listAttrC };
    List2D<InventoryAttribute> attributesMatrix(attributesArray, 3);

    string namesArray[] = { "Product A", "Product B", "Product C" };
    List1D<string> productNames(namesArray, 3);
    int quantitiesArray[] = { 50, 30, 20 };
    List1D<int> quantities(quantitiesArray, 3);

    InventoryManager inventory(attributesMatrix, productNames, quantities);

    InventoryAttribute attrD1("weight", 15);
    InventoryAttribute attrD2("height", 140);
    InventoryAttribute arrD[] = { attrD1, attrD2 };
    int numAttrD = sizeof(arrD) / sizeof(arrD[0]);
    List1D<InventoryAttribute> listAttrD(arrD, numAttrD);
    inventory.addProduct(listAttrD, "Product D", 40);
    os << "\nAfter adding Product D:" << endl;
    os << inventory.toString() << endl;
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

    InventoryAttribute attrC1("color", 2);
    InventoryAttribute arrC[] = { attrC1 };
    int numAttrC = sizeof(arrC) / sizeof(arrC[0]);
    List1D<InventoryAttribute> listAttrC(arrC, numAttrC);

    List1D<InventoryAttribute> attributesArray[3] = { listAttrA, listAttrB, listAttrC };
    List2D<InventoryAttribute> attributesMatrix(attributesArray, 3);

    string namesArray[] = { "Product A", "Product B", "Product C" };
    List1D<string> productNames(namesArray, 3);
    int quantitiesArray[] = { 50, 30, 20 };
    List1D<int> quantities(quantitiesArray, 3);

    InventoryManager inventory(attributesMatrix, productNames, quantities);

    List1D<string> queryResult = inventory.query("weight", 10, 20, 30, false);
    os << "\nQuery result (weight between 10 and 20, quantity >= 30):" << endl;
    os << queryResult << endl;
}

REGISTER_TESTCASE(tc_inventory1006) {
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

    InventoryAttribute attrC1("color", 2);
    InventoryAttribute arrC[] = { attrC1 };
    int numAttrC = sizeof(arrC) / sizeof(arrC[0]);
    List1D<InventoryAttribute> listAttrC(arrC, numAttrC);

    List1D<InventoryAttribute> attributesArray[3] = { listAttrA, listAttrB, listAttrC };
    List2D<InventoryAttribute> attributesMatrix(attributesArray, 3);

    string namesArray[] = { "Product A", "Product B", "Product C" };
    List1D<string> productNames(namesArray, 3);
    int quantitiesArray[] = { 50, 30, 20 };
    List1D<int> quantities(quantitiesArray, 3);

    InventoryManager inventory(attributesMatrix, productNames, quantities);

    inventory.addProduct(listAttrA, "Product A", 20);
    os << "\nAfter adding duplicate of Product A:" << endl;
    os << inventory.toString() << endl;
    inventory.removeDuplicates();
    os << "\nAfter removing duplicates:" << endl;
    os << inventory.toString() << endl;
}

REGISTER_TESTCASE(tc_inventory1007) {
    InventoryAttribute attrA1("weight", 5);
    List1D<InventoryAttribute> listAttrA(&attrA1, 1);
    List2D<InventoryAttribute> attributesMatrix(&listAttrA, 1);
    string names[] = { "Test Product" };
    List1D<string> productNames(names, 1);
    int quantitiesArray[] = { 10 };
    List1D<int> quantities(quantitiesArray, 1);

    InventoryManager inventory(attributesMatrix, productNames, quantities);
    os << "\nSimple inventory test:" << endl;
    os << inventory.toString() << endl;
}

REGISTER_TESTCASE(tc_inventory1008) {
    InventoryAttribute attrA1("weight", 10);
    List1D<InventoryAttribute> listAttrA(&attrA1, 1);
    List2D<InventoryAttribute> attributesMatrix(&listAttrA, 1);
    string names[] = { "Product A" };
    List1D<string> productNames(names, 1);
    int quantitiesArray[] = { 100 };
    List1D<int> quantities(quantitiesArray, 1);

    InventoryManager inventory(attributesMatrix, productNames, quantities);
    inventory.updateQuantity(0, 150);
    os << "\nAfter updating quantity of Product A to 150:" << endl;
    os << inventory.toString() << endl;
}

REGISTER_TESTCASE(tc_inventory1009) {
    InventoryAttribute attrA1("weight", 10);
    InventoryAttribute attrA2("height", 50);
    List1D<InventoryAttribute> listAttrA(&attrA1, 1);
    List1D<InventoryAttribute> listAttrB(&attrA2, 1);
    List1D<InventoryAttribute> attributesArray[2] = { listAttrA, listAttrB };
    List2D<InventoryAttribute> attributesMatrix(attributesArray, 2);

    string namesArray[] = { "Product A", "Product B" };
    List1D<string> productNames(namesArray, 2);
    int quantitiesArray[] = { 25, 35 };
    List1D<int> quantities(quantitiesArray, 2);

    InventoryManager inventory(attributesMatrix, productNames, quantities);
    inventory.removeProduct(1);
    os << "\nAfter removing Product B:" << endl;
    os << inventory.toString() << endl;
}

REGISTER_TESTCASE(tc_inventory1010) {
    InventoryAttribute attrA1("weight", 15);
    InventoryAttribute attrA2("height", 200);
    List1D<InventoryAttribute> listAttrA(&attrA1, 1);
    List1D<InventoryAttribute> listAttrB(&attrA2, 1);
    List1D<InventoryAttribute> attributesArray[2] = { listAttrA, listAttrB };
    List2D<InventoryAttribute> attributesMatrix(attributesArray, 2);

    string namesArray[] = { "Product A", "Product B" };
    List1D<string> productNames(namesArray, 2);
    int quantitiesArray[] = { 50, 60 };
    List1D<int> quantities(quantitiesArray, 2);

    InventoryManager inventory(attributesMatrix, productNames, quantities);
    InventoryManager section1, section2;
    inventory.split(section1, section2, 0.5);
    os << "\nSection 1 (after split):" << endl;
    os << section1.toString() << endl;
    os << "Section 2 (after split):" << endl;
    os << section2.toString() << endl;
}

// 5 testcase mới cho InventoryManager
REGISTER_TESTCASE(tc_inventory1011) {
    InventoryManager inventory;
    InventoryAttribute attrA1("weight", 10);
    List1D<InventoryAttribute> listAttrA(&attrA1, 1);
    inventory.addProduct(listAttrA, "Product A", 100);
    os << "\nAfter adding Product A to empty inventory:" << endl;
    os << inventory.toString() << endl;
    os << "Size: " << inventory.size() << endl;
}

REGISTER_TESTCASE(tc_inventory1012) {
    InventoryAttribute attrA1("weight", 10);
    InventoryAttribute attrA2("height", 156);
    List1D<InventoryAttribute> listAttrA(&attrA1, 1);
    List1D<InventoryAttribute> listAttrB(&attrA2, 1);
    List1D<InventoryAttribute> attributesArray[2] = { listAttrA, listAttrB };
    List2D<InventoryAttribute> matrix1(attributesArray, 2);
    string names1[] = { "Product A", "Product B" };
    List1D<string> productNames1(names1, 2);
    int quantities1[] = { 50, 30 };
    List1D<int> quantities1List(quantities1, 2);

    InventoryAttribute attrC1("color", 2);
    List1D<InventoryAttribute> listAttrC(&attrC1, 1);
    List2D<InventoryAttribute> matrix2(&listAttrC, 1);
    string names2[] = { "Product C" };
    List1D<string> productNames2(names2, 1);
    int quantities2[] = { 20 };
    List1D<int> quantities2List(quantities2, 1);

    InventoryManager inv1(matrix1, productNames1, quantities1List);
    InventoryManager inv2(matrix2, productNames2, quantities2List);
    InventoryManager merged = InventoryManager::merge(inv1, inv2);
    os << "\nMerged inventory:" << endl;
    os << merged.toString() << endl;
}

REGISTER_TESTCASE(tc_inventory1013) {
    InventoryAttribute attrA1("weight", 8);
    InventoryAttribute attrA2("height", 150);
    List1D<InventoryAttribute> listAttrA(&attrA1, 1);
    List1D<InventoryAttribute> listAttrB(&attrA2, 1);
    List1D<InventoryAttribute> attributesArray[2] = { listAttrA, listAttrB };
    List2D<InventoryAttribute> attributesMatrix(attributesArray, 2);

    string namesArray[] = { "Product A", "Product B" };
    List1D<string> productNames(namesArray, 2);
    int quantitiesArray[] = { 40, 60 };
    List1D<int> quantities(quantitiesArray, 2);

    InventoryManager inventory(attributesMatrix, productNames, quantities);
    os << "\nProduct A attributes: " << inventory.getProductAttributes(0).toString() << endl;
    os << "Product A name: " << inventory.getProductName(0) << endl;
    os << "Product A quantity: " << inventory.getProductQuantity(0) << endl;
}

REGISTER_TESTCASE(tc_inventory1014) {
    InventoryAttribute attrA1("weight", 10);
    List1D<InventoryAttribute> listAttrA(&attrA1, 1);
    List2D<InventoryAttribute> attributesMatrix(&listAttrA, 1);
    string names[] = { "Product A" };
    List1D<string> productNames(names, 1);
    int quantitiesArray[] = { 10 };
    List1D<int> quantities(quantitiesArray, 1);

    InventoryManager inventory(attributesMatrix, productNames, quantities);
    InventoryManager copy(inventory);
    os << "\nCopied inventory:" << endl;
    os << copy.toString() << endl;
}

REGISTER_TESTCASE(tc_inventory1015) {
    InventoryAttribute attrA1("weight", 10);
    InventoryAttribute attrA2("height", 156);
    List1D<InventoryAttribute> listAttrA(&attrA1, 1);
    List1D<InventoryAttribute> listAttrB(&attrA2, 1);
    List1D<InventoryAttribute> attributesArray[2] = { listAttrA, listAttrB };
    List2D<InventoryAttribute> attributesMatrix(attributesArray, 2);

    string namesArray[] = { "Product A", "Product B" };
    List1D<string> productNames(namesArray, 2);
    int quantitiesArray[] = { 50, 30 };
    List1D<int> quantities(quantitiesArray, 2);

    InventoryManager inventory(attributesMatrix, productNames, quantities);
    os << "\nAttributes matrix: " << inventory.getAttributesMatrix().toString() << endl;
    os << "Product names: " << inventory.getProductNames().toString() << endl;
    os << "Quantities: " << inventory.getQuantities().toString() << endl;
}

// Testcase cho XArrayList
REGISTER_TESTCASE(tc_xarraylist_001) {
    XArrayList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    os << "Initial XArrayList: " << list.toString() << endl;
    list.removeAt(1);
    os << "After removing index 1: " << list.toString() << endl;
    os << "Size: " << list.size() << endl;
}

REGISTER_TESTCASE(tc_xarraylist_002) {
    XArrayList<int> list;
    for (int i = 0; i < 10; i++)
        list.add(i, i * i);
    for (XArrayList<int>::Iterator it = list.begin(); it != list.end(); it++)
        os << *it << ", found at: " << list.indexOf(*it) << endl;
    os << endl;
    int item = 16;
    os << "lookup for " << item << " found at: " << list.indexOf(item) << endl;
}

REGISTER_TESTCASE(tc_xarraylist_003) {
    XArrayList<Point> list;
    list.add(Point(23.2f, 25.4f));
    list.add(Point(24.6f, 23.1f));
    os << list.toString() << endl;
}

REGISTER_TESTCASE(tc_xarraylist_004) {
    XArrayList<Point> list;
    list.add(Point(23.2f, 25.4f));
    list.add(Point(24.6f, 23.1f));
    int idx1 = list.indexOf(Point(24.6f, 23.1f));
    int idx2 = list.indexOf(Point(24.61f, 23.1f));
    os << "result 1 : " << idx1 << endl;
    os << "result 2 : " << idx2 << endl;
}

REGISTER_TESTCASE(tc_xarraylist_005) {
    XArrayList<Point*> list(&XArrayList<Point*>::free, &Point::pointEQ);
    list.add(new Point(23.2f, 25.4f));
    list.add(new Point(24.6f, 23.1f));
    list.add(new Point(12.5f, 22.3f));
    for (XArrayList<Point*>::Iterator it = list.begin(); it != list.end(); it++)
        os << **it << endl;
    Point* p1 = new Point(24.6f, 23.1f);
    Point* p2 = new Point(124.6f, 23.1f);
    os << *p1 << "=> " << (list.contains(p1) ? "found; " : "not found; ") << " indexOf returns: " << list.indexOf(p1) << endl;
    os << *p2 << "=> " << (list.contains(p2) ? "found; " : "not found; ") << " indexOf returns: " << list.indexOf(p2) << endl;
    delete p1;
    delete p2;
}

REGISTER_TESTCASE(tc_xarraylist_006) {
    XArrayList<int> list;
    list.add(10);
    list.add(20);
    list.add(0, 5);
    os << "After adding 5 at index 0: " << list.toString() << endl;
}

REGISTER_TESTCASE(tc_xarraylist_007) {
    XArrayList<float> list;
    list.add(1.5f);
    list.add(2.5f);
    list.add(3.5f);
    os << "Initial list: " << list.toString() << endl;
    float& item = list.get(1);
    item = 10.0f;
    os << "After modifying item at index 1: " << list.toString() << endl;
}

REGISTER_TESTCASE(tc_xarraylist_008) {
    XArrayList<string> list;
    list.add("Apple");
    list.add("Banana");
    list.add("Cherry");
    os << "Initial list: " << list.toString() << endl;
    list.removeAt(0);
    os << "After removing first item: " << list.toString() << endl;
}

REGISTER_TESTCASE(tc_xarraylist_009) {
    XArrayList<int> list;
    for (int i = 1; i <= 5; i++) list.add(i);
    os << "Initial list: " << list.toString() << endl;
    list.clear();
    os << "After clear: " << list.toString() << endl;
    os << "Size: " << list.size() << endl;
}

REGISTER_TESTCASE(tc_xarraylist_010) {
    XArrayList<Point*> list(&XArrayList<Point*>::free);
    list.add(new Point(1.0f, 2.0f));
    list.add(new Point(3.0f, 4.0f));
    Point* p = new Point(3.0f, 4.0f);
    os << "Contains " << *p << ": " << (list.contains(p) ? "yes" : "no") << endl;
    os << "Index of " << *p << ": " << list.indexOf(p) << endl;
    delete p;
}

// 5 testcase mới cho XArrayList
REGISTER_TESTCASE(tc_xarraylist_011) {
    XArrayList<int> list;
    list.add(5);
    list.add(10);
    int removed = list.removeAt(0);
    os << "Removed item: " << removed << endl;
    os << "List after removal: " << list.toString() << endl;
}

REGISTER_TESTCASE(tc_xarraylist_012) {
    XArrayList<int> list;
    list.add(1);
    list.add(2);
    list.add(1);
    bool removed = list.removeItem(1);
    os << "Remove item 1: " << (removed ? "success" : "failed") << endl;
    os << "List after removal: " << list.toString() << endl;
}

REGISTER_TESTCASE(tc_xarraylist_013) {
    XArrayList<int> list;
    os << "Is empty initially: " << (list.empty() ? "yes" : "no") << endl;
    list.add(42);
    os << "Is empty after adding: " << (list.empty() ? "yes" : "no") << endl;
}

REGISTER_TESTCASE(tc_xarraylist_014) {
    auto intToStr = [](int& i) -> string {
        return to_string(i);
    };
    XArrayList<int> list;
    list.add(10);
    list.add(20);
    list.add(30);
    os << "Custom toString: " << list.toString(intToStr) << endl;
}

REGISTER_TESTCASE(tc_xarraylist_015) {
    XArrayList<Point*> list(&XArrayList<Point*>::free, &Point::pointEQ);
    Point* p1 = new Point(1.0f, 2.0f);
    Point* p2 = new Point(1.0f, 2.0f);
    list.add(p1);
    os << "Contains duplicate " << *p2 << ": " << (list.contains(p2) ? "yes" : "no") << endl;
    os << "Index of " << *p2 << ": " << list.indexOf(p2) << endl;
    delete p2;
}

// Testcase cho DLinkedList
REGISTER_TESTCASE(tc_dlinkedlist_001) {
    DLinkedList<int> list;
    list.add(10);
    list.add(20);
    list.add(30);
    os << "Initial DLinkedList: " << list.toString() << endl;
    list.removeAt(0);
    os << "After removing index 0: " << list.toString() << endl;
    os << "Size: " << list.size() << endl;
}

REGISTER_TESTCASE(tc_dlinkedlist_002) {
    DLinkedList<int> list;
    for (int i = 0; i < 20; i++)
        list.add(i, i * i);
    os << list.toString() << endl;
    for (DLinkedList<int>::Iterator it = list.begin(); it != list.end(); it++)
        os << *it << " ";
    os << endl;
}

REGISTER_TESTCASE(tc_dlinkedlist_003) {
    DLinkedList<Point*> list(&DLinkedList<Point*>::free, &Point::pointEQ);
    list.add(new Point(23.2f, 25.4f));
    list.add(new Point(24.6f, 23.1f));
    list.add(new Point(12.5f, 22.3f));
    for (DLinkedList<Point*>::Iterator it = list.begin(); it != list.end(); it++)
        os << **it << endl;
    Point* p1 = new Point(24.6f, 23.1f);
    Point* p2 = new Point(124.6f, 23.1f);
    os << *p1 << "=> " << (list.contains(p1) ? "found; " : "not found; ") << " indexOf returns: " << list.indexOf(p1) << endl;
    os << *p2 << "=> " << (list.contains(p2) ? "found; " : "not found; ") << " indexOf returns: " << list.indexOf(p2) << endl;
    delete p1;
    delete p2;
}

REGISTER_TESTCASE(tc_dlinkedlist_004) {
    DLinkedList<Point> list;
    list.add(Point(1.5, 3.5));
    list.add(Point(2.5, 4.5));
    list.add(Point(1.6, 3.1));
    os << "test for indexOf: " << endl;
    Point p(1.6, 3.1);
    os << p << " at: " << list.indexOf(p) << endl;
}

REGISTER_TESTCASE(tc_dlinkedlist_005) {
    auto pointComparator = [](Point*& p1, Point*& p2) -> bool {
        return (p1->getX() == p2->getX()) && (p1->getY() == p2->getY());
    };
    auto LpointPtr2Str = [](Point*& ptr) -> string {
        stringstream os;
        os << "(" << ptr->getX() << ", " << ptr->getY() << ")";
        return os.str();
    };
    DLinkedList<Point*> list(&DLinkedList<Point*>::free, pointComparator);
    list.add(new Point(1.5, 3.5));
    list.add(new Point(2.5, 4.5));
    list.add(new Point(1.6, 3.1));
    os << list.toString(LpointPtr2Str) << endl;
    Point* p = new Point(1.6, 3.1);
    os << "test for indexOf: " << endl;
    os << *p << " at: " << list.indexOf(p) << endl;
    delete p;
}

REGISTER_TESTCASE(tc_dlinkedlist_006) {
    DLinkedList<float> list;
    list.add(3.2);
    list.add(5.5);
    os << list.toString() << endl;
    os << "index of 5.5: " << list.indexOf(5.5) << endl;
    os << "index of 15.5: " << list.indexOf(15.5) << endl;
}

REGISTER_TESTCASE(tc_dlinkedlist_007) {
    DLinkedList<int> list;
    for (int i = 0; i < 10; i++)
        list.add(i, i * i);
    os << setw(25) << left << "Original list: " << list.toString() << endl;
    int& item = list.get(5);
    item = 999;
    os << setw(25) << left << "After changing an item: " << list.toString() << endl;
}

REGISTER_TESTCASE(tc_dlinkedlist_008) {
    DLinkedList<string> list;
    list.add("Alpha");
    list.add("Beta");
    list.add("Gamma");
    os << "Initial list: " << list.toString() << endl;
    list.removeAt(1);
    os << "After removing index 1: " << list.toString() << endl;
}

REGISTER_TESTCASE(tc_dlinkedlist_009) {
    DLinkedList<int> list;
    list.add(100);
    list.add(0, 50);
    list.add(2, 150);
    os << "After adding items at specific indices: " << list.toString() << endl;
}

REGISTER_TESTCASE(tc_dlinkedlist_010) {
    DLinkedList<int> list;
    for (int i = 1; i <= 5; i++) list.add(i);
    os << "Initial list: " << list.toString() << endl;
    list.clear();
    os << "After clear: " << list.toString() << endl;
    os << "Size: " << list.size() << endl;
}

// 5 testcase mới cho DLinkedList
REGISTER_TESTCASE(tc_dlinkedlist_011) {
    DLinkedList<int> list;
    list.add(7);
    list.add(14);
    int removed = list.removeAt(1);
    os << "Removed item: " << removed << endl;
    os << "List after removal: " << list.toString() << endl;
}

REGISTER_TESTCASE(tc_dlinkedlist_012) {
    DLinkedList<int> list;
    list.add(3);
    list.add(3);
    list.add(4);
    bool removed = list.removeItem(3);
    os << "Remove item 3: " << (removed ? "success" : "failed") << endl;
    os << "List after removal: " << list.toString() << endl;
}

REGISTER_TESTCASE(tc_dlinkedlist_013) {
    DLinkedList<int> list;
    os << "Is empty initially: " << (list.empty() ? "yes" : "no") << endl;
    list.add(100);
    os << "Is empty after adding: " << (list.empty() ? "yes" : "no") << endl;
}

REGISTER_TESTCASE(tc_dlinkedlist_014) {
    auto intToStr = [](int& i) -> string {
        return to_string(i);
    };
    DLinkedList<int> list;
    list.add(5);
    list.add(10);
    list.add(15);
    os << "Custom toString: " << list.toString(intToStr) << endl;
}

REGISTER_TESTCASE(tc_dlinkedlist_015) {
    DLinkedList<Point*> list(&DLinkedList<Point*>::free, &Point::pointEQ);
    Point* p1 = new Point(2.0f, 3.0f);
    Point* p2 = new Point(2.0f, 3.0f);
    list.add(p1);
    os << "Contains duplicate " << *p2 << ": " << (list.contains(p2) ? "yes" : "no") << endl;
    os << "Index of " << *p2 << ": " << list.indexOf(p2) << endl;
    delete p2;
}


#endif /* TESTCASES_H */