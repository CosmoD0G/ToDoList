#ifndef TAG_H
#define TAG_H

#include <qcolor.h>
#include <qjsonobject.h>
#include <QMetaType>

class Tag
{
public:
    Tag() : name(""), hue(0) {}  // default constructor required by QVariant
    Tag(QString t, int h);

    QString getTagName() const;
    void setTagName();
    int getHue() const;
    QColor getColor();
    void setColor(QColor c);
    QJsonObject toJson() const;
    QString getBasicHTML() const;

    bool operator==(const Tag& other) const {
        return name == other.name && hue == other.hue;
    }

private:
    QString name;
    int hue;

};

Q_DECLARE_METATYPE(Tag)  // add this outside the class

#endif // TAG_H