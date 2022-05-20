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

#include <gui/DialogEditSmoke.h>
#include <ui_DialogEditSmoke.h>

////////////////////////////////////////////////////////////////////////////////

DialogEditSmoke::DialogEditSmoke(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::DialogEditSmoke),
    _smoke( nullptr )
{
    _ui->setupUi( this );
}

////////////////////////////////////////////////////////////////////////////////

DialogEditSmoke::~DialogEditSmoke()
{
    if ( _ui ) delete _ui;
    _ui = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditSmoke::edit( Smoke *smoke )
{
    _smoke = smoke;

    _ui->lineEditName->setText( _smoke->getName().c_str() );

    _ui->checkBoxDepthSortedBin->setChecked( _smoke->getDepthSortedBinState() );
    _ui->spinBoxDepthSortedBin->setValue( _smoke->getDepthSortedBinValue() );

    _ui->spinBoxPositionX->setValue( _smoke->getPx() );
    _ui->spinBoxPositionY->setValue( _smoke->getPy() );
    _ui->spinBoxPositionZ->setValue( _smoke->getPz() );

    show();
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditSmoke::save()
{
    _smoke->setName( _ui->lineEditName->text().toLatin1().data() );

    _smoke->setDepthSortedBinValue( _ui->spinBoxDepthSortedBin->value() );
    _smoke->setDepthSortedBinState( _ui->checkBoxDepthSortedBin->isChecked() );

    double px = _ui->spinBoxPositionX->value();
    double py = _ui->spinBoxPositionY->value();
    double pz = _ui->spinBoxPositionZ->value();

    _smoke->setPx( px );
    _smoke->setPy( py );
    _smoke->setPz( pz );
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditSmoke::on_checkBoxDepthSortedBin_toggled(bool checked)
{
    _ui->spinBoxDepthSortedBin->setEnabled( checked );
}
