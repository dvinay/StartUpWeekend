#include "login.h"
#include "ui_login.h"
#include "application.h"

#include <QMessageBox>
#include <QDebug>

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    QPixmap pix(Constants::logo);
    ui->label_picture->setPixmap(pix);
    if(!connOpen())
        ui->label->setText("Failed to open the database");
    else
        ui->label->setText("connected....");
}

Login::~Login()
{
    delete ui;
}

void Login::connClose()
{
    dborg.close();
    dborg.removeDatabase(QSqlDatabase::defaultConnection);
}

bool Login::connOpen()
{
    dborg = QSqlDatabase::addDatabase(Constants::Database_type);
    //dborg.setDatabaseName("DRIVER={SQL Server};Server=Server address;Database=Test;Uid=userid;Port=port;Pwd=*******;WSID=.");
    dborg.setDatabaseName(Constants::Database);
    if(!dborg.open())
        return false;
    else
        return true;
}

void Login::on_pushbutton_logon_clicked()
{
    username=ui->lineEdit_Username->text();
    password=ui->lineEdit_Password->text();
    if(!connOpen())
    {
        QMessageBox::critical(this,tr("Warning"),tr("Database is not connected"));
    }
    QSqlQuery qry;
    qry.prepare("select * from organizer where name ='"+username+"' and password = '"+password+"'");
    //qDebug () << qry.lastQuery();
    if(qry.exec())
    {
        int count=0;
        while(qry.next())
        {
            count++;
        }
        if(count>=1)
        {
            ui->label->setText("success");
            connClose();
            this->hide();
            Application application;
            application.setModal(true);
            application.exec();
            application.show();
        }
        else
        {
            QMessageBox::warning(this,tr("Wrong data"),tr("User id or password wrong"));
        }
    }
    else
    {
        QMessageBox::critical(this,tr("Error"),qry.lastError().text());
    }
}
