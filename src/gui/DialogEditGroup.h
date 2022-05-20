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
#ifndef DIALOGEDITGROUP_H
#define DIALOGEDITGROUP_H

////////////////////////////////////////////////////////////////////////////////

#include <QDialog>

#include <asm/Group.h>

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class DialogEditGroup;
}

////////////////////////////////////////////////////////////////////////////////

class DialogEditGroup : public QDialog
{
    Q_OBJECT

public:

    explicit DialogEditGroup( QWidget *parent = nullptr );

    ~DialogEditGroup();

    void edit( Group *group );
    void save();

private slots:
    void on_checkBoxDepthSortedBin_toggled(bool checked);

private:
    Ui::DialogEditGroup *_ui;

    Group *_group;
};

////////////////////////////////////////////////////////////////////////////////

#endif // DIALOGEDITGROUP_H
