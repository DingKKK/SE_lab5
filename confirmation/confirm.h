#ifndef CONFIRM_H
#define CONFIRM_H
#include <QStandardItemModel>
#include <QWidget>
#include<string>
#include<vector>
#include <queue>
#include<iostream>
#include"couple.h"
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class confirm; }
QT_END_NAMESPACE

class confirm : public QWidget
{
    Q_OBJECT

public:
    confirm(QWidget *parent = nullptr);
    ~confirm();
    void setColor();
    bool compare(string s1,string s2);
signals:
    void equalSignal();
    void inequalSignal();
    void ambiguousSignal();
    void coupleUpdated();
private slots:
    void on_Confirm_clicked();
    void on_equal_clicked();
    void equalSlot();
    void inequalSlot();
    void ambiguousSlot();
    void on_ambiguous_clicked();
    void on_inequal_clicked();
private:
    Ui::confirm *ui;
//    using couple=Item<string,string,int>;
//    priority_queue<couple, std::vector<couple>, std::less<couple>> coupleWeighted;
    vector<couple> coupleWeighted;
    vector<string> f1compare;
    vector<string> f2compare;
    string f1;
    string f2;
    QStandardItemModel* model1;
    QStandardItemModel* model2;
    int index;
};
#endif // CONFIRM_H
