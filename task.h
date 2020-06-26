#ifndef TASK_H
#define TASK_H

#include <QWidget>
#include<QString>
namespace Ui {
class Task;
}

class Task : public QWidget
{
    Q_OBJECT

public:
    explicit Task(const QString& name,QWidget *parent = nullptr);
    ~Task();
    void setName(const QString& name);
    QString name()const;
    bool isCompleted() const;

// Added to rename a task when creating it
public slots:
    void rename();
    void checked(bool checked);
    //Added to notify slot to remove a task
    //There is no function body for signals
signals:
    void removed(Task * task);
    void statusChanged(Task * task);
private:
    Ui::Task *ui;
};

#endif // TASK_H
