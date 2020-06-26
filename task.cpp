#include "task.h"
#include "ui_task.h"
// Adding
#include<QInputDialog>
#include<QDebug>
Task::Task(const QString& name,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Task)
{
    ui->setupUi(this);
    setName(name);

    // Signal, Slot to rename a task
    connect(ui->editButton, &QPushButton::clicked, this, &Task::rename);

    // Signal, Slot to remove a task
    // C++11 lamdas
    auto prettyName = [](const QString& taskname) -> QString{
        return "-------------" + taskname.toUpper();
    };

    connect(ui->removeButton, &QPushButton::clicked, [this, name, prettyName](){
        qDebug() << "Trying to remove" << prettyName(name);
        emit removed(this);
    });
    // a lambda is the construction of a closure capable of capturing variables in its scope.
    //Emit is a Qt macro that will immediately trigger the connected slot with what we passed in a parameter.
    /*Qt 5 accepts a lambda instead of a slot in a connect, and both syntaxes can be used.*/
    connect(ui->checkbox, &QCheckBox::toggled,
            this, &Task::checked);
}

Task::~Task()
{
    delete ui;
}

void Task::setName(const QString &name)
{
    ui->checkbox->setText(name);
}

QString Task::name() const
{
    return ui->checkbox->text();
}

bool Task::isCompleted() const
{
    return ui->checkbox->isChecked();
}

void Task::rename()
{
    bool ok;
    QString value = QInputDialog::getText(this,
                                          tr("Edit Task"),
                                          tr("Task name"),
                                          QLineEdit::Normal,
                                          this->name(),
                                          &ok);

    if(ok && !value.isEmpty()){
        setName(value);
    }
}

//1. when user check the box
void Task::checked(bool checked)
{
    QFont font(ui->checkbox->font());
    font.setStrikeOut(checked);
    ui->checkbox->setFont(font);

    //2. we emit a signal status changed
    emit statusChanged(this);
}
