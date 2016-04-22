#ifndef EXISTINGUSER_H
#define EXISTINGUSER_H

#include "constants.h"
#include "login.h"

class ExistingUser
{
public:
    Login *db;
    ExistingUser();
    ~ExistingUser();
    bool SearchData(QWidget *parent = 0);
};

#endif // EXISTINGUSER_H
