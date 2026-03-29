#include "taglabel.h"
#include "tag.h"

TagLabel::TagLabel(const Tag &tag, QWidget *parent)
    : QLabel(parent)
{
    setText(tag.getTagName());
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    adjustSize();

    setStyleSheet(QString(
                      "QLabel {"
                      "  border-radius: 8px;"
                      "  background-color: hsl(%1, %2%, 80%);"
                      "  border: 3px solid hsl(%1, %2%, 60%);"
                      "  padding: 2px 8px;"
                      "  color: black;"
                      "}"
                      ).arg(tag.getHue()).arg(tag.getSaturation()));
}