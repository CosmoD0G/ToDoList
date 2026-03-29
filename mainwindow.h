#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "userdata.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void updateFromUserData();
    bool hasActiveTag(ListItem l);
    UserData* getActiveUser();
    QVector<ListItem> sortByDueDate(QVector<ListItem> items);
    void updateDropDown();


private slots:
    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

    void on_comboBox_activated(int index);

    void on_checkNotStartable_clicked(bool checked);

    void on_checkCompleted_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    UserData *activeUser;
    QVector<Tag> activeTags;
    bool showCompleted;
    bool showNotStarted;
};
#endif // MAINWINDOW_H
