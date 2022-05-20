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

#include <QFileDialog>

#include <gui/DialogEditFLOLS.h>
#include <ui_DialogEditFLOLS.h>

////////////////////////////////////////////////////////////////////////////////

DialogEditFLOLS::DialogEditFLOLS(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::DialogEditFLOLS),
    _flols( nullptr )
{
    _ui->setupUi( this );
}

////////////////////////////////////////////////////////////////////////////////

DialogEditFLOLS::~DialogEditFLOLS()
{
    if ( _ui ) delete _ui;
    _ui = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditFLOLS::edit( FLOLS *flols )
{
    _flols = flols;

    _ui->checkBoxDepthSortedBin->setChecked( _flols->getDepthSortedBinState() );
    _ui->spinBoxDepthSortedBin->setValue( _flols->getDepthSortedBinValue() );

    _ui->spinBoxPositionX->setValue( _flols->getPx() );
    _ui->spinBoxPositionY->setValue( _flols->getPy() );
    _ui->spinBoxPositionZ->setValue( _flols->getPz() );

    _ui->spinBoxAttitudeX->setValue( _flols->getAx() );
    _ui->spinBoxAttitudeY->setValue( _flols->getAy() );
    _ui->spinBoxAttitudeZ->setValue( _flols->getAz() );

    show();
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditFLOLS::save()
{
    _flols->setName( _ui->lineEditName->text().toLatin1().data() );

    _flols->setDepthSortedBinValue( _ui->spinBoxDepthSortedBin->value() );
    _flols->setDepthSortedBinState( _ui->checkBoxDepthSortedBin->isChecked() );

    double px = _ui->spinBoxPositionX->value();
    double py = _ui->spinBoxPositionY->value();
    double pz = _ui->spinBoxPositionZ->value();

    double ax = _ui->spinBoxAttitudeX->value();
    double ay = _ui->spinBoxAttitudeY->value();
    double az = _ui->spinBoxAttitudeZ->value();

    _flols->setPx( px );
    _flols->setPy( py );
    _flols->setPz( pz );

    _flols->setAx( ax );
    _flols->setAy( ay );
    _flols->setAz( az );
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditFLOLS::on_checkBoxDepthSortedBin_toggled(bool checked)
{
    _ui->spinBoxDepthSortedBin->setEnabled( checked );
}
