#ifndef LISTITEM_H
#define LISTITEM_H
#include <QString>
#include <ctime>
#include <Qvector>
#include "subtask.h"
#include "tag.h"

class ListItem
{
public:
    ListItem(QString t, QString d, int p, QDate s, QDateTime due, QVector<Tag> tg, QVector<SubTask> sbt);
    ListItem();

    // getters and setters for class variables
    void setTitle(QString t);
    QString getTitle() const;

    void setDescription(QString d);
    QString getDescription() const;

    void setPriorityLevel();
    int getPriorityLevel();

    void setCanStart(bool b);
    bool getCanStart();

    QDateTime getDueDate() const;

    QDate getStartDate() const;

    void setCompleted(bool b);
    bool getCompleted();

    void setTags();
    QVector<Tag> getTags() const;

    QJsonObject toJson() const;



private:
    QString title;
    QString description;

    int priorityLevel;

    QDate startDate;
    bool canStart;

    bool completed;

    QDateTime dueDate;

    QVector<Tag> tags;
    QVector<SubTask> subTasks;


};


#endif // LISTITEM_H
