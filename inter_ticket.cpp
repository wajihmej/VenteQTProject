#include "inter_ticket.h"
#include "ui_inter_ticket.h"

#include <QMessageBox>
#include<QtCharts/QChartView>
#include<QtCharts/QBarSeries>
#include<QtCharts/QBarSet>
#include<QtCharts/QLegend>
#include<QtCharts/QBarCategoryAxis>
#include<QtCharts/QHorizontalStackedBarSeries>
#include<QtCharts/QLineSeries>
#include<QtCharts/QCategoryAxis>

#include<QtCharts/QPieSeries>
#include<QtCharts/QPieSlice>
#include<QGridLayout>

#include <QtPrintSupport/QPrintDialog>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QTextStream>

inter_ticket::inter_ticket(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::inter_ticket)
{
    ui->setupUi(this);

    setWindowTitle("Gestion Vente");

    //Column size
    ui->tableView_guichet->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_ticket->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //refresh combobox + tableau
    refresh();

    QStringList listguichet;
    listguichet << "" << "NOM" << "NBTICKET" << "TYPE" << "ETAT";
    QStringList listticket;
    listticket << "" << "NOM" << "PRIX" << "DATEDEB" << "NBHEURE";


    ui->comboBox_tri_guichet->addItems(listguichet);
    ui->comboBox_tri_ticket->addItems(listticket);


}

inter_ticket::~inter_ticket()
{
    delete ui;
}


void inter_ticket::refresh()
{
    //remplir tableau
    ui->tableView_guichet->setModel(tmpguichet.afficher());
    ui->tableView_ticket->setModel(tmpticket.afficher());

    //remplir comob box modif
    ui->id_modif_guichet->setModel(tmpguichet.remplircomboguichet());
    ui->id_modif_ticket->setModel(tmpticket.remplircomboticket());

    //remplir comob box supp
    ui->id_supp_guichet->setModel(tmpguichet.remplircomboguichet());
    ui->id_supp_ticket->setModel(tmpticket.remplircomboticket());

}

//************GUICHET************\\

//******AJOUTER


void inter_ticket::on_ajout_guichet_clicked()
{
    guichet g(ui->nom_ajout_guichet->text(),ui->nbticket_ajout_guichet->text().toInt(),ui->etat_ajout_guichet->currentText());
    if(g.ajouter())
    {
            refresh();
            //NOTIFICATION
            trayIcon = new QSystemTrayIcon(this);
            trayIcon->setVisible(true);
            trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_DesktopIcon));
            trayIcon->setToolTip("Ajouter" "\n"
                            "Ajouter avec sucées");
            trayIcon->showMessage("Ajouter","Ajouter avec sucées",QSystemTrayIcon::Information,1500);
            trayIcon->show();

            }
              else
              {
                  QMessageBox::critical(nullptr, QObject::tr("Ajouter un guichet"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
              }
}

//******COMBO BOX MODIFIER

void inter_ticket::on_id_modif_guichet_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;

    QString id = ui->id_modif_guichet->currentText();

    query =tmpguichet.request(id);
    if(query.exec())
    {
        while(query.next())
        {
            ui->nom_modif_guichet->setText(query.value(1).toString());
            ui->nbticket_modif_guichet->setText(query.value(2).toString());
            ui->etat_modif_guichet->setCurrentText(query.value(3).toString());

        }
    }
}

//******MODIFIER

void inter_ticket::on_modif_guichet_clicked()
{
    if((ui->nom_modif_guichet->text() != "") &&(ui->nbticket_modif_guichet->text() != ""))
    {
        if(tmpguichet.modifier(ui->id_modif_guichet->currentText(),ui->nom_modif_guichet->text(),ui->nbticket_modif_guichet->text(),ui->etat_modif_guichet->currentText()))
        {
            //refresh combobox + tableau
            refresh();
            //NOTIFICATION
            trayIcon = new QSystemTrayIcon(this);
            trayIcon->setVisible(true);
            trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_DesktopIcon));
            trayIcon->setToolTip("Modifier" "\n"
                            "Modifier avec sucées");
            trayIcon->showMessage("Modifier","Modifier avec sucées",QSystemTrayIcon::Warning,1500);
            trayIcon->show();

        }
        else
        {
            QMessageBox::critical(this, QObject::tr("Modifier un guichet"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }


    }
}

//******COMBO BOX SUPPRIMER
void inter_ticket::on_id_supp_guichet_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;

    QString id = ui->id_supp_guichet->currentText();

    query =tmpguichet.request(id);
    if(query.exec())
    {
        while(query.next())
        {
            ui->nom_supp_guichet->setText(query.value(1).toString());
            ui->nbticket_supp_guichet->setText(query.value(2).toString());
            ui->etat_supp_guichet->setText(query.value(3).toString());

        }
    }
}

//******SUPPRIMER

void inter_ticket::on_supp_guichet_clicked()
{
    QMessageBox::StandardButton reply =QMessageBox::question(this,
                          "Supprimer","Voulez-vous vraiment supprimer ?",
                          QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        bool test=tmpguichet.supprimer(ui->id_supp_guichet->currentText().toInt());
        if(test)
        {
            //refresh combobox + tableau
            refresh();

            //NOTIFICATION
            trayIcon = new QSystemTrayIcon(this);
            trayIcon->setVisible(true);
            trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_DesktopIcon));
            trayIcon->setToolTip("Supprimé" "\n"
                            "Supprimé avec sucées");
            trayIcon->showMessage("Supprimé","Supprimé avec sucées",QSystemTrayIcon::Warning,1500);
            trayIcon->show();

        }
        else
        {
            QMessageBox::critical(this, QObject::tr("Supprimer une Session"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }

    }

}

//******RECHERCHE AV

void inter_ticket::on_recherche_guichet_cursorPositionChanged(int arg1, int arg2)
{
    ui->tableView_guichet->setModel(tmpguichet.afficherecherche(ui->recherche_guichet->text()));

    QString test =ui->recherche_guichet->text();

    if(test=="")
    {
        ui->tableView_guichet->setModel(tmpguichet.afficher());//refresh
    }

}

//******TRI

void inter_ticket::on_comboBox_tri_guichet_currentIndexChanged(const QString &arg1)
{
    if(!(ui->comboBox_tri_guichet->currentText()==""))
    {
        ui->tableView_guichet->setModel(tmpguichet.triafficher(ui->comboBox_tri_guichet->currentText()));
    }

}

//************TICKET************\\

//******AJOUTER

void inter_ticket::on_ajout_ticket_clicked()
{
    ticket t(ui->nom_ajout_ticket->text(),ui->prix_ajout_ticket->text().toFloat(),ui->datedeb_ajout_ticket->date(),ui->nbheure_ajout_ticket->text().toInt());
    if(t.ajouter())
    {
            refresh();
            //NOTIFICATION
            trayIcon = new QSystemTrayIcon(this);
            trayIcon->setVisible(true);
            trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_DesktopIcon));
            trayIcon->setToolTip("Ajouter" "\n"
                            "Ajouter avec sucées");
            trayIcon->showMessage("Ajouter","Ajouter avec sucées",QSystemTrayIcon::Information,1500);
            trayIcon->show();

            }
              else
              {
                  QMessageBox::critical(nullptr, QObject::tr("Ajouter un ticket"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
              }

}

void inter_ticket::on_modif_ticket_clicked()
{
    if((ui->nom_modif_ticket->text() != "") && (ui->prix_modif_ticket->text() != "") && (ui->nbheure_modif_ticket->text() != ""))
    {
        if(tmpticket.modifier(ui->id_modif_ticket->currentText(),ui->nom_modif_ticket->text(),ui->prix_modif_ticket->text(),ui->datedeb_modif_ticket->date(),ui->nbheure_modif_ticket->text()))
        {
            //refresh combobox + tableau
            refresh();
            //message
            //NOTIFICATION
            trayIcon = new QSystemTrayIcon(this);
            trayIcon->setVisible(true);
            trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_DesktopIcon));
            trayIcon->setToolTip("Modifier" "\n"
                            "Modifier avec sucées");
            trayIcon->showMessage("Modifier","Modifier avec sucées",QSystemTrayIcon::Warning,1500);
            trayIcon->show();
        }
        else
        {
            QMessageBox::critical(this, QObject::tr("Modifier un Ticket"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }


    }
}

//******COMBO BOX MODIFIER

void inter_ticket::on_id_modif_ticket_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;

    QString id = ui->id_modif_ticket->currentText();

    query =tmpticket.request(id);
    if(query.exec())
    {
        while(query.next())
        {
            ui->nom_modif_ticket->setText(query.value(1).toString());
            ui->prix_modif_ticket->setText(query.value(2).toString());
            ui->datedeb_modif_ticket->setDate(query.value(3).toDate());
            ui->nbheure_modif_ticket->setText(query.value(4).toString());
        }
    }

}

//******COMBO BOX SUPP

void inter_ticket::on_id_supp_ticket_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;

    QString id = ui->id_supp_ticket->currentText();

    query =tmpticket.request(id);
    if(query.exec())
    {
        while(query.next())
        {
            ui->nom_supp_ticket->setText(query.value(1).toString());
            ui->prix_supp_ticket->setText(query.value(2).toString());
            ui->datedeb_supp_ticket->setText(query.value(3).toString());
            ui->nbheure_supp_ticket->setText(query.value(4).toString());

        }
    }
}

void inter_ticket::on_supp_ticket_clicked()
{
    QMessageBox::StandardButton reply =QMessageBox::question(this,
                          "Supprimer","Voulez-vous vraiment supprimer ?",
                          QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        bool test=tmpticket.supprimer(ui->id_supp_ticket->currentText().toInt());
        if(test)
        {
            //refresh combobox + tableau
            refresh();

            //NOTIFICATION
            trayIcon = new QSystemTrayIcon(this);
            trayIcon->setVisible(true);
            trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_DesktopIcon));
            trayIcon->setToolTip("Supprimé" "\n"
                            "Supprimé avec sucées");
            trayIcon->showMessage("Supprimé","Supprimé avec sucées",QSystemTrayIcon::Warning,1500);
            trayIcon->show();
        }
        else
        {
            QMessageBox::critical(this, QObject::tr("Supprimer une Ticket"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }

    }


}

//******RECHERCHE AV

void inter_ticket::on_recherche_ticket_cursorPositionChanged(int arg1, int arg2)
{
    ui->tableView_ticket->setModel(tmpticket.afficherecherche(ui->recherche_ticket->text()));

    QString test =ui->recherche_ticket->text();

    if(test=="")
    {
        ui->tableView_ticket->setModel(tmpticket.afficher());//refresh
    }
}

//******TRI

void inter_ticket::on_comboBox_tri_ticket_currentIndexChanged(const QString &arg1)
{
    if(!(ui->comboBox_tri_ticket->currentText()==""))
    {
        ui->tableView_ticket->setModel(tmpticket.triafficher(ui->comboBox_tri_ticket->currentText()));
    }
}

//******PDF

void inter_ticket::on_PDFbuttton_clicked()
{

        QString strStream;
                   QTextStream out(&strStream);
                   const int rowCount = ui->tableView_guichet->model()->rowCount();
                   const int columnCount =ui->tableView_guichet->model()->columnCount();

                   out <<  "<html>\n"
                           "<head>\n"
                           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                           <<  QString("<title>%1</title>\n").arg("eleve")
                           <<  "</head>\n"
                           "<body bgcolor=#F4B8B8 link=#5000A0>\n"
                              // "<img src='C:/Users/ksemt/Desktop/final/icon/logo.webp' width='20' height='20'>\n"
                               "<img src='C:/Users/DeLL/Desktop/logooo.png' width='100' height='100'>\n"
                               "<h1>   Liste des Session </h1>"
                                "<h1>  </h1>"

                               "<table border=1 cellspacing=0 cellpadding=2>\n";


                   // headers
                       out << "<thead><tr bgcolor=#f0f0f0>";
                       for (int column = 0; column < columnCount; column++)
                           if (!ui->tableView_guichet->isColumnHidden(column))
                               out << QString("<th>%1</th>").arg(ui->tableView_guichet->model()->headerData(column, Qt::Horizontal).toString());
                       out << "</tr></thead>\n";
                       // data table
                          for (int row = 0; row < rowCount; row++) {
                              out << "<tr>";
                              for (int column = 0; column < columnCount; column++) {
                                  if (!ui->tableView_guichet->isColumnHidden(column)) {
                                      QString data = ui->tableView_guichet->model()->data(ui->tableView_guichet->model()->index(row, column)).toString().simplified();
                                      out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                  }
                              }
                              out << "</tr>\n";
                          }
                          out <<  "</table>\n"
                              "</body>\n"
                              "</html>\n";

                          QTextDocument *document = new QTextDocument();
                          document->setHtml(strStream);

                          QPrinter printer;

                          QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                          if (dialog->exec() == QDialog::Accepted) {
                              document->print(&printer);
                       }


}
