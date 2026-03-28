#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "newitemform.h"
#include "userdata.h"
#include "itemview.h"
#include <qboxlayout.h>
#include "listitem.h"
#include "tag.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);

    activeUser = new UserData();

    activeUser->addTag(*new Tag("MATH 122",50));
    activeUser->addTag(*new Tag("DIGM 105",4));
    activeUser->addTag(*new Tag("CIVC 101",20));




}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    NewItemForm *newItemWindow = new NewItemForm(this, activeUser,this);
    newItemWindow->show();
}


void MainWindow::updateFromUserData() {
    qDebug() << "activeUser =" << activeUser;

    // Delete the old container widget if one exists
    QWidget *oldWidget = ui->scrollArea->takeWidget();
    if (oldWidget) delete oldWidget;

    QWidget *container = new QWidget();
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->setSizeConstraint(QLayout::SetMinimumSize); // critical
    //layout->addStretch(1);
    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(4);
    layout->setContentsMargins(4, 4, 4, 4);
    const QVector<ListItem>& itemList = activeUser->getListItems();
    int insertIndex = 0;
    for (const ListItem &l : itemList) {
        if (this->hasActiveTag(l)) {
            ItemView *item = new ItemView(this, &l);
            //layout->addWidget(item);
            layout->insertWidget(insertIndex++, item);
        }
    }

    ui->scrollArea->setWidget(container);
    ui->scrollArea->setWidgetResizable(true);
    container->show(); // force the container and children to become visible
    container->adjustSize();        // force container to recalculate its size
    ui->scrollArea->update();       // repaint the scroll area
}



bool MainWindow::hasActiveTag(ListItem l) {
    if (this->activeTags.size() == 0) {
        return true;
    }
    for (Tag t : l.getTags()) {
        for (Tag v : this->activeTags) {
            if (t.getTagName() == v.getTagName()) {
                return true;
            }
        }
    }
    return false;
}



