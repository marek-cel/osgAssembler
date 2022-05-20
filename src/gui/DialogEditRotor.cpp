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

#include <gui/DialogEditRotor.h>
#include <ui_DialogEditRotor.h>

////////////////////////////////////////////////////////////////////////////////

DialogEditRotor::DialogEditRotor(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::DialogEditRotor),
    _rotor( nullptr )
{
    _ui->setupUi( this );
}

////////////////////////////////////////////////////////////////////////////////

DialogEditRotor::~DialogEditRotor()
{
    if ( _ui ) delete _ui;
    _ui = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditRotor::edit( Rotor *rotor )
{
    _rotor = rotor;

    _ui->lineEditName->setText( _rotor->getName().c_str() );

    _ui->checkBoxDepthSortedBin->setChecked( _rotor->getDepthSortedBinState() );
    _ui->spinBoxDepthSortedBin->setValue( _rotor->getDepthSortedBinValue() );

    _ui->lineEditFileBlade->setText( _rotor->getFileBlade().c_str() );
    _ui->lineEditFileShaft->setText( _rotor->getFileShaft().c_str() );
    _ui->spinBoxBladesCount->setValue( _rotor->getBladesCount() );
    _ui->spinBoxBladesOffset->setValue( _rotor->getBladesOffset() );

    if ( _rotor->getDirection() == Rotor::CW )
    {
        _ui->radioButtonDirectionCW->setChecked( true );
        _ui->radioButtonDirectionCCW->setChecked( false );
    }
    else
    {
        _ui->radioButtonDirectionCW->setChecked( false );
        _ui->radioButtonDirectionCCW->setChecked( true );
    }

    _ui->spinBoxPositionX->setValue( _rotor->getPx() );
    _ui->spinBoxPositionY->setValue( _rotor->getPy() );
    _ui->spinBoxPositionZ->setValue( _rotor->getPz() );

    _ui->spinBoxAttitudeX->setValue( _rotor->getAx() );
    _ui->spinBoxAttitudeY->setValue( _rotor->getAy() );
    _ui->spinBoxAttitudeZ->setValue( _rotor->getAz() );

    show();
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditRotor::save()
{
    _rotor->setName( _ui->lineEditName->text().toLatin1().data() );

    _rotor->setDepthSortedBinValue( _ui->spinBoxDepthSortedBin->value() );
    _rotor->setDepthSortedBinState( _ui->checkBoxDepthSortedBin->isChecked() );

    _rotor->setFileBlade( _ui->lineEditFileBlade->text().toLatin1().data() );
    _rotor->setFileShaft( _ui->lineEditFileShaft->text().toLatin1().data() );
    _rotor->setBladesCount( _ui->spinBoxBladesCount->value() );
    _rotor->setBladesOffset( _ui->spinBoxBladesOffset->value() );

    _rotor->setDirection( ( _ui->radioButtonDirectionCW->isChecked() ) ? Rotor::CW : Rotor::CCW );

    double px = _ui->spinBoxPositionX->value();
    double py = _ui->spinBoxPositionY->value();
    double pz = _ui->spinBoxPositionZ->value();

    double ax = _ui->spinBoxAttitudeX->value();
    double ay = _ui->spinBoxAttitudeY->value();
    double az = _ui->spinBoxAttitudeZ->value();

    _rotor->setPx( px );
    _rotor->setPy( py );
    _rotor->setPz( pz );

    _rotor->setAx( ax );
    _rotor->setAy( ay );
    _rotor->setAz( az );
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditRotor::on_pushButtonBrowseBlade_clicked()
{
    QString newFile = getFile( _ui->lineEditFileBlade->text() );

    if ( newFile.length() > 0 )
    {
        _ui->lineEditFileBlade->setText( newFile );
    }
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditRotor::on_pushButtonBrowseShaft_clicked()
{
    QString newFile = getFile( _ui->lineEditFileShaft->text() );

    if ( newFile.length() > 0 )
    {
        _ui->lineEditFileShaft->setText( newFile );
    }
}

////////////////////////////////////////////////////////////////////////////////

QString DialogEditRotor::getFile(QString currentFile)
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

void DialogEditRotor::on_checkBoxDepthSortedBin_toggled(bool checked)
{
    _ui->spinBoxDepthSortedBin->setEnabled( checked );
}
