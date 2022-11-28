#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Buyt.h"

class Buyt : public QMainWindow
{
    Q_OBJECT

public:
    Buyt(QWidget *parent = nullptr);
    ~Buyt();

private:
    Ui::BuytClass ui;
};
