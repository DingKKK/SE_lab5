#ifndef COUPLE_H
#define COUPLE_H
#include<string>
#include<vector>
#include <queue>
#include<iostream>
using namespace std;
class couple
{
private:
    string c1;
    string c2;
    int weight;
public:
    couple()=default;
    couple(string c,string d){c1=c;c2=d;weight=0;}
    string getC1(){return c1;}
    string getC2(){return c2;}
    int getWeight(){return weight;}
    void setC1(string c){c1=c;}
    void setC2(string c){c2=c;}
    void setWeight(int w){weight=w;}
    void priorityQueue(vector<couple>& coupleWeighted);
};

#endif // COUPLE_H
