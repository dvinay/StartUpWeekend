#ifndef APPLICATION_H
#define APPLICATION_H


#include <QDialog>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QSqlDatabase>

#include "newuser.h"
#include "constants.h"
#include "existinguser.h"
#include "updateuser.h"
#include "smtp.h"

namespace Ui {
class Application;
}
class NewUser;
class ExistingUser;
class UpdateUser;

class Application : public QDialog
{
    Q_OBJECT
    QString cities[50]={"CA","AK","AL","AR","AZ","CO","CT","DE"
                       ,"FL","GA","HI","IA","ID","IL","IN","KS"
                       ,"KY","LA","MA","MD","ME","MI","MN","MO"
                       ,"MS","MT","NC","ND","NE","NH","NJ","NM"
                       ,"NV","NY","OH","OK","OR","PA","RI","SC"
                       ,"SD","TN","TX","UT","VA","VT","WA","WI","WV","WY"};
    QString deptList[5]={"","Computer Science","Management","Marketing","Others"};
public:
    QSqlDatabase dbuser;
    NewUser *newuser;
    ExistingUser *existinguser;
    UpdateUser *updateuser;
    //database connection functions
    bool connOpen();
    void connClose();
    //initialization of global variables
    void GlobaldataInit();

    explicit Application(QWidget *parent = 0);
    ~Application();
    //newuser operations
    void NewUserInit();
    void NewUserRefresh();
    void GetNewUserDetails();
    //Existing user operations
    void ExistUserInit();
    void ExistUserRefresh();
    void GetExistUserDetails();
    void FillExistUserDetails();
    //Update user operations
    void UpdateUserInit();
    void UpdateUserRefresh();
    void GetUpdateUserDetails();
    void FillUpdateUserDetails();
    //Schedule table loading tab operations
    void ScheduleInit();
    void mailSent(QString status);
    //Web page loading operation
    void WebpageInit();
private slots:
    //new user button operations
    void on_pushButton_save1_clicked();
    void on_pushButton_Refresh1_clicked();
    //existing user button operations
    void on_pushButton_search2_clicked();
    void on_pushButton_Refresh2_clicked();
    //update user button operations
    void on_pushButton_Search3_clicked();
    void on_pushButton_Refresh3_clicked();
    void on_pushButton_Update3_clicked();
    void on_tableView3_activated(const QModelIndex &index);
    void on_tableView4_activated(const QModelIndex &index);
    //schedule mail send operations
    void on_send4_clicked();

    void on_Refresh4_clicked();

private:
    Ui::Application *ui;
};

#endif // APPLICATION_H
