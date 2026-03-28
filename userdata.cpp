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
        QJsonObject jo = t.toJson();
        tagItems.append(jo);
    }

    // save JSON to File
    QFile file(filePath());
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Could not open file for writing:" << file.errorString();
        return false;
    }

    file.write(QJsonDocument(json).toJson());
    return true;


}

// get JSON file path to write/read from
QString UserData::filePath() {
    // Gets (and creates if needed) the app data directory
    QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dir); // ensure directory exists
    qDebug() << "Dir: "<<dir;
    return dir + "/userdata.json";
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

    QJsonObject json = doc.object();

}

void UserData::addTag(Tag t) {
    tags.append(t);
}




