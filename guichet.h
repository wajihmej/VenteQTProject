#ifndef GUICHET_H
#define GUICHET_H

#include "QString"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>

class guichet
{
public:
    guichet();
    guichet(QString,int,QString);
    guichet(int,QString,int,QString);


    bool ajouter();
    bool supprimer(int);
    bool modifier(QString,QString,QString,QString);

    QSqlQuery request(QString);

    QSqlQueryModel * afficherecherche(QString);
    QSqlQueryModel * triafficher(QString);
    QSqlQueryModel * afficher();
    QSqlQueryModel * remplircomboguichet();

private:
    int id;
    QString nom;
    int nbticket;
    QString etat;


};

#endif // GUICHET_H
