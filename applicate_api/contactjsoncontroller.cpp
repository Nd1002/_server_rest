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



void Contact::update(QString value)
{
   this->id.second = value;
}

QString Contact:: getId()
{
    return id.first;
}

// CLASS CONTROLLER

QString CONTROLLER :: getId()
{
    return id;
}


void CONTROLLER::append_jobj(QByteArray json){
    QJsonObject jContact = QJsonDocument::fromJson(json).object(),jobj;
    Contact iter;
    this->id = jContact.value("id").toString();
    iter.append(jContact);
    id_table.append(iter);

}

void CONTROLLER::update(QByteArray json){
    QJsonObject jContact = QJsonDocument::fromJson(json).object(),jobj;
    QString value;
    int iter = 0 ;

    this->id = jContact.value("id").toString();
    value = jContact.value("value").toString(); 

    for(iter = 0; iter < id_table.size();iter++){
        if(id_table[iter].getId() == id){
          id_table[iter].update(value);
          break;
        }
    }

    if(!(iter))
    {
        qDebug()<< "Указанного id не существует\n";
    }
}


void CONTROLLER::delet(QByteArray json){
    QJsonObject jContact = QJsonDocument::fromJson(json).object(),jobj;
    int indx = 0;


    this->id = jContact.value("id").toString();
        for( indx = 0;indx < id_table.size(); indx++){
               if(id_table[indx].getId() == id){
                   id_table.removeAt(indx);
                  break;
               }
        }

    if(!indx)
    {
        qDebug()<< "Указанного id не существует\n";
    }

}




QByteArray CONTROLLER :: id_list(){
 QJsonArray jContacts;

 foreach(Contact iter, id_table){
    jContacts.append(iter.toJsonObject_list());
 }
    return QJsonDocument(jContacts).toJson();
}




//id_table, id
