#ifndef LOGIN_H
#define LOGIN_H

#include "constants.h"

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QSqlDatabase>

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase dborg;
    QString username,password;
    bool connOpen();
    void connClose();
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_pushbutton_logon_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
