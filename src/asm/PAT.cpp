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

#include <asm/PAT.h>

////////////////////////////////////////////////////////////////////////////////

const char PAT::tagName[] = "pat";

////////////////////////////////////////////////////////////////////////////////

PAT::PAT() :
    Group( new osg::PositionAttitudeTransform() ),

    _pat ( dynamic_cast< osg::PositionAttitudeTransform* >( _node.get() ) ),

    _px ( 0.0 ),
    _py ( 0.0 ),
    _pz ( 0.0 ),

    _ax ( 0.0 ),
    _ay ( 0.0 ),
    _az ( 0.0 ),

    _convention ( XYZ )
{}

////////////////////////////////////////////////////////////////////////////////

PAT::PAT( QDomElement *xmlNode ) :
    Group( xmlNode, new osg::PositionAttitudeTransform() ),

    _pat ( dynamic_cast< osg::PositionAttitudeTransform* >( _node.get() ) )
{
    double px = xmlNode->attributeNode( "px" ).value().toDouble();
    double py = xmlNode->attributeNode( "py" ).value().toDouble();
    double pz = xmlNode->attributeNode( "pz" ).value().toDouble();

    double ax = xmlNode->attributeNode( "ax" ).value().toDouble();
    double ay = xmlNode->attributeNode( "ay" ).value().toDouble();
    double az = xmlNode->attributeNode( "az" ).value().toDouble();

    if ( xmlNode->attributeNode( "convention" ).value().toInt() == 0 )
    {
        _convention = XYZ;
    }
    else
    {
        _convention = ZYX;
    }

    setPx( px );
    setPy( py );
    setPz( pz );

    setAx( ax );
    setAy( ay );
    setAz( az );
}

////////////////////////////////////////////////////////////////////////////////

PAT::~PAT()
{
    removeAllChildren();
}

////////////////////////////////////////////////////////////////////////////////

void PAT::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomElement node = doc->createElement( PAT::tagName );
    parentNode->appendChild( node );

    saveParameters( doc, &node );
}

////////////////////////////////////////////////////////////////////////////////

void PAT::updatePositionAndAttitude()
{
    osg::Vec3d p( _px, _py, _pz );

    osg::Quat a;

    if ( _convention == ZYX )
    {
        a = osg::Quat( osg::DegreesToRadians( _az ), osg::Z_AXIS,
                       osg::DegreesToRadians( _ay ), osg::Y_AXIS,
                       osg::DegreesToRadians( _ax ), osg::X_AXIS );
    }
    else
    {
        a = osg::Quat( osg::DegreesToRadians( _ax ), osg::X_AXIS,
                       osg::DegreesToRadians( _ay ), osg::Y_AXIS,
                       osg::DegreesToRadians( _az ), osg::Z_AXIS );
    }

    _pat->setPosition( p );
    _pat->setAttitude( a );
}

////////////////////////////////////////////////////////////////////////////////

void PAT::saveParameters( QDomDocument *doc, QDomElement *xmlNode )
{
    //////////////////////////////////////
    Group::saveParameters( doc, xmlNode );
    //////////////////////////////////////

    QDomAttr nodePx = doc->createAttribute( "px" );
    QDomAttr nodePy = doc->createAttribute( "py" );
    QDomAttr nodePz = doc->createAttribute( "pz" );

    QDomAttr nodeAx = doc->createAttribute( "ax" );
    QDomAttr nodeAy = doc->createAttribute( "ay" );
    QDomAttr nodeAz = doc->createAttribute( "az" );

    QDomAttr nodeConvention = doc->createAttribute( "convention" );

    nodePx.setValue( QString::number( getPx(), 'f', 6 ) );
    nodePy.setValue( QString::number( getPy(), 'f', 6 ) );
    nodePz.setValue( QString::number( getPz(), 'f', 6 ) );

    nodeAx.setValue( QString::number( getAx(), 'f', 12 ) );
    nodeAy.setValue( QString::number( getAy(), 'f', 12 ) );
    nodeAz.setValue( QString::number( getAz(), 'f', 12 ) );

    nodeConvention.setValue( QString::number( _convention ) );

    xmlNode->setAttributeNode( nodePx );
    xmlNode->setAttributeNode( nodePy );
    xmlNode->setAttributeNode( nodePz );

    xmlNode->setAttributeNode( nodeAx );
    xmlNode->setAttributeNode( nodeAy );
    xmlNode->setAttributeNode( nodeAz );

    xmlNode->setAttributeNode( nodeConvention );
}
