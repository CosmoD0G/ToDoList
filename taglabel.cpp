#include "taglabel.h"
#include "tag.h"

TagLabel::TagLabel(const Tag &tag, QWidget *parent)
    : QLabel(parent)
{
    qDebug() << "Tag label created"<<tag.getTagName();
    this->setText(tag.getTagName());
    setStyleSheet(QString(
                      "QLabel {"
                      "  border-radius: 8px;"
                      "  background-color: hsl(%1, 100%, 80%);"
                      "  border: 3px solid hsl(%1, 100%, 60%);"
                      "  padding: 2px 8px;"
                      "  color: black;"
                      "}"
                      ).arg(tag.getHue()));
}