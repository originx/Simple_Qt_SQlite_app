#ifndef BAZA_H
#define BAZA_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtGui>
#include <QtSql>
#include <QTableView>

//ispuni comboBox-a
static void ispuniComboBox(QString upit, int pozicijaTeksta, QComboBox *cmbNaziv)
{   QSqlQuery query(upit);
    cmbNaziv->clear();//ocisti cmb

    while(query.next())
    {     cmbNaziv->addItem(query.value(pozicijaTeksta).toString());
    }   //while

}       //ispuniCmb

//ispuni tablicu
static int ispuniTablicuView(QString upit, QTableView *table)
{    QSqlQueryModel *model = new QSqlQueryModel;
     model->setQuery(upit);
     table->setModel(model);

     return upit.size();
}


#endif // BAZA_H
