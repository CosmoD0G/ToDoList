#include "userdata.h"
#include "listitem.h"
#include <qcontainerfwd.h>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

UserData::UserData() {

}

// adds an item to the QVector
void UserData::addListItem(ListItem l) {
    items.append(l);

}

// returns a QVector of the items the user has
const QVector<ListItem>& UserData::getListItems() {
    qDebug()<<"Attempted to return QVector of user list items";
    return items;
}

// checks to see if the user has a tag
bool UserData::userTagExists(Tag t) {
    for (Tag i : getTags()) {
        if (t.getTagName() == i.getTagName()) {
            return true;
        }
    }
    return false;
}

QVector<Tag> UserData::getTags() {
    return tags;
}

// get JSON file path to write/read from
QString UserData::filePath() {
    // Gets (and creates if needed) the app data directory
    QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dir); // ensure directory exists
    qDebug() << "Dir: "<<dir;
    return dir + "/userdata.json";
}

bool UserData::saveToFile() {
    QJsonObject json;
    // save every list item to JSON array
    QJsonArray listItems;
    for (ListItem l : items) {
        QJsonObject jo = l.toJson();
        listItems.append(jo);
    }

    // save every tag to JSON array
    QJsonArray tagItems;
    for (Tag t : tags) {
        qDebug() << "Saving Tag: "<<t.toJson();
        QJsonObject jo = t.toJson();
        tagItems.append(jo);
    }

    // save JSON to File
    QFile file(filePath());
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Could not open file for writing:" << file.errorString();
        return false;
    }
    json["list items"] = listItems;
    json["tags"] = tagItems;
    qDebug() << "JSON: "<<json;
    file.write(QJsonDocument(json).toJson());
    return true;
}

// fill in data by reading JSON file
bool UserData::loadFromFile() {
    QFile file(filePath());
    if (!file.exists()) return false; // first run, no data yet

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open file for reading:" << file.errorString();
        return false;
    }

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &err);
    if (err.error != QJsonParseError::NoError || !doc.isObject()) {
        qWarning() << "JSON parse error:" << err.errorString();
        return false;
    }

    // SAVE JSON TO VARIABLES //
    QJsonObject json = doc.object();

    // Tags
    QJsonArray tagArray = json["tags"].toArray();
    QVector<Tag> newTags;
    for (const QJsonValue& val : tagArray) {
        QJsonObject obj = val.toObject();
        newTags.append(Tag(obj["name"].toString(""), obj["hue"].toInt(0), obj["saturation"].toInt(100)));
    }
    tags = newTags;

    // List Items
    QJsonArray listArray = json["list items"].toArray();
    QVector<ListItem> newListItems;
    for (const QJsonValue& val : listArray) {
        QJsonObject obj = val.toObject();
        QDate start = QDate::fromString(obj["startDate"].toString(), Qt::ISODate);
        QDateTime due = QDateTime::fromString(obj["dueDate"].toString(), Qt::ISODateWithMs);
        //tags
        QVector<Tag> itemTags;
        for (const QJsonValue& tagVal : obj["tags"].toArray()) {
            itemTags.append(Tag(tagVal.toString(), getHueFromTagName(tagVal.toString())));
        }
        //subtasks
        QVector<SubTask> itemSubs;
        for (const QJsonValue& subVal : obj["subItems"].toArray()) {
            QJsonObject subObj = subVal.toObject();
            itemSubs.append(SubTask(subObj["title"].toString(""),subObj["completed"].toBool(false)));
        }

        newListItems.append(ListItem(obj["title"].toString(""), obj["desc"].toString(""), obj["priority"].toInt(1), start, due, itemTags, itemSubs));
    }
    items = newListItems;

    return true;
}

bool UserData::addTag(Tag t) {
    if (userTagExists(t)) {
        return false;
    } else {
        tags.append(t);
        return true;
    }

}

int UserData::getHueFromTagName(QString tagName) {
    for (Tag t : tags) {
        if (t.getTagName() == tagName) {
            return t.getHue();
        }
    }
    return 0;
}

int UserData::getSaturationFromTagName(QString tagName) {
    for (Tag t : tags) {
        if (t.getTagName() == tagName) {
            return t.getSaturation();
        }
    }
    return 0;
}

void UserData::removeListItem(ListItem l) {
    qDebug()<<"function called";
    for (int i=0; i < items.size(); i++) {
        qDebug()<<"looping through items: "<<i;
        if (items[i]==l) {
            items.removeAt(i);
            return;
        }
    }

}

void UserData::setIndex(int index, ListItem l) {
    items[index] = l;
}

void UserData::removeTag(Tag t) {
    for (int i=0; i < tags.size(); i++) {
        if (tags[i] == t) {
            tags.removeAt(i);
            return;
        }
    }
}

void UserData::setCompleted(ListItem l, bool completed) {
    for (int i = 0; i < items.size(); i++) {
        if (items[i] == l) {
            items[i].setCompleted(completed);
            return;
        }
    }
}






