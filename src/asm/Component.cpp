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

#include <asm/Component.h>

////////////////////////////////////////////////////////////////////////////////

Component::Component( osg::Node *osgNode ) :
    _node ( osgNode ),

    _depthSortedBinValue ( 1 ),
    _depthSortedBinState ( false )
{}

////////////////////////////////////////////////////////////////////////////////

Component::Component( QDomElement *xmlNode, osg::Node *osgNode ) :
    _node( osgNode )
{
    int  depthSortedBinValue = xmlNode->attributeNode( "depth_sorted_bin_value" ).value().toInt();
    bool depthSortedBinState = xmlNode->attributeNode( "depth_sorted_bin_state" ).value().toInt();

    setName( xmlNode->attributeNode( "name" ).value().toLatin1().data() );
    setDepthSortedBinState( depthSortedBinState ); // State First
    setDepthSortedBinValue( depthSortedBinValue );
}

////////////////////////////////////////////////////////////////////////////////

Component::~Component() {}

////////////////////////////////////////////////////////////////////////////////

void Component::update() {}

////////////////////////////////////////////////////////////////////////////////

void Component::setDepthSortedBinValue( int depthSortedBinValue )
{
    _depthSortedBinValue = depthSortedBinValue;

    if ( _depthSortedBinState && _node.valid() )
    {
        _node->getOrCreateStateSet()->setRenderBinDetails( _depthSortedBinValue, "DepthSortedBin" );
    }

    setTransparencyMode();
}

////////////////////////////////////////////////////////////////////////////////

void Component::setDepthSortedBinState( int depthSortedBinState )
{
    _depthSortedBinState = depthSortedBinState;

    if ( _depthSortedBinState && _node.valid() )
    {
        _node->getOrCreateStateSet()->setRenderBinDetails( _depthSortedBinValue, "DepthSortedBin" );
    }

    setTransparencyMode();
}

////////////////////////////////////////////////////////////////////////////////

void Component::setSelected( bool )
{
    osg::ref_ptr<osg::StateSet> stateSet = _node->getOrCreateStateSet();
}

////////////////////////////////////////////////////////////////////////////////

void Component::saveParameters( QDomDocument *doc, QDomElement *xmlNode )
{
    QDomAttr nodeName = doc->createAttribute( "name" );
    nodeName.setValue( getName().c_str() );
    xmlNode->setAttributeNode( nodeName );

    QDomAttr nodeDepthSortedBinValue = doc->createAttribute( "depth_sorted_bin_value" );
    QDomAttr nodeDepthSortedBinState = doc->createAttribute( "depth_sorted_bin_state" );

    nodeDepthSortedBinValue.setValue( QString::number( getDepthSortedBinValue() ) );
    nodeDepthSortedBinState.setValue( QString::number( (int)getDepthSortedBinState() ) );

    xmlNode->setAttributeNode( nodeDepthSortedBinValue );
    xmlNode->setAttributeNode( nodeDepthSortedBinState );
}

////////////////////////////////////////////////////////////////////////////////

void Component::setTransparencyMode()
{
    osg::ref_ptr< osg::StateSet > stateSet = _node->getOrCreateStateSet();

    if ( _depthSortedBinState && _depthSortedBinValue > 1 )
    {
        stateSet->setMode( GL_ALPHA_TEST , osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON );
        stateSet->setMode( GL_BLEND      , osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON );
        stateSet->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
    }
    else
    {
//        stateSet->setMode( GL_ALPHA_TEST , osg::StateAttribute::OVERRIDE | osg::StateAttribute::OFF );
//        stateSet->setMode( GL_BLEND      , osg::StateAttribute::OVERRIDE | osg::StateAttribute::OFF );
//        stateSet->setRenderingHint( osg::StateSet::DEFAULT_BIN );
    }
}
