#ifndef ITEMVIEW_H
#define ITEMVIEW_H

#include "listitem.h"
#include <QWidget>

namespace Ui {
class ItemView;
}

class ItemView : public QWidget
{
    Q_OBJECT

public:
    explicit ItemView(QWidget *parent = nullptr, const ListItem *l = nullptr);
    ~ItemView();
    void toggleBottomPanel();
    QString dueDateFormatting(QDateTime dt);
    QString startDateFormatting(QDate d);
    static QString getTagHTML(QVector<Tag> t);
    void addTagLabels(ListItem l);
    void paintGradient(QColor c1, QColor c2);
    void animateGradient(int duration, QColor L1, QColor L2, QColor R1, QColor R2);

private slots:

    void on_toolButton_2_clicked();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::ItemView *ui;
    QWidget *bottomPanel;
    bool isExpanded;

    QColor gradL = Qt::white;
    QColor gradR = Qt::white;
};

#endif // ITEMVIEW_H
