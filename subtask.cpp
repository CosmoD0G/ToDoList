#include "subtask.h"
#include <qjsonobject.h>

SubTask::SubTask(QString s, bool c) {
    title = s;
    completed = c;
}


QJsonObject SubTask::toJson() const {
    QJsonObject obj;
    obj["title"]  = title;
    obj["completed"] = completed;
    return obj;
}

QString SubTask::getTitle() const {
    return title;
}