#include "CString.hpp"
#include "CString0.hpp"
#include "CString1.hpp"
#include "factory.hpp"
#include "CString0factory.hpp"
#include "CString1factory.hpp"
#include "functions.hpp"

CString0 operator+(const CString& first, const CString& second)
{
    CString0 res;
    res.len = first.len + second.len;
    res.str.reserve(res.len);
    chrono::time_point<std::chrono::system_clock> start = chrono::system_clock::now();
    #pragma omp parallel for
    for (int i = 0; i < res.len; i++){
        if (i < first.len){
           res.str.push_back(first.str[i]);
        }
        if (i >= first.len){
          res.str.push_back(second.str[i - first.len]);
        }
    }
    chrono::time_point<std::chrono::system_clock> end = chrono::system_clock::now();
    double elapsed_ms = (chrono::duration_cast<chrono::milliseconds>(end - start).count());
    cout << "Operator '+' time is: " << elapsed_ms/1000 << " sec" << endl;
    return res;
}

void Test1()
{
    vector<CString*> v;
    CString0Factory* CString0_factory = new CString0Factory;
    CString1Factory* CString1_factory = new CString1Factory;

    ifstream file;
    Line line;
    int p = 0;
    string stroka;
    file.open("/Users/Misha/Task3-sem4/data.txt");
    if (!file)
    {
        cout << "Failed to open file (functions.cpp: row 27)" << endl;
    }
    //file.open(R"(полный путь к файлу)");
    while(getline(file,stroka))
    {
          if(stroka[0] == '0')
          {
            line.I = 0;
          }
          else
          {
            line.I = 1;
          }
          
          for (int i = 2; i < stroka.length(); i++)
          {
            if (stroka[i] == ' ')
            {
                p = i + 1;
                break;
            }
            line.Name += stroka[i];
          }
          
          for (int i = p; i < stroka.length(); i++)
          {
            line.Data += stroka[i];
          }
          
          if (line.I == 0)
          {
            v.push_back(CString0_factory->createString(line));
          }
          else if (line.I == 1)
          {
            v.push_back(CString1_factory->createString(line));
          }
          
          p = 0;
          line.Data = "";
          line.Name = "";
    }
    file.close();

    for(int i = 0; i < v.size(); i++)
    {
        v[i]->output();
    }

    cout << "\nTEST1: DONE. CHECK OUTPUT FILES" << endl;
}

void Test2()
{
    CString1 str = "abc";
    str.output("test.txt");
    
    cout << "TEST2: DONE. CHECK OUTPUT FILE" << endl;
}

void OpenMP_Test()
{
    CString1 a("");
    CString0 b("");
    CString0 c, c1;

    int N = 1000000000;
    cout << "Wait, please..." << endl;
    
    a.str.reserve(N);
    b.str.reserve(N);
    for (int i = 0; i < N; i++){
        a.str.push_back('a');
        b.str.push_back('b');
    }
    a.len = b.len = N;

    c = a + b;

    if ((c).str == a.str + b.str)
    {
        cout << "OpenMP_Test: PASSED!\n" << endl;
    }
    else
    {
        cout << "OpenMP_Test: FAILED!\n" << endl;
    }
}

void Test3()
{
    // CString0 c;
    string d = "Goodbye, world!";
    CString0 c = d;
    
    //c = d;
    
    if (c.str == "Goodbye, world!")
    {
        cout << "TEST3: PASSED!" << endl;
    }
    else
    {
        cout << "TEST3: FAILED!" << endl;
    }
}
