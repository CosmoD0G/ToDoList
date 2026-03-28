#include "tag.h"
#include <qjsonobject.h>
#include <QColor>

Tag::Tag(QString t, int h) {
    name = t;
    hue = h;
}

QString Tag::getTagName() const{
    return name;
}

QJsonObject Tag::toJson() const {
    QJsonObject obj;
    obj["name"]  = name;
    obj["hue"] = hue;
    return obj;
}

int Tag::getHue() const {
    return hue;
}

QString Tag::getBasicHTML() const {
    return "<span style='background-color: hsl("+QString::number(this->getHue())+", 100%, 80%);'>"+this->getTagName()+"</span>";
}
