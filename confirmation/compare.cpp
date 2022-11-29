#include "compare.h"

compare::compare(string ss1, string ss2)
{
    s1=ss1;
    s2=ss2;
}
bool compare::charJudgement(char c)
{
    if(c<33||c>126)
        return true;
    else
        return false;
}
bool compare::textComparison()
{
    char* c1=new char[s1.length()];
    char* c2=new char[s2.length()];
    int i=0,j=0;
    while(i<s1.length())
    {
        if(!charJudgement(s1[i]))
        {
            c1[j]=s1[i];
            j++;
        }
        i++;
    }
    c1[j]='\0';
    i=0;j=0;
    while(i<s2.length())
    {
        if(!charJudgement(s2[i]))
        {
            c2[j]=s2[i];
            j++;
        }
        i++;
    }
    c2[j]='\0';
    if(strcmp(c1,c2)==0)
        return true;
    else
        return false;
}
