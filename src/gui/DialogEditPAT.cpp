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

#include <gui/DialogEditPAT.h>
#include <ui_DialogEditPAT.h>

#include <gui/DialogWGS.h>

////////////////////////////////////////////////////////////////////////////////

DialogEditPAT::DialogEditPAT(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::DialogEditPAT),
    _pat( nullptr )
{
    _ui->setupUi( this );
}

////////////////////////////////////////////////////////////////////////////////

DialogEditPAT::~DialogEditPAT()
{
    if ( _ui ) delete _ui;
    _ui = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditPAT::edit( PAT *pat )
{
    _pat = pat;

    _ui->lineEditName->setText( _pat->getName().c_str() );

    _ui->checkBoxDepthSortedBin->setChecked( _pat->getDepthSortedBinState() );
    _ui->spinBoxDepthSortedBin->setValue( _pat->getDepthSortedBinValue() );

    _ui->spinBoxPositionX->setValue( _pat->getPx() );
    _ui->spinBoxPositionY->setValue( _pat->getPy() );
    _ui->spinBoxPositionZ->setValue( _pat->getPz() );

    _ui->spinBoxAttitudeX->setValue( _pat->getAx() );
    _ui->spinBoxAttitudeY->setValue( _pat->getAy() );
    _ui->spinBoxAttitudeZ->setValue( _pat->getAz() );

    if ( _pat->getConvention() == PAT::XYZ )
    {
        _ui->radioButtonXYZ->setChecked( true );
    }
    else
    {
        _ui->radioButtonZYX->setChecked( true );
    }

    show();
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditPAT::save()
{
    _pat->setName( _ui->lineEditName->text().toLatin1().data() );

    _pat->setDepthSortedBinValue( _ui->spinBoxDepthSortedBin->value() );
    _pat->setDepthSortedBinState( _ui->checkBoxDepthSortedBin->isChecked() );

    double px = _ui->spinBoxPositionX->value();
    double py = _ui->spinBoxPositionY->value();
    double pz = _ui->spinBoxPositionZ->value();

    double ax = _ui->spinBoxAttitudeX->value();
    double ay = _ui->spinBoxAttitudeY->value();
    double az = _ui->spinBoxAttitudeZ->value();

    _pat->setPx( px );
    _pat->setPy( py );
    _pat->setPz( pz );

    _pat->setAx( ax );
    _pat->setAy( ay );
    _pat->setAz( az );

    PAT::Convention convention = PAT::XYZ;

    if ( _ui->radioButtonZYX->isChecked() )
    {
        convention = PAT::ZYX;
    }

    _pat->setConvention( convention );
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditPAT::on_checkBoxDepthSortedBin_toggled(bool checked)
{
    _ui->spinBoxDepthSortedBin->setEnabled( checked );
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditPAT::on_pushButtonFromGeo_clicked()
{
    DialogWGS::PosAtt pos_att = DialogWGS::getPosAtt( this );

    if ( pos_att.accepted )
    {
        //_ui->radioButtonZYX->setChecked( true );
        _ui->radioButtonXYZ->setChecked( true );

        _ui->spinBoxPositionX->setValue( pos_att.x );
        _ui->spinBoxPositionY->setValue( pos_att.y );
        _ui->spinBoxPositionZ->setValue( pos_att.z );

        _ui->spinBoxAttitudeX->setValue( osg::RadiansToDegrees( pos_att.phi ) );
        _ui->spinBoxAttitudeY->setValue( osg::RadiansToDegrees( pos_att.tht ) );
        _ui->spinBoxAttitudeZ->setValue( osg::RadiansToDegrees( pos_att.psi ) );
    }
}
