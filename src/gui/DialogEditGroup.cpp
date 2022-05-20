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

#include <gui/DialogEditGroup.h>
#include <ui_DialogEditGroup.h>

////////////////////////////////////////////////////////////////////////////////

DialogEditGroup::DialogEditGroup(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::DialogEditGroup),
    _group ( nullptr )
{
    _ui->setupUi( this );
}

////////////////////////////////////////////////////////////////////////////////

DialogEditGroup::~DialogEditGroup()
{
    if ( _ui ) delete _ui;
    _ui = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditGroup::edit( Group *group )
{
    _group = group;

    _ui->lineEditName->setText( _group->getName().c_str() );

    _ui->checkBoxDepthSortedBin->setChecked( _group->getDepthSortedBinState() );
    _ui->spinBoxDepthSortedBin->setValue( _group->getDepthSortedBinValue() );

    show();
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditGroup::save()
{
    _group->setName( _ui->lineEditName->text().toLatin1().data() );

    _group->setDepthSortedBinValue( _ui->spinBoxDepthSortedBin->value() );
    _group->setDepthSortedBinState( _ui->checkBoxDepthSortedBin->isChecked() );
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditGroup::on_checkBoxDepthSortedBin_toggled(bool checked)
{
    _ui->spinBoxDepthSortedBin->setEnabled( checked );
}
