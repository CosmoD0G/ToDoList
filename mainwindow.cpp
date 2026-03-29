#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "newitemform.h"
#include "userdata.h"
#include "itemview.h"
#include <qboxlayout.h>
#include "listitem.h"
#include "tag.h"
#include "tageditor.h"
#include "QStandardItem"
#include "QStandardItemModel"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);

    activeUser = new UserData();
    activeUser->loadFromFile();

    showNotStarted = ui->checkNotStartable->isChecked();
    showCompleted = ui->checkCompleted->isChecked();

    updateFromUserData();
    updateDropDown();



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    NewItemForm *newItemWindow = new NewItemForm(this, activeUser,this, nullptr, -1);
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


    QVector<ListItem> itemList = sortByDueDate(activeUser->getListItems());

    sortByDueDate(itemList);
    int insertIndex = 0;
    int i = 0;
    for (const ListItem &l : itemList) {
        if (this->hasActiveTag(l)) {
            ItemView *item = new ItemView(this, &l, this, i);
            layout->insertWidget(insertIndex++, item);
        }
        i++;
    }



    ui->scrollArea->setWidget(container);
    ui->scrollArea->setWidgetResizable(true);
    container->show(); // force the container and children to become visible
    container->adjustSize();        // force container to recalculate its size
    ui->scrollArea->update();       // repaint the scroll area
    activeUser->saveToFile();
}


// check to see if a tag can be added
// 1- if no filters, add all items, if item has tag that matches tag filters
// 2- check if completed items are allowed
// 3- check if not-started items are allowed
bool MainWindow::hasActiveTag(ListItem l) {
    bool matchesTag = false;
    bool matchesCompleted = false;
    bool matchesNonStarted = false;

    // 1- check tags
    if (this->activeTags.size() == 0) {
        matchesTag = true;
    }
    for (Tag t : l.getTags()) {
        for (Tag v : this->activeTags) {
            if (t.getTagName() == v.getTagName()) {
                matchesTag = true;
                break;
            }
        }
    }

    // 2- check completed
    if ((l.getCompleted() == false) || (showCompleted)) {
        matchesCompleted = true;
    }

    // 3- check non-started
    if ((l.getCanStart())|| (showNotStarted)) {
        matchesNonStarted = true;
    }
    return matchesTag && matchesCompleted && matchesNonStarted;
}

UserData *MainWindow::getActiveUser() {
    return activeUser;
}




void MainWindow::on_pushButton_2_clicked()
{
    TagEditor *e = new TagEditor(this,activeUser);
    e->show();
}

QVector<ListItem> MainWindow::sortByDueDate(QVector<ListItem> items) {
    std::sort(items.begin(), items.end(), [](const ListItem &a, const ListItem &b) {
        return a.getDueDate() < b.getDueDate();
    });
    return items;
}

void MainWindow::updateDropDown() {
    QStandardItemModel* model = new QStandardItemModel(this);
    model->appendRow(new QStandardItem());
    for (Tag t : activeUser->getTags()) {
        QStandardItem* item = new QStandardItem();
        item->setText(t.getTagName()); // display text
        //item->setForeground(Qt::black); // text color
        item->setBackground(QColor::fromHslF(t.getHue()/360.0,t.getSaturation()/100.0,0.8)); // background color
        item->setData(QVariant::fromValue(t),Qt::UserRole);
        model->appendRow(item);
    }
    ui->comboBox->setModel(model);
    ui->labelTags->setText(ItemView::getTagHTML(activeTags));
}


void MainWindow::on_comboBox_activated(int index) {
    qDebug() << "combobox activated" << index;
    if (index == 0) {
        return;
    }
    Tag selectedData = ui->comboBox->currentData(Qt::UserRole).value<Tag>();
    if (activeTags.contains(selectedData)) {
        activeTags.removeOne(selectedData);  // removes first match
    } else {
        activeTags.append(selectedData);
    }
    ui->labelTags->setText(ItemView::getTagHTML(activeTags));
    updateFromUserData();
}


void MainWindow::on_checkNotStartable_clicked(bool checked)
{
    showNotStarted = checked;
    updateFromUserData();
}


void MainWindow::on_checkCompleted_clicked(bool checked)
{
    showCompleted = checked;
    updateFromUserData();
}

