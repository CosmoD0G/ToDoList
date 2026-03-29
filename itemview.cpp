#include "itemview.h"
#include "listitem.h"
#include "mainwindow.h"
#include "subtaskview.h"
#include "ui_itemview.h"
#include "qboxlayout.h"
#include "newitemform.h"
#include "QEasingCurve.h"
#include "qpropertyanimation.h"
#include "taglabel.h"
#include "QPainter.h"
#include "QMessageBox"
#include "QThread"

ItemView::ItemView(QWidget *parent, const ListItem *l, MainWindow *m, int dataIndex)
    : QWidget(parent)
    , ui(new Ui::ItemView) {
    ui->setupUi(this);

    mw = m;
    listVar = *l;
    // set layout variables for ItemView widget
    // In ItemView constructor
    //setMinimumHeight(0);  // let the layout determine minimum, not a fixed value
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    // In your ItemView widget's constructor

    isExpanded = false;
    // Collapsible bottom panel
    bottomPanel = new QWidget(this);
    bottomPanel->setMinimumHeight(0);
    bottomPanel->setMaximumHeight(0);  // start collapsed
    bottomPanel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    bottomPanel->setBackgroundRole(QPalette::AlternateBase);
    // In ItemView constructor, after setupUi:
    ui->frame->setMaximumWidth(300);

    QVBoxLayout *panelLayout = new QVBoxLayout(bottomPanel);
    for (SubTask st : listVar.getSubTasks()) {
       panelLayout->addWidget(new SubTaskView(this,&st));
    }





    ui->frame->setFrameShape(QFrame::NoFrame);
    // ... populate bottomPanel with your widgets ...
    ui->vertLayoutHeader->addWidget(bottomPanel, 0);  // stretch = 0, fixed height
    ui->horiLayoutTLabels->parentWidget()->setFixedWidth(300);
    ui->txtTitle->setText(l->getTitle());
    ui->txtDue->setText(dueDateFormatting(l->getDueDate()));
    ui->txtStart->setText(startDateFormatting(l->getStartDate()));
    //ui->txtTag->setText(getTagHTML(l->getTags()));
    addTagLabels(*l);

    if (listVar.getCompleted()) {
        ui->checkBox->setChecked(true);
        paintGradient(QColor(99,117,90), QColor(125,125,125));
    } else {
        ui->checkBox->setChecked(false);
        paintGradient(QColor(214,214,214), QColor(237,237,237));
    }

    qDebug() << this->size();
}

ItemView::~ItemView()
{
    delete ui;
}

void ItemView::paintGradient(QColor c1, QColor c2) {
    gradL = c1;
    gradR = c2;
    update();  // schedules a repaint — paintEvent will fire shortly after
}

void ItemView::paintEvent(QPaintEvent *event) {
    //header
    qDebug() << "painting "<<gradL<<" "<<gradR;
    QLinearGradient gradient(0, 0, 450, 76);
    gradient.setColorAt(0.0, gradL);
    gradient.setColorAt(1.0,gradR);

    QPainter painter(this);
    painter.setBrush(QBrush(gradient));
    painter.setPen(Qt::NoPen);   // removes the default black border around the rect
    painter.drawRect(0, 0, 450, 76);
}

void ItemView::animateGradient(int duration, QColor L1, QColor L2, QColor R1, QColor R2) {

}

void ItemView::toggleBottomPanel() {
    qDebug() << this->size();
    int panelHeight = bottomPanel->sizeHint().height();

    auto *anim = new QPropertyAnimation(bottomPanel, "maximumHeight");
    anim->setDuration(200);
    anim->setEasingCurve(QEasingCurve::InOutQuad);

    if (isExpanded) {
        anim->setStartValue(panelHeight);
        anim->setEndValue(0);
    } else {
        anim->setStartValue(0);
        anim->setEndValue(panelHeight);
    }

    isExpanded = !isExpanded;

    // Force the parent chain to reflow on every animation frame
    connect(anim, &QPropertyAnimation::valueChanged, this, [this](const QVariant &) {
        adjustSize();
        if (parentWidget()) parentWidget()->adjustSize();
    });

    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void ItemView::addTagLabels(ListItem l) {
    for (Tag t : l.getTags()) {
        ui->horiLayoutTLabels->addWidget(new TagLabel(t,this));
    }
    ui->horiLayoutTLabels->parentWidget()->setMaximumWidth(300);
}

void ItemView::on_toolButton_2_clicked() {
    toggleBottomPanel();
}

QString ItemView::getTagHTML(QVector<Tag> ts) {
    QString html = "";
    for (Tag t : ts) {
        qDebug() << t.getTagName()<<t.getHue();
        html += "<span style='border-radius: 8px; "
                "background-color: hsl("+QString::number(t.getHue())+", 100%, 80%); "
                "border: 3px solid hsl("+QString::number(t.getHue())+", 100%, 60%); "
                "padding: 2px 8px 2px 8px; "
                "font-family: \'Helvetica Neue\', Helvetica, Arial, sans-serif; "
                "color: black;'>"
                +t.getTagName()+
                "</span>";
    }
    return html;
}

QString ItemView::dueDateFormatting(QDateTime dt) {
    QString color;
    QString days;
    int daysInt = QDateTime::currentDateTime().secsTo(dt)/86400;
    if (daysInt == 1) {
        days = "1 day";
    } else {
        days = QString::number(daysInt) + " days";
    }
    int daysThreshold = 1;
    if (daysInt <= daysThreshold) {
        color = "red";
    } else {
        color = "black";
    }
    return "<span style='color: black;'>"+dt.toString("M/dd h:mm ap")+"</span><span style='color: "+color+";'> " + days + "</span>";
}

QString ItemView::startDateFormatting(QDate d) {
    QDate today = QDate::currentDate();
    int daysUntil = today.daysTo(d);
    if (daysUntil <= 0) {
        return "<span style='color: green;'>go ahead</span>";
    } else {
        return "<span style='color: black;'> Not yet ("+d.toString("MM/dd")+")</span>";
    }
}

void ItemView::on_toolButton_clicked() {

}


void ItemView::on_deleteButton_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Item?", "Are you sure you want to delete this item? This cannot be undone",QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        qDebug() << "reply yes confirmed";
        qDebug() << "listVar:" << &listVar;
        qDebug() << "activeUser:" << mw->getActiveUser();
        mw->getActiveUser()->removeListItem(listVar);
    } else {
        // no
    }
    mw->updateFromUserData();
}


void ItemView::on_checkBox_clicked(bool checked) {
    if (checked) {
        paintGradient(QColor(99,117,90), QColor(125,125,125));
        update();
        QThread::msleep(750);
        mw->getActiveUser()->setCompleted(listVar, true);
        mw->updateFromUserData();
    } else {
        paintGradient(QColor(214,214,214), QColor(237,237,237));
        update();
        mw->getActiveUser()->setCompleted(listVar, false);
        mw->updateFromUserData();
    }
}

