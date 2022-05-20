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

#include <asm/LOD.h>

////////////////////////////////////////////////////////////////////////////////

const char LOD::tagName[] = "lod";

////////////////////////////////////////////////////////////////////////////////

LOD::LOD() :
    Group( new osg::LOD() ),

    _lod ( dynamic_cast< osg::LOD* >( _node.get() ) ),

    _interval_f ( 1000.0 ),
    _interval_s ( 1000.0 ),
    _interval_o ( 1000.0 )
{
    _lod->setCenter( osg::Vec3d( 0.0, 0.0, 0.0 ) );
    _lod->setCenterMode( osg::LOD::USER_DEFINED_CENTER );
    _lod->setRangeMode( osg::LOD::DISTANCE_FROM_EYE_POINT );
}

////////////////////////////////////////////////////////////////////////////////

LOD::LOD( QDomElement *xmlNode ) :
    Group( xmlNode, new osg::LOD() ),

    _lod ( dynamic_cast< osg::LOD* >( _node.get() ) )
{
    _lod->setCenter( osg::Vec3d( 0.0, 0.0, 0.0 ) );
    _lod->setCenterMode( osg::LOD::USER_DEFINED_CENTER );
    _lod->setRangeMode( osg::LOD::DISTANCE_FROM_EYE_POINT );

    double interval_f = xmlNode->attributeNode( "interval_f" ).value().toDouble();
    double interval_s = xmlNode->attributeNode( "interval_s" ).value().toDouble();
    double interval_o = xmlNode->attributeNode( "interval_o" ).value().toDouble();

    if ( !xmlNode->hasAttribute( "interval_s" ) )
    {
        interval_s = interval_o;
    }

    setIntervalF( interval_f );
    setIntervalS( interval_s );
    setIntervalO( interval_o );
}

////////////////////////////////////////////////////////////////////////////////

LOD::~LOD()
{
    removeAllChildren();
}

////////////////////////////////////////////////////////////////////////////////

bool LOD::addChild( Component *child )
{
    _children.push_back( child );

    inflateLOD();

    return true;
}

////////////////////////////////////////////////////////////////////////////////

void LOD::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomElement node = doc->createElement( LOD::tagName );
    parentNode->appendChild( node );

    saveParameters( doc, &node );
}

////////////////////////////////////////////////////////////////////////////////

void LOD::setIntervalF( double interval_f )
{
    _interval_f = interval_f;

    inflateLOD();
}

////////////////////////////////////////////////////////////////////////////////

void LOD::setIntervalS( double interval_s )
{
    _interval_s = interval_s;

    inflateLOD();
}

////////////////////////////////////////////////////////////////////////////////

void LOD::setIntervalO( double interval_o )
{
    _interval_o = interval_o;

    inflateLOD();
}

////////////////////////////////////////////////////////////////////////////////

void LOD::inflateLOD()
{
    if ( _lod->getNumChildren() > 0 )
    {
        _lod->removeChildren( 0, _lod->getNumChildren() );
    }

    for ( unsigned int i = 0; i < _children.size(); i++ )
    {
        float r_0 = 0.0f;
        float r_1 = 0.0f;

        if ( i == 0 )
        {
            r_0 = 0.0f;
            r_1 = _interval_f;
        }
        else if ( i == 1 )
        {
            r_0 = _interval_f;
            r_1 = r_0 + _interval_s;
        }
        else
        {
            r_0 = _interval_f + _interval_s;
            r_1 = r_0 + ( i - 1 ) * _interval_o;
        }

        _lod->addChild( _children[ i ]->getNode(), r_0, r_1 );
        //_lod->setRange( i, r_0, r_1 );
    }
}

////////////////////////////////////////////////////////////////////////////////

void LOD::saveParameters( QDomDocument *doc, QDomElement *xmlNode )
{
    Group::saveParameters( doc, xmlNode );

    QDomAttr nodeIntervalF = doc->createAttribute( "interval_f" );
    QDomAttr nodeIntervalS = doc->createAttribute( "interval_s" );
    QDomAttr nodeIntervalO = doc->createAttribute( "interval_o" );

    nodeIntervalF.setValue( QString::number( getIntervalF() ) );
    nodeIntervalS.setValue( QString::number( getIntervalS() ) );
    nodeIntervalO.setValue( QString::number( getIntervalO() ) );

    xmlNode->setAttributeNode( nodeIntervalF );
    xmlNode->setAttributeNode( nodeIntervalS );
    xmlNode->setAttributeNode( nodeIntervalO );
}
