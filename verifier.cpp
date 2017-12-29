#include "verifier.h"
#include "ui_verifier.h"

Verifier::Verifier(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Verifier)
{
    ui->setupUi(this);
}

Verifier::~Verifier()
{
    delete ui;
}
