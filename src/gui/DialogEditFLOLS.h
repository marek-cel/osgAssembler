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
#ifndef DIALOGEDITFLOLS_H
#define DIALOGEDITFLOLS_H

////////////////////////////////////////////////////////////////////////////////

#include <QDialog>

#include <asm/FLOLS.h>

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class DialogEditFLOLS;
}

////////////////////////////////////////////////////////////////////////////////

/** Fresnel Lens Optical Landing System - FLOLS */
class DialogEditFLOLS : public QDialog
{
    Q_OBJECT

public:

    explicit DialogEditFLOLS( QWidget *parent = nullptr );

    ~DialogEditFLOLS();

    void edit( FLOLS *flols );
    void save();

private slots:

    void on_checkBoxDepthSortedBin_toggled(bool checked);

private:
    Ui::DialogEditFLOLS *_ui;

    FLOLS *_flols;
};

////////////////////////////////////////////////////////////////////////////////

#endif // DIALOGEDITFLOLS_H
