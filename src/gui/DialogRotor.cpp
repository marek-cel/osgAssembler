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

#include <gui/DialogRotor.h>
#include <ui_DialogRotor.h>

#include <cmath>

#include <Data.h>

////////////////////////////////////////////////////////////////////////////////

const double DialogRotor::deg2rad = M_PI / 180.0;

////////////////////////////////////////////////////////////////////////////////

DialogRotor::DialogRotor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRotor),
    _timerId ( 0 ),
    _ccw ( false )
{
    ui->setupUi( this );

    _timerId = startTimer( 10 );
}

////////////////////////////////////////////////////////////////////////////////

DialogRotor::~DialogRotor()
{
    killTimer( _timerId );

    delete ui;
}

////////////////////////////////////////////////////////////////////////////////

void DialogRotor::timerEvent( QTimerEvent *event )
{
    /////////////////////////////
    QDialog::timerEvent( event );
    /////////////////////////////

    double beta_0  =  Data::get()->rotor.coningAngle;
    double beta_1c = -Data::get()->rotor.diskPitch;
    double beta_1s = ( _ccw ? -1.0 : 1.0 ) * Data::get()->rotor.diskRoll;

    double theta_0  = Data::get()->rotor.collective;
    double theta_1c = ( _ccw ? -1.0 : 1.0 ) * Data::get()->rotor.cyclicLat;
    double theta_1s = Data::get()->rotor.cyclicLon;

    unsigned int bladesCount = ui->spinBoxBlades->value();
    double psiStep = 2.0*M_PI / (float)bladesCount;

    for ( unsigned int i = 0; i < bladesCount; i++ )
    {
        double psi = Data::get()->rotor.azimuth + (double)(i*psiStep);

        double cosPsi = cos( psi );
        double sinPsi = sin( psi );

        Data::get()->blade[ i ].beta  =  beta_0 +  beta_1c * cosPsi +  beta_1s * sinPsi;
        Data::get()->blade[ i ].theta = theta_0 + theta_1c * cosPsi + theta_1s * sinPsi;
    }
}

////////////////////////////////////////////////////////////////////////////////

void DialogRotor::on_sliderConing_sliderMoved(int position)
{
    const double min = -20.0;
    const double max =  20.0;

    double coef = 0.01 * (double)position;

    double val = min + coef * ( max - min );

    Data::get()->rotor.coningAngle = deg2rad * val;

    ui->spinBoxConing->setValue( val );
}

////////////////////////////////////////////////////////////////////////////////

void DialogRotor::on_sliderDiskPitch_sliderMoved(int position)
{
    const double min = -20.0;
    const double max =  20.0;

    double coef = 0.01 * (double)position;

    double val = min + coef * ( max - min );

    Data::get()->rotor.diskPitch = deg2rad * val;

    ui->spinBoxDiskPitch->setValue( val );
}

////////////////////////////////////////////////////////////////////////////////

void DialogRotor::on_sliderDiskRoll_sliderMoved(int position)
{
    const double min = -20.0;
    const double max =  20.0;

    double coef = 0.01 * (double)position;

    double val = min + coef * ( max - min );

    Data::get()->rotor.diskRoll = deg2rad * val;

    ui->spinBoxDiskRoll->setValue( val );
}

////////////////////////////////////////////////////////////////////////////////

void DialogRotor::on_sliderCollective_sliderMoved(int position)
{
    const double min = -20.0;
    const double max =  20.0;

    double coef = 0.01 * (double)position;

    double val = min + coef * ( max - min );

    Data::get()->rotor.collective = deg2rad * val;

    ui->spinBoxCollective->setValue( val );
}

////////////////////////////////////////////////////////////////////////////////

void DialogRotor::on_sliderCyclicLon_sliderMoved(int position)
{
    const double min = -20.0;
    const double max =  20.0;

    double coef = 0.01 * (double)position;

    double val = min + coef * ( max - min );

    Data::get()->rotor.cyclicLon = deg2rad * val;

    ui->spinBoxCyclicLon->setValue( val );
}

////////////////////////////////////////////////////////////////////////////////

void DialogRotor::on_sliderCyclicLat_sliderMoved(int position)
{
    const double min = -20.0;
    const double max =  20.0;

    double coef = 0.01 * (double)position;

    double val = min + coef * ( max - min );

    Data::get()->rotor.cyclicLat = deg2rad * val;

    ui->spinBoxCyclicLat->setValue( val );
}

////////////////////////////////////////////////////////////////////////////////

void DialogRotor::on_sliderAzimuth_sliderMoved(int position)
{
    const double min =   0.0;
    const double max = 360.0;

    double coef = 0.01 * (double)position;

    double val = min + coef * ( max - min );

    Data::get()->rotor.azimuth = deg2rad * val;

    ui->spinBoxAzimuth->setValue( val );
}

////////////////////////////////////////////////////////////////////////////////

void DialogRotor::on_radioButtonCCW_toggled(bool checked)
{
    _ccw = checked;
}
