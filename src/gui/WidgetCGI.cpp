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

#include <osgViewer/ViewerEventHandlers>

#include <gui/WidgetCGI.h>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

WidgetCGI::WidgetCGI( QWidget *parent ) :
    QWidget ( parent ),

    _sceneRoot  ( nullptr ),
    _gridLayout ( nullptr )
{
#   ifdef SIM_OSGDEBUGINFO
    osg::setNotifyLevel( osg::DEBUG_INFO );
#   else
    osg::setNotifyLevel( osg::WARN );
#   endif

    //std::cout << "WidgetCGI::WidgetCGI( QWidget* )" << std::endl;

    _sceneRoot = new SceneRoot();

    _manipulatorOrbit = new ManipulatorOrbit();
    _manipulatorTrack = new ManipulatorTrack();

    setThreadingModel( osgViewer::ViewerBase::SingleThreaded );
    //setThreadingModel( osgViewer::ViewerBase::CullDrawThreadPerContext );

    _graphicsWindow = createGraphicsWindow( x(), y(), width(), height() );

    QWidget *widget = addViewWidget( _graphicsWindow, _sceneRoot->getSceneRoot() );

    _gridLayout = new QGridLayout( this );
    _gridLayout->setContentsMargins( 1, 1, 1, 1 );

    _gridLayout->addWidget( widget, 0, 0 );

    setLayout( _gridLayout );
}

////////////////////////////////////////////////////////////////////////////////

WidgetCGI::~WidgetCGI()
{
    if ( _sceneRoot ) delete _sceneRoot;
    _sceneRoot = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void WidgetCGI::setRootNode( osg::Node *root )
{
    if ( root )
    {
        _sceneRoot->setRootNode( root );
    }
}

////////////////////////////////////////////////////////////////////////////////

void WidgetCGI::update()
{
    //////////////////
    QWidget::update();
    //////////////////
}

////////////////////////////////////////////////////////////////////////////////

void WidgetCGI::setManipulatorOrbit( osg::Node *node )
{
    setCameraManipulator( _manipulatorOrbit.get() );
    _manipulatorOrbit->setTrackNode( node );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetCGI::setManipulatorTrack( osg::Node *node )
{
    setCameraManipulator( _manipulatorTrack.get() );
    _manipulatorTrack->setNode( node );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetCGI::paintEvent( QPaintEvent *event )
{
    /////////////////////////////
    QWidget::paintEvent( event );
    /////////////////////////////

    frame();
}

////////////////////////////////////////////////////////////////////////////////

QWidget* WidgetCGI::addViewWidget( GraphicsWindowQt *graphicsWindow, osg::Node *scene )
{
    osg::ref_ptr<osg::Camera> camera = getCamera();

    camera->setGraphicsContext( graphicsWindow );

    const osg::GraphicsContext::Traits *traits = graphicsWindow->getTraits();

    camera->setClearColor( osg::Vec4( 0.47, 0.71, 1.0, 1.0 ) );
    //camera->setClearColor( osg::Vec4( 0.0, 0.0, 0.0, 1.0 ) );
    camera->setViewport( new osg::Viewport( 0, 0, traits->width, traits->height ) );

    camera->setComputeNearFarMode( osg::CullSettings::COMPUTE_NEAR_FAR_USING_BOUNDING_VOLUMES );
    camera->setProjectionMatrixAsPerspective( 30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.00, 10000000.0 );

    setSceneData( scene );
    addEventHandler( new osgViewer::StatsHandler );
    setCameraManipulator( _manipulatorTrack.get() );

    setKeyEventSetsDone( 0 );

    assignSceneDataToCameras();

    return graphicsWindow->getGLWidget();
}

////////////////////////////////////////////////////////////////////////////////

osg::ref_ptr<GraphicsWindowQt> WidgetCGI::createGraphicsWindow( int x, int y, int w, int h,
                                                                const std::string &name, bool windowDecoration )
{
    osg::DisplaySettings *displaySettings = osg::DisplaySettings::instance().get();
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits();

    traits->windowName       = name;
    traits->windowDecoration = windowDecoration;
    traits->x                = x;
    traits->y                = y;
    traits->width            = w;
    traits->height           = h;
    traits->doubleBuffer     = true;
    traits->alpha            = displaySettings->getMinimumNumAlphaBits();
    traits->stencil          = displaySettings->getMinimumNumStencilBits();
    traits->sampleBuffers    = displaySettings->getMultiSamples();
    //traits->samples          = displaySettings->getNumMultiSamples();
    traits->samples          = 4;

    osg::ref_ptr<GraphicsWindowQt> graphicsWindow =  new GraphicsWindowQt( traits.get() );

    return graphicsWindow;
}
