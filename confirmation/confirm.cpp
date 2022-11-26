#include "confirm.h"
#include "ui_confirm.h"
#include <dirent.h>
#include<iostream>
#include<vector>
#include<cstring>
#include<fstream>
#include<QDebug>
#include<QMessageBox>
#include"confirm.h"
using namespace std;
confirm::confirm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::confirm)
{
    ui->setupUi(this);

}

confirm::~confirm()
{
    delete ui;
}


void confirm::on_Confirm_clicked()
{
    QString f_n=ui->f_name->text();
    QByteArray folderName=f_n.toLatin1();
    string p=folderName.data();
    p="/home/njucs/SE_lab5/confirmation/"+p;
    ifstream equalFile(p+"/output/equal.csv",ios::in);
    if(!equalFile)
    {
        QMessageBox::about(this, "Tip", "Invalid Folder Name");
    }
    else
    {
        vector<vector<string*>> couples;
        char temp[200];
        while(!equalFile.eof())
        {
            equalFile.getline(temp,200);
            char f1[200];
            char f2[200];
            int index;
            for(index=0;temp[index]!=',';++index)
            {
                f1[index]=temp[index];
            }
            f1[index]='\0';
            index++;
            int i=0;
            for(;temp[index]!='\0';++index)
            {
                f2[i]=temp[index];
                ++i;
            }
            f2[i]='\0';
            string* str1=new string;*str1=f1;
            string* str2=new string;*str2=f2;
            vector<string*> temp;
            temp.push_back(str1);
            temp.push_back(str2);
            couples.push_back(temp);
        }
        f1=*couples[0][0];
        f2=*couples[0][1];
        ui->fN1->setText(f1.c_str());
        ui->fN2->setText(f2.c_str());
        index=0;
        model1 = new QStandardItemModel(this);
        model1->setColumnCount(1);
        model1->setHeaderData(0,Qt::Horizontal, "Code");
        model2 = new QStandardItemModel(this);
        model2->setColumnCount(1);
        model2->setHeaderData(0,Qt::Horizontal, "Code");
        ifstream file1(f1,ios::in);
        char tmp[100];
        int i=0;
        while(!file1.eof())
        {
            file1.getline(tmp,100);
            model1->setItem(i,0,new QStandardItem(tmp));
            i++;
        }
        ifstream file2(f2,ios::in);
        int j=0;
        while(!file2.eof())
        {
            file2.getline(tmp,100);
            model2->setItem(j,0,new QStandardItem(tmp));
            j++;
        }
        ui->f1->setModel(model1);
        ui->f1->setAutoScroll(true);
        ui->f1->setShowGrid(true);
        ui->f1->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->f1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->f2->setModel(model2);
        ui->f2->setAutoScroll(true);
        ui->f2->setShowGrid(true);
        ui->f2->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->f2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        connect(this,&confirm::coupleUpdated,this,[=](){
            ifstream file1(f1,ios::in);
            char temp[100];
            int i=0;
            while(!file1.eof())
            {
                file1.getline(temp,100);
                model1->setItem(i,0,new QStandardItem(temp));
                i++;
            }
            ifstream file2(f2,ios::in);
            int j=0;
            while(!file2.eof())
            {
                file2.getline(temp,100);
                model2->setItem(j,0,new QStandardItem(temp));
                j++;
            }
        });
        connect(this,SIGNAL(equalSignal()),this, SLOT(equalSlot()));
        connect(this,SIGNAL(ambiguousSignal()),this, SLOT(ambiguousSlot()));
        connect(this,SIGNAL(inequalSignal()),this, SLOT(inequalSlot()));
    }
}

void confirm::on_equal_clicked()
{
    emit this->equalSignal();
}
void confirm::equalSlot()
{
    for(int i=index;i<(int)couples.size();++i)
    {
        if(*couples[i][0]==f1||*couples[i][1]==f1||*couples[i][0]==f2||*couples[i][1]==f2)
        {
            couplesDeleted.push_back(couples[i]);
            couples.erase(couples.begin()+i);
        }
    }
    if(couples.size()>0)
    {
        f1=*couples[0][0];
        f2=*couples[0][1];
        emit this->coupleUpdated();
    }
    else
    {
        for(int i=0;i<(int)couplesDeleted.size();++i)
        {
            f1=*couples[i][0];
            f2=*couples[i][1];
            emit this->coupleUpdated();
        }
    }
}

void confirm::on_ambiguous_clicked()
{
    emit this->ambiguousSignal();
}

void confirm::ambiguousSlot()
{
    for(int i=index;i<(int)couples.size();++i)
    {
        if(*couples[i][0]==f1||*couples[i][1]==f1||*couples[i][0]==f2||*couples[i][1]==f2)
        {
            f1=*couples[i][0];
            f2=*couples[i][1];
            emit this->coupleUpdated();
        }
    }
}

void confirm::on_inequal_clicked()
{
    emit this->inequalSignal();
}
void confirm::inequalSlot()
{
    for(int i=index;i<(int)couples.size();++i)
    {
        if(*couples[i][0]==f1||*couples[i][1]==f1||*couples[i][0]==f2||*couples[i][1]==f2)
        {
            f1=*couples[i][0];
            f2=*couples[i][1];
            emit this->coupleUpdated();
        }
    }
}
