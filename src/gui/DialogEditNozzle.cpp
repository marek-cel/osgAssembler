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

#include <gui/DialogEditNozzle.h>
#include <ui_DialogEditNozzle.h>

////////////////////////////////////////////////////////////////////////////////

DialogEditNozzle::DialogEditNozzle(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::DialogEditNozzle),
    _nozzle( nullptr )
{
    _ui->setupUi( this );
}

////////////////////////////////////////////////////////////////////////////////

DialogEditNozzle::~DialogEditNozzle()
{
    if ( _ui ) delete _ui;
    _ui = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditNozzle::edit( Nozzle *nozzle )
{
    _nozzle = nozzle;

    _ui->lineEditName->setText( _nozzle->getName().c_str() );

    _ui->checkBoxDepthSortedBin->setChecked( _nozzle->getDepthSortedBinState() );
    _ui->spinBoxDepthSortedBin->setValue( _nozzle->getDepthSortedBinValue() );

    _ui->lineEditFileGlow->setText( _nozzle->getFileGlow().c_str() );
    _ui->lineEditFileExhaust->setText( _nozzle->getFileExhaust().c_str() );

    _ui->lineEditSuffix->setText( _nozzle->getSuffix().c_str() );

    _ui->spinBoxPositionX->setValue( _nozzle->getPx() );
    _ui->spinBoxPositionY->setValue( _nozzle->getPy() );
    _ui->spinBoxPositionZ->setValue( _nozzle->getPz() );

    _ui->spinBoxAttitudeX->setValue( _nozzle->getAx() );
    _ui->spinBoxAttitudeY->setValue( _nozzle->getAy() );
    _ui->spinBoxAttitudeZ->setValue( _nozzle->getAz() );

    show();
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditNozzle::save()
{
    _nozzle->setName( _ui->lineEditName->text().toLatin1().data() );

    _nozzle->setDepthSortedBinValue( _ui->spinBoxDepthSortedBin->value() );
    _nozzle->setDepthSortedBinState( _ui->checkBoxDepthSortedBin->isChecked() );

    _nozzle->setFileGlow( _ui->lineEditFileGlow->text().toLatin1().data() );
    _nozzle->setFileExhaust( _ui->lineEditFileExhaust->text().toLatin1().data() );

    _nozzle->setSuffix( _ui->lineEditSuffix->text().toLatin1().data() );

    double px = _ui->spinBoxPositionX->value();
    double py = _ui->spinBoxPositionY->value();
    double pz = _ui->spinBoxPositionZ->value();

    double ax = _ui->spinBoxAttitudeX->value();
    double ay = _ui->spinBoxAttitudeY->value();
    double az = _ui->spinBoxAttitudeZ->value();

    _nozzle->setPx( px );
    _nozzle->setPy( py );
    _nozzle->setPz( pz );

    _nozzle->setAx( ax );
    _nozzle->setAy( ay );
    _nozzle->setAz( az );
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditNozzle::on_pushButtonBrowseGlow_clicked()
{
    QString newFile = getFile( _ui->lineEditFileGlow->text() );

    if ( newFile.length() > 0 )
    {
        _ui->lineEditFileGlow->setText( newFile );
    }
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditNozzle::on_pushButtonBrowseExhaust_clicked()
{
    QString newFile = getFile( _ui->lineEditFileExhaust->text() );

    if ( newFile.length() > 0 )
    {
        _ui->lineEditFileExhaust->setText( newFile );
    }
}

////////////////////////////////////////////////////////////////////////////////

QString DialogEditNozzle::getFile(QString currentFile)
{
    QString caption = "Browse";
    QString dir = ( currentFile.length() > 0 ) ? QFileInfo( currentFile ).absolutePath() : ".";
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

    return newFile;
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditNozzle::on_checkBoxDepthSortedBin_toggled(bool checked)
{
    _ui->spinBoxDepthSortedBin->setEnabled( checked );
}
