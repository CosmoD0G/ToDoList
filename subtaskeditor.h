#ifndef SUBTASKEDITOR_H
#define SUBTASKEDITOR_H

#include <QDialog>

namespace Ui {
class SubTaskEditor;
}

class SubTaskEditor : public QDialog
{
    Q_OBJECT

public:
    explicit SubTaskEditor(QWidget *parent = nullptr);
    ~SubTaskEditor();

private:
    Ui::SubTaskEditor *ui;
};

#endif // SUBTASKEDITOR_H
