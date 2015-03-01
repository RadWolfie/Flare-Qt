#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

extern "C" {
#include "ZZTHaloGametype.h"
}

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void on_a_gametype_type_currentIndexChanged();
    void update_gametype_panel();
    HaloGametype *generateGametype();
    void on_a_health_slider_sliderMoved(int position);
    void on_a_health_percent_valueChanged(int arg1);
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_a_vehi_type_1_currentIndexChanged();
    void on_a_vehi_type_2_currentIndexChanged();
    void update_vehicle_tab();
    void save_gametype();

    void on_actionAbout_Flare_triggered();

    void on_a_teams_enabled_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
