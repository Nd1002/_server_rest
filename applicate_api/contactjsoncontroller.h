#ifndef CONTACTJSONCONTROLLER_H
#define CONTACTJSONCONTROLLER_H

#include <QMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>


class Contact{
public:
    void append(QJsonObject jObj);
    QJsonObject toJsonObject_list();

    void update(QString value);
    QString getId();
private:
    QPair<QString, QString> id;

};


class contactjsoncontroller
{
public:
    void append_jobj(QByteArray json);
    void update(QByteArray json);
    void delet(QByteArray json);
    void clear_list();
    QString getId();
    QByteArray id_list();
private:

    QList<Contact> id_table;
    QString id;
};

#endif // CONTACTJSONCONTROLLER_H
