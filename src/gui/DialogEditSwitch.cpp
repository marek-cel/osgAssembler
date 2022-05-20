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

#include <gui/DialogEditSwitch.h>
#include <ui_DialogEditSwitch.h>

////////////////////////////////////////////////////////////////////////////////

DialogEditSwitch::DialogEditSwitch(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::DialogEditSwitch),
    _switch ( nullptr )
{
    _ui->setupUi( this );
}

////////////////////////////////////////////////////////////////////////////////

DialogEditSwitch::~DialogEditSwitch()
{
    if ( _ui ) delete _ui;
    _ui = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditSwitch::edit( Switch *aswitch )
{
    _switch = aswitch;

    _ui->lineEditName->setText( _switch->getName().c_str() );

    _ui->checkBoxDepthSortedBin->setChecked( _switch->getDepthSortedBinState() );
    _ui->spinBoxDepthSortedBin->setValue( _switch->getDepthSortedBinValue() );

    _ui->checkBoxVisible->setChecked( _switch->getVisible() );

    show();
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditSwitch::save()
{
    _switch->setName( _ui->lineEditName->text().toLatin1().data() );

    _switch->setDepthSortedBinValue( _ui->spinBoxDepthSortedBin->value() );
    _switch->setDepthSortedBinState( _ui->checkBoxDepthSortedBin->isChecked() );

    _switch->setVisible( _ui->checkBoxVisible->isChecked() );
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditSwitch::on_checkBoxDepthSortedBin_toggled(bool checked)
{
    _ui->spinBoxDepthSortedBin->setEnabled( checked );
}
