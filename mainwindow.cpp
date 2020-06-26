#include "mainwindow.h"
#include "ui_mainwindow.h"


// Adding debug class like console in js
// adding to output text for testing purposes,
// Adding dialog as an input field
#include<QDebug>
#include<QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      mTasks()
{
    ui->setupUi(this);

    // signal and slot connection
    // @params : 1- sender object, 2- pointer to the member signal function
    // 3- reciever object , 4- A pointer to one of the reciever's members solt functions
    connect(ui->addTaskButton, &QPushButton::clicked,
            this, &MainWindow::addTask );
    updateStatus();

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::addTask()
{
    qDebug() << "User clicked on the button";
    bool ok;

    // Displaying the dialog using getText function of QInputDialog class

/*  QString QinputDialog::getText(
        QWidget* parent,
        const QString& title,
        const QString& label,
        QLineEdit::EchoMode mode = QLineEdit::Normal,
        const QString& text = QString(),
        bool* ok = 0, ...)
*/
    QString name = QInputDialog::getText(this,
                                         tr("Add task"),
                                         tr("Task name"),
                                         QLineEdit::EchoMode::Normal,
                                         tr("Untitled task"),
                                         &ok);
    if(ok && !name.isEmpty()){
        qDebug() << "Adding new Task";
        Task * task = new Task(name);

        // Task now emits the removed() signal. This signal has to be consumed by MainWindow:
        connect(task, &Task::removed, this, &MainWindow::removeTask);


        // Update a task
        connect(task, &Task::statusChanged, this, &MainWindow::taskStatusChanged);

        mTasks.append(task);
        ui->tasksLayout->addWidget(task);

        updateStatus();
    }

}

void MainWindow::removeTask(Task *task)
{
    mTasks.removeOne(task); // remove it from the queue
    ui->tasksLayout->removeWidget(task); // remove it from the ui layout
    task->setParent(0); // set the pointer to zero (null maybe)
    delete task; // then safely delete it
}

void MainWindow::taskStatusChanged(Task *task)
{
    updateStatus();
}

void MainWindow::updateStatus()
{
    int completedCount =0;
    for(auto t: mTasks){
        if(t->isCompleted()){
            completedCount++;
        }
    }
    int todoCount = mTasks.size() - completedCount;

    ui->statusLabel->setText(
                QString("Status: %1 todo / %2 completedCount")
                        .arg(todoCount)
                        .arg(completedCount));
}
