#ifndef TICKET_H
#define TICKET_H
#include "QString"
#include "QDate"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>


class ticket
{
    public:
    ticket();
    ticket(QString,float,QDate,int);
    ticket(int,QString,float,QDate,int);

    bool ajouter();
    bool supprimer(int);
    bool modifier(QString,QString,QString,QDate,QString);

    QSqlQuery request(QString);

    QSqlQueryModel * afficherecherche(QString);
    QSqlQueryModel * triafficher(QString);
    QSqlQueryModel * afficher();
    QSqlQueryModel * remplircomboticket();

private:
    int id;
    QString nom;
    float prix;
    QDate datedebut;
    int nbheure;
};

#endif // TICKET_H
