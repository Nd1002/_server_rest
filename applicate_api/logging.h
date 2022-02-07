#ifndef LOGGING_H
#define LOGGING_H

#include <QString>
#include <QList>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

struct logging_message{
    int count;
    QString message;
};

class logging
{

public:
    logging();
    void called_method(QString method, QString id);
    QByteArray list();
private:
    int count;
   QList<logging_message> message_list;
};

#endif // LOGGING_H
