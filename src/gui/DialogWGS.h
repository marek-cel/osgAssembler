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
#ifndef DIALOGWGS_H
#define DIALOGWGS_H

////////////////////////////////////////////////////////////////////////////////

#include <QDialog>

#include <osg/Vec3d>
#include <osg/Quat>

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class DialogWGS;
}

////////////////////////////////////////////////////////////////////////////////

class DialogWGS : public QDialog
{
    Q_OBJECT

public:

    struct PosAtt
    {
        double x;
        double y;
        double z;

        double phi;
        double tht;
        double psi;

        bool accepted;
    };

    static PosAtt getPosAtt( QWidget *parent = Q_NULLPTR );

    explicit DialogWGS( QWidget *parent = nullptr );

    ~DialogWGS();

    inline double getX() const { return _x; }
    inline double getY() const { return _y; }
    inline double getZ() const { return _z; }

    inline double getPhi() const { return _phi; }
    inline double getTht() const { return _tht; }
    inline double getPsi() const { return _psi; }

private:

    Ui::DialogWGS *_ui;

    double _x;      ///< [m]
    double _y;      ///< [m]
    double _z;      ///< [m]

    double _phi;    ///< [rad]
    double _tht;    ///< [rad]
    double _psi;    ///< [rad]

    bool _reversed;

    void calc();

private slots:

    void on_spinBoxLat_valueChanged(double arg1);
    void on_spinBoxLon_valueChanged(double arg1);
    void on_spinBoxAlt_valueChanged(double arg1);
    void on_checkBoxRev_toggled(bool checked);
};

////////////////////////////////////////////////////////////////////////////////

#endif // DIALOGWGS_H
