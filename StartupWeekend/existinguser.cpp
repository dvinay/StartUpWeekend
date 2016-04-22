#include "existinguser.h"
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

ExistingUser::ExistingUser()
{
    db=new Login();
}

ExistingUser::~ExistingUser()
{
    delete this;
}

bool ExistingUser::SearchData(QWidget *parent)
{
    if(g_pnumber==""&&g_emailid=="")
    {
        QMessageBox::critical(parent,"Information","Fill required fields <phone number or email id>");
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
        if(g_pnumber=="")
            qry.prepare("SELECT * FROM users WHERE Email_id = "+g_emailid);
        else if(g_emailid=="")
            qry.prepare("SELECT * FROM users WHERE Phone_number = "+g_pnumber);
        else
            qry.prepare("SELECT * FROM users WHERE Phone_number = '"+g_pnumber+"' AND Email_id='"+g_emailid+"'");
        qDebug () << qry.lastQuery();

        if(qry.exec( ))
        {
            int count=0;
            while(qry.next())
            {
                count++;
                g_fname=qry.value(0).toString();
                g_lname=qry.value(1).toString();
                g_pnumber=qry.value(2).toString();
                g_emailid=qry.value(3).toString();
                g_amount=qry.value(4).toString();;
                g_userid=qry.value(5).toString();
                g_department=qry.value(6).toString();
                g_address=qry.value(7).toString();
                g_city=qry.value(8).toString();
                g_state=qry.value(9).toString();;
                g_zip=qry.value(10).toString();
                g_notes=qry.value(11).toString();
            }
            if(count == 0)
            {
                QMessageBox::information(parent,"Information","No user exist with given details");
                db->connClose();
                return false;
            }
            else
            {
                db->connClose();
                return true;
            }
        }
        else
        {
            QMessageBox::critical(parent,"Error",qry.lastError().text());
            db->connClose();
            return false;
        }
    }
}
