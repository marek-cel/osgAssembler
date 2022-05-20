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

#include <gui/DialogLighting.h>
#include <ui_DialogLighting.h>

#include <QSettings>

#include <defs.h>

////////////////////////////////////////////////////////////////////////////////

DialogLighting::DialogLighting( QWidget *parent ) :
    QDialog( parent ),
    _ui( new Ui::DialogLighting ),
    _sceneRoot ( nullptr )
{
    _ui->setupUi( this );

    connect( this, SIGNAL(accepted()), this, SLOT(on_accepted()) );
    connect( this, SIGNAL(rejected()), this, SLOT(on_rejected()) );

    settingsRead();
}

////////////////////////////////////////////////////////////////////////////////

DialogLighting::~DialogLighting()
{
    if ( _ui ) { delete _ui; } _ui = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void DialogLighting::updateLighting()
{
    if ( _sceneRoot )
    {
        _sceneRoot->setLightingPositionX( _ui->spinBox_X->value() );
        _sceneRoot->setLightingPositionY( _ui->spinBox_Y->value() );
        _sceneRoot->setLightingPositionZ( _ui->spinBox_Z->value() );
        _sceneRoot->setLightingEnabled( _ui->checkBoxEnabled->isChecked() );
    }
}

////////////////////////////////////////////////////////////////////////////////

void DialogLighting::settingsRead()
{
    QSettings settings( ORG_NAME, APP_NAME );

    settings.beginGroup( "dialog_lighting" );

    _ui->spinBox_X->setValue( settings.value( "position_x",     0 ).toInt() );
    _ui->spinBox_Y->setValue( settings.value( "position_y",     0 ).toInt() );
    _ui->spinBox_Z->setValue( settings.value( "position_z", 10000 ).toInt() );

    _ui->checkBoxEnabled->setChecked( settings.value( "enabled", 1 ).toBool() );


    settings.endGroup();
}

////////////////////////////////////////////////////////////////////////////////

void DialogLighting::settingsSave()
{
    QSettings settings( ORG_NAME, APP_NAME );

    settings.beginGroup( "dialog_lighting" );

    settings.setValue( "position_x", _ui->spinBox_X->value() );
    settings.setValue( "position_y", _ui->spinBox_Y->value() );
    settings.setValue( "position_z", _ui->spinBox_Z->value() );

    settings.setValue( "enabled", _ui->checkBoxEnabled->isChecked() ? 1 : 0 );

    settings.endGroup();
}

////////////////////////////////////////////////////////////////////////////////

void DialogLighting::on_accepted()
{
    settingsSave();
    updateLighting();
}

////////////////////////////////////////////////////////////////////////////////

void DialogLighting::on_rejected()
{
    settingsRead();
    updateLighting();
}

////////////////////////////////////////////////////////////////////////////////

void DialogLighting::on_spinBox_X_valueChanged(int arg1)
{
    if ( _sceneRoot ) _sceneRoot->setLightingPositionX( arg1 );
}

////////////////////////////////////////////////////////////////////////////////

void DialogLighting::on_spinBox_Y_valueChanged(int arg1)
{
    if ( _sceneRoot ) _sceneRoot->setLightingPositionY( arg1 );
}

////////////////////////////////////////////////////////////////////////////////

void DialogLighting::on_spinBox_Z_valueChanged(int arg1)
{
    if ( _sceneRoot ) _sceneRoot->setLightingPositionZ( arg1 );
}

////////////////////////////////////////////////////////////////////////////////

void DialogLighting::on_checkBoxEnabled_toggled(bool checked)
{
    if ( _sceneRoot ) _sceneRoot->setLightingEnabled( checked );
}

