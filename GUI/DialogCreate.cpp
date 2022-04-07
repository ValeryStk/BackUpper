#include "DialogCreate.h"
#include "ui_DialogCreate.h"

DialogCreate::DialogCreate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCreate)
{
    ui->setupUi(this);
}

DialogCreate::~DialogCreate()
{
    delete ui;
}
