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

#include <gui/DialogWGS.h>
#include <ui_DialogWGS.h>

#include <asm/WGS84.h>

DialogWGS::PosAtt DialogWGS::getPosAtt( QWidget *parent )
{
    PosAtt result;

    result.x = 0.0;
    result.y = 0.0;
    result.z = 0.0;

    result.phi = 0.0;
    result.tht = 0.0;
    result.psi = 0.0;

    result.accepted = false;

    DialogWGS *dialog = Q_NULLPTR;

    dialog = new DialogWGS( parent );

    if ( dialog->exec() == QDialog::Accepted )
    {
        result.x = dialog->getX();
        result.y = dialog->getY();
        result.z = dialog->getZ();

        result.phi = dialog->getPhi();
        result.tht = dialog->getTht();
        result.psi = dialog->getPsi();

        result.accepted = true;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////

DialogWGS::DialogWGS( QWidget *parent ) :
    QDialog( parent ),
    _ui( new Ui::DialogWGS ),
    _reversed ( false )
{
    _ui->setupUi( this );
}

////////////////////////////////////////////////////////////////////////////////

DialogWGS::~DialogWGS()
{
    if ( _ui ) delete _ui;
    _ui = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void DialogWGS::calc()
{
    double lat_rad = osg::DegreesToRadians( _ui->spinBoxLat->value() );
    double lon_rad = osg::DegreesToRadians( _ui->spinBoxLon->value() );

    WGS84 wgs( lat_rad, lon_rad, _ui->spinBoxAlt->value() );

    osg::Quat  att = wgs.getAttitude();
    osg::Vec3d pos = wgs.getPosition();

    if ( _reversed )
    {
        pos = -pos;
        att = att.inverse();
    }
    else
    {
        //att = att.inverse();
    }

    _x = pos.x();
    _y = pos.y();
    _z = pos.z();

    osg::Matrix rot_mat;
    rot_mat.makeRotate( att );

    double sinTht = -rot_mat(0,2);
    double cosTht = sqrt( 1.0 - std::min( 1.0, sinTht*sinTht ) );

    _tht = atan2( sinTht, cosTht );

    if ( cosTht > 0.0 )
    {
        _phi = atan2( rot_mat(1,2), rot_mat(2,2) );
        _psi = atan2( rot_mat(0,1), rot_mat(0,0) );
    }
    else
    {
        _phi = atan2( rot_mat(1,0), -rot_mat(2,0) );
        _psi = 0.0;
    }
}

////////////////////////////////////////////////////////////////////////////////

void DialogWGS::on_spinBoxLat_valueChanged(double )
{
    calc();
}

////////////////////////////////////////////////////////////////////////////////

void DialogWGS::on_spinBoxLon_valueChanged(double )
{
    calc();
}

////////////////////////////////////////////////////////////////////////////////

void DialogWGS::on_spinBoxAlt_valueChanged(double )
{
    calc();
}

////////////////////////////////////////////////////////////////////////////////

void DialogWGS::on_checkBoxRev_toggled(bool checked)
{
    _reversed = checked;
}
