#ifndef SERVER_H
#define SERVER_H


#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include "contactjsoncontroller.h"
#include "logging.h"

class server : public QTcpServer
{
    Q_OBJECT
public:
    explicit server(QObject *parent = nullptr);
    void incomingConnection(qintptr handle);

signals:

public slots:
    void onReadyRead();
    void onDisconnected();

private:
    contactjsoncontroller controller;
    logging list_message;

};

#endif // SERVER_H
