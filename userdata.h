#ifndef USERDATA_H
#define USERDATA_H

#include "tag.h"
#include "listitem.h"
#include <qcontainerfwd.h>
class UserData
{
public:
    UserData();
    void addListItem(ListItem l);
    const QVector<ListItem>& getListItems();
    QVector<Tag> getTags();
    bool userTagExists(Tag t);
    bool saveToFile();
    bool loadFromFile();
    bool addTag(Tag t);
    int getHueFromTagName(QString tagName);
    int getSaturationFromTagName(QString tagName);
    void removeListItem(ListItem l);
    void setIndex(int index, ListItem l);
    void removeTag(Tag t);
    void setCompleted(ListItem l, bool completed);

private:
    QString username;
    QVector<Tag> tags;
    QVector<ListItem> items;
    QString filePath();
};

#endif // USERDATA_H
