#ifndef NEWITEMFORM_H
#define NEWITEMFORM_H

#include <QDialog>
#include "mainwindow.h"
#include "userdata.h"

namespace Ui {
class NewItemForm;
}

class NewItemForm : public QDialog
{
    Q_OBJECT

public:
    explicit NewItemForm(QWidget *parent = nullptr, UserData *activeUser =  nullptr, MainWindow *m = nullptr, ListItem *li = nullptr, int editIndex = -1);
    ~NewItemForm();


private slots:
    void on_buttonBox_accepted();

    void on_comboBox_activated(int index);

private:
    Ui::NewItemForm *ui;
    UserData *activeUser;
    MainWindow *mainWindow;
    QVector<Tag> selectedTags;
    QVector<SubTask> subTasks;
    bool modify;
    ListItem *listPtr;
    int editIndex;
};

#endif // NEWITEMFORM_H
