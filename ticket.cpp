#include "ticket.h"


//******CONSTRUCTEUR VIDE
ticket::ticket()
{

}

//******CONSTRUCTEUR AJOUTER

ticket::ticket(QString nom,float prix,QDate datedebut, int nbheure)
{

    this->nom=nom;
    this->prix=prix;
    this->datedebut=datedebut;
    this->nbheure=nbheure;

}

//******CONSTRUCTEUR AFFICHER/MODIFIER

ticket::ticket( int id, QString nom,float prix,QDate datedebut, int nbheure)
{
    this->id=id;
    this->nom=nom;
    this->prix=prix;
    this->datedebut=datedebut;
    this->nbheure=nbheure;

}

//******AJOUTER

bool ticket::ajouter()
{
QSqlQuery query;

query.prepare("INSERT INTO ticket (NOM, prix, DATEDEB,nbheure) "
                    "VALUES (:nom, :prix, :datedebut, :nbheure)");

QString res= QString::number(nbheure);
QString res1= QString::number(prix);

query.bindValue(":nom", nom);
query.bindValue(":prix", res1);
query.bindValue(":datedebut", datedebut);
query.bindValue(":nbheure", res);


return    query.exec();
}


//******AFFICHER

QSqlQueryModel * ticket::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from ticket");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date debut"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Nombre d'heure"));

    return model;
}

//*******SUPPRIMPER

bool ticket::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from ticket where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}



//*******MODIFIER

bool ticket::modifier(QString id, QString nom,QString prix, QDate datedebut,QString nbheure)
{
QSqlQuery query;

query.prepare("UPDATE ticket SET NOM= :nom, prix= :prix, DATEDEB= :datedebut, nbheure= :nbheure "
                    " WHERE  ID = :id ");

query.bindValue(":id", id);
query.bindValue(":nom", nom);
query.bindValue(":prix", prix);
query.bindValue(":datedebut", datedebut);
query.bindValue(":nbheure", nbheure);


return    query.exec();
}

//******REMPLIR COMBO BOX

QSqlQueryModel * ticket::remplircomboticket()
{
    QSqlQueryModel * mod= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select ID from ticket");
    query.exec();
    mod->setQuery(query);
    return mod;
}


QSqlQuery ticket::request(QString id)
{
    QSqlQuery query;
    query.prepare("select * from ticket where ID= '"+id+"'");
    query.addBindValue(id);
    query.exec();
    return query;
}

//******RECHERCHE AVANCEE

QSqlQueryModel * ticket::afficherecherche(QString res)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select * from ticket  where (NOM LIKE '%"+res+"%' or prix LIKE '%"+res+"%' or nbheure LIKE '%"+res+"%')");
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date debut"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Nombre d'heure"));


    return model;
}

//******AFFICHER TRI

QSqlQueryModel * ticket::triafficher(QString col)
{QSqlQueryModel * model= new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("select * from ticket order by "+col);
    query.exec();


model->setQuery(query);

model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date debut"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Nombre d'heure"));

return model;
}



