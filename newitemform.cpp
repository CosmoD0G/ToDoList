#include "newitemform.h"
#include "itemview.h"
#include "ui_newitemform.h"
#include "userdata.h"
#include <QString>
#include <QDateTime>
#include "mainwindow.h"
#include "QVector.h"
#include "QStandardItem"

NewItemForm::NewItemForm(QWidget *parent, UserData *user, MainWindow *m)
    : QDialog(parent)
    , ui(new Ui::NewItemForm)
{
    ui->setupUi(this);
    activeUser = user;
    mainWindow = m;

    // setup default date values
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());

    // setup tags dropdown
    QStandardItemModel* model = new QStandardItemModel(this);
    model->appendRow(new QStandardItem());
    for (Tag t : user->getTags()) {
        QStandardItem* item = new QStandardItem();
        item->setText(t.getTagName()); // display text
        //item->setForeground(Qt::black); // text color
        item->setBackground(QColor::fromHslF(t.getHue()/360.0,1.0,0.8)); // background color
        item->setData(QVariant::fromValue(t),Qt::UserRole);
        model->appendRow(item);
    }
    ui->comboBox->setModel(model);
    ui->tagsDisplay->setText(ItemView::getTagHTML(selectedTags));

}

NewItemForm::~NewItemForm()
{
    delete ui;
}

void NewItemForm::on_buttonBox_accepted() {

    // TAG TESTING

    QString title = ui->txtInputTitle->text();
    QString desc = ui->txtInputDesc->toPlainText();
    int pLvl = ui->spinPriorityLvl->value();
    QDate stDate = ui->dateEdit->date();
    QDateTime dueDate = ui->dateTimeEdit->dateTime();
    activeUser->addListItem(ListItem(title,desc,pLvl,stDate,dueDate,selectedTags,subTasks));
    mainWindow->updateFromUserData();
}




void NewItemForm::on_comboBox_activated(int index) {
    qDebug() << "combobox activated" << index;
    if (index == 0) {
        return;
    }
    Tag selectedData = ui->comboBox->currentData(Qt::UserRole).value<Tag>();
    if (selectedTags.contains(selectedData)) {
        selectedTags.removeOne(selectedData);  // removes first match
    } else {
        selectedTags.append(selectedData);
    }
    ui->tagsDisplay->setText(ItemView::getTagHTML(selectedTags));
}

