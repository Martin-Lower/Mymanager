#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include <QObject>

class PageManager : public QObject
{
    Q_OBJECT
public:
    explicit PageManager(QObject *parent = nullptr);

signals:
};

#endif // PAGEMANAGER_H
