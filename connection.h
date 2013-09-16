#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDir>

static bool createConnection(QString path)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path+"/baza.db");
        if (!db.open())
    {
            QMessageBox::critical(0, qApp->tr("Nije moguce otvoriti bazu podataka"),
            qApp->tr("Nije moguce otvoriti konekciju prema bazi.\n"
                     "Kliknite Cancel za izlaz."), QMessageBox::Cancel);
            return false;
    }     

    return true;
}

#endif
