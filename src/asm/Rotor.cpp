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

#include <asm/Rotor.h>

#include <Data.h>

////////////////////////////////////////////////////////////////////////////////

const char Rotor::tagName[] = "rotor";

////////////////////////////////////////////////////////////////////////////////

Rotor::Rotor() :
    _bladesCount ( 2 ),
    _bladesOffset ( 0.0 ),
    _direction ( CW )
{
    _fileBlade = "";
    _fileShaft = "";
}

////////////////////////////////////////////////////////////////////////////////

Rotor::Rotor( QDomElement *xmlNode ) :
    PAT( xmlNode ),

    _bladesCount ( 0 ),
    _bladesOffset ( 0.0 ),
    _direction ( CW )
{
    setFileBlade( xmlNode->attributeNode( "file_blade" ).value().toLatin1().data() );
    setFileShaft( xmlNode->attributeNode( "file_shaft" ).value().toLatin1().data() );

    setBladesCount( xmlNode->attributeNode( "blades_count" ).value().toInt() );
    setBladesOffset( xmlNode->attributeNode( "blades_offset" ).value().toDouble() );

    setDirection( (Direction)(xmlNode->attributeNode( "direction" ).value().toInt()) );
}

////////////////////////////////////////////////////////////////////////////////

Rotor::~Rotor()
{
    removeAllChildren();
}

////////////////////////////////////////////////////////////////////////////////

void Rotor::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomElement node = doc->createElement( Rotor::tagName );
    parentNode->appendChild( node );

    saveParameters( doc, &node );
}

////////////////////////////////////////////////////////////////////////////////

void Rotor::update()
{
    //////////////
    PAT::update();
    //////////////

    double coef = 1.0;

    if ( _direction ==  CCW )
    {
        coef = -1.0;
    }

    // main rotor
    if ( _mainRotor.valid() )
    {
        double psi = coef * Data::get()->rotor.azimuth;
        _mainRotor->setAttitude( osg::Quat( psi, osg::Z_AXIS ) );
    }

    // main rotor blades
    for ( unsigned int i = 0; i < _blades.size() && i < MAX_BLADES; i++ )
    {
        double pitching = Data::get()->blade[ i ].theta * ( -coef );
        double flapping = Data::get()->blade[ i ].beta;

        _blades[ i ]->setAttitude( osg::Quat( pitching, osg::X_AXIS,
                                              flapping, osg::Y_AXIS,
                                                   0.0, osg::Z_AXIS ) );
    }
}

////////////////////////////////////////////////////////////////////////////////

void Rotor::setBladesCount( unsigned int bladesCount )
{
    removeAllChildren();

    _bladesCount = bladesCount;
    if ( _bladesCount < 2 ) _bladesCount = 2;

    create();
}

////////////////////////////////////////////////////////////////////////////////

void Rotor::setBladesOffset( double bladesOffset )
{
    removeAllChildren();
    _bladesOffset = fabs( bladesOffset );
    create();
}

////////////////////////////////////////////////////////////////////////////////

void Rotor::setDirection( Direction direction )
{
    removeAllChildren();
    _direction = direction;
    create();
}

////////////////////////////////////////////////////////////////////////////////

void Rotor::setFileBlade( std::string fileBlade )
{
    removeAllChildren();
    _fileBlade = fileBlade;
    create();
}

////////////////////////////////////////////////////////////////////////////////

void Rotor::setFileShaft( std::string fileShaft )
{
    removeAllChildren();
    _fileShaft = fileShaft;
    create();
}

////////////////////////////////////////////////////////////////////////////////

void Rotor::create()
{
    _mainRotor = new osg::PositionAttitudeTransform();
    _mainRotor->setName( "MainRotor" );
    _pat->addChild( _mainRotor.get() );

    if ( _fileBlade.length() > 0 ) createBlades();
    if ( _fileShaft.length() > 0 ) createShaft();
}

////////////////////////////////////////////////////////////////////////////////

void Rotor::createBlades()
{
    osg::ref_ptr<osg::Group> blades = new osg::Group();
    blades->setName( "Blades" );
    _mainRotor->addChild( blades.get() );

    osg::ref_ptr<osg::Node> bladeNode = osgDB::readNodeFile( _fileBlade );

    if ( bladeNode.valid() )
    {
        const double angleStep = (_direction == CCW ? -1.0 : 1.0)*2.0*M_PI/((double)_bladesCount);

        for ( unsigned int i = 0; i < _bladesCount; i++ )
        {
            double azimuth = i*angleStep + M_PI;

            while ( azimuth < 0.0        ) azimuth += 2.0 * M_PI;
            while ( azimuth > 2.0 * M_PI ) azimuth -= 2.0 * M_PI;

            double offset_x = cos( azimuth ) * _bladesOffset;
            double offset_y = sin( azimuth ) * _bladesOffset;

            osg::ref_ptr<osg::PositionAttitudeTransform> patHinge = new osg::PositionAttitudeTransform();
            patHinge->setName( "BladeHinge" );
            patHinge->addChild( bladeNode.get() );

            osg::ref_ptr<osg::PositionAttitudeTransform> patBlade = new osg::PositionAttitudeTransform();
            patBlade->setName( "BladePAT" );
            patBlade->setAttitude( osg::Quat( azimuth, osg::Vec3( 0,0,1 ) ) );
            patBlade->setPosition( osg::Vec3( offset_x, offset_y, 0.0 ) );
            patBlade->addChild( patHinge.get() );

            blades->addChild( patBlade.get() );

            _blades.push_back( patHinge.get() );
        }
    }
    else
    {
        std::cout << "MainRotorBlade ERROR!" << std::endl;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Rotor::createShaft()
{
    osg::ref_ptr<osg::Node> shaftNode = osgDB::readNodeFile( _fileShaft );

    if ( shaftNode.valid() )
    {
        _mainRotor->addChild( shaftNode.get() );
    }
}

////////////////////////////////////////////////////////////////////////////////

void Rotor::removeAllChildren()
{
    if ( _mainRotor.valid() )
    {
        _mainRotor->removeChild( 0, _mainRotor->getNumChildren() );
    }

    ///////////////////////////
    Group::removeAllChildren();
    ///////////////////////////

    _blades.clear();

    _mainRotor = 0;
}

////////////////////////////////////////////////////////////////////////////////

void Rotor::saveParameters( QDomDocument *doc, QDomElement *xmlNode )
{
    PAT::saveParameters( doc, xmlNode );

    QDomAttr nodeFileBlade = doc->createAttribute( "file_blade" );
    QDomAttr nodeFileShaft = doc->createAttribute( "file_shaft" );

    nodeFileBlade.setValue( getFileBlade().c_str() );
    nodeFileShaft.setValue( getFileShaft().c_str() );

    xmlNode->setAttributeNode( nodeFileBlade );
    xmlNode->setAttributeNode( nodeFileShaft );

    QDomAttr nodeBladesCount = doc->createAttribute( "blades_count" );
    QDomAttr nodeBladesOffset = doc->createAttribute( "blades_offset" );

    nodeBladesCount.setValue( QString::number( getBladesCount() ) );
    nodeBladesOffset.setValue( QString::number( getBladesOffset() ) );

    xmlNode->setAttributeNode( nodeBladesCount );
    xmlNode->setAttributeNode( nodeBladesOffset );

    QDomAttr nodeDirection = doc->createAttribute( "direction" );
    nodeDirection.setValue( QString::number( getDirection() ) );
    xmlNode->setAttributeNode( nodeDirection );
}
