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
#ifndef DIALOGEDITROTOR_H
#define DIALOGEDITROTOR_H

////////////////////////////////////////////////////////////////////////////////

#include <QDialog>

#include <asm/Rotor.h>

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class DialogEditRotor;
}

////////////////////////////////////////////////////////////////////////////////

class DialogEditRotor : public QDialog
{
    Q_OBJECT

public:

    explicit DialogEditRotor( QWidget *parent = nullptr );

    ~DialogEditRotor();

    void edit( Rotor *rotor );
    void save();

private slots:

    void on_pushButtonBrowseBlade_clicked();
    void on_pushButtonBrowseShaft_clicked();

    void on_checkBoxDepthSortedBin_toggled(bool checked);

private:

    Ui::DialogEditRotor *_ui;

    Rotor *_rotor;

    QString getFile( QString currentFile );
};

////////////////////////////////////////////////////////////////////////////////

#endif // DIALOGEDITROTOR_H
