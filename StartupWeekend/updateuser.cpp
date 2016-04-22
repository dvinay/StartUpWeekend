#include "updateuser.h"
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

UpdateUser::UpdateUser()
{
    db=new Login();
}

UpdateUser::~UpdateUser()
{
    delete this;
}

bool UpdateUser::UpdateData(QWidget *parent)
{
    if(!db->connOpen())
    {
        QMessageBox::critical(parent,"Information","Database is not connected");
        db->connClose();
        return false;
    }
    else
    {
        if(g_pnumber==""&&g_emailid=="")
        {
            QMessageBox::critical(parent,"Information","Fill required fields <Phone number or Email id>");
            db->connClose();
            return false;
        }

        QSqlQuery qry;
        qry.prepare("UPDATE users set First_name ='"+g_fname+"', Last_name='"+g_lname+"', Email_id='"+g_emailid+"', Amount_paid='"+g_amount+"', User_id='"+g_userid+"', Department='"+g_department+"', Address='"+g_address+"', City='"+g_city+"', State='"+g_state+"', Zip='"+g_zip+"', Notes='"+g_notes+"' where  Phone_number='"+g_pnumber+"'");
        //qDebug () << qry.lastQuery();
        if(qry.exec( ))
        {
            //QMessageBox::critical(parent,"Information","Data Updated");
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

