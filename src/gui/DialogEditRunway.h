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
#ifndef DIALOGEDITRUNWAY_H
#define DIALOGEDITRUNWAY_H

////////////////////////////////////////////////////////////////////////////////

#include <QDialog>
#include <QListWidgetItem>

#include <asm/Runway.h>

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class DialogEditRunway;
}

////////////////////////////////////////////////////////////////////////////////

class DialogEditRunway : public QDialog
{
    Q_OBJECT

public:

    explicit DialogEditRunway( QWidget *parent = nullptr );

    ~DialogEditRunway();

    void edit( Runway *runway );
    void save();

private slots:

    void on_checkBoxDepthSortedBin_toggled( bool checked );

    void on_pushButtonGapAdd_clicked();
    void on_pushButtonGapEdit_clicked();
    void on_pushButtonGapRemove_clicked();

    void on_listWidgetGaps_doubleClicked( const QModelIndex &index );

private:

    Ui::DialogEditRunway *_ui;

    Runway *_runway;

    Gaps _gaps;

    Runway::RALS getRALS( int index );
    Runway::VGSI getVGSI( int index );

    void editGap();

    void updateListWidgetGaps();
};

////////////////////////////////////////////////////////////////////////////////

#endif // DIALOGEDITRUNWAY_H
