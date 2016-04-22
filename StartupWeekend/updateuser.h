#ifndef UPDATEUSER_H
#define UPDATEUSER_H

#include "constants.h"
#include "login.h"

#include <QMessageBox>


class UpdateUser
{
public:
    Login *db;
    UpdateUser();
    ~UpdateUser();
    bool UpdateData(QWidget *parent = 0);
};

#endif // UPDATEUSER_H
