#include "server.h"




server::server(QObject *parent)
    : QTcpServer{parent}
{
    if(listen(QHostAddress :: Any, 1234)){
        qDebug() << "Listening...";
    }
    else{
        qDebug() << "Error while starting: "<< errorString();
    }
}


void server::incomingConnection(qintptr handle)
{
    QTcpSocket *socket = new QTcpSocket();
    socket->setSocketDescriptor(handle);
    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(onDisconnected()));

}

void server::onReadyRead()
{
   qDebug() << "onReadyRead";
   QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
   QString    request = socket->readAll();
   QStringList           h = request.split('\n');
   QStringList           f = h[0].split(' ');
   QString          method = f[0];
   QString            path = f[1];

   qDebug()<<request;

   socket->write("HTTP/1.1 200 OK\r\n\r\n");

   //sending response section
        if (path == "/api"){
   if(request.startsWith("GET")){
   socket->write(controller.id_list());
   }
   else if(request.startsWith("POST")){
       QString data = request.section("\r\n\r\n",1,1);
       qDebug()<<"\n called POST \n";
       controller.append_jobj(data.toUtf8());
       list_message.called_method("POST", controller.getId());
   }
   else if(request.startsWith("PUT")){
       QString data = request.section("\r\n\r\n",1,1);
       qDebug()<<"\n called PUT \n";
       controller.update(data.toUtf8());
   list_message.called_method("PUT", controller.getId());
    }
    else if(request.startsWith("DELETE")){
       QString data = request.section("\r\n\r\n",1,1);
       qDebug()<<"\n called DELETE \n";
       controller.delet(data.toUtf8());
   list_message.called_method("DELETE", controller.getId());
   }
        }
        else if(path == "/test"){
     socket->write(list_message.list());

        }
    socket->disconnectFromHost();

}

void server::onDisconnected(){
     QTcpSocket*socket = qobject_cast<QTcpSocket *>(sender());
     socket->close();
     socket->deleteLater();

}
