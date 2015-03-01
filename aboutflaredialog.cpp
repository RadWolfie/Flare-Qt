#include "aboutflaredialog.h"
#include "ui_aboutflaredialog.h"

AboutFlareDialog::AboutFlareDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutFlareDialog)
{
    ui->setupUi(this);
}

AboutFlareDialog::~AboutFlareDialog()
{
    delete ui;
}
