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

#include <osgDB/ReadFile>

#include <osg/AlphaFunc>
#include <osg/BlendFunc>
#include <osg/Depth>

#include <asm/Nozzle.h>

#include <Data.h>

////////////////////////////////////////////////////////////////////////////////

const char Nozzle::tagName[] = "nozzle";

////////////////////////////////////////////////////////////////////////////////

Nozzle::Nozzle()
{
    _fileGlow = "";
    _fileExhaust = "";

    _suffix = "";
}

////////////////////////////////////////////////////////////////////////////////

Nozzle::Nozzle( QDomElement *xmlNode ) :
    PAT( xmlNode )
{
    setFileGlow( xmlNode->attributeNode( "file_glow" ).value().toLatin1().data() );
    setFileExhaust( xmlNode->attributeNode( "file_exhaust" ).value().toLatin1().data() );
    setSuffix( xmlNode->attributeNode( "suffix" ).value().toLatin1().data() );
}

////////////////////////////////////////////////////////////////////////////////

Nozzle::~Nozzle()
{
    removeAllChildren();
}

////////////////////////////////////////////////////////////////////////////////

void Nozzle::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomElement node = doc->createElement( Nozzle::tagName );
    parentNode->appendChild( node );

    saveParameters( doc, &node );
}

////////////////////////////////////////////////////////////////////////////////

void Nozzle::update()
{
    //////////////
    PAT::update();
    //////////////
}

////////////////////////////////////////////////////////////////////////////////

void Nozzle::setFileGlow( std::string fileGlow )
{
    removeAllChildren();
    _fileGlow = fileGlow;
    create();
}

////////////////////////////////////////////////////////////////////////////////

void Nozzle::setFileExhaust( std::string fileExhaust )
{
    removeAllChildren();
    _fileExhaust = fileExhaust;
    create();
}

////////////////////////////////////////////////////////////////////////////////

void Nozzle::setSuffix( std::string suffix )
{
    removeAllChildren();
    _suffix = suffix;
    create();
}

////////////////////////////////////////////////////////////////////////////////

void Nozzle::create()
{
    std::string temp = "Afterburner";
    temp += _suffix;

    _switch = new osg::Switch();
    _switch->setName( temp.c_str() );
    _pat->addChild( _switch.get() );

    _exhaust = new osg::PositionAttitudeTransform();
    _exhaust->setName( "Exhaust" );
    _switch->addChild( _exhaust.get() );

    if ( _fileGlow.length() > 0 ) createGlow();
    if ( _fileExhaust.length() > 0 ) createExhaust();
    
//    osg::ref_ptr<osg::StateSet> stateSet = _switch->getOrCreateStateSet();

//    stateSet->setMode( GL_RESCALE_NORMAL , osg::StateAttribute::ON  );
//    stateSet->setMode( GL_LIGHTING       , osg::StateAttribute::ON  );
//    stateSet->setMode( GL_LIGHT0         , osg::StateAttribute::ON  );
//    stateSet->setMode( GL_BLEND          , osg::StateAttribute::ON  );
//    stateSet->setMode( GL_ALPHA_TEST     , osg::StateAttribute::ON  );
//    stateSet->setMode( GL_DEPTH_TEST     , osg::StateAttribute::ON  );
//    stateSet->setMode( GL_DITHER         , osg::StateAttribute::OFF );
//    stateSet->setMode( GL_CULL_FACE      , osg::StateAttribute::OFF );

//    osg::ref_ptr<osg::AlphaFunc> alphaFunc = new osg::AlphaFunc();
//    osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc();
//    blendFunc->setFunction( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
//    alphaFunc->setFunction( osg::AlphaFunc::GEQUAL, 0.05 );
//    stateSet->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
//    stateSet->setAttributeAndModes( blendFunc.get(), osg::StateAttribute::ON );
//    stateSet->setAttributeAndModes( alphaFunc.get(), osg::StateAttribute::ON );
//    stateSet->setMode( GL_BLEND, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE );

//    osg::ref_ptr<osg::Depth> depth = new osg::Depth;
//    depth->setWriteMask( false );
//    stateSet->setAttributeAndModes( depth.get(), osg::StateAttribute::ON );
}

////////////////////////////////////////////////////////////////////////////////

void Nozzle::createGlow()
{
    osg::ref_ptr<osg::Node> fileNode = osgDB::readNodeFile( _fileGlow );

    if ( fileNode.valid() )
    {
        _switch->addChild( fileNode.get() );
    }
}

////////////////////////////////////////////////////////////////////////////////

void Nozzle::createExhaust()
{
    osg::ref_ptr<osg::Node> fileNode = osgDB::readNodeFile( _fileExhaust );

    if ( fileNode.valid() )
    {
        _exhaust->addChild( fileNode.get() );
    }
}

////////////////////////////////////////////////////////////////////////////////

void Nozzle::removeAllChildren()
{
    if ( _exhaust.valid() )
    {
        _exhaust->removeChild( 0, _exhaust->getNumChildren() );
    }

    if ( _switch.valid() )
    {
        _switch->removeChild( 0, _switch->getNumChildren() );
    }

    ///////////////////////////
    Group::removeAllChildren();
    ///////////////////////////

    _exhaust = 0;
    _switch = 0;
}

////////////////////////////////////////////////////////////////////////////////

void Nozzle::saveParameters( QDomDocument *doc, QDomElement *xmlNode )
{
    PAT::saveParameters( doc, xmlNode );

    QDomAttr nodeFileGlow = doc->createAttribute( "file_glow" );
    QDomAttr nodeFileExhaust = doc->createAttribute( "file_exhaust" );

    nodeFileGlow.setValue( getFileGlow().c_str() );
    nodeFileExhaust.setValue( getFileExhaust().c_str() );

    xmlNode->setAttributeNode( nodeFileGlow );
    xmlNode->setAttributeNode( nodeFileExhaust );

    QDomAttr nodeSuffix = doc->createAttribute( "suffix" );
    nodeSuffix.setValue( getSuffix().c_str() );
    xmlNode->setAttributeNode( nodeSuffix );
}
