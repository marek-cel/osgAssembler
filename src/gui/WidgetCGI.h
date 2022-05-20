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
#ifndef WIDGETCGI_H
#define WIDGETCGI_H

////////////////////////////////////////////////////////////////////////////////

#include <osgViewer/Viewer>

#include <QDateTime>
#include <QGridLayout>
#include <QWidget>

#include <asm/ManipulatorOrbit.h>
#include <asm/ManipulatorTrack.h>

#include <asm/SceneRoot.h>

#include <gui/GraphicsWindowQt.h>

////////////////////////////////////////////////////////////////////////////////

/** This is widget wrapper for CGI. */
class WidgetCGI : public QWidget, public osgViewer::Viewer
{
    Q_OBJECT

public:

    /** Constructor. */
    WidgetCGI( QWidget *parent = nullptr );

    /** Destructor. */
    virtual ~WidgetCGI();

    /** */
    void setRootNode( osg::Node* root );

    /** */
    void update();

    SceneRoot* getSceneRoot() { return _sceneRoot; }

    void setManipulatorOrbit( osg::Node *node );
    void setManipulatorTrack( osg::Node *node );

protected:

    /** */
    void paintEvent( QPaintEvent *event );

private:

    SceneRoot   *_sceneRoot;
    QGridLayout *_gridLayout;

    osg::ref_ptr<ManipulatorOrbit> _manipulatorOrbit;
    osg::ref_ptr<ManipulatorTrack> _manipulatorTrack;

    osg::ref_ptr<GraphicsWindowQt> _graphicsWindow;

    /** */
    QWidget* addViewWidget( GraphicsWindowQt *graphicsWindow, osg::Node *scene );

    /** */
    osg::ref_ptr<GraphicsWindowQt> createGraphicsWindow( int x, int y, int w, int h,
                                                         const std::string &name = "", bool windowDecoration = false );
};

////////////////////////////////////////////////////////////////////////////////

#endif // WIDGETCGI_H
