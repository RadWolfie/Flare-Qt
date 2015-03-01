#ifndef ABOUTFLAREDIALOG_H
#define ABOUTFLAREDIALOG_H

#include <QDialog>

namespace Ui {
class AboutFlareDialog;
}

class AboutFlareDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutFlareDialog(QWidget *parent = 0);
    ~AboutFlareDialog();

private:
    Ui::AboutFlareDialog *ui;
};

#endif // ABOUTFLAREDIALOG_H
