#include "tageditor.h"
#include "taglabel.h"
#include "ui_tageditor.h"
#include <qlabel.h>
#include <qlayoutitem.h>
#include <QVBoxLayout>
#include "QMessageBox"
#include "QStandardItem"
#include "QStandardItemModel"

TagEditor::TagEditor(QWidget *parent, UserData *user)
    : QDialog(parent)
    , ui(new Ui::TagEditor)
{
    ui->setupUi(this);
    activeUser = user;
    Tag selectedTag = Tag("",0,100);
    updateDropDown();
}

TagEditor::~TagEditor()
{
    delete ui;
}

void TagEditor::updateExampleTag(Tag t) {
    QLayout *layout = ui->frame->layout();
    // Clear old widgets
    QLayoutItem *item;

    if (!layout) {
        layout = new QVBoxLayout();
        ui->frame->setLayout(layout);
    }
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    // add new tag
    layout->addWidget(new TagLabel(t));
}

void TagEditor::updateDropDown() {
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
    //ui->tagsDisplay->setText(ItemView::getTagHTML(selectedTags));
}

void TagEditor::confirmNewTag(Tag t) {
    if (activeUser->addTag(t)) {
        updateDropDown();
    } else {
        QMessageBox::information(this, "ERROR", "ERROR: Tag already exists");
    }
}

void TagEditor::on_txtInputName_textChanged(const QString &arg1) {
    selectedTag.setTagName(ui->txtInputName->text());
    updateExampleTag(selectedTag);
}

void TagEditor::on_sliderHue_sliderMoved(int position) {
    selectedTag.setHue(position);
    updateExampleTag(selectedTag);
}

void TagEditor::on_sliderSatur_sliderMoved(int position) {
    selectedTag.setSaturation(position);
    updateExampleTag(selectedTag);
}


void TagEditor::on_comboBox_activated(int index) {
    qDebug() << "combobox activated" << index;
    if (index == 0) {
        return;
    }
    Tag selectedData = ui->comboBox->currentData(Qt::UserRole).value<Tag>();
    selectedTag = selectedData;
    updateExampleTag(selectedTag);
    //ui->tagsDisplay->setText(ItemView::getTagHTML(selectedTags));
}


void TagEditor::on_pushButton_clicked()
{
    confirmNewTag(selectedTag);
}


void TagEditor::on_pushButton_2_clicked()
{
    activeUser->removeTag(selectedTag);
    updateDropDown();
    selectedTag = Tag("",0,100);
    updateExampleTag(selectedTag);
}

