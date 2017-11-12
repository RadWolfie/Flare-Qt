#include <QFileDialog>
#include <QMessageBox>
#include <stdio.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutflaredialog.h"

QString fileLocation = NULL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->update_vehicle_tab();
    this->update_gametype_panel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_gametype_panel()
{
    ui->a_gametype_widgets->setCurrentIndex(ui->a_gametype_type->currentIndex());
    ui->a_teams_enabled->setCheckable(true);
    if(ui->a_gametype_type->currentIndex() + 1 == GAMETYPE_CTF) {
        ui->a_teams_enabled->setChecked(true);
        ui->a_teams_enabled->setEnabled(false);
        ui->a_blue_vehi_box->setEnabled(true);
    }
    else {
        ui->a_teams_enabled->setEnabled(true);
    }

}

void MainWindow::update_vehicle_tab()
{
    HaloVehicleType type1 = (HaloVehicleType)(ui->a_vehi_type_1->currentIndex());
    ui->a_num_banshees_1->setEnabled(type1 == VEHICLE_CUSTOM);
    ui->a_num_ghosts_1->setEnabled(type1 == VEHICLE_CUSTOM);
    ui->a_num_rockets_1->setEnabled(type1 == VEHICLE_CUSTOM);
    ui->a_num_scorpions_1->setEnabled(type1 == VEHICLE_CUSTOM);
    ui->a_num_turrets_1->setEnabled(type1 == VEHICLE_CUSTOM);
    ui->a_num_warthogs_1->setEnabled(type1 == VEHICLE_CUSTOM);
    if(type1 != VEHICLE_CUSTOM) {
        ui->a_num_banshees_1->setValue(0);
        ui->a_num_ghosts_1->setValue(0);
        ui->a_num_rockets_1->setValue(0);
        ui->a_num_scorpions_1->setValue(0);
        ui->a_num_turrets_1->setValue(0);
        ui->a_num_warthogs_1->setValue(0);
    }
    if(type1 == VEHICLE_BANSHEES) {
        ui->a_num_banshees_1->setValue(4);
    }
    else if(type1 == VEHICLE_DEFAULT) {
        ui->a_num_banshees_1->setValue(4);
        ui->a_num_ghosts_1->setValue(4);
        ui->a_num_rockets_1->setValue(4);
        ui->a_num_scorpions_1->setValue(4);
        ui->a_num_turrets_1->setValue(4);
        ui->a_num_warthogs_1->setValue(4);
    }
    else if(type1 == VEHICLE_GHOSTS) {
        ui->a_num_ghosts_1->setValue(4);
    }
    else if(type1 == VEHICLE_GUN_TURRETS) {
        ui->a_num_turrets_1->setValue(4);
    }
    else if(type1 == VEHICLE_ROCKET_WARTHOGS) {
        ui->a_num_rockets_1->setValue(4);
    }
    else if(type1 == VEHICLE_SCORPIONS) {
        ui->a_num_scorpions_1->setValue(4);
    }
    else if(type1 == VEHICLE_WARTHOGS) {
        ui->a_num_warthogs_1->setValue(4);
    }

    HaloVehicleType type2 = (HaloVehicleType)(ui->a_vehi_type_2->currentIndex());
    ui->a_num_banshees_2->setEnabled(type2 == VEHICLE_CUSTOM);
    ui->a_num_ghosts_2->setEnabled(type2 == VEHICLE_CUSTOM);
    ui->a_num_rockets_2->setEnabled(type2 == VEHICLE_CUSTOM);
    ui->a_num_scorpions_2->setEnabled(type2 == VEHICLE_CUSTOM);
    ui->a_num_turrets_2->setEnabled(type2 == VEHICLE_CUSTOM);
    ui->a_num_warthogs_2->setEnabled(type2 == VEHICLE_CUSTOM);
    if(type2 != VEHICLE_CUSTOM) {
        ui->a_num_banshees_2->setValue(0);
        ui->a_num_ghosts_2->setValue(0);
        ui->a_num_rockets_2->setValue(0);
        ui->a_num_scorpions_2->setValue(0);
        ui->a_num_turrets_2->setValue(0);
        ui->a_num_warthogs_2->setValue(0);
    }
    if(type2 == VEHICLE_BANSHEES) {
        ui->a_num_banshees_2->setValue(4);
    }
    else if(type2 == VEHICLE_DEFAULT) {
        ui->a_num_banshees_2->setValue(4);
        ui->a_num_ghosts_2->setValue(4);
        ui->a_num_rockets_2->setValue(4);
        ui->a_num_scorpions_2->setValue(4);
        ui->a_num_turrets_2->setValue(4);
        ui->a_num_warthogs_2->setValue(4);
    }
    else if(type2 == VEHICLE_GHOSTS) {
        ui->a_num_ghosts_2->setValue(4);
    }
    else if(type2 == VEHICLE_GUN_TURRETS) {
        ui->a_num_turrets_2->setValue(4);
    }
    else if(type2 == VEHICLE_ROCKET_WARTHOGS) {
        ui->a_num_rockets_2->setValue(4);
    }
    else if(type2 == VEHICLE_SCORPIONS) {
        ui->a_num_scorpions_2->setValue(4);
    }
    else if(type2 == VEHICLE_WARTHOGS) {
        ui->a_num_warthogs_2->setValue(4);
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open a Halo Gametype"), ".", tr("Halo Gametype (*.lst)"));
    FILE *f = fopen((const char *)fileName.toUtf8(),"rb");
    if(f == NULL) {
        return;
    }
    fseek(f,0x0,SEEK_END);
    uint32_t length = ftell(f);
    uint32_t expected_length = sizeof(HaloGametype);
    if(length != expected_length) {
        qDebug("Tried to open something that wasn't the right size. %u instead of %u",length,expected_length);
        QMessageBox msgBox;
        msgBox.setText("Game variant has an invalid file size.                              ");
        msgBox.setInformativeText("The game variant could not be loaded.");
        msgBox.setIcon(msgBox.Critical);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    HaloGametypeBase *buffer = (HaloGametypeBase *)malloc(length);
    fseek(f,0x0,SEEK_SET);
    fread(buffer,length,0x1,f);
    fclose(f);
    HaloGametype *generic = (HaloGametype *)buffer;


    uint32_t calculated_crc32 = calculateGametypeChecksum(generic);
    uint32_t calculated_crc32_ce = calculateCEGametypeChecksum(generic);

    bool is_ce = calculated_crc32_ce == generic->end.crc32_ce;
    bool is_pc = calculated_crc32 == generic->end.crc32;


    if(!is_pc && !is_ce) {
        qDebug("WARNING! Gametype is corrupted. Wrong checksum!");
        QMessageBox msgBox;
        msgBox.setText("Game variant is corrupt.                                         ");
        msgBox.setInformativeText("The game variant could not be loaded.");
        msgBox.setIcon(msgBox.Critical);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        free(buffer);
        return;
    }

    if(is_ce && !is_pc) {
        convertCEGametypeToPC(buffer);
    }

    int32_t gametype = buffer->gametype; //0x30 - 1 = CTF, 2 = Slayer, 3 = Oddball, 4 = King, 5 = Race
    ui->a_variant_name->setText(QString::fromUtf16(buffer->name));
    ui->a_gametype_type->setCurrentIndex(gametype-1);
    update_gametype_panel();
    switch(gametype) {
        case GAMETYPE_CTF: {
            HaloGametypeCTF *ctf = (HaloGametypeCTF *)buffer;
            ui->a_ctf_assault->setChecked(ctf->assault);
            ui->a_ctf_caps_to_win->setValue(buffer->score_limit);
            ui->a_ctf_flag_must_be_at_home->setChecked(ctf->flag_must_be_at_home);
            ui->a_ctf_flag_must_reset->setChecked(ctf->flag_must_reset);
            ui->a_ctf_single_flag_time->setValue(ctf->single_flag_time / 30);
            break;
        }
        case GAMETYPE_SLAYER: {
            HaloGametypeSlayer *slayer = (HaloGametypeSlayer *)buffer;
            ui->a_slayer_death_bonus->setChecked(slayer->death_bonus == 0);
            ui->a_slayer_kills_to_win->setValue(buffer->score_limit);
            ui->a_slayer_kill_penalty->setChecked(slayer->kill_penalty == 0);
            ui->a_slayer_kill_in_order->setChecked(slayer->kill_in_order);
            break;
        }
        case GAMETYPE_ODDBALL: {
            HaloGametypeOddball *oddball = (HaloGametypeOddball *)buffer;
            ui->a_oddball_ball_count->setValue(oddball->ball_count);
            ui->a_oddball_max_points->setValue(buffer->score_limit);
            ui->a_oddball_ball_type->setCurrentIndex(oddball->ball_type);
            ui->a_oddball_speed_with_ball->setCurrentIndex(oddball->speed_with_ball);
            ui->a_oddball_trait_without_ball->setCurrentIndex(oddball->trait_without_ball);
            ui->a_oddball_trait_with_ball->setCurrentIndex(oddball->trait_with_ball);
            ui->a_oddball_random_ball->setChecked(oddball->random_ball);
            break;
        }
        case GAMETYPE_KING: {
            HaloGametypeKing *king = (HaloGametypeKing *)buffer;
            ui->a_king_minutes_to_win->setValue(buffer->score_limit);
            ui->a_king_moving_hill->setChecked(king->moving_hill);
        }
        case GAMETYPE_RACE: {
            HaloGametypeRace *race = (HaloGametypeRace *)buffer;
            ui->a_race_laps_to_win->setValue(buffer->score_limit);
            ui->a_race_order->setCurrentIndex(race->order); //verify!
            ui->a_race_team_score->setCurrentIndex(race->pointsUsed);
        }
    }
    ui->a_teams_enabled->setChecked(buffer->team_play);

    if(buffer->player_settings.playerOnRadar) {
        if(buffer->player_settings.hideEnemiesFromRadar) {
            ui->a_motion_sensor->setCurrentIndex(1);
        }
        else {
            ui->a_motion_sensor->setCurrentIndex(2);
        }
    }
    else {
        ui->a_motion_sensor->setCurrentIndex(0);
    }
    ui->a_teams_hud->setChecked(buffer->player_settings.friendOnHud);
    ui->a_infinite_grenades->setChecked(buffer->player_settings.infiniteGrenades);
    ui->a_shields_enabled->setChecked(!buffer->player_settings.shieldsDisabled);
    ui->a_invisible->setChecked(buffer->player_settings.invisible);
    ui->a_generic_weapons->setChecked(buffer->player_settings.weaponsGeneric);

    ui->a_objectives_indicator->setCurrentIndex(buffer->objective_indicator);

    ui->a_odd_man_out->setChecked(buffer->odd_man_out);

    ui->a_respawn_growth->setValue(buffer->respawn_time_growth / 30);
    ui->a_respawn_base->setValue(buffer->respawn_time / 30);
    ui->a_respawn_suicide->setValue(buffer->respawn_suicide_penalty / 30);

    ui->a_lives->setValue(buffer->lives);

    ui->a_health_percent->setValue(buffer->health * 100.0);
    ui->a_health_slider->setValue(buffer->health * 100.0);

    ui->a_weapons->setCurrentIndex(buffer->weapon_type);

    ui->a_vehi_type_1->setCurrentIndex(buffer->vehicle_red.type);

    ui->a_vehi_type_2->setCurrentIndex(buffer->vehicle_blue.type);

    this->update_vehicle_tab();

    ui->a_num_banshees_1->setValue(buffer->vehicle_red.banshees);
    ui->a_num_ghosts_1->setValue(buffer->vehicle_red.ghosts);
    ui->a_num_rockets_1->setValue(buffer->vehicle_red.rocket_warthogs);
    ui->a_num_scorpions_1->setValue(buffer->vehicle_red.scorpions);
    ui->a_num_turrets_1->setValue(buffer->vehicle_red.gun_turrets);
    ui->a_num_warthogs_1->setValue(buffer->vehicle_red.warthogs);
    ui->a_num_banshees_2->setValue(buffer->vehicle_blue.banshees);
    ui->a_num_ghosts_2->setValue(buffer->vehicle_blue.ghosts);
    ui->a_num_rockets_2->setValue(buffer->vehicle_blue.rocket_warthogs);
    ui->a_num_scorpions_2->setValue(buffer->vehicle_blue.scorpions);
    ui->a_num_turrets_2->setValue(buffer->vehicle_blue.gun_turrets);
    ui->a_num_warthogs_2->setValue(buffer->vehicle_blue.warthogs);

    ui->a_vehi_respawn_time->setValue(buffer->vehicle_respawn_time / 30);

    ui->a_teams_friendly_fire->setCurrentIndex(buffer->friendly_fire);

    ui->a_respawn_betrayal->setValue(buffer->respawn_betrayal_penalty / 30);

    ui->a_teams_balance->setChecked(buffer->auto_team_balance);

    ui->a_time_limit->setValue(buffer->time_limit / 30 / 60);

    fileLocation = fileName;

    ui->a_blue_vehi_box->setEnabled(buffer->team_play);

    free(buffer);
}

HaloGametype *MainWindow::generateGametype()
{
    HaloGametype *gametype = (HaloGametype *)calloc(sizeof(HaloGametype),0x1);
    HaloGametypeBase *base = (HaloGametypeBase *)gametype;
    memcpy(base->name, ui->a_variant_name->text().utf16(),ui->a_variant_name->text().length() * sizeof(uint16_t));
    base->gametype = ui->a_gametype_type->currentIndex() + 1;
    base->team_play = (ui->a_teams_enabled->isChecked()) ? 1 : 0;
    int indexOfRadar = ui->a_motion_sensor->currentIndex();
    if(indexOfRadar > 0)
        base->player_settings.playerOnRadar = 1;
    if(indexOfRadar == 2)
        base->player_settings.hideEnemiesFromRadar = 0;
    else
        base->player_settings.hideEnemiesFromRadar = 1;
    base->player_settings.friendOnHud = ui->a_teams_hud->isChecked() ? 1 : 0;
    base->player_settings.infiniteGrenades = ui->a_infinite_grenades->isChecked() ? 1 : 0;
    base->player_settings.shieldsDisabled = ui->a_shields_enabled->isChecked() ? 0 : 1;
    base->player_settings.invisible = ui->a_invisible->isChecked() ? 1 : 0;
    base->player_settings.weaponsGeneric = ui->a_generic_weapons->isChecked() ? 1 : 0;
    base->objective_indicator = ui->a_objectives_indicator->currentIndex();
    base->odd_man_out = ui->a_odd_man_out->isChecked() ? 1 : 0;
    base->respawn_time_growth = ui->a_respawn_growth->value() * 30;
    base->respawn_time = ui->a_respawn_base->value() * 30;
    base->respawn_suicide_penalty = ui->a_respawn_suicide->value() * 30;
    base->lives = ui->a_lives->value();
    base->health = (float)(ui->a_health_percent->value()) / 100.0;
    base->weapon_type = ui->a_weapons->currentIndex();

    base->vehicle_red.banshees = ui->a_num_banshees_1->value();
    base->vehicle_red.ghosts = ui->a_num_ghosts_1->value();
    base->vehicle_red.gun_turrets = ui->a_num_turrets_1->value();
    base->vehicle_red.rocket_warthogs = ui->a_num_rockets_1->value();
    base->vehicle_red.scorpions = ui->a_num_scorpions_1->value();
    base->vehicle_red.type = (HaloVehicleType)ui->a_vehi_type_1->currentIndex();
    base->vehicle_red.warthogs = ui->a_num_warthogs_1->value();

    base->vehicle_blue.banshees = ui->a_num_banshees_2->value();
    base->vehicle_blue.ghosts = ui->a_num_ghosts_2->value();
    base->vehicle_blue.gun_turrets = ui->a_num_turrets_2->value();
    base->vehicle_blue.rocket_warthogs = ui->a_num_rockets_2->value();
    base->vehicle_blue.scorpions = ui->a_num_scorpions_2->value();
    base->vehicle_blue.type = (HaloVehicleType)ui->a_vehi_type_2->currentIndex();
    base->vehicle_blue.warthogs = ui->a_num_warthogs_2->value();

    base->vehicle_respawn_time = ui->a_vehi_respawn_time->value() * 30;
    base->friendly_fire = ui->a_teams_friendly_fire->currentIndex();
    base->respawn_betrayal_penalty = ui->a_respawn_betrayal->value() * 30;
    base->auto_team_balance = ui->a_teams_balance->isChecked() ? 1 : 0;
    base->time_limit = ui->a_time_limit->value() * 60 * 30;

    switch(base->gametype) {
        case GAMETYPE_CTF: {
            HaloGametypeCTF *ctf = (HaloGametypeCTF *)gametype;
            ctf->assault = ui->a_ctf_assault->isChecked() ? 1 : 0;
            ctf->flag_must_be_at_home = ui->a_ctf_flag_must_be_at_home->isChecked() ? 1 : 0;
            ctf->flag_must_reset = ui->a_ctf_flag_must_reset->isChecked() ? 1 : 0;
            ctf->single_flag_time = ui->a_ctf_single_flag_time->value() * 30;
            base->score_limit = ui->a_ctf_caps_to_win->value();
            break;
        }
        case GAMETYPE_KING: {
            HaloGametypeKing *king = (HaloGametypeKing *)gametype;
            king->moving_hill = ui->a_king_moving_hill->isChecked() ? 1 : 0;
            base->score_limit = ui->a_king_minutes_to_win->value();
            break;
        }
        case GAMETYPE_ODDBALL: {
            HaloGametypeOddball *oddball = (HaloGametypeOddball *)gametype;
            oddball->ball_count = ui->a_oddball_ball_count->value();
            oddball->ball_type = ui->a_oddball_ball_type->currentIndex();
            oddball->random_ball = ui->a_oddball_random_ball->isChecked() ? 1 : 0;
            oddball->speed_with_ball = ui->a_oddball_speed_with_ball->currentIndex();
            oddball->trait_without_ball = ui->a_oddball_trait_without_ball->currentIndex();
            oddball->trait_with_ball = ui->a_oddball_trait_with_ball->currentIndex();
            base->score_limit = ui->a_oddball_max_points->value();
            break;
        }
        case GAMETYPE_RACE: {
            HaloGametypeRace *race = (HaloGametypeRace *)gametype;
            race->order = ui->a_race_order->currentIndex();
            race->pointsUsed = ui->a_race_team_score->currentIndex();
            base->score_limit = ui->a_race_laps_to_win->value();
            break;
        }
        case GAMETYPE_SLAYER: {
            HaloGametypeSlayer *slayer = (HaloGametypeSlayer *)gametype;
            slayer->death_bonus = ui->a_slayer_death_bonus->isChecked() ? 0 : 1;
            slayer->kill_in_order = ui->a_slayer_kill_in_order->isChecked() ? 1 : 0;
            slayer->kill_penalty = ui->a_slayer_kill_penalty->isChecked() ? 0 : 1;
            base->score_limit = ui->a_slayer_kills_to_win->value();
            break;
        }
    }
    gametype->end.crc32 = calculateGametypeChecksum(gametype);
    return gametype;
}

void MainWindow::on_a_gametype_type_currentIndexChanged()
{
    this->update_gametype_panel();
}

void MainWindow::on_a_health_slider_sliderMoved(int position)
{
    ui->a_health_percent->setValue(position);
}

void MainWindow::on_a_health_percent_valueChanged(int arg1)
{
    ui->a_health_slider->setValue(arg1);
}

void MainWindow::save_gametype()
{
    FILE *f = fopen((const char *)fileLocation.toUtf8(),"wb+");
    if(f == NULL) {
        fileLocation = QString::null;
        QMessageBox msgBox;
        msgBox.setText("Failed to save to path.                                         ");
        msgBox.setInformativeText("You might not have write permission to the gametype.");
        msgBox.setIcon(msgBox.Critical);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    HaloGametype *gametype = this->generateGametype();
    convertPCGametypeToHybrid(gametype);
    gametype->end.crc32_ce = calculateCEGametypeChecksum(gametype);
    fwrite(gametype,sizeof(HaloGametype),1,f);
    fclose(f);
    free(gametype);
}

void MainWindow::on_actionSave_As_triggered()
{
    if(ui->a_variant_name->text().isEmpty()) {
        QMessageBox msgBox;
        msgBox.setText("No game variant name specified.                                         ");
        msgBox.setInformativeText("Please name your game variant before saving.");
        msgBox.setIcon(msgBox.Information);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    fileLocation = QFileDialog::getSaveFileName(this, tr("Save Gametype"),"blam.lst",tr("Halo Gametype (*.lst)"));
    if(fileLocation == NULL) return;
    this->save_gametype();
}

void MainWindow::on_actionSave_triggered()
{
    if(fileLocation == NULL) {
        this->on_actionSave_As_triggered();
        return;
    }
    if(ui->a_variant_name->text().isEmpty()) {
        QMessageBox msgBox;
        msgBox.setText("No game variant name specified.                                         ");
        msgBox.setInformativeText("Please name your game variant before saving.");
        msgBox.setIcon(msgBox.Information);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    this->save_gametype();
}

void MainWindow::on_a_vehi_type_1_currentIndexChanged()
{
    this->update_vehicle_tab();
}

void MainWindow::on_a_vehi_type_2_currentIndexChanged()
{
    this->update_vehicle_tab();
}

void MainWindow::on_actionAbout_Flare_triggered()
{
    AboutFlareDialog abfd;
    abfd.exec();
}

void MainWindow::on_a_teams_enabled_clicked()
{
    ui->a_blue_vehi_box->setEnabled(ui->a_teams_enabled->isChecked());
}
