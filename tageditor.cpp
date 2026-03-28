#include "tageditor.h"
#include "ui_tageditor.h"

TagEditor::TagEditor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TagEditor)
{
    ui->setupUi(this);
}

TagEditor::~TagEditor()
{
    delete ui;
}
