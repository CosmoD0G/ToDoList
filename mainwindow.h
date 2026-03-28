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


private slots:
    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;
    UserData *activeUser;
    QVector<Tag> activeTags;
    bool showCompleted;
};
#endif // MAINWINDOW_H
