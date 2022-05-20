/****************************************************************************//*
 * Copyright (C) 2022 Marek M. Cel
 *
 * This file is part of osgAssembler.
 *
 * osgAssembler is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * osgAssembler is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 ******************************************************************************/
#ifndef DIALOGROTOR_H
#define DIALOGROTOR_H

////////////////////////////////////////////////////////////////////////////////

#include <QDialog>

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class DialogRotor;
}

////////////////////////////////////////////////////////////////////////////////

class DialogRotor : public QDialog
{
    Q_OBJECT

public:

    static const double deg2rad;


    explicit DialogRotor(QWidget *parent = 0);
    ~DialogRotor();

protected:

    void timerEvent( QTimerEvent *event );

private slots:

    void on_sliderConing_sliderMoved(int position);

    void on_sliderDiskPitch_sliderMoved(int position);

    void on_sliderDiskRoll_sliderMoved(int position);

    void on_sliderCollective_sliderMoved(int position);

    void on_sliderCyclicLon_sliderMoved(int position);

    void on_sliderCyclicLat_sliderMoved(int position);

    void on_sliderAzimuth_sliderMoved(int position);

    void on_radioButtonCCW_toggled(bool checked);

private:
    Ui::DialogRotor *ui;

    int _timerId;

    bool _ccw;
};

////////////////////////////////////////////////////////////////////////////////

#endif // DIALOGROTOR_H
