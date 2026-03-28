#ifndef SUBTASKVIEW_H
#define SUBTASKVIEW_H

#include "subtask.h"
#include <QWidget>

namespace Ui {
class SubTaskView;
}

class SubTaskView : public QWidget
{
    Q_OBJECT

public:
    explicit SubTaskView(QWidget *parent = nullptr, SubTask *s = nullptr);
    ~SubTaskView();

private:
    Ui::SubTaskView *ui;
};

#endif // SUBTASKVIEW_H
