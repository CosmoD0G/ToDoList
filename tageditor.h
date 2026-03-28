#ifndef TAGEDITOR_H
#define TAGEDITOR_H

#include <QDialog>

namespace Ui {
class TagEditor;
}

class TagEditor : public QDialog
{
    Q_OBJECT

public:
    explicit TagEditor(QWidget *parent = nullptr);
    ~TagEditor();

private:
    Ui::TagEditor *ui;
};

#endif // TAGEDITOR_H
