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
#ifndef DIALOGLIGHTING_H
#define DIALOGLIGHTING_H

////////////////////////////////////////////////////////////////////////////////

#include <QDialog>

#include <asm/SceneRoot.h>

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class DialogLighting;
}

////////////////////////////////////////////////////////////////////////////////

class DialogLighting : public QDialog
{
    Q_OBJECT

public:

    explicit DialogLighting( QWidget *parent = nullptr );

    ~DialogLighting();

    void setSceneRoot( SceneRoot *sceneRoot )
    {
        _sceneRoot = sceneRoot;
    }

    void updateLighting();

private:

    Ui::DialogLighting *_ui;

    SceneRoot *_sceneRoot;

    void settingsRead();
    void settingsSave();

private slots:

    void on_accepted();
    void on_rejected();

    void on_spinBox_X_valueChanged(int arg1);
    void on_spinBox_Y_valueChanged(int arg1);
    void on_spinBox_Z_valueChanged(int arg1);

    void on_checkBoxEnabled_toggled(bool checked);
};

////////////////////////////////////////////////////////////////////////////////

#endif // DIALOGLIGHTING_H
