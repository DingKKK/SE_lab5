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
    ofstream file1("../confirmation/judgement/equal.csv",ios::out);
    if(!file1) exit(-1);
    file1<<"";
    file1.close();
    ofstream file2("../confirmation/judgement/inequal.csv",ios::out);
    if(!file2) exit(-1);
    file2<<"";
    file2.close();
    ofstream file3("../confirmation/judgement/ambiguous.csv",ios::out);
    if(!file3) exit(-1);
    file3<<"";
    file3.close();
}

confirm::~confirm()
{
    delete ui;
}


void confirm::on_Confirm_clicked()
{
    qDebug()<<"test revert version1";
    f1compare.clear();
    f2compare.clear();
    ui->fN1->clear();
    ui->fN2->clear();
    QString f_n=ui->f_name->text();
    QByteArray folderName=f_n.toLatin1();
    string p=folderName.data();
    p="../confirmation/"+p;
    ifstream equalFile(p+"/output/equal.csv",ios::in);
    if(!equalFile)
    {
        model1 = new QStandardItemModel(this);
        model1->removeRows(0, model1->rowCount());
        model1->setColumnCount(1);
        model1->setHeaderData(0,Qt::Horizontal, "Code");
        model2 = new QStandardItemModel(this);
        model2->removeRows(0, model2->rowCount());
        model2->setColumnCount(1);
        model2->setHeaderData(0,Qt::Horizontal, "Code");
        QMessageBox::about(this, "Tip", "Invalid Folder Name");
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
    }
    else
    {
        char temp[200];
        while(!equalFile.eof())
        {
            equalFile.getline(temp,200);
            char fi1[200];
            char fi2[200];
            int index;
            if(temp[0]=='\0') break;
            for(index=0;temp[index]!=',';++index)
            {
                fi1[index]=temp[index];
            }
            fi1[index]='\0';
            index++;
            int i=0;
            for(;temp[index]!='\0';++index)
            {
                fi2[i]=temp[index];
                ++i;
            }
            fi2[i]='\0';
            string str1=fi1;
            string str2=fi2;
            couple temp(str1,str2);
            coupleWeighted.push_back(temp);
        }
        f1=coupleWeighted[0].getC1();
        f2=coupleWeighted[0].getC2();
        ui->fN1->setText(f1.c_str());
        ui->fN2->setText(f2.c_str());
        index=0;
        model1 = new QStandardItemModel(this);
        model1->removeRows(0, model1->rowCount());
        model1->setColumnCount(1);
        model1->setHeaderData(0,Qt::Horizontal, "Code");
        model2 = new QStandardItemModel(this);
        model2->removeRows(0, model2->rowCount());
        model2->setColumnCount(1);
        model2->setHeaderData(0,Qt::Horizontal, "Code");
        ifstream file1(f1,ios::in);
        char tmp[100];
        int i=0;
        while(!file1.eof())
        {
            file1.getline(tmp,100);
            f1compare.push_back(tmp);
            i++;
        }
        ifstream file2(f2,ios::in);
        int j=0;
        while(!file2.eof())
        {
            file2.getline(tmp,100);
            f2compare.push_back(tmp);
            j++;
        }
        setColor();
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
        index++;
        connect(this,&confirm::coupleUpdated,this,[=](){
            ui->fN1->setText(f1.c_str());
            ui->fN2->setText(f2.c_str());
            f1compare.clear();
            f2compare.clear();
            ifstream file1(f1,ios::in);
            char temp[100];
            int i=0;
            while(!file1.eof())
            {
                file1.getline(temp,100);
                f1compare.push_back(temp);
                i++;
            }

            ifstream file2(f2,ios::in);
            int j=0;
            while(!file2.eof())
            {
                file2.getline(temp,100);
                f2compare.push_back(temp);
                j++;
            }
            setColor();
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
            index++;
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
    qDebug()<<coupleWeighted.size();
    ofstream file("../confirmation/judgement/equal.csv",ios::app);
    if(!file) exit(-1);
    file<<f1<<","<<f2<<endl;
    file.close();
    for(int i=0;i<(int)coupleWeighted.size();++i)
    {
        if(coupleWeighted[i].getC1()==f1&&coupleWeighted[i].getC2()==f2)
        {
            coupleWeighted.erase(coupleWeighted.begin()+i);//deleted last judged couple
        }
        else
        {
            if(coupleWeighted[i].getC1()!=f1&&coupleWeighted[i].getC2()!=f1&&coupleWeighted[i].getC1()!=f2&&coupleWeighted[i].getC2()!=f2)
            {
                coupleWeighted[i].setWeight(coupleWeighted[i].getWeight()+1);
            }
        }
    }
    couple c;
    c.priorityQueue(coupleWeighted);
    if(coupleWeighted.size()>0)
    {
        f1=coupleWeighted[0].getC1();
        f2=coupleWeighted[0].getC2();
        emit this->coupleUpdated();
    }
    else
    {
        QMessageBox::about(this, "Tip", "The End");
    }
}

void confirm::on_ambiguous_clicked()
{
    emit this->ambiguousSignal();
}

void confirm::ambiguousSlot()
{
    ofstream file("../confirmation/judgement/ambiguous.csv",ios::app);
    if(!file) exit(-1);
    file<<f1<<","<<f2<<endl;
    file.close();
    for(int i=0;i<(int)coupleWeighted.size();++i)
    {
        if(coupleWeighted[i].getC1()==f1&&coupleWeighted[i].getC2()==f2)
        {
            coupleWeighted.erase(coupleWeighted.begin()+i);//deleted last judged couple
        }
        if(coupleWeighted[i].getC1()==f1||coupleWeighted[i].getC2()==f1||coupleWeighted[i].getC1()==f2||coupleWeighted[i].getC2()==f2)
        {
            coupleWeighted[i].setWeight(coupleWeighted[i].getWeight()+1);
        }
    }
    couple c;
    c.priorityQueue(coupleWeighted);
    if(coupleWeighted.size()>0)
    {
        f1=coupleWeighted[0].getC1();
        f2=coupleWeighted[0].getC2();
        emit this->coupleUpdated();
    }
    else
        QMessageBox::about(this, "Tip", "The End");
}

void confirm::on_inequal_clicked()
{
    emit this->inequalSignal();
}
void confirm::inequalSlot()
{
    ofstream file("../confirmation/judgement/inequal.csv",ios::app);
    if(!file) exit(-1);
    file<<f1<<","<<f2<<endl;
    file.close();
    for(int i=0;i<(int)coupleWeighted.size();++i)
    {
        if(coupleWeighted[i].getC1()==f1&&coupleWeighted[i].getC2()==f2)
        {
            coupleWeighted.erase(coupleWeighted.begin()+i);//deleted last judged couple
        }
        if(coupleWeighted[i].getC1()==f1||coupleWeighted[i].getC2()==f1||coupleWeighted[i].getC1()==f2||coupleWeighted[i].getC2()==f2)
        {
            coupleWeighted[i].setWeight(coupleWeighted[i].getWeight()+1);
        }
    }
    couple c;
    c.priorityQueue(coupleWeighted);
    if(coupleWeighted.size()>0)
    {
        f1=coupleWeighted[0].getC1();
        f2=coupleWeighted[0].getC2();
        emit this->coupleUpdated();
    }
    else
        QMessageBox::about(this, "Tip", "The End");
}
void confirm::setColor()
{
    model1->removeRows(0, model1->rowCount());
    model2->removeRows(0, model2->rowCount());
    int lineI=0;
    int lineJ=0;
    int flag;
    int* color1=new int[f1compare.size()];
    int* color2=new int[f2compare.size()];
    vector<int> same1;
    vector<int> same2;
    for(int i=0;i<(int)f1compare.size();++i)
    {
        flag=0;
        for(int j=0;j<(int)f2compare.size();++j)
        {
            if(compare(f1compare[i],f2compare[j]))
            {
                flag=1;
                color1[i]=0;
                color2[j]=0;
                same1.push_back(i);
                same2.push_back(j);
            }
        }
        if(flag==0)
        {
            color1[i]=1;
        }
    }
    for(int i=0;i<(int)f2compare.size();++i)
    {
        flag=0;
        for(int j=0;j<(int)f1compare.size();++j)
        {
            if(compare(f2compare[i],f1compare[j]))
            {
                flag=1;
                color2[i]=0;
                color1[j]=0;
            }
        }
        if(flag==0)
        {
            color2[i]=1;
        }
    }
    int x=0,y=0;
    while(same1.size()>0)
    {
        qDebug()<<same1[0]<<" "<<same2[0];
        while(x<same1[0]&&y<same2[0])
        {
            model1->setItem(lineI,0,new QStandardItem(f1compare[x].c_str()));
            model1->item(lineI, 0)->setForeground(QBrush(QColor(0, 255, 0)));
            model1->item(lineI, 0)->setBackground(QBrush(QColor(245, 255, 250)));
            model2->setItem(lineJ,0,new QStandardItem(f2compare[y].c_str()));
            model2->item(lineJ, 0)->setForeground(QBrush(QColor(255, 0, 0)));
            model2->item(lineJ, 0)->setBackground(QBrush(QColor(255, 228, 225)));
            lineI++;
            lineJ++;
            x++;
            y++;
        }
        for(;x<same1[0];++x)
        {
            model1->setItem(lineI,0,new QStandardItem(f1compare[x].c_str()));
            model1->item(lineI, 0)->setForeground(QBrush(QColor(0, 255, 0)));
            model1->item(lineI, 0)->setBackground(QBrush(QColor(245, 255, 250)));
            model2->setItem(lineJ,0,new QStandardItem("//////////////////////////////////////////////////////////////////////////////////"));
            model2->item(lineJ, 0)->setForeground(QBrush(QColor(105, 105, 105)));
            model2->item(lineJ, 0)->setBackground(QBrush(QColor(220, 220, 220)));
            lineI++;
            lineJ++;
        }
        for(;y<same2[0];++y)
        {
            model2->setItem(lineJ,0,new QStandardItem(f2compare[y].c_str()));
            model2->item(lineJ, 0)->setForeground(QBrush(QColor(255, 0, 0)));
            model2->item(lineJ, 0)->setBackground(QBrush(QColor(255, 228, 225)));
            model1->setItem(lineI,0,new QStandardItem("//////////////////////////////////////////////////////////////////////////////////"));
            model1->item(lineI, 0)->setForeground(QBrush(QColor(105, 105, 105)));
            model1->item(lineI, 0)->setBackground(QBrush(QColor(220, 220, 220)));
            lineI++;
            lineJ++;
        }
        model1->setItem(lineI,0,new QStandardItem(f1compare[x].c_str()));
        model2->setItem(lineJ,0,new QStandardItem(f2compare[y].c_str()));
        lineI++;
        lineJ++;
        x++;
        y++;
        same1.erase(same1.begin());
        same2.erase(same2.begin());
    }
    while(x<f1compare.size())
    {
        model1->setItem(lineI,0,new QStandardItem(f1compare[x].c_str()));
        model1->item(lineI, 0)->setForeground(QBrush(QColor(0, 255, 0)));
        model1->item(lineI, 0)->setBackground(QBrush(QColor(245, 255, 250)));
        x++;
        lineI++;
    }
    while(y<f2compare.size())
    {
        model2->setItem(lineJ,0,new QStandardItem(f2compare[y].c_str()));
        model2->item(lineJ, 0)->setForeground(QBrush(QColor(255, 0, 0)));
        model2->item(lineJ, 0)->setBackground(QBrush(QColor(255, 228, 225)));
        y++;
        lineJ++;
    }

//    while(i<(int)f1compare.size()&&j<(int)f2compare.size())
//    {
//        if(compare(f1compare[i],f2compare[j]))
//        {
//            while(lineI<lineJ)
//            {
//                model1->setItem(lineI,0,new QStandardItem("//////////////////////////////////////////////////////////////////////////////////"));
//                model1->item(lineI, 0)->setBackground(QBrush(QColor(169, 169, 169)));
//                lineI++;
//            }
//            while(lineJ<lineI)
//            {
//                model2->setItem(lineJ,0,new QStandardItem("//////////////////////////////////////////////////////////////////////////////////"));
//                model2->item(lineJ, 0)->setBackground(QBrush(QColor(169, 169, 169)));
//                lineJ++;
//            }
//            model1->setItem(lineI,0,new QStandardItem(f1compare[i].c_str()));
//            model2->setItem(lineJ,0,new QStandardItem(f2compare[j].c_str()));
//            lineI++;
//            lineJ++;
//            i++;
//            j++;
//        }
//        else
//        {
//            model2->setItem(lineJ,0,new QStandardItem(f2compare[j].c_str()));
//            model2->item(lineJ, 0)->setForeground(QBrush(QColor(255, 0, 0)));
//            model2->item(lineJ, 0)->setBackground(QBrush(QColor(255, 228, 225)));
//            lineJ++;
//            j++;
//        }
//    }
//    for(;i<(int)f1compare.size();++i)
//    {
//        model1->setItem(lineI,0,new QStandardItem(f1compare[i].c_str()));
//        model1->item(lineI, 0)->setForeground(QBrush(QColor(0, 255, 0)));
//        model1->item(lineI, 0)->setBackground(QBrush(QColor(245, 255, 250)));
//        lineI++;
//    }
//    while(lineJ<lineI)
//    {
//        model2->setItem(lineJ,0,new QStandardItem("//////////////////////////////////////////////////////////////////////////////////"));
//        model2->item(lineJ, 0)->setBackground(QBrush(QColor(169, 169, 169)));
//        lineJ++;
//    }
}
bool judge(char c)
{
    if(c<33||c>126)
        return true;
    else return false;
}
bool confirm::compare(string s1,string s2)
{
    char* c1=new char[s1.length()];
    char* c2=new char[s2.length()];
    int i=0,j=0;
    while(i<s1.length())
    {
        if(!judge(s1[i]))
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
        if(!judge(s2[i]))
        {
            c2[j]=s2[i];
            j++;
        }
        i++;
    }
    c2[j]='\0';
    qDebug()<<c1;
    qDebug()<<c2;
    if(strcmp(c1,c2)==0)
        return true;
    else
        return false;
}
