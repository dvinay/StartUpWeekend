#include "application.h"
#include "ui_application.h"

#include <QtWebKitWidgets/QWebView>
#include <QUrl>

QString g_fname = "";
QString g_lname = "";
QString g_pnumber = "";
QString g_emailid = "";
QString g_amount = "";
QString g_userid = "";
QString g_address = "";
QString g_city = "";
QString g_zip = "";
QString g_notes = "";
QString g_department = "";
QString g_state = "";

Application::Application(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Application)
{
    ui->setupUi(this);
    newuser= new NewUser();
    NewUserInit();
    existinguser = new ExistingUser();
    ExistUserInit();
    updateuser = new UpdateUser();
    UpdateUserInit();
    ScheduleInit();
    WebpageInit();
}

Application::~Application()
{
    delete ui;
    close();
}
//database connections check
void Application::connClose()
{
    dbuser.close();
    dbuser.removeDatabase(QSqlDatabase::defaultConnection);
}

bool Application::connOpen()
{
    dbuser = QSqlDatabase::addDatabase(Constants::Database_type);
    //dborg.setDatabaseName("DRIVER={SQL Server};Server=Server address;Database=Test;Uid=userid;Port=port;Pwd=*******;WSID=.");
    dbuser.setDatabaseName(Constants::Database);
    if(!dbuser.open())
        return false;
    else
        return true;
}
void Application::GlobaldataInit()
{
    g_fname = "";
    g_lname = "";
    g_pnumber = "";
    g_emailid = "";
    g_amount = "";
    g_userid = "";
    g_address = "";
    g_city = "";
    g_zip = "";
    g_notes = "";
    g_department = "";
    g_state = "";
}
//new user page initialization
void Application::NewUserInit()
{
    if(!connOpen())
        ui->label_status1->setText("Failed to open the database");
    else
    {
        ui->label_status1->setText("connected");
        ui->lineEdit_fname1->setText("");
        ui->lineEdit_lname1->setText("");
        QRegExp rxphonenumber("[0-9]{1,10}");
        ui->lineEdit_phone1->setValidator(new QRegExpValidator(rxphonenumber,this));
        ui->lineEdit_phone1->setText("");
        QString emailPatt = "\\b[A-Z0-9a-z._%+-]+@[A-Z0-9a-z.-]+\\.[A-Za-z]{2,4}\\b";
        QRegExp rxemail(emailPatt);
        ui->lineEdit_emailid1->setText("");
        ui->lineEdit_emailid1->setValidator(new QRegExpValidator(rxemail,this));
        ui->lineEdit_amount1->setText("");
        ui->lineEdit_amount1->setValidator( new QIntValidator(0,99,this) );
        ui->lineEdit_netid1->setText("");
        ui->lineEdit_address1->setText("");
        ui->lineEdit_city1->setText("");
        ui->lineEdit_zip1->setValidator( new QIntValidator(0,99999,this) );
        ui->lineEdit_zip1->setText("");
        ui->lineEdit_notes1->setText("");
        for(int i=0;i<=4;i++)
        {
            ui->comboBox_department1->addItem(deptList[i]);
        }
        for(int i=0;i<50;i++)
        {
            ui->comboBox_state1->addItem(cities[i]);
        }
        connClose();
    }
}
//
void Application::NewUserRefresh()
{
    if(!connOpen())
        ui->label_status1->setText("Failed to open the database");
    else
    {
        ui->label_status1->setText("connected");
        ui->lineEdit_fname1->setText("");
        ui->lineEdit_lname1->setText("");
        ui->lineEdit_phone1->setText("");
        ui->lineEdit_emailid1->setText("");
        ui->lineEdit_amount1->setText("");
        ui->lineEdit_netid1->setText("");
        ui->lineEdit_address1->setText("");
        ui->lineEdit_city1->setText("");
        ui->lineEdit_zip1->setText("");
        ui->lineEdit_notes1->setText("");
        ui->comboBox_department1->setCurrentIndex(0);
        ui->comboBox_state1->setCurrentIndex(0);
        connClose();
    }
}

void Application::GetNewUserDetails()
{
    g_fname=ui->lineEdit_fname1->text();
    g_lname=ui->lineEdit_lname1->text();
    g_pnumber=ui->lineEdit_phone1->text();
    g_emailid=ui->lineEdit_emailid1->text();
    g_amount=ui->lineEdit_amount1->text();
    g_userid=ui->lineEdit_netid1->text();
    g_department=ui->comboBox_department1->currentText();
    g_address=ui->lineEdit_address1->text();
    g_city=ui->lineEdit_city1->text();
    g_state=ui->comboBox_state1->currentText();
    g_zip=ui->lineEdit_zip1->text();
    g_notes=ui->lineEdit_notes1->text();
}

void Application::on_pushButton_save1_clicked()
{
    GlobaldataInit();
    GetNewUserDetails();
    if(newuser->InsertData(this))
    {
        ui->label_status1->setText("Data inserted");
        GlobaldataInit();
        NewUserRefresh();
    }
    else
    {
        ui->label_status1->setText("Data not inserted");
    }
}

void Application::on_pushButton_Refresh1_clicked()
{
    this->NewUserRefresh();
}

//Existing user application function
void Application::ExistUserInit()
{
    if(!connOpen())
        ui->label_status2->setText("Failed to open the database");
    else
    {
        ui->label_status2->setText("connected");
        QPalette palette;
        palette.setColor(QPalette::Base,Qt::gray);

        ui->lineEdit_fname2->setText("");
        ui->lineEdit_fname2->setPalette(palette);
        ui->lineEdit_lname2->setText("");
        ui->lineEdit_lname2->setPalette(palette);

        QRegExp rxphonenumber("[0-9]{1,10}");
        ui->lineEdit_phone2->setValidator(new QRegExpValidator(rxphonenumber,this));
        ui->lineEdit_phone2->setText("");
        QString emailPatt = "\\b[A-Z0-9a-z._%+-]+@[A-Z0-9a-z.-]+\\.[A-Za-z]{2,4}\\b";
        QRegExp rxemail(emailPatt);
        ui->lineEdit_emailid2->setText("");
        ui->lineEdit_emailid2->setValidator(new QRegExpValidator(rxemail,this));

        ui->lineEdit_amount2->setText("");
        ui->lineEdit_amount2->setPalette(palette);
        ui->lineEdit_netid2->setText("");
        ui->lineEdit_netid2->setPalette(palette);
        ui->lineEdit_address2->setText("");
        ui->lineEdit_address2->setPalette(palette);
        ui->lineEdit_city2->setText("");
        ui->lineEdit_city2->setPalette(palette);
        ui->lineEdit_zip2->setText("");
        ui->lineEdit_zip2->setPalette(palette);
        ui->lineEdit_notes2->setText("");
        ui->lineEdit_notes2->setPalette(palette);
        for(int i=0;i<=4;i++)
        {
            ui->comboBox_department2->addItem(deptList[i]);
        }
        for(int i=0;i<50;i++)
        {
            ui->comboBox_state2->addItem(cities[i]);
        }
        connClose();
    }
}

void Application::ExistUserRefresh()
{
    if(!connOpen())
        ui->label_status2->setText("Failed to open the database");
    else
    {
        ui->label_status2->setText("connected");
        ui->lineEdit_fname2->setText("");
        ui->lineEdit_lname2->setText("");
        ui->lineEdit_phone2->setText("");
        ui->lineEdit_emailid2->setText("");
        ui->lineEdit_amount2->setText("");
        ui->lineEdit_netid2->setText("");
        ui->lineEdit_address2->setText("");
        ui->lineEdit_city2->setText("");
        ui->lineEdit_zip2->setText("");
        ui->lineEdit_notes2->setText("");
        ui->comboBox_department2->setCurrentIndex(0);
        ui->comboBox_state2->setCurrentIndex(0);
    }
}

void Application::GetExistUserDetails()
{
    g_pnumber=ui->lineEdit_phone2->text();
    g_emailid=ui->lineEdit_emailid2->text();
}

void Application::FillExistUserDetails()
{
    ui->lineEdit_fname2->setText(g_fname);
    ui->lineEdit_lname2->setText(g_lname);
    ui->lineEdit_phone2->setText(g_pnumber);
    ui->lineEdit_emailid2->setText(g_emailid);
    ui->lineEdit_amount2->setText(g_amount);
    ui->lineEdit_netid2->setText(g_userid);
    ui->lineEdit_address2->setText(g_address);
    ui->lineEdit_city2->setText(g_city);
    ui->lineEdit_zip2->setText(g_zip);
    ui->lineEdit_notes2->setText(g_notes);
    int i=0;
    for(i=0;i<=4;i++)
    {
        if(g_department==deptList[i])
            break;
    }
    ui->comboBox_department2->setCurrentIndex(i);
    for(i=0;i<50;i++)
    {
        if(g_state==cities[i])
            break;
    }
    ui->comboBox_state2->setCurrentIndex(i);
}

void Application::on_pushButton_search2_clicked()
{
    GlobaldataInit();
    GetExistUserDetails();
    if(existinguser->SearchData(this))
    {
        ui->label_status2->setText("Data Found");
        FillExistUserDetails();
        GlobaldataInit();
    }
    else
    {
        ui->label_status2->setText("No Data Found");
    }
}

void Application::on_pushButton_Refresh2_clicked()
{
    ExistUserRefresh();
}

//Update user oprations
void Application::UpdateUserInit()
{
    if(!connOpen())
        ui->label_status3->setText("Failed to open the database");
    else
    {
        ui->label_status3->setText("connected");
        ui->lineEdit_fname3->setText("");
        ui->lineEdit_lname3->setText("");
        QRegExp rxphonenumber("[0-9]{1,10}");
        ui->lineEdit_phone3->setValidator(new QRegExpValidator(rxphonenumber,this));
        ui->lineEdit_phone3->setText("");
        QString emailPatt = "\\b[A-Z0-9a-z._%+-]+@[A-Z0-9a-z.-]+\\.[A-Za-z]{2,4}\\b";
        QRegExp rxemail(emailPatt);
        ui->lineEdit_emailid3->setText("");
        ui->lineEdit_emailid3->setValidator(new QRegExpValidator(rxemail,this));
        ui->lineEdit_amount3->setText("");
        ui->lineEdit_amount3->setValidator( new QIntValidator(0,99,this) );
        ui->lineEdit_netid3->setText("");
        ui->lineEdit_address3->setText("");
        ui->lineEdit_city3->setText("");
        ui->lineEdit_zip3->setText("");
        ui->lineEdit_zip3->setValidator( new QIntValidator(0,99999,this) );
        ui->lineEdit_notes3->setText("");
        for(int i=0;i<=4;i++)
        {
            ui->comboBox_department3->addItem(deptList[i]);
        }
        ui->comboBox_state3->addItem("");
        for(int i=0;i<50;i++)
        {
            ui->comboBox_state3->addItem(cities[i]);
        }
        connClose();
    }
}

void Application::UpdateUserRefresh()
{
    if(!connOpen())
        ui->label_status3->setText("Failed to open the database");
    else
    {
        ui->label_status3->setText("connected");
        ui->lineEdit_fname3->setText("");
        ui->lineEdit_lname3->setText("");
        ui->lineEdit_phone3->setText("");
        ui->lineEdit_emailid3->setText("");
        ui->lineEdit_amount3->setText("");
        ui->lineEdit_netid3->setText("");
        ui->lineEdit_address3->setText("");
        ui->lineEdit_city3->setText("");
        ui->lineEdit_zip3->setText("");
        ui->lineEdit_notes3->setText("");
        ui->comboBox_department3->setCurrentIndex(0);
        ui->comboBox_state3->setCurrentIndex(0);
        connClose();
    }
}

void Application::GetUpdateUserDetails()
{
    g_fname=ui->lineEdit_fname3->text();
    g_lname=ui->lineEdit_lname3->text();
    g_pnumber=ui->lineEdit_phone3->text();
    g_emailid=ui->lineEdit_emailid3->text();
    g_amount=ui->lineEdit_amount3->text();
    g_userid=ui->lineEdit_netid3->text();
    g_department=ui->comboBox_department3->currentText();
    g_address=ui->lineEdit_address3->text();
    g_city=ui->lineEdit_city3->text();
    g_state=ui->comboBox_state3->currentText();
    g_zip=ui->lineEdit_zip3->text();
    g_notes=ui->lineEdit_notes3->text();
}

void Application::FillUpdateUserDetails()
{
    ui->lineEdit_fname3->setText(g_fname);
    ui->lineEdit_lname3->setText(g_lname);
    ui->lineEdit_phone3->setText(g_pnumber);
    ui->lineEdit_emailid3->setText(g_emailid);
    ui->lineEdit_amount3->setText(g_amount);
    ui->lineEdit_netid3->setText(g_userid);
    ui->lineEdit_address3->setText(g_address);
    ui->lineEdit_city3->setText(g_city);
    ui->lineEdit_zip3->setText(g_zip);
    ui->lineEdit_notes3->setText(g_notes);
    int i=0;
    for(i=0;i<=4;i++)
    {
        if(g_department==deptList[i])
            break;
    }
    ui->comboBox_department3->setCurrentIndex(i);
    for(i=0;i<50;i++)
    {
        if(g_state==cities[i])
            break;
    }
    ui->comboBox_state3->setCurrentIndex(i);
}


void Application::on_pushButton_Search3_clicked()
{
    GlobaldataInit();
    GetUpdateUserDetails();
    if(!connOpen())
    {
        QMessageBox::critical(this,tr("Information"),tr("Database is not connected"));
    }
    else
    {
        QSqlQueryModel *model=new QSqlQueryModel();
        QSqlQuery qry;

        if(g_fname!="")
        {
            qry.prepare("SELECT * FROM users WHERE First_name = '"+g_fname+"'");
        }
        else if(g_lname!="")
        {
            qry.prepare("SELECT * FROM users WHERE Last_name = '"+g_lname+"'");
        }
        else if(g_pnumber!="")
        {
            qry.prepare("SELECT * FROM users WHERE Phone_number = '"+g_pnumber+"'");
        }
        else if(g_emailid!="")
        {
            qry.prepare("SELECT * FROM users WHERE Email_id = '"+g_emailid+"'");
        }
        else if(g_amount!="")
        {
            qry.prepare("SELECT * FROM users WHERE Amount_paid = '"+g_amount+"'");
        }
        else if(g_userid!="")
        {
            qry.prepare("SELECT * FROM users WHERE User_id = '"+g_userid+"'");
        }
        else if(g_department!="")
        {
            qry.prepare("SELECT * FROM users WHERE Department = '"+g_department+"'");
        }
        else if(g_address!="")
        {
            qry.prepare("SELECT * FROM users WHERE Address = '"+g_address+"'");
        }
        else if(g_city!="")
        {
            qry.prepare("SELECT * FROM users WHERE City = '"+g_city+"'");
        }
        else if(g_state!="")
        {
            qry.prepare("SELECT * FROM users WHERE State = '"+g_state+"'");
        }
        else if(g_zip!="")
        {
            qry.prepare("SELECT * FROM users WHERE Zip = '"+g_zip+"'");
        }
        else if(g_notes!="")
        {
            qry.prepare("SELECT * FROM users WHERE Notes = '"+g_notes+"'");
        }
        else if(g_fname==""&&g_lname==""&&g_pnumber==""&&g_emailid==""&&g_amount==""&&g_userid==""&&g_department==""&&g_address==""&&g_city==""&&g_state==""&&g_zip==""&&g_notes=="")
        {
            qry.prepare("SELECT * FROM users");
        }
        //qDebug () << qry.lastQuery();
        if(qry.exec( ))
        {
            model->setQuery(qry);
            ui->tableView3->setModel(model);
            connClose();
        }
        else
        {
            QMessageBox::critical(this,tr("Error"),qry.lastError().text());
            connClose();
        }
    }
    UpdateUserRefresh();
}

void Application::on_pushButton_Refresh3_clicked()
{
    UpdateUserRefresh();
}

void Application::on_pushButton_Update3_clicked()
{
    GlobaldataInit();
    GetUpdateUserDetails();
    if(updateuser->UpdateData(this))
    {
        ui->label_status3->setText("Data updated");
        FillUpdateUserDetails();
        GlobaldataInit();
    }
    else
    {
        ui->label_status3->setText("Data was not updated");
    }
}

void Application::on_tableView3_activated(const QModelIndex &index)
{
    GlobaldataInit();
    QString val=ui->tableView3->model()->data(index).toString();
    if(!connOpen())
    {
        QMessageBox::critical(this,tr("Information"),tr("Database is not connected"));
    }
    else
    {
        QSqlQuery qry;
        qry.prepare("SELECT * FROM users WHERE First_name ='"+val+"' OR Last_name='"+val+"' OR Phone_number='"+val+"' OR Email_id='"+val+"' OR Amount_paid='"+val+"' OR User_id='"+val+"' OR Department='"+val+"' OR Address='"+val+"' OR City='"+val+"' OR State='"+val+"' OR Zip='"+val+"' OR Notes='"+val+"'");
        //qDebug () << qry.lastQuery();
        if(qry.exec( ))
        {
            while(qry.next())
            {
                ui->lineEdit_fname3->setText(qry.value(0).toString());
                ui->lineEdit_lname3->setText(qry.value(1).toString());
                ui->lineEdit_phone3->setText(qry.value(2).toString());
                ui->lineEdit_emailid3->setText(qry.value(3).toString());
                ui->lineEdit_amount3->setText(qry.value(4).toString());
                ui->lineEdit_netid3->setText(qry.value(5).toString());
                for(int i=0;i<=4;i++)
                {
                    if(qry.value(6).toString()==deptList[i])
                        ui->comboBox_department3->setCurrentIndex(i);
                }
                ui->lineEdit_address3->setText(qry.value(7).toString());
                ui->lineEdit_city3->setText(qry.value(8).toString());
                for(int i=0;i<50;i++)
                {
                    if(qry.value(9).toString()==cities[i])
                        ui->comboBox_state3->setCurrentIndex(i);
                }
                ui->lineEdit_zip3->setText(qry.value(10).toString());
                ui->lineEdit_notes3->setText(qry.value(11).toString());
            }
        }
        else
        {
            QMessageBox::critical(this,tr("Error"),qry.lastError().text());
            connClose();
        }
    }
}
//Schedule initialization
void Application::ScheduleInit()
{
    if(!connOpen())
    {
        QMessageBox::critical(this,tr("Information"),tr("Database is not connected"));
    }
    else
    {
        ui->label_status4->setText("Connected");
        QSqlQueryModel *model=new QSqlQueryModel();
        QSqlQuery qry;
        qry.prepare("SELECT * FROM schedule");
        //qDebug () << qry.lastQuery();
        if(qry.exec( ))
        {
            model->setQuery(qry);
            ui->tableView4->setModel(model);
            connClose();
        }
        else
        {
            QMessageBox::critical(this,tr("Error"),qry.lastError().text());
        }
    }
    ui->lineEdit_Starttime4->setText("");
    ui->lineEdit_Endtime4->setText("");
    ui->lineEdit_Eventname4->setText("");
    ui->lineEdit_Date4->setText("");
}

void Application::on_send4_clicked()
{
    Smtp* smtp = new Smtp("dvinay22914125@gmail.com","Dvc#127543g",Constants::Server_address,465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    smtp->sendMail("dvinay22914125@gmail.com","vinay.chowdary518@gmail.com","CSU EASTBAY STARTUP-WEEKEND",ui->message4->toPlainText());

    /*
    if(!connOpen())
    {
        QMessageBox::critical(this,tr("Information"),tr("Database is not connected"));
    }
    else
    {
        QSqlQuery qry;
        qry.prepare("SELECT Email_id FROM users");
        //qDebug () << qry.lastQuery();
        if(qry.exec( ))
        {
            while(qry.next())
            {
                smtp->sendMail("dvinay22914125@gmail.com",qry.value(0).toString(),"CSU EASTBAY STARTUP-WEEKEND",ui->message4->toPlainText());
            }
            connClose();
        }
        else
        {
            QMessageBox::critical(this,tr("Error"),qry.lastError().text());
            connClose();
        }
    }
    */

}

void Application::mailSent(QString status)
{
    if(status == "Message sent")
        ui->label_status4->setText("Mail send");
}

//Lading Webpage
void Application::WebpageInit()
{
    ui->webView_page->load(QUrl("http://eastbay.startupweekend.org/"));
}

void Application::on_tableView4_activated(const QModelIndex &index)
{
    GlobaldataInit();
    QString stime="",etime="",Eventname="",date="";
    QString val=ui->tableView4->model()->data(index).toString();
    ui->message4->clear();
    if(!connOpen())
    {
        QMessageBox::critical(this,tr("Information"),tr("Database is not connected"));
    }
    else
    {
        ui->label_status4->setText("Connected");
        QSqlQuery qry;
        qry.prepare("SELECT * FROM schedule WHERE Start_time ='"+val+"' OR End_time='"+val+"' OR Topic='"+val+"' OR Date='"+val+"'");
        //qDebug () << qry.lastQuery();
        if(qry.exec( ))
        {
            while(qry.next())
            {
                ui->lineEdit_Starttime4->setText(qry.value(0).toString());
                stime= qry.value(0).toString();
                ui->lineEdit_Endtime4->setText(qry.value(1).toString());
                etime= qry.value(1).toString();
                ui->lineEdit_Eventname4->setText(qry.value(2).toString());
                Eventname= qry.value(2).toString();
                ui->lineEdit_Date4->setText(qry.value(3).toString());
                date= qry.value(3).toString();
            }
            ui->message4->setPlainText("Next Event ('"+Eventname+"') is scheduled from '"+stime+"'"+" to "+etime+"'");
        }
        else
        {
            QMessageBox::critical(this,tr("Error"),qry.lastError().text());
            connClose();
        }
    }
}


void Application::on_Refresh4_clicked()
{
    ScheduleInit();
    ui->message4->clear();
}
