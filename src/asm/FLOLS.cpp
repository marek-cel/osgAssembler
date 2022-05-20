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

#include <asm/FLOLS.h>

#include <asm/Colors.h>
#include <asm/Lights.h>

////////////////////////////////////////////////////////////////////////////////

const char FLOLS::tagName[] = "flols";

const float FLOLS::_sectorDegFrom = osg::DegreesToRadians( 250.0f );
const float FLOLS::_sectorDegUnto = osg::DegreesToRadians( 290.0f );

////////////////////////////////////////////////////////////////////////////////

FLOLS::FLOLS()
{
    create();
}

////////////////////////////////////////////////////////////////////////////////

FLOLS::FLOLS( QDomElement *xmlNode ) :
    PAT( xmlNode )
{
    create();
}

////////////////////////////////////////////////////////////////////////////////

FLOLS::~FLOLS()
{
    removeAllChildren();
}

////////////////////////////////////////////////////////////////////////////////

void FLOLS::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomElement node = doc->createElement( FLOLS::tagName );
    parentNode->appendChild( node );

    saveParameters( doc, &node );
}

////////////////////////////////////////////////////////////////////////////////

void FLOLS::create()
{
    osg::ref_ptr<osgSim::LightPointNode> lightPointNode = new osgSim::LightPointNode();

    createIFLOLS( lightPointNode );

    Lights::setTexture( lightPointNode.get(), "data/textures/lightpoint_flols.png" );

    _pat->addChild( lightPointNode.get() );
}

////////////////////////////////////////////////////////////////////////////////

void FLOLS::createIFLOLS( osgSim::LightPointNode *lightPointNode )
{
    createIFLOLS_Datum( lightPointNode );
    createIFLOLS_Ball( lightPointNode );
    createIFLOLS_WaveOff( lightPointNode );
    createIFLOLS_CutOff( lightPointNode );
}

////////////////////////////////////////////////////////////////////////////////

void FLOLS::createIFLOLS_Datum( osgSim::LightPointNode *lightPointNode )
{
    const float radius    = 4.0f * 0.3f;
    const float intensity = 1.0f;
    const float dist      = 0.3;

    osg::ref_ptr<osgSim::Sector> sector =
            new osgSim::AzimElevationSector( _sectorDegFrom, _sectorDegUnto,
                                             osg::DegreesToRadians(   5.0f ),
                                             osg::DegreesToRadians( -10.0f ) );

    for ( int i = 0; i < 10; i++ )
    {
        float y = ( i + 5 ) * dist;

        osgSim::LightPoint lighPntL( osg::Vec3( 0.0, -y, 0.0 ), Colors::Green );
        osgSim::LightPoint lighPntR( osg::Vec3( 0.0,  y, 0.0 ), Colors::Green );

        lighPntL._intensity = intensity;
        lighPntR._intensity = intensity;

        lighPntL._radius = radius;
        lighPntR._radius = radius;

        lighPntL._sector = sector;
        lighPntR._sector = sector;

        lightPointNode->addLightPoint( lighPntL );
        lightPointNode->addLightPoint( lighPntR );
    }
}

////////////////////////////////////////////////////////////////////////////////

void FLOLS::createIFLOLS_Ball( osgSim::LightPointNode *lightPointNode )
{
    const float radius    = 4.0f * 0.3f;
    const float intensity = 5.0f;
    const float dist      = 0.3;

    osg::ref_ptr<osgSim::Sector> sector_0 =
            new osgSim::AzimElevationSector( _sectorDegFrom, _sectorDegUnto,
                                             osg::DegreesToRadians(  5.00f ),
                                             osg::DegreesToRadians( -1.55f ) );

    osg::ref_ptr<osgSim::Sector> sector_1 =
            new osgSim::AzimElevationSector( _sectorDegFrom, _sectorDegUnto,
                                             osg::DegreesToRadians( -1.45f ),
                                             osg::DegreesToRadians( -2.30f ) );
    osg::ref_ptr<osgSim::Sector> sector_2 =
            new osgSim::AzimElevationSector( _sectorDegFrom, _sectorDegUnto,
                                             osg::DegreesToRadians( -2.20f ),
                                             osg::DegreesToRadians( -3.05f ) );
    osg::ref_ptr<osgSim::Sector> sector_3 =
            new osgSim::AzimElevationSector( _sectorDegFrom, _sectorDegUnto,
                                             osg::DegreesToRadians( -2.95f ),
                                             osg::DegreesToRadians( -3.80f ) );
    osg::ref_ptr<osgSim::Sector> sector_4 =
            new osgSim::AzimElevationSector( _sectorDegFrom, _sectorDegUnto,
                                             osg::DegreesToRadians( -3.70f ),
                                             osg::DegreesToRadians( -4.55f ) );
    osg::ref_ptr<osgSim::Sector> sector_5 =
            new osgSim::AzimElevationSector( _sectorDegFrom, _sectorDegUnto,
                                             osg::DegreesToRadians( -4.45f ),
                                             osg::DegreesToRadians( -5.30f ) );
    osg::ref_ptr<osgSim::Sector> sector_6 =
            new osgSim::AzimElevationSector( _sectorDegFrom, _sectorDegUnto,
                                             osg::DegreesToRadians( -5.20f ),
                                             osg::DegreesToRadians( -6.05f ) );
    osg::ref_ptr<osgSim::Sector> sector_7 =
            new osgSim::AzimElevationSector( _sectorDegFrom, _sectorDegUnto,
                                             osg::DegreesToRadians( -5.95f ),
                                             osg::DegreesToRadians( -6.80f ) );
    osg::ref_ptr<osgSim::Sector> sector_8 =
            new osgSim::AzimElevationSector( _sectorDegFrom, _sectorDegUnto,
                                             osg::DegreesToRadians(  -6.70f ),
                                             osg::DegreesToRadians( -10.00f ) );

    osgSim::LightPoint lighPnt0a( osg::Vec3( 0.0, 0.0,  4.5 * dist ), Colors::Red );
    osgSim::LightPoint lighPnt0b( osg::Vec3( 0.0, 0.0,  3.5 * dist ), Colors::Red );
    osgSim::LightPoint lighPnt_1( osg::Vec3( 0.0, 0.0,  2.5 * dist ), Colors::Yellow );
    osgSim::LightPoint lighPnt_2( osg::Vec3( 0.0, 0.0,  1.5 * dist ), Colors::Yellow );
    osgSim::LightPoint lighPnt_3( osg::Vec3( 0.0, 0.0,  0.5 * dist ), Colors::Yellow );
    osgSim::LightPoint lighPnt_4( osg::Vec3( 0.0, 0.0, -0.5 * dist ), Colors::Yellow );
    osgSim::LightPoint lighPnt_5( osg::Vec3( 0.0, 0.0, -1.5 * dist ), Colors::Yellow );
    osgSim::LightPoint lighPnt_6( osg::Vec3( 0.0, 0.0, -2.5 * dist ), Colors::Yellow );
    osgSim::LightPoint lighPnt_7( osg::Vec3( 0.0, 0.0, -3.5 * dist ), Colors::Yellow );
    osgSim::LightPoint lighPnt_8( osg::Vec3( 0.0, 0.0, -4.5 * dist ), Colors::Yellow );

    lighPnt0a._intensity = intensity;
    lighPnt0b._intensity = intensity;
    lighPnt_1._intensity = intensity;
    lighPnt_2._intensity = intensity;
    lighPnt_3._intensity = intensity;
    lighPnt_4._intensity = intensity;
    lighPnt_5._intensity = intensity;
    lighPnt_6._intensity = intensity;
    lighPnt_7._intensity = intensity;
    lighPnt_8._intensity = intensity;

    lighPnt0a._radius = radius;
    lighPnt0b._radius = radius;
    lighPnt_1._radius = radius;
    lighPnt_2._radius = radius;
    lighPnt_3._radius = radius;
    lighPnt_4._radius = radius;
    lighPnt_5._radius = radius;
    lighPnt_6._radius = radius;
    lighPnt_7._radius = radius;
    lighPnt_8._radius = radius;

    lighPnt0a._sector = sector_0;
    lighPnt0b._sector = sector_0;
    lighPnt_1._sector = sector_1;
    lighPnt_2._sector = sector_2;
    lighPnt_3._sector = sector_3;
    lighPnt_4._sector = sector_4;
    lighPnt_5._sector = sector_5;
    lighPnt_6._sector = sector_6;
    lighPnt_7._sector = sector_7;
    lighPnt_8._sector = sector_8;

    osg::ref_ptr<osgSim::BlinkSequence> blinkSequence = new osgSim::BlinkSequence;

    blinkSequence->addPulse( 0.5f, Colors::Red );
    blinkSequence->addPulse( 0.5f, osg::Vec4( 0.0f, 0.0f, 0.0f, 0.0f ) );

    lighPnt0a._blinkSequence = blinkSequence;
    lighPnt0b._blinkSequence = blinkSequence;

    lightPointNode->addLightPoint( lighPnt0a );
    lightPointNode->addLightPoint( lighPnt0b );
    lightPointNode->addLightPoint( lighPnt_1 );
    lightPointNode->addLightPoint( lighPnt_2 );
    lightPointNode->addLightPoint( lighPnt_3 );
    lightPointNode->addLightPoint( lighPnt_4 );
    lightPointNode->addLightPoint( lighPnt_5 );
    lightPointNode->addLightPoint( lighPnt_6 );
    lightPointNode->addLightPoint( lighPnt_7 );
    lightPointNode->addLightPoint( lighPnt_8 );
}

////////////////////////////////////////////////////////////////////////////////

void FLOLS::createIFLOLS_WaveOff( osgSim::LightPointNode *lightPointNode )
{
    const float radius    = 4.0f * 0.3f;
    const float intensity = 5.0f;
    const float dist      = 0.3;

    float y1 = 5.0 * dist;
    float y2 = 7.0 * dist;

    float z[] =
    {
        -1.5f * dist,
         2.0f * dist,
         4.0f * dist
    };

    osg::ref_ptr<osgSim::Sector> sector [] =
    {
        new osgSim::AzimElevationSector( _sectorDegFrom, _sectorDegUnto,
                                         osg::DegreesToRadians(  5.00f ),
                                         osg::DegreesToRadians( -1.30f ) ),
        new osgSim::AzimElevationSector( _sectorDegFrom, _sectorDegUnto,
                                         osg::DegreesToRadians(  5.00f ),
                                         osg::DegreesToRadians( -1.45f ) ),
        new osgSim::AzimElevationSector( _sectorDegFrom, _sectorDegUnto,
                                         osg::DegreesToRadians(  5.00f ),
                                         osg::DegreesToRadians( -1.50f ) )
    };

    osg::ref_ptr<osgSim::BlinkSequence> blinkSequence = new osgSim::BlinkSequence;

    blinkSequence->addPulse( 0.5f, Colors::Red );
    blinkSequence->addPulse( 0.5f, osg::Vec4( 0.0f, 0.0f, 0.0f, 0.0f ) );

    for ( int i = 0; i < 3; i++ )
    {
        osgSim::LightPoint lighPnt_L1( osg::Vec3( 0.0, -y1,  z[ i ] ), Colors::Red );
        osgSim::LightPoint lighPnt_L2( osg::Vec3( 0.0, -y2,  z[ i ] ), Colors::Red );
        osgSim::LightPoint lighPnt_R1( osg::Vec3( 0.0,  y1,  z[ i ] ), Colors::Red );
        osgSim::LightPoint lighPnt_R2( osg::Vec3( 0.0,  y2,  z[ i ] ), Colors::Red );

        lighPnt_L1._intensity = intensity;
        lighPnt_L2._intensity = intensity;
        lighPnt_R1._intensity = intensity;
        lighPnt_R2._intensity = intensity;

        lighPnt_L1._radius = radius;
        lighPnt_L2._radius = radius;
        lighPnt_R1._radius = radius;
        lighPnt_R2._radius = radius;

        lighPnt_L1._sector = sector[ i ];
        lighPnt_L2._sector = sector[ i ];
        lighPnt_R1._sector = sector[ i ];
        lighPnt_R2._sector = sector[ i ];

        lighPnt_L1._blinkSequence = blinkSequence;
        lighPnt_L2._blinkSequence = blinkSequence;
        lighPnt_R1._blinkSequence = blinkSequence;
        lighPnt_R2._blinkSequence = blinkSequence;

        lightPointNode->addLightPoint( lighPnt_L1 );
        lightPointNode->addLightPoint( lighPnt_L2 );
        lightPointNode->addLightPoint( lighPnt_R1 );
        lightPointNode->addLightPoint( lighPnt_R2 );
    }
}

////////////////////////////////////////////////////////////////////////////////

void FLOLS::createIFLOLS_CutOff( osgSim::LightPointNode *lightPointNode )
{
    const float radius    = 4.0f * 0.3f;
    const float intensity = 5.0f;
    const float dist      = 0.3;

    float y1 = 2.0 * dist;
    float y2 = 4.0 * dist;

    float z = -2.5 * dist;

    osg::ref_ptr<osgSim::Sector> sector =
            new osgSim::AzimElevationSector( _sectorDegFrom, _sectorDegUnto,
                                             osg::DegreesToRadians(  -6.70f ),
                                             osg::DegreesToRadians( -10.00f ) );

    osgSim::LightPoint lighPnt_L1( osg::Vec3( 0.0, -y1,  z ), Colors::Green );
    osgSim::LightPoint lighPnt_L2( osg::Vec3( 0.0, -y2,  z ), Colors::Green );
    osgSim::LightPoint lighPnt_R1( osg::Vec3( 0.0,  y1,  z ), Colors::Green );
    osgSim::LightPoint lighPnt_R2( osg::Vec3( 0.0,  y2,  z ), Colors::Green );

    lighPnt_L1._intensity = intensity;
    lighPnt_L2._intensity = intensity;
    lighPnt_R1._intensity = intensity;
    lighPnt_R2._intensity = intensity;

    lighPnt_L1._radius = radius;
    lighPnt_L2._radius = radius;
    lighPnt_R1._radius = radius;
    lighPnt_R2._radius = radius;

    lighPnt_L1._sector = sector;
    lighPnt_L2._sector = sector;
    lighPnt_R1._sector = sector;
    lighPnt_R2._sector = sector;

    lightPointNode->addLightPoint( lighPnt_L1 );
    lightPointNode->addLightPoint( lighPnt_L2 );
    lightPointNode->addLightPoint( lighPnt_R1 );
    lightPointNode->addLightPoint( lighPnt_R2 );
}

////////////////////////////////////////////////////////////////////////////////

void FLOLS::saveParameters( QDomDocument *doc, QDomElement *xmlNode )
{
    ////////////////////////////////////
    PAT::saveParameters( doc, xmlNode );
    ////////////////////////////////////
}
