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

#include <gui/DialogEditLOD.h>
#include <ui_DialogEditLOD.h>

////////////////////////////////////////////////////////////////////////////////

DialogEditLOD::DialogEditLOD(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::DialogEditLOD),
    _lod( nullptr )
{
    _ui->setupUi( this );
}

////////////////////////////////////////////////////////////////////////////////

DialogEditLOD::~DialogEditLOD()
{
    if ( _ui ) delete _ui;
    _ui = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditLOD::edit( LOD *lod )
{
    _lod = lod;

    _ui->lineEditName->setText( _lod->getName().c_str() );

    _ui->checkBoxDepthSortedBin->setChecked( _lod->getDepthSortedBinState() );
    _ui->spinBoxDepthSortedBin->setValue( _lod->getDepthSortedBinValue() );

    _ui->spinBoxInterval_F->setValue( _lod->getIntervalF() );
    _ui->spinBoxInterval_S->setValue( _lod->getIntervalS() );
    _ui->spinBoxInterval_O->setValue( _lod->getIntervalO() );

    show();
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditLOD::save()
{
    _lod->setName( _ui->lineEditName->text().toLatin1().data() );

    _lod->setDepthSortedBinValue( _ui->spinBoxDepthSortedBin->value() );
    _lod->setDepthSortedBinState( _ui->checkBoxDepthSortedBin->isChecked() );

    _lod->setIntervalF( _ui->spinBoxInterval_F->value() );
    _lod->setIntervalS( _ui->spinBoxInterval_S->value() );
    _lod->setIntervalO( _ui->spinBoxInterval_O->value() );
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditLOD::on_checkBoxDepthSortedBin_toggled(bool checked)
{
    _ui->spinBoxDepthSortedBin->setEnabled( checked );
}
