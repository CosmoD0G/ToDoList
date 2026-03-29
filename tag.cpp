#include "tag.h"
#include <qjsonobject.h>
#include <QColor>

Tag::Tag(QString t, int h, int s) {
    name = t;
    hue = h;
    saturation = s;
}

QString Tag::getTagName() const{
    return name;
}

QJsonObject Tag::toJson() const {
    QJsonObject obj;
    obj["name"]  = name;
    obj["hue"] = hue;
    obj["saturation"] = saturation;
    return obj;
}

int Tag::getHue() const {
    return hue;
}

void Tag::setHue(int h) {
    hue = h;
}

int Tag::getSaturation() const {
    return saturation;
}

void Tag::setSaturation(int s) {
    saturation = s;
}

void Tag::setTagName(QString n) {
    name = n;
}

QString Tag::getBasicHTML() const {
    return "<span style='background-color: hsl("+QString::number(this->getHue())+", "+QString::number(this->getSaturation())+"%, 80%);'>"+this->getTagName()+"</span>";
}
