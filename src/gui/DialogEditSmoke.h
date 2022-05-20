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
#ifndef DIALOGEDITSMOKE_H
#define DIALOGEDITSMOKE_H

////////////////////////////////////////////////////////////////////////////////

#include <QDialog>

#include <asm/Smoke.h>

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class DialogEditSmoke;
}

////////////////////////////////////////////////////////////////////////////////

class DialogEditSmoke : public QDialog
{
    Q_OBJECT

public:

    explicit DialogEditSmoke( QWidget *parent = nullptr );

    ~DialogEditSmoke();

    void edit( Smoke *smoke );
    void save();

private slots:
    void on_checkBoxDepthSortedBin_toggled(bool checked);

private:
    Ui::DialogEditSmoke *_ui;

    Smoke *_smoke;
};

////////////////////////////////////////////////////////////////////////////////

#endif // DIALOGEDITSMOKE_H
