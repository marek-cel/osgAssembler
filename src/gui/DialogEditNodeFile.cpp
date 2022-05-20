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

#include <gui/DialogEditNodeFile.h>
#include <ui_DialogEditNodeFile.h>

////////////////////////////////////////////////////////////////////////////////

DialogEditNodeFile::DialogEditNodeFile(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::DialogEditNodeFile),
    _file ( nullptr )
{
    _ui->setupUi( this );
}

////////////////////////////////////////////////////////////////////////////////

DialogEditNodeFile::~DialogEditNodeFile()
{
    if ( _ui ) delete _ui;
    _ui = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditNodeFile::edit( NodeFile *file )
{
    _file = file;

    _ui->lineEditName->setText( _file->getName().c_str() );

    _ui->checkBoxDepthSortedBin->setChecked( _file->getDepthSortedBinState() );
    _ui->spinBoxDepthSortedBin->setValue( _file->getDepthSortedBinValue() );

    _ui->lineEditFile->setText( _file->getFile().c_str() );

    show();
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditNodeFile::save()
{
    _file->setName( _ui->lineEditName->text().toLatin1().data() );

    _file->setDepthSortedBinValue( _ui->spinBoxDepthSortedBin->value() );
    _file->setDepthSortedBinState( _ui->checkBoxDepthSortedBin->isChecked() );

    _file->setFile( _ui->lineEditFile->text().toLatin1().data() );
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditNodeFile::on_pushButtonBrowse_clicked()
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

void DialogEditNodeFile::on_checkBoxDepthSortedBin_toggled(bool checked)
{
    _ui->spinBoxDepthSortedBin->setEnabled( checked );
}
