#ifndef GLAVNIPROZOR_H
#define GLAVNIPROZOR_H

#include <QMainWindow>

namespace Ui {
    class GlavniProzor;
}

class GlavniProzor : public QMainWindow
{
    Q_OBJECT

public:
    explicit GlavniProzor(QWidget *parent = 0);
    ~GlavniProzor();

private slots:
    void on_radioButton_toggled(bool checked);


    void on_radioButton_3_toggled(bool checked);

    void on_radioButton_4_toggled(bool checked);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();


    void on_radioButton_2_toggled(bool checked);

    void on_pushButton_7_clicked();


    void on_checkBox_toggled(bool checked);

    void on_pushButton_8_clicked();

    void on_checkBox_2_toggled(bool checked);

private:
    Ui::GlavniProzor *ui;
};

#endif // GLAVNIPROZOR_H
