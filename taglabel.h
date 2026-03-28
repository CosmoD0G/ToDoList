#ifndef TAGLABEL_H
#define TAGLABEL_H

#include <QLabel>
#include "userdata.h" // wherever Tag is defined

class TagLabel : public QLabel
{
    Q_OBJECT

public:
    explicit TagLabel(const Tag &tag, QWidget *parent = nullptr);
};

#endif // TAGLABEL_H