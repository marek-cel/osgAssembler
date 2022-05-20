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

#include <gui/DialogEditWorld.h>
#include <ui_DialogEditWorld.h>

#include <QFileDialog>

////////////////////////////////////////////////////////////////////////////////

DialogEditWorld::DialogEditWorld(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::DialogEditWorld),
    _world( nullptr )
{
    _ui->setupUi( this );
}

////////////////////////////////////////////////////////////////////////////////

DialogEditWorld::~DialogEditWorld()
{
    if ( _ui ) delete _ui;
    _ui = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditWorld::edit( World *world )
{
    _world = world;

    _ui->lineEditName->setText( _world->getName().c_str() );

    _ui->checkBoxDepthSortedBin->setChecked( _world->getDepthSortedBinState() );
    _ui->spinBoxDepthSortedBin->setValue( _world->getDepthSortedBinValue() );

    _ui->spinBoxLat->setValue( _world->getLat() );
    _ui->spinBoxLon->setValue( _world->getLon() );
    _ui->spinBoxAlt->setValue( _world->getAlt() );

    _ui->lineEditFile->setText( _world->getFile().c_str() );

    show();
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditWorld::save()
{
    _world->setName( _ui->lineEditName->text().toLatin1().data() );

    _world->setDepthSortedBinValue( _ui->spinBoxDepthSortedBin->value() );
    _world->setDepthSortedBinState( _ui->checkBoxDepthSortedBin->isChecked() );

    _world->setLat( _ui->spinBoxLat->value() );
    _world->setLon( _ui->spinBoxLon->value() );
    _world->setAlt( _ui->spinBoxAlt->value() );

    _world->setFile( _ui->lineEditFile->text().toLatin1().data() );
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditWorld::on_pushButtonBrowse_clicked()
{
    QString file = _ui->lineEditFile->text();

    QString caption = "Browse";
    QString dir = ( file.length() > 0 ) ? QFileInfo( file ).path() : ".";
    QString filter;
    QString selectedFilter;

    filter += "AC3D (*.ac)";
    filter += ";;";
    filter += "3D Studio (*.3ds)";
    filter += ";;";
    filter += "COLLADA (*.dae)";
    filter += ";;";
    filter += selectedFilter = "OpenSceneGraph (*.osg *.osga *.osgb *.osgt *.ive)";
    filter += ";;";
    filter += "Wavefront OBJ (*.obj)";

    QString newFile = QFileDialog::getOpenFileName( this, caption, dir, filter, &selectedFilter );
    QString workDir = QDir::currentPath();

    // relative path
    if ( 1 )
    {
        int n = newFile.length() - workDir.length() - 1;
        newFile = newFile.right( n );
    }

    if ( newFile.length() > 0 )
    {
        _ui->lineEditFile->setText( newFile );
    }
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditWorld::on_checkBoxDepthSortedBin_toggled(bool checked)
{
    _ui->spinBoxDepthSortedBin->setEnabled( checked );
}
