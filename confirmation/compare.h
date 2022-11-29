#ifndef COMPARE_H
#define COMPARE_H
#include<string>
#include<iostream>
#include<cstring>
using namespace std;

class compare
{
private:
    string s1;
    string s2;
public:
    compare(string ss1,string ss2);
    bool textComparison();
    bool charJudgement(char c);
};

#endif // COMPARE_H
