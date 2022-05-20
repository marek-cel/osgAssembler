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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

////////////////////////////////////////////////////////////////////////////////

#include <QMainWindow>
#include <QSettings>
#include <QShortcut>

#include "DialogLighting.h"
#include "DialogRotor.h"
#include "RecentFileAction.h"

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class MainWindow;
}

////////////////////////////////////////////////////////////////////////////////

/** */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

    /** */
    explicit MainWindow( QWidget *parent = nullptr );

    /** */
    virtual ~MainWindow();

protected:

    /** */
    void closeEvent( QCloseEvent *event );

    /** */
    void keyPressEvent( QKeyEvent *event );

    /** */
    void timerEvent( QTimerEvent *event );
    
private:

    Ui::MainWindow *_ui;        ///<

    DialogLighting *_dialogLighting;
    DialogRotor *_dialogRotor;  ///<

    QShortcut *_shortcutSave;
    QShortcut *_shortcutExport;
    QShortcut *_shortcutRefresh;

    bool _saved;                ///<
    int _timerId;               ///<

    QString _currentFile;       ///<

    QStringList _recentFilesList;   ///<
    std::vector< RecentFileAction* > _recentFilesActions;

    void askIfSave();

    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void exportFileAs();

    void readFile( QString fileName );
    void saveFile( QString fileName );
    void exportAs( QString fileName );

    void settingsRead();
    void settingsRead_RecentFiles( QSettings &settings );

    void settingsSave();
    void settingsSave_RecentFiles( QSettings &settings );

    void updateGUI();
    void updateRecentFiles( QString file = "" );

public slots:

    void document_changed();
    void recentFile_triggered( int id );

private slots:

    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionExport_triggered();
    void on_actionExit_triggered();

    void on_actionClearRecent_triggered();

    void on_actionRotor_triggered();

    void on_actionRefresh_triggered();

    void on_actionViewOrbit_triggered();
    void on_actionViewTrack_triggered();

    void on_actionLighting_triggered();

    void on_actionAbout_triggered();
};

////////////////////////////////////////////////////////////////////////////////

#endif // MAINWINDOW_H
