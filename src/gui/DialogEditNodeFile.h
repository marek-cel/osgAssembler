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
#ifndef DIALOGEDITNODEFILE_H
#define DIALOGEDITNODEFILE_H

////////////////////////////////////////////////////////////////////////////////

#include <QDialog>

#include <asm/NodeFile.h>

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class DialogEditNodeFile;
}

////////////////////////////////////////////////////////////////////////////////

class DialogEditNodeFile : public QDialog
{
    Q_OBJECT

public:

    explicit DialogEditNodeFile( QWidget *parent = nullptr );

    ~DialogEditNodeFile();

    void edit( NodeFile *file );
    void save();

private slots:
    void on_pushButtonBrowse_clicked();

    void on_checkBoxDepthSortedBin_toggled(bool checked);

private:
    Ui::DialogEditNodeFile *_ui;

    NodeFile *_file;
};

////////////////////////////////////////////////////////////////////////////////

#endif // DIALOGEDITNODEFILE_H
