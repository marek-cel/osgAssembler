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

#include <osg/ShapeDrawable>
#include <osg/LightSource>
#include <osg/Material>
#include <osg/PositionAttitudeTransform>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <asm/SceneRoot.h>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

SceneRoot::SceneRoot()
{
    //std::cout << "SceneRoot::create()" << std::endl;

    _sceneRoot = new osg::Group();
    _sceneRoot->setName( "SceneRoot" );

    osg::ref_ptr<osg::StateSet> rootStateSet = _sceneRoot->getOrCreateStateSet();

    rootStateSet->setMode( GL_RESCALE_NORMAL , osg::StateAttribute::ON );
    rootStateSet->setMode( GL_LIGHT0         , osg::StateAttribute::ON );
    rootStateSet->setMode( GL_LIGHT1         , osg::StateAttribute::ON );
    rootStateSet->setMode( GL_LIGHTING       , osg::StateAttribute::ON );
//    rootStateSet->setMode( GL_BLEND          , osg::StateAttribute::ON );
//    rootStateSet->setMode( GL_ALPHA_TEST     , osg::StateAttribute::ON );
//    rootStateSet->setMode( GL_DEPTH_TEST     , osg::StateAttribute::ON );
//    rootStateSet->setRenderBinDetails( 1, "DepthSortedBin" );

    //_lightPos = osg::Vec4d( 10000.0f, 0.0f, 0.0f, 0.0f );
    //_lightPos = osg::Vec4d( 0.0f, 10000.0f, -10000.0f, 0.0f );
    _lightPos = osg::Vec4d( 0.0f, -10000.0f, 10000.0f, 0.0f );
}

////////////////////////////////////////////////////////////////////////////////

SceneRoot::~SceneRoot() {}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::setRootNode( osg::Node *rootNode )
{
    _rootNode = rootNode;
    _sceneRoot->removeChildren( 0, _sceneRoot->getNumChildren() );
    if ( rootNode ) _sceneRoot->addChild( rootNode );

    createSceneLight();
}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::setLightingPositionX( double x )
{
    _lightPos.x() = x;

    if ( _light.valid() )
        _light->setPosition( _lightPos );
}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::setLightingPositionY( double y )
{
    _lightPos.y() = y;

    if ( _light.valid() )
        _light->setPosition( _lightPos );
}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::setLightingPositionZ( double z )
{
    _lightPos.z() = z;

    if ( _light.valid() )
        _light->setPosition( _lightPos );
}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::setLightingEnabled( bool enabled )
{
    _lightEnabled = enabled;

    if ( _lightSwitch.valid() )
    {
        if ( _lightEnabled )
        {
            _lightSwitch->setAllChildrenOn();
        }
        else
        {
            _lightSwitch->setAllChildrenOff();
        }
    }

}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::createSceneLight()
{
    _lightSwitch = new osg::Switch();
    _sceneRoot->addChild( _lightSwitch.get() );

    osg::ref_ptr<osg::PositionAttitudeTransform> lightPAT = new osg::PositionAttitudeTransform();
    _lightSwitch->addChild( lightPAT.get() );

    if ( _lightEnabled )
    {
        _lightSwitch->setAllChildrenOn();
    }
    else
    {
        _lightSwitch->setAllChildrenOff();
    }

    //lightPAT->setAttitude( osg::Quat( -M_PI_2 - M_PI_4, osg::Z_AXIS, M_PI_4, osg::Y_AXIS, 0.0, osg::X_AXIS ) );
//    lightPAT->setAttitude( osg::Quat( -M_PI_2 + M_PI_4, osg::Z_AXIS,
//                                               -M_PI_4, osg::Y_AXIS,
//                                                   0.0, osg::X_AXIS ) );

    osg::ref_ptr<osg::LightSource> lightSource = new osg::LightSource();
    lightPAT->addChild( lightSource.get() );

    _light = new osg::Light();

    _light->setLightNum( 0 );

    _light->setPosition( _lightPos );

    osg::Vec4 lightColor( 255.0f/255.0f, 253.0f/255.0f, 250.0f/255.0f, 1.0f );

    _light->setAmbient( lightColor );
    _light->setDiffuse( lightColor );
    _light->setSpecular( lightColor );

    _light->setConstantAttenuation( 1.0 );

    lightSource->setLight( _light.get() );

    lightSource->setLocalStateSetModes( osg::StateAttribute::ON );
    lightSource->setStateSetModes( *_sceneRoot->getOrCreateStateSet(), osg::StateAttribute::ON );
}
