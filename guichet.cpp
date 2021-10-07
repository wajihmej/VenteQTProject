#include "guichet.h"

guichet::guichet()
{

}

guichet::guichet(QString nom,int nbticket,QString etat)
{

    this->nom=nom;
    this->nbticket=nbticket;
    this->etat=etat;
}


guichet::guichet(int id,QString nom,int nbticket,QString etat)
{

    this->id=id;
    this->nom=nom;
    this->nbticket=nbticket;
    this->etat=etat;
}

//******AJOUTER

bool guichet::ajouter()
{
QSqlQuery query;

query.prepare("INSERT INTO guichet (NOM, nbticket, etat) "
                    "VALUES (:nom, :nbticket, :etat)");


query.bindValue(":nom", nom);
query.bindValue(":nbticket", nbticket);
query.bindValue(":etat", etat);


return    query.exec();
}


//******AFFICHER

QSqlQueryModel * guichet::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from guichet");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre ticket"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Etat"));

    return model;
}

//*******SUPPRIMPER

bool guichet::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from guichet where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}



//*******MODIFIER

bool guichet::modifier(QString id, QString nom,QString nbticket, QString etat)
{
QSqlQuery query;

query.prepare("UPDATE guichet SET NOM= :nom, nbticket= :nbticket, etat= :etat "
                    " WHERE  ID = :id ");

query.bindValue(":id", id);
query.bindValue(":nom", nom);
query.bindValue(":nbticket", nbticket);
query.bindValue(":etat", etat);


return    query.exec();
}

//******REMPLIR COMBO BOX

QSqlQueryModel * guichet::remplircomboguichet()
{
    QSqlQueryModel * mod= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select ID from guichet");
    query.exec();
    mod->setQuery(query);
    return mod;
}


QSqlQuery guichet::request(QString id)
{
    QSqlQuery query;
    query.prepare("select * from guichet where ID= '"+id+"'");
    query.addBindValue(id);
    query.exec();
    return query;
}

//******RECHERCHE AVANCEE

QSqlQueryModel * guichet::afficherecherche(QString res)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select * from guichet  where (NOM LIKE '%"+res+"%' OR nbticket LIKE '%"+res+"%' or etat LIKE '%"+res+"%' )");
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre ticket"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Etat"));


    return model;
}

//******AFFICHER TRI

QSqlQueryModel * guichet::triafficher(QString col)
{QSqlQueryModel * model= new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("select * from guichet order by "+col);
    query.exec();


model->setQuery(query);

model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre ticket"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Etat"));

return model;
}


