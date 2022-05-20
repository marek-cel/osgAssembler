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

#include <iostream>

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

#include <asm/Models.h>
#include <asm/Textures.h>

#include <defs.h>
#include <gui/MainWindow.h>
#include <ui_MainWindow.h>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow ( parent ),
    _ui ( new Ui::MainWindow ),

    _dialogLighting ( nullptr ),
    _dialogRotor ( nullptr ),

    _shortcutSave ( nullptr ),
    _shortcutExport ( nullptr ),
    _shortcutRefresh ( nullptr ),

    _saved ( true ),
    _timerId ( 0 )
{
    _ui->setupUi( this );

    connect( _ui->widgetDoc, SIGNAL(changed()), this, SLOT(document_changed()) );

    _dialogLighting = new DialogLighting( this );
    _dialogRotor = new DialogRotor( this );

    _shortcutSave = new QShortcut( QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(on_actionSave_triggered()) );
    _shortcutExport = new QShortcut( QKeySequence(Qt::CTRL + Qt::Key_E), this, SLOT(on_actionExport_triggered()) );
    _shortcutRefresh =  new QShortcut( QKeySequence(Qt::CTRL + Qt::Key_R), this, SLOT(on_actionRefresh_triggered()) );

    settingsRead();

    _dialogLighting->setSceneRoot( _ui->widgetCGI->getSceneRoot() );
    _dialogLighting->updateLighting();

    _timerId = startTimer( 50 );

    updateGUI();
}

////////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow()
{
    killTimer( _timerId );

    settingsSave();

    if ( _dialogRotor ) delete _dialogRotor;
    _dialogRotor = nullptr;

    if ( _shortcutSave ) delete _shortcutSave;
    _shortcutSave = nullptr;

    if ( _shortcutExport ) delete _shortcutExport;
    _shortcutExport = nullptr;

    if ( _shortcutRefresh ) delete _shortcutRefresh;
    _shortcutRefresh = nullptr;

    if ( _ui ) delete _ui;
    _ui = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::closeEvent( QCloseEvent *event )
{
    askIfSave();

    /////////////////////////////////
    QMainWindow::closeEvent( event );
    /////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::keyPressEvent( QKeyEvent *event )
{
    ////////////////////////////////////
    QMainWindow::keyPressEvent( event );
    ////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::timerEvent( QTimerEvent *event )
{
    /////////////////////////////////
    QMainWindow::timerEvent( event );
    /////////////////////////////////

    if ( _ui->widgetCGI->isVisible() )
    {
        _ui->widgetCGI->update();
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::askIfSave()
{
    if ( !_saved )
    {
        QString title = windowTitle();
        QString text = tr( "File have unsaved changes." );

        QMessageBox::StandardButton result = QMessageBox::question( this, title, text,
                                                                    QMessageBox::Save | QMessageBox::Discard,
                                                                    QMessageBox::Save );

        if ( result == QMessageBox::Save )
        {
            saveFile();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::newFile()
{
    askIfSave();

    _currentFile = "";

    _ui->widgetDoc->newEmpty();

    updateGUI();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::openFile()
{
    askIfSave();

    QString caption = "Open...";
    QString dir = ( _currentFile.length() > 0 ) ? QFileInfo( _currentFile ).absolutePath() : "";
    QString filter;
    QString selectedFilter;

    filter += selectedFilter = "XML (*.xml)";

    QString file = QFileDialog::getOpenFileName( this, caption, dir, filter, &selectedFilter );

    if ( file.length() > 0 )
    {
        _currentFile = file;

        updateRecentFiles( _currentFile );
        readFile( _currentFile );
    }

    updateGUI();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::saveFile()
{
    if ( _currentFile.length() > 0 )
    {
        saveFile( _currentFile );
    }
    else
    {
        saveFileAs();
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::saveFileAs()
{
    QString caption = "Save as...";
    QString dir = ( _currentFile.length() > 0 ) ? QFileInfo( _currentFile ).absolutePath() : ".";
    QString filter;
    QString selectedFilter;

    filter += selectedFilter = "XML (*.xml)";

    QString newFile = QFileDialog::getSaveFileName( this, caption, dir, filter, &selectedFilter );

    if ( newFile.length() > 0 )
    {
        _currentFile = newFile;
        saveFile( _currentFile );
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::exportFileAs()
{
    QString fileName = "";

    QString caption = "Export as...";
    QString dir = ( fileName.length() > 0 ) ? QFileInfo( fileName ).absolutePath() : ".";
    QString filter;
    QString selectedFilter;

    filter += "AC3D (*.ac)";
    filter += ";;";
    filter += "3D Studio (*.3ds)";
    filter += ";;";
    filter += "COLLADA (*.dae)";
    filter += ";;";
    filter += selectedFilter = "OpenSceneGraph (*.osg *.osga *.osgb *.osgt *.ive)";
    filter += ";;";
    filter += "Wavefront OBJ (*.obj)";

    fileName = QFileDialog::getSaveFileName( this, caption, dir, filter, &selectedFilter );

    if ( fileName.length() > 0 )
    {
        exportAs( fileName );
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::readFile( QString fileName )
{
    if ( QFileInfo( fileName ).suffix() == QString( "xml" ) )
    {
        if ( !_ui->widgetDoc->readFile( fileName ) )
        {
            QMessageBox::warning( this, tr( APP_TITLE ),
                                 tr( "Cannot read file %1:." ).arg( fileName ) );
        }
    }

    updateGUI();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::saveFile( QString fileName )
{
    if ( _ui->widgetDoc->saveFile( fileName ) )
    {
        _saved = true;
    }
    else
    {
        QMessageBox::warning( this, tr( APP_TITLE ),
                             tr( "Cannot save file %1:." ).arg(fileName) );
    }

    updateGUI();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::exportAs( QString fileName )
{
    if ( !_ui->widgetDoc->exportAs( fileName ) )
    {
        QMessageBox::warning( this, tr( APP_TITLE ),
                             tr( "Cannot export file %1:." ).arg(fileName) );
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::settingsRead()
{
    QSettings settings( ORG_NAME, APP_NAME );

    settings.beginGroup( "main_window" );

    restoreState( settings.value( "state" ).toByteArray() );
    restoreGeometry( settings.value( "geometry" ).toByteArray() );

    settingsRead_RecentFiles( settings );

    settings.endGroup();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::settingsRead_RecentFiles( QSettings &settings )
{
    _recentFilesList = settings.value( "recent_files" ).toStringList();

    updateRecentFiles();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::settingsSave()
{
    QSettings settings( ORG_NAME, APP_NAME );

    settings.beginGroup( "main_window" );

    settings.setValue( "state"    , saveState() );
    settings.setValue( "geometry" , saveGeometry() );

    settingsSave_RecentFiles( settings );

    settings.endGroup();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::settingsSave_RecentFiles( QSettings &settings )
{
    settings.setValue( "recent_files", _recentFilesList );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::updateGUI()
{
    _ui->widgetCGI->setRootNode( _ui->widgetDoc->getRootNode() );

    QString title = tr( APP_TITLE );

    if ( _currentFile.length() > 0 )
    {
        title += " - " + QFileInfo( _currentFile ).fileName();
    }

    if ( !_saved ) title += " (*)";

    setWindowTitle( title );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::updateRecentFiles( QString file )
{
    for ( unsigned int i = 0; i < _recentFilesActions.size(); i++ )
    {
        disconnect( _recentFilesActions.at( i ), SIGNAL(triggered(int)), this, SLOT(recentFile_triggered(int)) );
    }

    _recentFilesActions.clear();

    if ( file.length() > 0 )
    {
        QStringList temp;

        temp.push_back( file );

        for ( int i = 0; i < _recentFilesList.size() && i < 4; i++ )
        {
            temp.push_back( _recentFilesList.at( i ) );
        }

        _recentFilesList = temp;
    }

    _ui->menuRecentFiles->clear();

    for ( int i = 0; i < _recentFilesList.size(); i++ )
    {
        _recentFilesActions.push_back( new RecentFileAction( i, _recentFilesList.at( i ), _ui->menuRecentFiles ) );
        connect( _recentFilesActions.at( i ), SIGNAL(triggered(int)), this, SLOT(recentFile_triggered(int)) );
        _ui->menuRecentFiles->addAction( _recentFilesActions.at( i ) );
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::document_changed()
{
    _saved = false;
    updateGUI();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::recentFile_triggered( int id )
{
    _currentFile = _recentFilesList.at( id );

    readFile( _currentFile );
    updateGUI();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionNew_triggered()
{
    newFile();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionOpen_triggered()
{
    openFile();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionSave_triggered()
{
    saveFile();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionSaveAs_triggered()
{
    saveFileAs();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionExport_triggered()
{
    exportFileAs();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionExit_triggered()
{
    close();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionClearRecent_triggered()
{
    _recentFilesList.clear();

    updateRecentFiles();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionRotor_triggered()
{
    _dialogRotor->show();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionRefresh_triggered()
{
    Models::reset();
    Textures::reset();

    readFile( _currentFile );
    updateGUI();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionViewOrbit_triggered()
{
    _ui->widgetCGI->setManipulatorOrbit( _ui->widgetDoc->getCurrentNode() );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionViewTrack_triggered()
{
    _ui->widgetCGI->setManipulatorTrack( _ui->widgetDoc->getCurrentNode() );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionLighting_triggered()
{
    _dialogLighting->show();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionAbout_triggered()
{
    QFile aboutHtmlFile( ":/gui/html/about.html" );

    QString aboutWinTitle;
    QString aboutInfoText;

    aboutWinTitle = tr( "About" );

    if ( aboutHtmlFile.open( QIODevice::ReadOnly ) )
    {
        aboutInfoText = aboutHtmlFile.readAll();
        aboutHtmlFile.close();
    }

    QMessageBox::about( this, aboutWinTitle, aboutInfoText );
}
