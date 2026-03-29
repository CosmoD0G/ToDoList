#ifndef SUBTASK_H
#define SUBTASK_H
#include <QString>
#include <qjsonobject.h>


class SubTask
{
public:
    SubTask(QString s, bool c = false);
    QJsonObject toJson() const;
    QString getTitle() const;

private:
    QString title;
    bool completed;
};

#endif // SUBTASK_H
