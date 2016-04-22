#ifndef NEWUSER_H
#define NEWUSER_H

#include "constants.h"
#include "login.h"

#include <QMessageBox>

class NewUser
{
public:
    Login *db;
    NewUser();
    ~NewUser();
    bool InsertData(QWidget *parent = 0);
};

#endif // NEWUSER_H
