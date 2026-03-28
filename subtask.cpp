#include "subtask.h"
#include <qjsonobject.h>

SubTask::SubTask(QString s) {
    title = s;
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