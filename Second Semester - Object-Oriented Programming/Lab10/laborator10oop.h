#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_laborator10oop.h"

class laborator10oop : public QMainWindow
{
    Q_OBJECT

public:
    laborator10oop(QWidget *parent = nullptr);
    ~laborator10oop();

private:
    Ui::laborator10oopClass ui;
};
