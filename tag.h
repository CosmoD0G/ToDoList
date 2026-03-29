#ifndef TAG_H
#define TAG_H

#include <qcolor.h>
#include <qjsonobject.h>
#include <QMetaType>

class Tag
{
public:
    Tag() : name(""), hue(0) {}  // default constructor required by QVariant
    Tag(QString t, int h, int s = 100);

    QString getTagName() const;
    void setTagName(QString n);
    int getHue() const;
    void setHue(int h);
    int getSaturation() const;
    void setSaturation(int s);
    QJsonObject toJson() const;
    QString getBasicHTML() const;

    bool operator==(const Tag& other) const {
        return name == other.name && hue == other.hue;
    }

private:
    QString name;
    int hue;
    int saturation;

};

Q_DECLARE_METATYPE(Tag)  // add this outside the class

#endif // TAG_H