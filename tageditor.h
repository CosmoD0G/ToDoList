#ifndef TAGEDITOR_H
#define TAGEDITOR_H

#include "tag.h"
#include "userdata.h"
#include <QDialog>

namespace Ui {
class TagEditor;
}

class TagEditor : public QDialog
{
    Q_OBJECT

public:
    explicit TagEditor(QWidget *parent = nullptr, UserData *user = nullptr);
    ~TagEditor();
    void updateExampleTag(Tag t);
    void confirmNewTag(Tag t);
    void updateDropDown();

private slots:
    void on_sliderHue_sliderMoved(int position);

    void on_txtInputName_textChanged(const QString &arg1);

    void on_sliderSatur_sliderMoved(int position);

    void on_comboBox_activated(int index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::TagEditor *ui;
    Tag selectedTag;
    QVector<Tag> tags;
    UserData *activeUser;
};

#endif // TAGEDITOR_H
