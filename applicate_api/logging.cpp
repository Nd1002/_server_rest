#include "logging.h"

#define LOG logging
//message_list
LOG::logging(){
   count  = 0;
}
 //item with id <> has been added, item with id <> has been deleted, item with id <> has been changed).



void LOG :: called_method(QString method,QString id){
    QString message;
    QString count;
    logging_message log_message;

    this->count++;

    count = QString::number(this->count);


    if(method == "POST"){
        message = count + ". item with id <" + id + " > has been added.";
    }
    else if(method == "PUT"){
       message = count + ". item with id <" + id + " > has been changed.";
    }
    else if(method == "DELETE"){
        message = count + ". item with id <" + id + " > has been deleted.";
    }

    log_message.count = this->count;
    log_message.message = message;

    message_list.append(log_message);


}

QByteArray LOG :: list(){
    QJsonArray jContacts;
    QString message;
    foreach(logging_message iter, message_list){
        message = iter.message;
        jContacts.append(message);
    }
    return QJsonDocument(jContacts).toJson();
}



