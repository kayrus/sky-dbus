#ifndef CALLBACKCLASS_H
#define CALLBACKCLASS_H

#include <QObject>

class callbackClass : public QObject
{
    Q_OBJECT
public:
    explicit callbackClass(QObject *parent = 0);

signals:

public slots:
    Q_SCRIPTABLE void recvMsg(QString sender, QString text);
};

#endif // CALLBACKCLASS_H
