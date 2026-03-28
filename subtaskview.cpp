#include "subtaskview.h"
#include "ui_subtaskview.h"

SubTaskView::SubTaskView(QWidget *parent, SubTask *s)
    : QWidget(parent)
    , ui(new Ui::SubTaskView)
{
    ui->setupUi(this);

    ui->txtTitle->setText(s->getTitle());

}

SubTaskView::~SubTaskView()
{
    delete ui;
}
