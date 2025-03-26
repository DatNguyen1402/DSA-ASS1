#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include "test/testcase.h"

using namespace std;

void runAllTestCases(ostream& os) {
    const auto& testCases = TestCaseRegistry::getTestCases();
    for (const auto& [name, func] : testCases) {
        os << "Running " << name << ":\n";
        func(os);
        os << "End of " << name << "\n\n";
    }
}

void generateExpectedOutput(const string& filename) {
    ofstream outFile(filename, ios::out);
    if (!outFile.is_open()) {
        cerr << "Error: Could not open " << filename << " for writing!" << endl;
        return;
    }
    runAllTestCases(outFile);
    outFile.close();
    cout << "Generated expected output in " << filename << endl;
}

void generateActualOutput(const string& filename) {
    ofstream outFile(filename, ios::out);
    if (!outFile.is_open()) {
        cerr << "Error: Could not open " << filename << " for writing!" << endl;
        return;
    }
    runAllTestCases(outFile);
    outFile.close();
    cout << "Generated actual output in " << filename << endl;
}

vector<string> compareFiles(const string& file1, const string& file2) {
    ifstream f1(file1), f2(file2);
    if (!f1.is_open() || !f2.is_open()) {
        cerr << "Error opening files for comparison!" << endl;
        return {"Error opening files"};
    }

    vector<string> failedTests;
    string line1, line2;
    string currentTestCase;
    regex testCaseStart("^Running (tc_[a-z]+_[0-9]+):$");
    smatch match;

    while (getline(f1, line1) && getline(f2, line2)) {
        if (regex_match(line1, match, testCaseStart)) {
            currentTestCase = match[1];
        }

        if (line1 != line2) {
            if (!currentTestCase.empty() && 
                find(failedTests.begin(), failedTests.end(), currentTestCase) == failedTests.end()) {
                failedTests.push_back(currentTestCase);
            }
            cout << "Mismatch in " << (currentTestCase.empty() ? "unknown section" : currentTestCase) 
                 << ":\n  " << file1 << ": " << line1 << "\n  " << file2 << ": " << line2 << "\n";
        }
    }

    if (getline(f1, line1) || getline(f2, line2)) {
        cout << "Files have different lengths!\n";
        if (!currentTestCase.empty() && 
            find(failedTests.begin(), failedTests.end(), currentTestCase) == failedTests.end()) {
            failedTests.push_back(currentTestCase);
        }
    }

    f1.close();
    f2.close();
    return failedTests;
}

int main() {
    // generateExpectedOutput("expectoutput.txt");
    generateActualOutput("output.txt");
    cout << "\nComparing expectoutput.txt and output.txt...\n";
    vector<string> failedTests = compareFiles("expectoutput.txt", "output.txt");
    
    if (failedTests.empty()) {
        cout << "All test cases match expected output!" << endl;
    } else {
        cout << "The following test cases differ from expected output:\n";
        for (const auto& test : failedTests) {
            cout << "  - " << test << "\n";
        }
    }

    return 0;
}