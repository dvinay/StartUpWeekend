#include "newuser.h"
#include "constants.h"
#include <QDebug>
#include <QMessageBox>

extern QString g_fname;
extern QString g_lname;
extern QString g_pnumber;
extern QString g_emailid;
extern QString g_amount;
extern QString g_userid;
extern QString g_address;
extern QString g_city;
extern QString g_zip;
extern QString g_notes;
extern QString g_department;
extern QString g_state;

NewUser::NewUser()
{
     db=new Login();
}

NewUser::~NewUser()
{
    delete this;
}

bool NewUser::InsertData(QWidget *parent)
{
    if(g_fname==""||g_lname==""||g_pnumber==""||g_emailid==""||g_amount=="")
    {
        QMessageBox::critical(parent,"Information","Fill required fields");
        db->connClose();
        return false;
    }
    else
    {
        if(!db->connOpen())
        {
            QMessageBox::critical(parent,"Information","Database is not connected");
            db->connClose();
            return false;
        }
        QSqlQuery qry;
        qry.prepare("INSERT INTO users (First_name,Last_name,Phone_number,Email_id,Amount_paid,User_id,Department,Address,City,State,Zip,Notes) VALUES ('"+g_fname+"','"+g_lname+"','"+g_pnumber+"','"+g_emailid+"','"+g_amount+"','"+g_userid+"','"+g_department+"','"+g_address+"','"+g_city+"','"+g_state+"','"+g_zip+"','"+g_notes+"')");

        //qDebug () << qry.lastQuery() ;
        if(qry.exec( ))
        {
            //QMessageBox::critical(parent,"Information","Data Inserted");
            db->connClose();
            return true;
        }
        else
        {
            QMessageBox::critical(parent,"Error",qry.lastError().text());
            db->connClose();
            return false;
        }
    }
}
