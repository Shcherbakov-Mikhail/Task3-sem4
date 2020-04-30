#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "omp.h"
#include <chrono>
using namespace std;

typedef struct Line
{
    int I;
    string Name;
    string Data;
}Line;

class CString
{
    public:
        int len;
        string str;
        Line line;
        string fname;
        bool isFabric;
        CString();
        CString(string str);
        CString(Line line);
        CString(const CString& second);
        virtual ~CString();
        virtual void output(const char *FileName = NULL) = 0;
        CString& operator=(const CString& second);
};
