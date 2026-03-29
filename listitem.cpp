#include "listitem.h"
#include <QString>
#include <QVector>
#include <QJsonArray>
#include <QJsonObject>


ListItem::ListItem(QString t, QString d, int p, QDate s, QDateTime due, QVector<Tag> tg, QVector<SubTask> sbt) {
    title = t;
    description = d;
    priorityLevel = p;
    startDate = s;
    dueDate = due;
    tags = tg;
    subTasks = sbt;
}

ListItem::ListItem() {

}

QString ListItem::getDescription() const {
    return description;
}

int ListItem::getPriorityLevel() const {
    return priorityLevel;
}

QVector<Tag> ListItem::getTags() const{
    return tags;
}

QString ListItem::getTitle() const {
    return title;
}

QDateTime ListItem::getDueDate() const{
    return dueDate;
}

QDate ListItem::getStartDate() const {
    return startDate;
}

bool ListItem::getCanStart() {
    return getStartDate() <= QDate::currentDate();
}

bool ListItem::getCompleted() {
    return completed;
}

void ListItem::setCompleted(bool b) {
    completed = b;
}

QVector<SubTask> ListItem::getSubTasks() const{
    return subTasks;
}

QJsonObject ListItem::toJson() const {
    QJsonObject obj;
    obj["title"]  = title;
    obj["desc"] = description;
    obj["priortiy"] = priorityLevel;
    obj["startDate"] = startDate.toString(Qt::ISODate);
    obj["dueDate"] = dueDate.toString(Qt::ISODateWithMs);
    obj["completed"] = completed;
    QJsonArray tagItems;
    for (Tag t : tags) {
        tagItems.append(t.getTagName());
    }
    obj["tags"] = tagItems;

    QJsonArray subItems;
    for (SubTask s : subTasks) {
        QJsonObject jo = s.toJson();
        subItems.append(jo);
    }
    obj["subItems"] = subItems;

    return obj;
}

bool ListItem::operator==(const ListItem &other) const {
    return title == other.title &&
           description == other.description &&
           priorityLevel == other.priorityLevel &&
           startDate == other.startDate &&
           dueDate == other.dueDate &&
           completed == other.completed &&
           tags == other.tags;
}