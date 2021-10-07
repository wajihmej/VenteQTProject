#ifndef INTER_TICKET_H
#define INTER_TICKET_H

#include <QMainWindow>
#include "guichet.h"
#include "ticket.h"
#include <QSystemTrayIcon>

namespace Ui {
class inter_ticket;
}

class inter_ticket : public QMainWindow
{
    Q_OBJECT

public:
    explicit inter_ticket(QWidget *parent = nullptr);
    ~inter_ticket();

private slots:
    void on_ajout_guichet_clicked();
    void refresh();

    void on_id_modif_guichet_currentIndexChanged(const QString &arg1);

    void on_modif_guichet_clicked();

    void on_id_supp_guichet_currentIndexChanged(const QString &arg1);

    void on_supp_guichet_clicked();

    void on_ajout_ticket_clicked();

    void on_modif_ticket_clicked();

    void on_id_modif_ticket_currentIndexChanged(const QString &arg1);

    void on_id_supp_ticket_currentIndexChanged(const QString &arg1);

    void on_supp_ticket_clicked();

    void on_recherche_guichet_cursorPositionChanged(int arg1, int arg2);

    void on_recherche_ticket_cursorPositionChanged(int arg1, int arg2);

    void on_comboBox_tri_ticket_currentIndexChanged(const QString &arg1);

    void on_comboBox_tri_guichet_currentIndexChanged(const QString &arg1);

    void on_PDFbuttton_clicked();

private:
    Ui::inter_ticket *ui;
    guichet tmpguichet;
    ticket tmpticket;
    QSystemTrayIcon * trayIcon;

};

#endif // INTER_TICKET_H
