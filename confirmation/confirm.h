#ifndef CONFIRM_H
#define CONFIRM_H
#include <QStandardItemModel>
#include <QWidget>
#include<string>
#include<vector>
#include<iostream>
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
    vector<vector<string*>> couples;
    vector<vector<string*>> couplesDeleted;
    string f1;
    string f2;
    QStandardItemModel* model1;
    QStandardItemModel* model2;
    int index;
};
#endif // CONFIRM_H
