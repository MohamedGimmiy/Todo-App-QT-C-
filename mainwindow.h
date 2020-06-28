#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// Adding vector and task.h
#include<QVector>
#include "task.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateStatus();
// Adding the slot function addTask
public slots:
    void addTask();
    void removeTask(Task* task);
    void taskStatusChanged(Task * task);
    void resetAll();
private:
    Ui::MainWindow *ui;
    QVector<Task*> mTasks;

};
#endif // MAINWINDOW_H
