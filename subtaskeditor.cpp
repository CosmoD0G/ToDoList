#include "subtaskeditor.h"
#include "ui_subtaskeditor.h"

SubTaskEditor::SubTaskEditor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SubTaskEditor)
{
    ui->setupUi(this);

}

SubTaskEditor::~SubTaskEditor()
{
    delete ui;
}
