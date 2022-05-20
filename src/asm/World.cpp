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

#include <asm/World.h>

#include <iostream>

#include <asm/Models.h>
#include <asm/WGS84.h>

////////////////////////////////////////////////////////////////////////////////

const char World::tagName[] = "world";

////////////////////////////////////////////////////////////////////////////////

World::World() :
    _lat ( 0.0 ),
    _lon ( 0.0 ),
    _alt ( 0.0 )
{
    _file = "";
}

////////////////////////////////////////////////////////////////////////////////

World::World( QDomElement *xmlNode ) :
    PAT( xmlNode )
{
    setLat( xmlNode->attributeNode( "lat" ).value().toDouble() );
    setLon( xmlNode->attributeNode( "lon" ).value().toDouble() );
    setAlt( xmlNode->attributeNode( "alt" ).value().toDouble() );

    setFile( xmlNode->attributeNode( "file" ).value().toLatin1().data() );

//    std::cout << "lat: " << _lat << std::endl;
//    std::cout << "lon: " << _lon << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

World::~World()
{
    removeAllChildren();
}

////////////////////////////////////////////////////////////////////////////////

void World::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomElement node = doc->createElement( World::tagName );
    parentNode->appendChild( node );

    saveParameters( doc, &node );
}

////////////////////////////////////////////////////////////////////////////////

void World::setLat( double lat )
{
    _lat = lat;
    updatePositionAndAttitude();
}

////////////////////////////////////////////////////////////////////////////////

void World::setLon( double lon )
{
    _lon = lon;
    updatePositionAndAttitude();
}

////////////////////////////////////////////////////////////////////////////////

void World::setAlt( double alt )
{
    _alt = alt;
    updatePositionAndAttitude();
}

////////////////////////////////////////////////////////////////////////////////

bool World::setFile( std::string file )
{
    _pat->removeChild( 0, _group->getNumChildren() );

    _file = file;

    _fileNode = Models::get( _file );

    if ( _fileNode.valid() )
    {
        _pat->addChild( _fileNode.get() );
        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////

void World::updatePositionAndAttitude()
{
    double lat_rad = osg::DegreesToRadians( _lat );
    double lon_rad = osg::DegreesToRadians( _lon );

    WGS84 wgs( lat_rad, lon_rad, _alt );

    osg::Quat  att = wgs.getAttitude().inverse();
    osg::Vec3d pos = att * ( -wgs.getPosition() );

    _px = pos.x();
    _py = pos.y();
    _pz = pos.z();

    _ax = 0.0;
    _ay = 0.0;
    _az = 0.0;

    double sinTht2 = att.w()*att.y() - att.x()*att.z();

    if( sinTht2 >= 0.5 )
    {
        _ax =  2.0 * asin( att.x() / cos( M_PI_4 ) );
        _ay =  M_PI_2;
        _az =  0.0;
    }
    else if ( sinTht2 <= -0.5 )
    {
        _ax =  2.0 * asin( att.x() / cos( M_PI_4 ) );
        _ay = -M_PI_2;
        _az =  0.0;
    }
    else
    {
        _ax = atan2( 2.0*( att.w()*att.x() + att.y()*att.z() ), 1.0 - 2.0*( att.x()*att.x() + att.y()*att.y() ) );
        _ay =  asin( 2.0*sinTht2 );
        _az = atan2( 2.0*( att.w()*att.z() + att.x()*att.y() ), 1.0 - 2.0*( att.y()*att.y() + att.z()*att.z() ) );
    }

    _ax *= 180.0 / M_PI;
    _ay *= 180.0 / M_PI;
    _az *= 180.0 / M_PI;

    /////////////////////////////////
    PAT::updatePositionAndAttitude();
    /////////////////////////////////

    //_pat->setAttitude( att );
}

////////////////////////////////////////////////////////////////////////////////

void World::saveParameters( QDomDocument *doc, QDomElement *xmlNode )
{
    ////////////////////////////////////
    PAT::saveParameters( doc, xmlNode );
    ////////////////////////////////////

    QDomAttr nodeLat = doc->createAttribute( "lat" );
    QDomAttr nodeLon = doc->createAttribute( "lon" );
    QDomAttr nodeAlt = doc->createAttribute( "alt" );

    nodeLat.setValue( QString::number( _lat, 'f', 8 ) );
    nodeLon.setValue( QString::number( _lon, 'f', 8 ) );
    nodeAlt.setValue( QString::number( _alt, 'f', 3 ) );

    xmlNode->setAttributeNode( nodeLat );
    xmlNode->setAttributeNode( nodeLon );
    xmlNode->setAttributeNode( nodeAlt );

    QDomAttr nodeFile = doc->createAttribute( "file" );
    nodeFile.setValue( getFile().c_str() );
    xmlNode->setAttributeNode( nodeFile );
}
