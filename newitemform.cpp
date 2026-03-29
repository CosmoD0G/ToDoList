#include "newitemform.h"
#include "itemview.h"
#include "ui_newitemform.h"
#include "userdata.h"
#include <QString>
#include <QDateTime>
#include "mainwindow.h"
#include "QVector.h"
#include "QStandardItem"

NewItemForm::NewItemForm(QWidget *parent, UserData *user, MainWindow *m, ListItem *li, int eI)
    : QDialog(parent)
    , ui(new Ui::NewItemForm)
{
    ui->setupUi(this);
    activeUser = user;
    mainWindow = m;
    //QVector<Tag> selectedTags;

    listPtr = li;
    editIndex = eI;
    qDebug() << "li:" << li;
    qDebug() << "eI:" << eI;
    qDebug() << "user:" << user;
    if (li != nullptr && eI != -1) {
        // EDITING - li is valid, safe to dereference
        modify = true;
        ui->txtInputTitle->setText(li->getTitle());
        ui->txtInputDesc->setText(li->getDescription());
        selectedTags = li->getTags();
        ui->spinPriorityLvl->setValue(li->getPriorityLevel());
        ui->dateEdit->setDate(li->getStartDate());
        ui->dateTimeEdit->setDateTime(li->getDueDate());
    } else {
        // NEW ITEM - li is null, don't touch it
        modify = false;
        ui->dateEdit->setDate(QDate::currentDate());
        ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    }

    // setup tags dropdown
    QStandardItemModel* model = new QStandardItemModel(this);
    model->appendRow(new QStandardItem());
    for (Tag t : user->getTags()) {
        QStandardItem* item = new QStandardItem();
        item->setText(t.getTagName()); // display text
        //item->setForeground(Qt::black); // text color
        item->setBackground(QColor::fromHslF(t.getHue()/360.0,t.getSaturation()/100.0,0.8)); // background color
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

    ListItem newLI = ListItem(title,desc,pLvl,stDate,dueDate,selectedTags,subTasks);

    if (listPtr != nullptr || editIndex != -1) {


            activeUser->setIndex(editIndex, newLI);

    } else {
        activeUser->addListItem(newLI);
    }

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

