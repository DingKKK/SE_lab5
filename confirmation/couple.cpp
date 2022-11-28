#include "couple.h"
void couple::priorityQueue(vector<couple>& coupleWeighted)
{
    int n=coupleWeighted.size();
    for(int i=0;i<n-1;++i)
    {
        for(int j=0;j<n-1-i;++j)
        {
            if(coupleWeighted[j].weight<coupleWeighted[j+1].weight)
            {
                couple temp(coupleWeighted[j].getC1(),coupleWeighted[j].getC2());
                temp.setWeight(coupleWeighted[j].getWeight());
                coupleWeighted[j].setWeight(coupleWeighted[j+1].getWeight());
                coupleWeighted[j].setC1(coupleWeighted[j+1].getC1());
                coupleWeighted[j].setC2(coupleWeighted[j+1].getC2());
                coupleWeighted[j+1].setWeight(temp.getWeight());
                coupleWeighted[j+1].setC1(temp.getC1());
                coupleWeighted[j+1].setC2(temp.getC2());
            }
        }
    }
}
