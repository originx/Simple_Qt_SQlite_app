#include "glavniprozor.h"
#include "ui_glavniprozor.h"
#include "baza.h"
#include "connection.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtGui>
#include <QtSql>
#include <QTableView>
#include <QModelIndex>
#include <QApplication>

GlavniProzor::GlavniProzor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GlavniProzor)
{
    ui->setupUi(this);

    //otvara bazu podataka
    QString path  = "";
    path=QApplication::applicationDirPath();
    createConnection(path);

    //Inicijalizacija suèelja
    ui->frame_3->hide();
    ui->frame_4->hide();
    ui->frame_5->hide();
     ui->frame_6->hide();

    //ispuni formular podacima iz baze
    ispuniTablicuView("SELECT * from knjiga",ui->tableView);
    ui->tableView->resizeColumnsToContents();
    ui->statusBar->showMessage("SELECT * from knjiga",0);
    ispuniComboBox("Select * from izdavac",1,ui->comboBox_2);

}
//destruktor
GlavniProzor::~GlavniProzor()
{
    delete ui;
}

//ispuni tablicu knjiga
void GlavniProzor::on_radioButton_toggled(bool checked)
{
    ispuniTablicuView("SELECT * from knjiga",ui->tableView);
    ui->statusBar->showMessage("SELECT * from knjiga",0);
}
//ispuni tablicu izdavac
void GlavniProzor::on_radioButton_3_toggled(bool checked)
{
    ispuniTablicuView("SELECT * from izdavac",ui->tableView);
    ui->statusBar->showMessage("SELECT * from izdavac",0);
}
//ispuni tablicu autor
void GlavniProzor::on_radioButton_4_toggled(bool checked)
{
    ispuniTablicuView("SELECT * from autor",ui->tableView);
    ui->statusBar->showMessage("SELECT * from autor",0);
}

//sucelje
//odabir tablice za prikaz
void GlavniProzor::on_pushButton_3_clicked()
{
     ui->frame_3->hide();
     ui->frame_4->hide();
    ui->frame_2->show();
}
//dodavanje izdavaca
void GlavniProzor::on_pushButton_2_clicked()
{
   ui->frame_2->hide();
   ui->frame_4->hide();
   ui->frame_3->show();
}

//dodaj autora
void GlavniProzor::on_pushButton_clicked()
{
    ui->frame_2->hide();
    ui->frame_3->hide();
    ui->frame_4->show();
}
// sucelje

//dodavanje izdavaèa
void GlavniProzor::on_pushButton_4_clicked()
{
    QSqlQuery query;
    if(ui->lnIzdavac->text()==""){
     ui->statusBar->showMessage("Molimo unesite naziv izdavaca",0);
    }
    else{
        QString upit="INSERT into izdavac (naziv) values ('"+ui->lnIzdavac->text()+"')";
        query.exec(upit);
        ui->statusBar->showMessage(upit,0);
        ispuniComboBox("Select * from izdavac",1,ui->comboBox_2);
       }
}


//dodavanje autora
void GlavniProzor::on_pushButton_5_clicked()
{
    QSqlQuery query;
    if(ui->lnIme->text()==""||ui->lnPrezime->text()==""){
     ui->statusBar->showMessage("Molimo unesite ime i prezime autora",0);
    }
    else{
        QString upit="INSERT into autor (prezime,ime) values ('"+ui->lnPrezime->text()+"','"+ui->lnIme->text()+"')";
        query.exec(upit);
        ui->statusBar->showMessage(upit,0);
       }
}
//dodavanje knjige
void GlavniProzor::on_pushButton_6_clicked()
{
    QSqlQuery query;

    QString naziv = ui->lnNaziv->text();
    QString isbn=ui->lnISBN->text();
    QString godina=ui->lnGodina->text();
    QString izdavac=ui->comboBox_2->currentText().toAscii();
    query.exec("SELECT * from izdavac where naziv ='"+izdavac+"'");
    query.next();

   // QMessageBox::information(this,"DEBUG","TEKST: "+query.lastError().text(),QMessageBox::Ok);

    izdavac=query.value(0).toString();
       //provjera da li su svi podaci unešeni
     if(naziv==""||isbn==""||godina==""||izdavac==""){
     ui->statusBar->showMessage("Molimo unesite sve potrebne podatke",0);
    }
    else{
        QString upit="INSERT into knjiga (naziv, isbn, godina, izdavac) values ('"+naziv+"','"+isbn+"',"+godina+","+izdavac+")";
        query.exec(upit);
        ui->statusBar->showMessage(upit,0);
        ispuniTablicuView("SELECT * from knjiga",ui->tableView);
       }
}

//primjer prikaza relacije
void GlavniProzor::on_radioButton_2_toggled(bool checked)
{

    QSqlRelationalTableModel *model= new QSqlRelationalTableModel();
    model->clear();
    model->setTable("autor_knjige");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//! [1]
    model->setRelation(0, QSqlRelation("knjiga", "sifra", "naziv"));
//! [1] //! [2]
    model->setRelation(1, QSqlRelation("autor", "sifra", "prezime"));
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->statusBar->showMessage("Relacija knjiga / autor",0);
}

//brisanje iz baze
void GlavniProzor::on_pushButton_7_clicked()
{
    QSqlQuery query;

   qint16 row=( ui->tableView->currentIndex().row());
   QModelIndex indeks= ui->tableView->model()->index(row,0,QModelIndex());

   QString sifra=ui->tableView->model()->data(indeks,Qt::DisplayRole).toString();

   if(ui->radioButton->isChecked()){
       query.exec("DELETE from knjiga where sifra = "+sifra);
        ui->statusBar->showMessage("DELETE  from knjiga where sifra = "+sifra,0);
        ispuniTablicuView("SELECT * from knjiga",ui->tableView);
   }
   else if(ui->radioButton_2->isChecked()){
       QMessageBox::information(this,"Info","Nazalost ova funkcija nije implementirana :)",QMessageBox::Ok);
   }
   else if(ui->radioButton_4->isChecked()){
       query.exec("DELETE from autor where sifra = "+sifra);
        ui->statusBar->showMessage("DELETE  from autor where sifra = "+sifra,0);
        ispuniTablicuView("SELECT * from autor",ui->tableView);
   }
   else if(ui->radioButton_3->isChecked()){
       query.exec("DELETE from izdavac where sifra = "+sifra);
        ui->statusBar->showMessage("DELETE  from izdavac where sifra = "+sifra,0);
        ispuniTablicuView("SELECT * from izdavac",ui->tableView);
   }


}
//pretraga
void GlavniProzor::on_checkBox_toggled(bool checked)
{
    if(ui->checkBox->isChecked()){
    ui->frame_5->show();
    }
    else
     ui->frame_5->hide();
}

void GlavniProzor::on_pushButton_8_clicked()
{
    ispuniTablicuView("SELECT * from knjiga where godina = '"+ui->lnNaziv_2->text()+"'",ui->tableView);
    ui->statusBar->showMessage("SELECT * from knjiga where godina = '"+ui->lnNaziv_2->text()+"'",0);
}
//pretraga

void GlavniProzor::on_checkBox_2_toggled(bool checked)
{
    if(ui->checkBox_2->isChecked()){
    ui->frame_6->show();
    }
    else
     ui->frame_6->hide();
}
