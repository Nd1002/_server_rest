#include "contactjsoncontroller.h"

#include <QVariant>

#define CONTROLLER contactjsoncontroller


//CLASS CONTACT


void Contact :: append(QJsonObject jObj){
        QString id, value;
        id = jObj.value("id").toString();
        value = jObj.value("value").toString();
        this->id.first = id;
        this->id.second = value;
}


QJsonObject Contact:: toJsonObject_list(){
    QJsonObject jObj;
    QString id, value;

        id = this->id.first;
        value = this->id.second;
        jObj.insert("id",QJsonValue::fromVariant(id));
        jObj.insert("value", QJsonValue::fromVariant(value));

    return jObj;
}



void Contact::update(QString value){
    qDebug()<<"\n------------ update Contact check------------- "<< value <<"\n";
   this->id.second = value;
    qDebug()<<"\n------------ end of check ------------- "<<"\n";
}

QString Contact:: getId(){
    return id.first;
}

// CLASS CONTROLLER

QString CONTROLLER :: getId(){
    return id;
}


void CONTROLLER::append_jobj(QByteArray json){
    QJsonObject jContact = QJsonDocument::fromJson(json).object(),jobj;
    Contact iter;
    qDebug() << "append_jobj\n";
    qDebug() << jContact.value("id").toString();
    qDebug() << jContact.value("value").toString();
    id = jContact.value("id").toString(); //id для логирования сообщений, в будущем доработать
    iter.append(jContact);
    id_table.append(iter);

}

void CONTROLLER::update(QByteArray json){
    QJsonObject jContact = QJsonDocument::fromJson(json).object(),jobj;
    QString value;
    int count = 0 ;

    id = jContact.value("id").toString();
    value = jContact.value("value").toString(); //данные для обновления id, доработать функционал

    for(int iter = 0; iter < id_table.size();iter++){
        if(id_table[iter].getId() == id){
          id_table[iter].update(value);
          break;
        }
    }

    if(!(count))
    {
        qDebug()<< "Указанного id не существует\n";
    } else
    {

    }


}

void CONTROLLER::delet(QByteArray json){
    QJsonObject jContact = QJsonDocument::fromJson(json).object(),jobj;
    QString value;
    Contact delet;
    int count = 0, indx;

    id = jContact.value("id").toString();
        for(int i = 0; i < id_table.size(); i++){
               if(id_table[i].getId() == id){
                   indx = i;
                   count++;
               }
        }
    if(!count)
    {
        qDebug()<< "Указанного id не существует\n";
    }
    else
    {
        id_table.removeAt(indx);
    }


}




QByteArray CONTROLLER :: id_list(){
 QJsonArray jContacts;

 foreach(Contact iter, id_table){
    jContacts.append(iter.toJsonObject_list());
 }
    return QJsonDocument(jContacts).toJson();
}




void CONTROLLER::clear_list(){
   id_table.clear();
}

//id_table, id
