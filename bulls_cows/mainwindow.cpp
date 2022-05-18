#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    count=1;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(1);
    count=1;

    while(1){
        auto rnd = QRandomGenerator::global();
        x = rnd->bounded(0, 10000);
        if(x<1000){
            x+=1000;
        }
        QString y = QString::number(x);
        if ((y[0]!=y[1])&&(y[0]!=y[2])&&(y[0]!=y[3])&&(y[1]!=y[2])&&(y[1]!=y[3])&&(y[2]!=y[3]))
            break;
    }

    qDebug() << x;

    ui->label->setText("Игра начата");
    ui->lineEdit->setEnabled(1);
    ui->pushButton_4->setEnabled(1);

}

void MainWindow::on_pushButton_4_clicked()
{
    QString s = ui->lineEdit->text();
    if((s.size()>=5)||(s.size()<4)){
        QMessageBox::warning(this, "Ошибка", "введите 4хзначное число");
        ui->lineEdit->clear();
        return;
    }

    if((s[0]==s[1])||(s[0]==s[2])||(s[0]==s[3])||(s[1]==s[2])||(s[1]==s[3])||(s[2]==s[3])){
        QMessageBox::warning(this, "Ошибка", "введите число с разными цифрами");
        ui->lineEdit->clear();
        return;
    }
    int bulls=0, cows = 0;


    QString x1 = QString::number(x);
    for(int i=0;i<4;i++){
        if (s[i]==x1[i])
            bulls++;
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(s[i]==x1[j])
                cows++;
        }
    }

    cows-=bulls;
    ui->tableWidget->setRowCount(count);
    ui->tableWidget->setItem(count-1,0,new QTableWidgetItem(s));
    ui->tableWidget->setItem(count-1,1,new QTableWidgetItem("Быки: " + QString::number(bulls) + " Коровы: " + QString::number(cows)));

    count++;
    ui->lineEdit->clear();
    if ((bulls==4)&&(cows==0)){
        QMessageBox::warning(this, "Поздравляем", "Вы выйграли");
        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(1);
    }
}
