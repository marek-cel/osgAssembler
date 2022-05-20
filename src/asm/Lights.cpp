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

#include <asm/Lights.h>

#include <iostream>

#include <osg/Group>
#include <osg/Texture2D>

#include <asm/Colors.h>
#include <asm/Textures.h>

////////////////////////////////////////////////////////////////////////////////

const float Lights::_sectorDegFromFN = osg::DegreesToRadians( 225.0f );
const float Lights::_sectorDegUntoFN = osg::DegreesToRadians( 315.0f );
const float Lights::_sectorDegFromBN = osg::DegreesToRadians(  45.0f );
const float Lights::_sectorDegUntoBN = osg::DegreesToRadians( 135.0f );

const float Lights::_sectorDegFromFW = osg::DegreesToRadians( 180.0f );
const float Lights::_sectorDegUntoFW = osg::DegreesToRadians( 360.0f );
const float Lights::_sectorDegFromBW = osg::DegreesToRadians(   0.0f );
const float Lights::_sectorDegUntoBW = osg::DegreesToRadians( 180.0f );

const float Lights::_sectorDegFromFVN = osg::DegreesToRadians( 240.0f );
const float Lights::_sectorDegUntoFVN = osg::DegreesToRadians( 300.0f );
const float Lights::_sectorDegFromBVN = osg::DegreesToRadians(  60.0f );
const float Lights::_sectorDegUntoBVN = osg::DegreesToRadians( 120.0f );

////////////////////////////////////////////////////////////////////////////////

const float Lights::RALS::_height    = 3.0f;
const float Lights::RALS::_radius    = 4.0f * 0.2f;
const float Lights::RALS::_intensity = 2.0f;

const float Lights::RCLS::_height    = 0.0f;
const float Lights::RCLS::_radius    = 4.0f * 0.1f;
const float Lights::RCLS::_intensity = 1.5f;

const float Lights::RELS::_height    = 0.8f;
const float Lights::RELS::_radius    = 4.0f * 0.2f;
const float Lights::RELS::_intensity = 2.0f;
const float Lights::RELS::_offset    = 1.0f;

const float Lights::RTEL::_height    = Lights::RELS::_height;
const float Lights::RTEL::_radius    = Lights::RELS::_radius;
const float Lights::RTEL::_intensity = Lights::RELS::_intensity;
const float Lights::RTEL::_offset    = Lights::RELS::_offset;

const float Lights::TDZL::_height    = 0.0f;
const float Lights::TDZL::_radius    = 4.0f * 0.1f;
const float Lights::TDZL::_intensity = 1.5f;

const float Lights::VGSI::_height    = 1.0f;
const float Lights::VGSI::_radius    = 4.0f * 0.3f;
const float Lights::VGSI::_intensity = 4.5f;

////////////////////////////////////////////////////////////////////////////////

void Lights::setTexture( osgSim::LightPointNode *lightPointNode,
                         const std::string &textureFile )
{
    osg::ref_ptr<osg::Texture2D> texture = Textures::get( textureFile );

    if ( texture.valid() )
    {
        osg::ref_ptr<osg::StateSet> stateSet = lightPointNode->getOrCreateStateSet();

        lightPointNode->setPointSprite();

        stateSet->setTextureAttributeAndModes( 0, texture.get(), osg::StateAttribute::ON );
    }
}

////////////////////////////////////////////////////////////////////////////////

void Lights::RALS::createALSF1( osg::Group *group, float runwayWidth,
                                float xdel )
{
    osg::ref_ptr<osgSim::LightPointNode> lightPointNode = new osgSim::LightPointNode();

    createALSF1( lightPointNode, xdel );
    RTEL::createRTEL_Cat2( lightPointNode, runwayWidth, xdel );

    setTexture( lightPointNode.get(), "data/textures/lightpoint_rals.png" );

    group->addChild( lightPointNode.get() );
}

////////////////////////////////////////////////////////////////////////////////

void Lights::RALS::createALSF2( osg::Group *group, float runwayWidth,
                                float xdel )
{
    osg::ref_ptr<osgSim::LightPointNode> lightPointNode = new osgSim::LightPointNode();

    createALSF2( lightPointNode, xdel );
    RTEL::createRTEL_Cat2( lightPointNode, runwayWidth, xdel );

    setTexture( lightPointNode.get(), "data/textures/lightpoint_rals.png" );

    group->addChild( lightPointNode.get() );
}

////////////////////////////////////////////////////////////////////////////////

void Lights::RALS::createMALS( osg::Group *group, float runwayWidth,
                               float xdel )
{
    osg::ref_ptr<osgSim::LightPointNode> lightPointNode = new osgSim::LightPointNode();

    createMALS( lightPointNode, xdel );
    RTEL::createRTEL_Cat2( lightPointNode, runwayWidth, xdel );

    setTexture( lightPointNode.get(), "data/textures/lightpoint_rals.png" );

    group->addChild( lightPointNode.get() );
}

////////////////////////////////////////////////////////////////////////////////

void Lights::RALS::createMALSF( osg::Group *group, float runwayWidth,
                                float xdel )
{
    osg::ref_ptr<osgSim::LightPointNode> lightPointNode = new osgSim::LightPointNode();

    createMALSF( lightPointNode, xdel );
    RTEL::createRTEL_Cat2( lightPointNode, runwayWidth, xdel );

    setTexture( lightPointNode.get(), "data/textures/lightpoint_rals.png" );

    group->addChild( lightPointNode.get() );
}

////////////////////////////////////////////////////////////////////////////////

void Lights::RALS::createMALSR( osg::Group *group, float runwayWidth,
                                float xdel )
{
    osg::ref_ptr<osgSim::LightPointNode> lightPointNode = new osgSim::LightPointNode();

    createMALSR( lightPointNode, xdel );
    RTEL::createRTEL_Cat2( lightPointNode, runwayWidth, xdel );

    setTexture( lightPointNode.get(), "data/textures/lightpoint_rals.png" );

    group->addChild( lightPointNode.get() );
}

////////////////////////////////////////////////////////////////////////////////

void Lights::RCLS::createRCLS( osg::Group *group, float runwayLength )
{
    osg::ref_ptr<osgSim::LightPointNode> lightPointNode = new osgSim::LightPointNode();

    float xdel = runwayLength / 2.0f;

    createRCLS( lightPointNode, -xdel );
    createRCLS( lightPointNode,  xdel );

    setTexture( lightPointNode.get(), "data/textures/lightpoint_rcls.png" );

    group->addChild( lightPointNode.get() );
}

////////////////////////////////////////////////////////////////////////////////

void Lights::RELS::createRELS( osg::Group *group, float runwayWidth, float runwayLength,
                               const Gaps &gaps )
{
    osg::ref_ptr<osgSim::LightPointNode> lightPointNode = new osgSim::LightPointNode();

    float xdel = runwayLength / 2.0f;

    createRELS( lightPointNode, runwayWidth, -xdel, gaps );
    createRELS( lightPointNode, runwayWidth,  xdel, gaps );

    RTEL::createRTEL_Base( lightPointNode, runwayWidth, -xdel );
    RTEL::createRTEL_Base( lightPointNode, runwayWidth,  xdel );

    setTexture( lightPointNode.get(), "data/textures/lightpoint_rels.png" );

    group->addChild( lightPointNode.get() );
}

////////////////////////////////////////////////////////////////////////////////

void Lights::TDZL::createTDZL( osg::Group *groupL, osg::Group *groupH, float runwayLength )
{
    osg::ref_ptr<osgSim::LightPointNode> lightPointNodeL = new osgSim::LightPointNode();
    osg::ref_ptr<osgSim::LightPointNode> lightPointNodeH = new osgSim::LightPointNode();

    float xdel = runwayLength / 2.0f;

    createTDZL( lightPointNodeL, -xdel, 18.0f );
    createTDZL( lightPointNodeH,  xdel, 18.0f );

    setTexture( lightPointNodeL.get(), "data/textures/lightpoint_tdzl.png" );
    setTexture( lightPointNodeH.get(), "data/textures/lightpoint_tdzl.png" );

    groupL->addChild( lightPointNodeL.get() );
    groupH->addChild( lightPointNodeH.get() );
}

////////////////////////////////////////////////////////////////////////////////

void Lights::VGSI::createPAPI( osg::Group *group, float xdel, float ydel )
{
    osg::ref_ptr<osgSim::LightPointNode> lightPointNode = new osgSim::LightPointNode();

    createPAPI( lightPointNode, xdel, ydel );

    setTexture( lightPointNode.get(), "data/textures/lightpoint_vgsi.png" );

    group->addChild( lightPointNode.get() );
}

////////////////////////////////////////////////////////////////////////////////

void Lights::VGSI::createVASI( osg::Group *group, float xdel, float ydel )
{
    osg::ref_ptr<osgSim::LightPointNode> lightPointNode = new osgSim::LightPointNode();

    createVASI( lightPointNode, xdel, ydel );

    setTexture( lightPointNode.get(), "data/textures/lightpoint_vgsi.png" );

    group->addChild( lightPointNode.get() );
}

////////////////////////////////////////////////////////////////////////////////

void Lights::VGSI::createVASI3( osg::Group *group, float xdel, float ydel )
{
    osg::ref_ptr<osgSim::LightPointNode> lightPointNode = new osgSim::LightPointNode();

    createVASI3( lightPointNode, xdel, ydel );

    setTexture( lightPointNode.get(), "data/textures/lightpoint_vgsi.png" );

    group->addChild( lightPointNode.get() );
}

////////////////////////////////////////////////////////////////////////////////

void Lights::SSP1::createSSP1( osg::Group *group, float runwayWidth, float runwayLength )
{
    osg::ref_ptr<osgSim::LightPointNode> lightPointNode = new osgSim::LightPointNode();

    float xdel = runwayLength / 2.0f;

    RALS::createSSP1( lightPointNode.get(), xdel );
    RELS::createSSP1( lightPointNode.get(), runwayWidth, runwayLength );
    RTEL::createSSP1( lightPointNode.get(), runwayWidth, runwayLength );

    setTexture( lightPointNode.get(), "data/textures/lightpoint_ssp1.png" );

    group->addChild( lightPointNode.get() );
}

////////////////////////////////////////////////////////////////////////////////

void Lights::RALS::createALSF1( osgSim::LightPointNode *lightPointNode,
                                float xdel )
{
    float ycur = 0.0f;

    float xcur = 0.0f;
    float ydel = 0.0f;

    float step = 0.0f;

    int iFlash = 0;

    double sectorDegFrom = _sectorDegFromFW;
    double sectorDegUnto = _sectorDegUntoFW;

    if ( xdel > 0.0f )
    {
        sectorDegFrom = _sectorDegFromBW;
        sectorDegUnto = _sectorDegUntoBW;
    }

    osg::ref_ptr<osgSim::Sector> sector = new osgSim::AzimSector( sectorDegFrom, sectorDegUnto );

    step = -30.0f;
    xcur = -30.0f;

    ycur = -20.0f;

    for ( int iSide = 0; iSide < 2; iSide++ )
    {
        ydel = -2.0f;

        for ( int iLat = 0; iLat < 3; iLat++ )
        {
            double x_real = ( xdel > 0.0f ) ? xdel + 15.0 : xdel - 15.0;

            osgSim::LightPoint lighPntR( osg::Vec3( x_real, ycur + ydel, -_height ), Colors::Red );

            lighPntR._intensity = _intensity;
            lighPntR._radius    = _radius;
            lighPntR._sector    = sector;

            lightPointNode->addLightPoint( lighPntR );

            ydel += 2.0;
        }

        ycur = 20.0;
    }

    while ( xcur + 720.0f >= -1.0e-4 )
    {
        double x_real = ( xdel > 0.0f ) ? xdel - xcur : xdel + xcur;

        ydel = -2.0f;

        for ( int iLat = 0; iLat < 5; iLat++ )
        {
            osgSim::LightPoint lighPntW( osg::Vec3( x_real, ydel, -_height ), Colors::White );

            lighPntW._intensity = _intensity;
            lighPntW._radius    = _radius;
            lighPntW._sector    = sector;

            lightPointNode->addLightPoint( lighPntW );

            ydel += 1.0;
        }

        // decision bar
        if( fabs( xcur + 300.0f ) < 1.0e-4 )
        {
            ycur = -12.5f;

            for ( int iSide = 0; iSide < 2; iSide++ )
            {
                ydel = -6.0;

                for ( int iLat = 0; iLat < 5; iLat++ )
                {
                    osgSim::LightPoint lighPntW( osg::Vec3( x_real, ycur + ydel, -_height ), Colors::White );

                    lighPntW._intensity = _intensity;
                    lighPntW._radius    = _radius;
                    lighPntW._sector    = sector;

                    lightPointNode->addLightPoint( lighPntW );

                    ydel += 1.5f;
                }

                ycur = 18.5f;
            }
        }

        if ( xcur < -300.0f + 1.0e-9 )
        {
            osg::ref_ptr<osgSim::BlinkSequence> blinkSequence = new osgSim::BlinkSequence;

            for ( int iBlink = 16; iBlink >= 0; iBlink-- )
            {
                float alpha = ( iFlash == iBlink ) ? 1.0f : 0.0f;
                blinkSequence->addPulse( 0.05f, osg::Vec4( 1.0f, 1.0f, 1.0f, alpha ) );
            }

            osgSim::LightPoint lighPntW( osg::Vec3( x_real, 0.0f, -_height ), Colors::White );

            lighPntW._intensity = 2.0f * _intensity;
            lighPntW._radius    = 2.0f * _radius;
            lighPntW._sector    = sector;
            lighPntW._blinkSequence = blinkSequence;

            lightPointNode->addLightPoint( lighPntW );

            iFlash++;
        }

        if( fabs( xcur + 60.0 ) < 1.0e-4 )
        {
            ycur = -10.0f;

            for ( int iSide = 0; iSide < 2; iSide++ )
            {
                ydel = -2.0f;

                for ( int iLat = 0; iLat < 3; iLat++ )
                {
                    osgSim::LightPoint lighPntR( osg::Vec3( x_real, ycur + ydel, -_height ), Colors::Red );

                    lighPntR._intensity = _intensity;
                    lighPntR._radius    = _radius;
                    lighPntR._sector    = sector;

                    lightPointNode->addLightPoint( lighPntR );

                    ydel += 2.0;
                }

                ycur = 10.0;
            }
        }

        xcur += step;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Lights::RALS::createALSF2( osgSim::LightPointNode *lightPointNode,
                                float xdel )
{
    float ycur = 0.0f;

    float xcur = 0.0f;
    float ydel = 0.0f;

    float step = 0.0f;

    int iFlash = 0;

    double sectorDegFrom = _sectorDegFromFW;
    double sectorDegUnto = _sectorDegUntoFW;

    if ( xdel > 0.0f )
    {
        sectorDegFrom = _sectorDegFromBW;
        sectorDegUnto = _sectorDegUntoBW;
    }

    osg::ref_ptr<osgSim::Sector> sector = new osgSim::AzimSector( sectorDegFrom, sectorDegUnto );

    step = -30.0f;
    xcur = -30.0f;

    while ( xcur + 720.0f >= -1.0e-4 )
    {
        double x_real = xdel + xcur;

        if ( xdel > 0.0f )
        {
            x_real = xdel - xcur;
        }

        ydel = -2.0f;

        for ( int iLat = 0; iLat < 5; iLat++ )
        {
            osgSim::LightPoint lighPntW( osg::Vec3( x_real, ydel, -_height ), Colors::White );

            lighPntW._intensity = _intensity;
            lighPntW._radius    = _radius;
            lighPntW._sector    = sector;

            lightPointNode->addLightPoint( lighPntW );

            ydel += 1.0;
        }

        if( fabs( xcur + 150.0f ) < 1.0e-4 )
        {
            ycur = -7.5f;

            for ( int iSide = 0; iSide < 2; iSide++ )
            {
                ydel = -2.25f;

                for ( int iLat = 0; iLat < 4; iLat++ )
                {
                    osgSim::LightPoint lighPntW( osg::Vec3( x_real, ycur + ydel, -_height ), Colors::White );

                    lighPntW._intensity = _intensity;
                    lighPntW._radius    = _radius;
                    lighPntW._sector    = sector;

                    lightPointNode->addLightPoint( lighPntW );

                    ydel += 1.5;
                }

                ycur = 7.5;
            }
        }

        // decision bar
        if( fabs( xcur + 300.0f ) < 1.0e-4 )
        {
            ycur = -12.5f;

            for ( int iSide = 0; iSide < 2; iSide++ )
            {
                ydel = -6.0;

                for ( int iLat = 0; iLat < 9; iLat++ )
                {
                    osgSim::LightPoint lighPntW( osg::Vec3( x_real, ycur + ydel, -_height ), Colors::White );

                    lighPntW._intensity = _intensity;
                    lighPntW._radius    = _radius;
                    lighPntW._sector    = sector;

                    lightPointNode->addLightPoint( lighPntW );

                    ydel += 1.5f;
                }

                ycur = 12.5f;
            }
        }

        if ( xcur > -300.0f )
        {
            ycur = -15.0f;

            for ( int iSide = 0; iSide < 2; iSide++ )
            {
                ydel = -2.0f;

                for ( int iLat = 0; iLat < 3; iLat++ )
                {
                    osgSim::LightPoint lighPntR( osg::Vec3( x_real, ycur + ydel, -_height ), Colors::Red );

                    lighPntR._intensity = _intensity;
                    lighPntR._radius    = _radius;
                    lighPntR._sector    = sector;

                    lightPointNode->addLightPoint( lighPntR );

                    ydel += 2.0;
                }

                ycur = 15.0;
            }

        }
        else
        {
            osg::ref_ptr<osgSim::BlinkSequence> blinkSequence = new osgSim::BlinkSequence;

            for ( int iBlink = 16; iBlink >= 0; iBlink-- )
            {
                float alpha = ( iFlash == iBlink ) ? 1.0f : 0.0f;
                blinkSequence->addPulse( 0.05f, osg::Vec4( 1.0f, 1.0f, 1.0f, alpha ) );
            }

            osgSim::LightPoint lighPntW( osg::Vec3( x_real, 0.0f, -_height ), Colors::White );

            lighPntW._intensity = 2.0f * _intensity;
            lighPntW._radius    = 2.0f * _radius;
            lighPntW._sector    = sector;
            lighPntW._blinkSequence = blinkSequence;

            lightPointNode->addLightPoint( lighPntW );

            iFlash++;
        }

        xcur += step;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Lights::RALS::createMALS( osgSim::LightPointNode *lightPointNode,
                               float xdel )
{
    float ycur = 0.0f;

    float xcur = 0.0f;
    float ydel = 0.0f;

    float step = 0.0f;


    double sectorDegFrom = _sectorDegFromFW;
    double sectorDegUnto = _sectorDegUntoFW;

    if ( xdel > 0.0f )
    {
        sectorDegFrom = _sectorDegFromBW;
        sectorDegUnto = _sectorDegUntoBW;
    }

    osg::ref_ptr<osgSim::Sector> sector = new osgSim::AzimSector( sectorDegFrom, sectorDegUnto );

    step = -60.0f;
    xcur = -60.0f;

    ycur = -20.0f;

    while ( xcur + 420.0f >= -1.0e-4 )
    {
        double x_real = ( xdel > 0.0f ) ? xdel - xcur : xdel + xcur;

        ydel = -2.0f;

        for ( int iLat = 0; iLat < 5; iLat++ )
        {
            osgSim::LightPoint lighPntW( osg::Vec3( x_real, ydel, -_height ), Colors::White );

            lighPntW._intensity = _intensity;
            lighPntW._radius    = _radius;
            lighPntW._sector    = sector;

            lightPointNode->addLightPoint( lighPntW );

            ydel += 1.0;
        }

        // decision bar
        if( fabs( xcur + 300.0f ) < 1.0e-4 )
        {
            ycur = -3.0f;

            for ( int iSide = 0; iSide < 2; iSide++ )
            {
                ydel = -7.5;

                for ( int iLat = 0; iLat < 5; iLat++ )
                {
                    osgSim::LightPoint lighPntW( osg::Vec3( x_real, ycur + ydel, -_height ), Colors::White );

                    lighPntW._intensity = _intensity;
                    lighPntW._radius    = _radius;
                    lighPntW._sector    = sector;

                    lightPointNode->addLightPoint( lighPntW );

                    ydel += 1.5f;
                }

                ycur = 12.0f;
            }
        }

        xcur += step;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Lights::RALS::createMALSF( osgSim::LightPointNode *lightPointNode,
                                float xdel )
{
    createMALS( lightPointNode, xdel );

    float xcur = 0.0f;

    float step = 0.0f;

    int iFlash = 0;

    double sectorDegFrom = _sectorDegFromFW;
    double sectorDegUnto = _sectorDegUntoFW;

    if ( xdel > 0.0f )
    {
        sectorDegFrom = _sectorDegFromBW;
        sectorDegUnto = _sectorDegUntoBW;
    }

    osg::ref_ptr<osgSim::Sector> sector = new osgSim::AzimSector( sectorDegFrom, sectorDegUnto );

    step = -60.0f;
    xcur = -300.0f;

    while ( xcur + 420.0f >= -1.0e-4 )
    {
        double x_real = ( xdel > 0.0f ) ? xdel - xcur : xdel + xcur;

        osg::ref_ptr<osgSim::BlinkSequence> blinkSequence = new osgSim::BlinkSequence;

        for ( int iBlink = 3; iBlink >= 0; iBlink-- )
        {
            float alpha = ( iFlash == iBlink ) ? 1.0f : 0.0f;
            blinkSequence->addPulse( 0.1, osg::Vec4( 1.0f, 1.0f, 1.0f, alpha ) );
        }

        osgSim::LightPoint lighPntW( osg::Vec3( x_real, 0.0f, -_height ), Colors::White );

        lighPntW._intensity = 2.0f * _intensity;
        lighPntW._radius    = 2.0f * _radius;
        lighPntW._sector    = sector;
        lighPntW._blinkSequence = blinkSequence;

        lightPointNode->addLightPoint( lighPntW );

        iFlash++;

        xcur += step;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Lights::RALS::createMALSR( osgSim::LightPointNode *lightPointNode,
                                float xdel )
{
    createMALS( lightPointNode, xdel );

    float xcur = 0.0f;

    float step = 0.0f;

    int iFlash = 0;

    double sectorDegFrom = _sectorDegFromFW;
    double sectorDegUnto = _sectorDegUntoFW;

    if ( xdel > 0.0f )
    {
        sectorDegFrom = _sectorDegFromBW;
        sectorDegUnto = _sectorDegUntoBW;
    }

    osg::ref_ptr<osgSim::Sector> sector = new osgSim::AzimSector( sectorDegFrom, sectorDegUnto );

    step = -60.0f;
    xcur = -480.0f;

    while ( xcur + 720.0f >= -1.0e-4 )
    {
        double x_real = ( xdel > 0.0f ) ? xdel - xcur : xdel + xcur;

        osg::ref_ptr<osgSim::BlinkSequence> blinkSequence = new osgSim::BlinkSequence;

        for ( int iBlink = 5; iBlink >= 0; iBlink-- )
        {
            float alpha = ( iFlash == iBlink ) ? 1.0f : 0.0f;
            blinkSequence->addPulse( 0.1, osg::Vec4( 1.0f, 1.0f, 1.0f, alpha ) );
        }

        osgSim::LightPoint lighPntW( osg::Vec3( x_real, 0.0f, -_height ), Colors::White );

        lighPntW._intensity = 2.0f * _intensity;
        lighPntW._radius    = 2.0f * _radius;
        lighPntW._sector    = sector;
        lighPntW._blinkSequence = blinkSequence;

        lightPointNode->addLightPoint( lighPntW );

        iFlash++;

        xcur += step;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Lights::RALS::createSSP1( osgSim::LightPointNode *lightPointNode, float runwayLength )
{
    float x = -runwayLength / 2.0f - 100.0f;
    float z = -5.0f;

    float intensity = 3.0f;
    float radius    = 4.0f * 0.2f;

    osg::ref_ptr<osgSim::Sector> sector = new osgSim::AzimSector( _sectorDegFromFW, _sectorDegUntoFW );

    for ( int i = 0; i < 9; i++ )
    {
        float y_tmp = 3.0f;

        for ( int j = 0; j < 3; j++ )
        {
            osgSim::LightPoint lighPnt( osg::Vec3( x, y_tmp, z ), Colors::Yellowish );

            lighPnt._intensity = intensity;
            lighPnt._radius    = radius;
            lighPnt._sector    = sector;

            lightPointNode->addLightPoint( lighPnt );

            y_tmp -= 3.0f;
        }

        if ( i == 2 )
        {
            y_tmp = 15.5f;

            for ( int j = 0; j < 5; j++ )
            {
                osgSim::LightPoint lighPntL( osg::Vec3( x, -y_tmp, z ), Colors::Yellowish );
                osgSim::LightPoint lighPntR( osg::Vec3( x,  y_tmp, z ), Colors::Yellowish );

                lighPntL._intensity = intensity;
                lighPntR._intensity = intensity;

                lighPntL._radius = radius;
                lighPntR._radius = radius;

                lighPntL._sector = sector;
                lighPntR._sector = sector;

                lightPointNode->addLightPoint( lighPntL );
                lightPointNode->addLightPoint( lighPntR );

                y_tmp -= 2.5f;
            }
        }

        x -= 100.0f;
    }

    osgSim::LightPoint lighPnt( osg::Vec3( -runwayLength / 2.0f - 1050.0f, 0.0f, z ), Colors::Red );

    lighPnt._intensity = intensity;
    lighPnt._radius    = radius;
    lighPnt._sector    = sector;

    lightPointNode->addLightPoint( lighPnt );
}

////////////////////////////////////////////////////////////////////////////////

void Lights::RCLS::createRCLS( osgSim::LightPointNode *lightPointNode,
                                float xdel )
{
    float xcur = 0.0f;
    float step = 0.0f;

    float sectorDegFromB = 0.0f;
    float sectorDegUntoB = 0.0f;
    float sectorDegFromF = 0.0f;
    float sectorDegUntoF = 0.0f;

    osg::ref_ptr<osgSim::Sector> sectorF;
    osg::ref_ptr<osgSim::Sector> sectorB;

    step = 15.0f;

    if ( xdel < 0.0 )
    {
        xcur = xdel + step;

        sectorDegFromB = _sectorDegFromBW;
        sectorDegUntoB = _sectorDegUntoBW;
        sectorDegFromF = _sectorDegFromFW;
        sectorDegUntoF = _sectorDegUntoFW;
    }
    else
    {
        xcur = xdel - step;

        sectorDegFromB = _sectorDegFromFW;
        sectorDegUntoB = _sectorDegUntoFW;
        sectorDegFromF = _sectorDegFromBW;
        sectorDegUntoF = _sectorDegUntoBW;
    }

    sectorB = new osgSim::AzimSector( sectorDegFromB, sectorDegUntoB );
    sectorF = new osgSim::AzimSector( sectorDegFromF, sectorDegUntoF );

    int iter = 0;

    while ( fabs( xcur ) > 0.0f )
    {
        osg::Vec4 colorB = Colors::White;
        osg::Vec4 colorF = Colors::White;

        if ( fabs( xcur ) > fabs( xdel ) - 900.0f ) colorB = ( iter % 2 == 0 ) ? Colors::Red : Colors::White;
        if ( fabs( xcur ) > fabs( xdel ) - 300.0f ) colorB = Colors::Red;

        osgSim::LightPoint lighPntF( osg::Vec3( xcur, 0.0f, -_height ), colorF );
        osgSim::LightPoint lighPntB( osg::Vec3( xcur, 0.0f, -_height ), colorB );

        lighPntF._intensity = _intensity;
        lighPntB._intensity = _intensity;

        lighPntF._radius = _radius;
        lighPntB._radius = _radius;

        lighPntF._sector = sectorF;
        lighPntB._sector = sectorB;

        lightPointNode->addLightPoint( lighPntF );
        lightPointNode->addLightPoint( lighPntB );

        if ( fabs( xcur ) < fabs( step ) )
        {
            break;
        }

        if ( xdel < 0.0 )
        {
            xcur += step;
        }
        else
        {
            xcur -= step;
        }

        iter++;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Lights::RELS::createRELS( osgSim::LightPointNode *lightPointNode, float runwayWidth,
                             float xdel, const Gaps &gaps )
{
    float xcur = 0.0f;
    float ydel = runwayWidth / 2.0f;
    float step = 0.0f;

    double sectorDegFromB = 0.0f;
    double sectorDegUntoB = 0.0f;
    double sectorDegFromF = 0.0f;
    double sectorDegUntoF = 0.0f;

    if ( xdel < 0.0f )
    {
        sectorDegFromB = _sectorDegFromBW;
        sectorDegUntoB = _sectorDegUntoBW;
        sectorDegFromF = _sectorDegFromFW;
        sectorDegUntoF = _sectorDegUntoFW;
    }
    else
    {
        sectorDegFromB = _sectorDegFromFW;
        sectorDegUntoB = _sectorDegUntoFW;
        sectorDegFromF = _sectorDegFromBW;
        sectorDegUntoF = _sectorDegUntoBW;
    }

    osg::ref_ptr<osgSim::Sector> sectorB = new osgSim::AzimSector( sectorDegFromB, sectorDegUntoB );
    osg::ref_ptr<osgSim::Sector> sectorF = new osgSim::AzimSector( sectorDegFromF, sectorDegUntoF );

    step = 60.0f;
    xcur = 30.0f;

    while ( xcur < fabs( xdel ) )
    {
        bool gap_l = false;
        bool gap_r = false;

        float x_abs = ( xdel > 0.0 ) ? 2.0 * fabs( xdel ) - xcur : xcur;

        for ( Gaps::const_iterator it = gaps.begin(); it != gaps.end(); ++it )
        {
            if ( x_abs > (*it).from && x_abs < (*it).to )
            {
                gap_l |= ( (*it).side == Gap::Left  ) || ( (*it).side == Gap::Both );
                gap_r |= ( (*it).side == Gap::Right ) || ( (*it).side == Gap::Both );
            }
        }

        osg::Vec4 colorB = Colors::White;    // color backward
        osg::Vec4 colorF = Colors::White;    // color foreward

        if ( xcur <=  600.0f ) colorB = Colors::Yellow;

        float x_real = 0.0f;

        if ( xdel < 0.0 )
            x_real = xdel + xcur;
        else
            x_real = xdel - xcur;

        osgSim::LightPoint lighPntF1( osg::Vec3( x_real, -ydel - _offset, -_height ), colorF );
        osgSim::LightPoint lighPntF2( osg::Vec3( x_real,  ydel + _offset, -_height ), colorF );
        osgSim::LightPoint lighPntB1( osg::Vec3( x_real, -ydel - _offset, -_height ), colorB );
        osgSim::LightPoint lighPntB2( osg::Vec3( x_real,  ydel + _offset, -_height ), colorB );

        lighPntF1._intensity = _intensity;
        lighPntF2._intensity = _intensity;
        lighPntB1._intensity = _intensity;
        lighPntB2._intensity = _intensity;

        lighPntF1._radius = _radius;
        lighPntF2._radius = _radius;
        lighPntB1._radius = _radius;
        lighPntB2._radius = _radius;

        lighPntF1._sector = sectorF;
        lighPntF2._sector = sectorF;
        lighPntB1._sector = sectorB;
        lighPntB2._sector = sectorB;

        if ( !gap_l  )
        {
            lightPointNode->addLightPoint( lighPntF1 );
            lightPointNode->addLightPoint( lighPntB1 );
        }

        if ( !gap_r )
        {
            lightPointNode->addLightPoint( lighPntF2 );
            lightPointNode->addLightPoint( lighPntB2 );
        }

        xcur += step;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Lights::RELS::createSSP1( osgSim::LightPointNode *lightPointNode, float runwayWidth, float runwayLength )
{
    float x = -runwayLength / 2.0f + 100.0f;
    float y =  runwayWidth  / 2.0f + 1.0f;
    float z = -1.0f;

    float intensity = 1.5f;
    float radius    = 4.0f * 0.2f;

    osg::ref_ptr<osgSim::Sector> sector = new osgSim::AzimSector( _sectorDegFromFW, _sectorDegUntoFW );

    int iter = 0;

    while ( x < runwayLength / 2.0f )
    {
        osgSim::LightPoint lighPnt1( osg::Vec3( x, -y, z ), Colors::Yellowish );
        osgSim::LightPoint lighPnt2( osg::Vec3( x,  y, z ), Colors::Yellowish );

        lighPnt1._intensity = intensity;
        lighPnt2._intensity = intensity;

        lighPnt1._radius = radius;
        lighPnt2._radius = radius;

//        lighPnt1._sector = sector;
//        lighPnt2._sector = sector;

        lightPointNode->addLightPoint( lighPnt1 );
        lightPointNode->addLightPoint( lighPnt2 );

        if ( iter == 5 )
        {
            float y_tmp = y + 2.5;

            for ( int j = 0; j < 2; j++ )
            {
                osgSim::LightPoint lighPntL( osg::Vec3( x, -y_tmp, z ), Colors::Yellowish );
                osgSim::LightPoint lighPntR( osg::Vec3( x,  y_tmp, z ), Colors::Yellowish );

                lighPntL._intensity = intensity;
                lighPntR._intensity = intensity;

                lighPntL._radius = radius;
                lighPntR._radius = radius;

                lighPntL._sector = sector;
                lighPntR._sector = sector;

                lightPointNode->addLightPoint( lighPntL );
                lightPointNode->addLightPoint( lighPntR );

                y_tmp += 2.5f;
            }
        }

        x += 100.0;
        iter++;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Lights::RTEL::createRTEL_Base( osgSim::LightPointNode *lightPointNode, float runwayWidth,
                                  float xdel )
{
    float ycur = 0.0f;
    float ydel = runwayWidth / 2.0f;
    float step = 3.0f;

    float sectorDegFromG = 0.0f;
    float sectorDegUntoG = 0.0f;
    float sectorDegFromR = 0.0f;
    float sectorDegUntoR = 0.0f;

    if ( xdel < 0.0f )
    {
        sectorDegFromG = _sectorDegFromFW;
        sectorDegUntoG = _sectorDegUntoFW;
        sectorDegFromR = _sectorDegFromBW;
        sectorDegUntoR = _sectorDegUntoBW;
    }
    else
    {
        sectorDegFromG = _sectorDegFromBW;
        sectorDegUntoG = _sectorDegUntoBW;
        sectorDegFromR = _sectorDegFromFW;
        sectorDegUntoR = _sectorDegUntoFW;
    }

    osg::ref_ptr<osgSim::Sector> sectorG = new osgSim::AzimSector( sectorDegFromG, sectorDegUntoG );
    osg::ref_ptr<osgSim::Sector> sectorR = new osgSim::AzimSector( sectorDegFromR, sectorDegUntoR );

    int iLatMax = 4;

    if ( 2.0*ydel < 45.0f ) iLatMax = 3;

    ycur = -ydel - _offset;

    for ( int iSide = 0; iSide < 2; iSide++ )
    {
        float step_y = 0.0f;

        for ( int iLat = 0; iLat < iLatMax; iLat++ )
        {
            osgSim::LightPoint lighPntG( osg::Vec3( xdel, ycur + step_y, -_height ), Colors::Green );
            osgSim::LightPoint lighPntR( osg::Vec3( xdel, ycur + step_y, -_height ), Colors::Red );

            lighPntG._intensity = _intensity;
            lighPntG._radius    = _radius;
            lighPntG._sector    = sectorG;

            lighPntR._intensity = _intensity;
            lighPntR._radius    = _radius;
            lighPntR._sector    = sectorR;

            lightPointNode->addLightPoint( lighPntG );
            lightPointNode->addLightPoint( lighPntR );

            step_y += step;
        }

        ycur = ydel + _offset - ( iLatMax - 1 ) * step;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Lights::RTEL::createRTEL_Cat2( osgSim::LightPointNode *lightPointNode, float runwayWidth,
                                  float xdel )
{
    int steps = ceil( ( runwayWidth + 2.0f * _offset - 3.0f ) / 3.0f );

    if ( steps < 1 ) steps = 1;

    float halfWidth = runwayWidth  / 2.0f;

    float step = ( runwayWidth + 2.0f * _offset - 3.0f ) / steps;
    float ycur = -halfWidth - _offset + 1.5f;

    double sectorDegFrom = 0.0f;
    double sectorDegUnto = 0.0f;

    if ( xdel < 0.0f )
    {
        sectorDegFrom = _sectorDegFromFW;
        sectorDegUnto = _sectorDegUntoFW;
    }
    else
    {
        sectorDegFrom = _sectorDegFromBW;
        sectorDegUnto = _sectorDegUntoBW;
    }

    osg::ref_ptr<osgSim::Sector> sector = new osgSim::AzimSector( sectorDegFrom, sectorDegUnto );

    osg::Vec4 color = Colors::Green;

    float ylimit = halfWidth + _offset - 1.5f;

    while ( ycur - ylimit <= 1.0e-4 )
    {
        osgSim::LightPoint lighPnt( osg::Vec3( xdel, ycur, -_height ), color );

        lighPnt._intensity = _intensity;
        lighPnt._radius    = _radius;
        lighPnt._sector    = sector;

        lightPointNode->addLightPoint( lighPnt );

        ycur += step;
    }

    createRTEL_Bars( lightPointNode, runwayWidth, xdel );
}

////////////////////////////////////////////////////////////////////////////////

void Lights::RTEL::createRTEL_Bars( osgSim::LightPointNode *lightPointNode, float runwayWidth,
                                  float xdel )
{
    float halfWidth = runwayWidth  / 2.0f;

    float ycur = -halfWidth - _offset - 1.5f;
    float step = -1.5f;

    double sectorDegFrom = 0.0f;
    double sectorDegUnto = 0.0f;

    if ( xdel < 0.0f )
    {
        sectorDegFrom = _sectorDegFromFW;
        sectorDegUnto = _sectorDegUntoFW;
    }
    else
    {
        sectorDegFrom = _sectorDegFromBW;
        sectorDegUnto = _sectorDegUntoBW;
    }

    osg::ref_ptr<osgSim::Sector> sector = new osgSim::AzimSector( sectorDegFrom, sectorDegUnto );

    osg::Vec4 color = Colors::Green;

    for ( int iSide = 0; iSide < 2; iSide++ )
    {
        for ( int iLat = 0; iLat < 8; iLat++ )
        {
            osgSim::LightPoint lighPnt( osg::Vec3( xdel, ycur, -_height ), color );

            lighPnt._intensity = _intensity;
            lighPnt._radius    = _radius;
            lighPnt._sector    = sector;

            lightPointNode->addLightPoint( lighPnt );

            ycur += step;
        }

        ycur = halfWidth + _offset + 1.5f;
        step = 1.5f;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Lights::RTEL::createSSP1( osgSim::LightPointNode *lightPointNode, float runwayWidth, float runwayLength )
{
    float x = -runwayLength / 2.0f - 3.0f;
    float y =  runwayWidth  / 2.0f - 5.0f;
    float z = -1.0f;

    float intensity = 3.0f;
    float radius    = 4.0f * 0.2f;

    osg::ref_ptr<osgSim::Sector> sector = new osgSim::AzimSector( _sectorDegFromFW, _sectorDegUntoFW );

    for ( int i = 0; i < 8; i++ )
    {
        osgSim::LightPoint lighPntL( osg::Vec3( x, -y, z ), Colors::Green );
        osgSim::LightPoint lighPntR( osg::Vec3( x,  y, z ), Colors::Green );

        lighPntL._intensity = intensity;
        lighPntR._intensity = intensity;

        lighPntL._radius = radius;
        lighPntR._radius = radius;

        lighPntL._sector = sector;
        lighPntR._sector = sector;

        lightPointNode->addLightPoint( lighPntL );
        lightPointNode->addLightPoint( lighPntR );

        y += 2.5f;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Lights::TDZL::createTDZL( osgSim::LightPointNode *lightPointNode,
                             float xdel, float spacing )
{
    float xcur = 0.0f;
    float ycur = 0.0f;

    float step = 0.0f;

    float length = 900.0f;

    if ( fabs( xdel ) < 900.0f ) length = fabs( xdel );

    float sectorFrom = 0.0f;
    float sectorUnto = 0.0f;

    if ( xdel < 0.0 )
    {
        sectorFrom = _sectorDegFromFW;
        sectorUnto = _sectorDegUntoFW;
    }
    else
    {
        sectorFrom = _sectorDegFromBW;
        sectorUnto = _sectorDegUntoBW;
    }

    osg::ref_ptr<osgSim::Sector> sector = new osgSim::AzimSector( sectorFrom, sectorUnto );

    step = 30.0f;
    xcur = 30.0f;

    while ( xcur < length + 1.0e-6 )
    {
        ycur = -spacing / 2.0f - 3.0f - 1.0f;

        for ( int iSide = 0; iSide < 2; iSide++ )
        {
            for ( int iLat = 0; iLat < 3; iLat++ )
            {
                float x_real = 0.0;

                if ( xdel < 0.0 )
                    x_real = xdel + xcur;
                else
                    x_real = xdel - xcur;

                osgSim::LightPoint lighPnt( osg::Vec3( x_real, ycur, -_height ), Colors::White );

                lighPnt._intensity = _intensity;
                lighPnt._radius    = _radius;
                lighPnt._sector    = sector;

                lightPointNode->addLightPoint( lighPnt );

                ycur += 1.5f;
            }

            ycur = spacing / 2.0f + 1.0f;
        }

        xcur += step;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Lights::VGSI::createPAPI( osgSim::LightPointNode *lightPointNode,
                               float xdel, float ydel )
{
    if ( ydel < 0.0 ) ydel -= 3.0f * 9.0f;

    float ya = -ydel - 9.0f * 3.0f;
    float yb = -ydel - 9.0f * 2.0f;
    float yc = -ydel - 9.0f;
    float yd = -ydel;

    double sectorDegFrom = _sectorDegFromFVN;
    double sectorDegUnto = _sectorDegUntoFVN;

    if ( xdel > 0.0f )
    {
        ya = ydel + 9.0f * 3.0f;
        yb = ydel + 9.0f * 2.0f;
        yc = ydel + 9.0f;
        yd = ydel;

        sectorDegFrom = _sectorDegFromBVN;
        sectorDegUnto = _sectorDegUntoBVN;
    }

    osg::ref_ptr<osgSim::Sector> sectorAR =
            new osgSim::AzimElevationSector( sectorDegFrom, sectorDegUnto,
                                             osg::DegreesToRadians(   0.0f ), osg::DegreesToRadians(  -2.5f ) );
    osg::ref_ptr<osgSim::Sector> sectorAW =
            new osgSim::AzimElevationSector( sectorDegFrom, sectorDegUnto,
                                             osg::DegreesToRadians(  -2.5f ), osg::DegreesToRadians( -30.0f ) );
    osg::ref_ptr<osgSim::Sector> sectorBR =
            new osgSim::AzimElevationSector( sectorDegFrom, sectorDegUnto,
                                             osg::DegreesToRadians(   0.0f ), osg::DegreesToRadians(  -2.8f ) );
    osg::ref_ptr<osgSim::Sector> sectorBW =
            new osgSim::AzimElevationSector( sectorDegFrom, sectorDegUnto,
                                             osg::DegreesToRadians(  -2.8f ), osg::DegreesToRadians( -30.0f ) );
    osg::ref_ptr<osgSim::Sector> sectorCR =
            new osgSim::AzimElevationSector( sectorDegFrom, sectorDegUnto,
                                             osg::DegreesToRadians(   0.0f ), osg::DegreesToRadians(  -3.2f ) );
    osg::ref_ptr<osgSim::Sector> sectorCW =
            new osgSim::AzimElevationSector( sectorDegFrom, sectorDegUnto,
                                             osg::DegreesToRadians(  -3.2f ), osg::DegreesToRadians( -30.0f ) );
    osg::ref_ptr<osgSim::Sector> sectorDR =
            new osgSim::AzimElevationSector( sectorDegFrom, sectorDegUnto,
                                             osg::DegreesToRadians(   0.0f ), osg::DegreesToRadians(  -3.5f ) );
    osg::ref_ptr<osgSim::Sector> sectorDW =
            new osgSim::AzimElevationSector( sectorDegFrom, sectorDegUnto,
                                             osg::DegreesToRadians(  -3.5f ), osg::DegreesToRadians( -30.0f ) );

    osgSim::LightPoint lighPntAR( osg::Vec3( xdel, ya, -_height ), Colors::Red );
    osgSim::LightPoint lighPntAW( osg::Vec3( xdel, ya, -_height ), Colors::White );
    osgSim::LightPoint lighPntBR( osg::Vec3( xdel, yb, -_height ), Colors::Red );
    osgSim::LightPoint lighPntBW( osg::Vec3( xdel, yb, -_height ), Colors::White );
    osgSim::LightPoint lighPntCR( osg::Vec3( xdel, yc, -_height ), Colors::Red );
    osgSim::LightPoint lighPntCW( osg::Vec3( xdel, yc, -_height ), Colors::White );
    osgSim::LightPoint lighPntDR( osg::Vec3( xdel, yd, -_height ), Colors::Red );
    osgSim::LightPoint lighPntDW( osg::Vec3( xdel, yd, -_height ), Colors::White );

    lighPntAR._intensity = _intensity;
    lighPntAW._intensity = _intensity;
    lighPntBR._intensity = _intensity;
    lighPntBW._intensity = _intensity;
    lighPntCR._intensity = _intensity;
    lighPntCW._intensity = _intensity;
    lighPntDR._intensity = _intensity;
    lighPntDW._intensity = _intensity;

    lighPntAR._radius = _radius;
    lighPntAW._radius = _radius;
    lighPntBR._radius = _radius;
    lighPntBW._radius = _radius;
    lighPntCR._radius = _radius;
    lighPntCW._radius = _radius;
    lighPntDR._radius = _radius;
    lighPntDW._radius = _radius;

    lighPntAR._sector = sectorAR;
    lighPntAW._sector = sectorAW;
    lighPntBR._sector = sectorBR;
    lighPntBW._sector = sectorBW;
    lighPntCR._sector = sectorCR;
    lighPntCW._sector = sectorCW;
    lighPntDR._sector = sectorDR;
    lighPntDW._sector = sectorDW;

    lightPointNode->addLightPoint( lighPntAR );
    lightPointNode->addLightPoint( lighPntAW );
    lightPointNode->addLightPoint( lighPntBR );
    lightPointNode->addLightPoint( lighPntBW );
    lightPointNode->addLightPoint( lighPntCR );
    lightPointNode->addLightPoint( lighPntCW );
    lightPointNode->addLightPoint( lighPntDR );
    lightPointNode->addLightPoint( lighPntDW );
}

////////////////////////////////////////////////////////////////////////////////

void Lights::VGSI::createVASI( osgSim::LightPointNode *lightPointNode,
                               float xdel, float ydel )
{
    float y1 = -ydel - 3.0f;
    float y2 = -ydel;

    float xl = xdel - 100.0;
    float xh = xdel + 100.0;

    double sectorDegFrom = _sectorDegFromFVN;
    double sectorDegUnto = _sectorDegUntoFVN;

    if ( xdel > 0.0f )
    {
        y1 = ydel + 3.0f;
        y2 = ydel;

        sectorDegFrom = _sectorDegFromBVN;
        sectorDegUnto = _sectorDegUntoBVN;
    }

    osg::ref_ptr<osgSim::Sector> sectorR =
            new osgSim::AzimElevationSector( sectorDegFrom, sectorDegUnto,
                                             osg::DegreesToRadians(  0.0f ), osg::DegreesToRadians(  -3.0f ) );

    osg::ref_ptr<osgSim::Sector> sectorW =
            new osgSim::AzimElevationSector( sectorDegFrom, sectorDegUnto,
                                             osg::DegreesToRadians( -3.0f ), osg::DegreesToRadians( -30.0f ) );

    osgSim::LightPoint lighPntLR1( osg::Vec3( xl, y1, -_height ), Colors::Red );
    osgSim::LightPoint lighPntLR2( osg::Vec3( xl, y2, -_height ), Colors::Red );
    osgSim::LightPoint lighPntLW1( osg::Vec3( xl, y1, -_height ), Colors::White );
    osgSim::LightPoint lighPntLW2( osg::Vec3( xl, y2, -_height ), Colors::White );

    osgSim::LightPoint lighPntHR1( osg::Vec3( xh, y1, -_height ), Colors::Red );
    osgSim::LightPoint lighPntHR2( osg::Vec3( xh, y2, -_height ), Colors::Red );
    osgSim::LightPoint lighPntHW1( osg::Vec3( xh, y1, -_height ), Colors::White );
    osgSim::LightPoint lighPntHW2( osg::Vec3( xh, y2, -_height ), Colors::White );

    lighPntLR1._intensity = _intensity;
    lighPntLR2._intensity = _intensity;
    lighPntLW1._intensity = _intensity;
    lighPntLW2._intensity = _intensity;
    lighPntHR1._intensity = _intensity;
    lighPntHR2._intensity = _intensity;
    lighPntHW1._intensity = _intensity;
    lighPntHW2._intensity = _intensity;

    lighPntLR1._radius = _radius;
    lighPntLR2._radius = _radius;
    lighPntLW1._radius = _radius;
    lighPntLW2._radius = _radius;
    lighPntHR1._radius = _radius;
    lighPntHR2._radius = _radius;
    lighPntHW1._radius = _radius;
    lighPntHW2._radius = _radius;

    lighPntLR1._sector = sectorR;
    lighPntLR2._sector = sectorR;
    lighPntLW1._sector = sectorW;
    lighPntLW2._sector = sectorW;
    lighPntHR1._sector = sectorR;
    lighPntHR2._sector = sectorR;
    lighPntHW1._sector = sectorW;
    lighPntHW2._sector = sectorW;

    lightPointNode->addLightPoint( lighPntLR1 );
    lightPointNode->addLightPoint( lighPntLR2 );
    lightPointNode->addLightPoint( lighPntLW1 );
    lightPointNode->addLightPoint( lighPntLW2 );
    lightPointNode->addLightPoint( lighPntHR1 );
    lightPointNode->addLightPoint( lighPntHR2 );
    lightPointNode->addLightPoint( lighPntHW1 );
    lightPointNode->addLightPoint( lighPntHW2 );
}

////////////////////////////////////////////////////////////////////////////////

void Lights::VGSI::createVASI3( osgSim::LightPointNode *lightPointNode,
                                float xdel, float ydel )
{
    float y1 = -ydel - 3.0f;
    float y2 = -ydel;

    float xl = xdel - 200.0;
    float xm = xdel;
    float xh = xdel + 200.0;

    double sectorDegFrom = _sectorDegFromFVN;
    double sectorDegUnto = _sectorDegUntoFVN;

    if ( xdel > 0.0f )
    {
        y1 = ydel + 3.0f;
        y2 = ydel;

        sectorDegFrom = _sectorDegFromBVN;
        sectorDegUnto = _sectorDegUntoBVN;
    }

    osg::ref_ptr<osgSim::Sector> sectorR =
            new osgSim::AzimElevationSector( sectorDegFrom, sectorDegUnto,
                                             osg::DegreesToRadians(  0.0f ), osg::DegreesToRadians(  -3.0f ) );

    osg::ref_ptr<osgSim::Sector> sectorW =
            new osgSim::AzimElevationSector( sectorDegFrom, sectorDegUnto,
                                             osg::DegreesToRadians( -3.0f ), osg::DegreesToRadians( -30.0f ) );

    osgSim::LightPoint lighPntLR1( osg::Vec3( xl, y1, -_height ), Colors::Red );
    osgSim::LightPoint lighPntLR2( osg::Vec3( xl, y2, -_height ), Colors::Red );
    osgSim::LightPoint lighPntLW1( osg::Vec3( xl, y1, -_height ), Colors::White );
    osgSim::LightPoint lighPntLW2( osg::Vec3( xl, y2, -_height ), Colors::White );

    osgSim::LightPoint lighPntMR1( osg::Vec3( xm, y1, -_height ), Colors::Red );
    osgSim::LightPoint lighPntMR2( osg::Vec3( xm, y2, -_height ), Colors::Red );
    osgSim::LightPoint lighPntMW1( osg::Vec3( xm, y1, -_height ), Colors::White );
    osgSim::LightPoint lighPntMW2( osg::Vec3( xm, y2, -_height ), Colors::White );

    osgSim::LightPoint lighPntHR1( osg::Vec3( xh, y1, -_height ), Colors::Red );
    osgSim::LightPoint lighPntHR2( osg::Vec3( xh, y2, -_height ), Colors::Red );
    osgSim::LightPoint lighPntHW1( osg::Vec3( xh, y1, -_height ), Colors::White );
    osgSim::LightPoint lighPntHW2( osg::Vec3( xh, y2, -_height ), Colors::White );

    lighPntLR1._intensity = _intensity;
    lighPntLR2._intensity = _intensity;
    lighPntLW1._intensity = _intensity;
    lighPntLW2._intensity = _intensity;
    lighPntMR1._intensity = _intensity;
    lighPntMR2._intensity = _intensity;
    lighPntMW1._intensity = _intensity;
    lighPntMW2._intensity = _intensity;
    lighPntHR1._intensity = _intensity;
    lighPntHR2._intensity = _intensity;
    lighPntHW1._intensity = _intensity;
    lighPntHW2._intensity = _intensity;

    lighPntLR1._radius = _radius;
    lighPntLR2._radius = _radius;
    lighPntLW1._radius = _radius;
    lighPntLW2._radius = _radius;
    lighPntMR1._radius = _radius;
    lighPntMR2._radius = _radius;
    lighPntMW1._radius = _radius;
    lighPntMW2._radius = _radius;
    lighPntHR1._radius = _radius;
    lighPntHR2._radius = _radius;
    lighPntHW1._radius = _radius;
    lighPntHW2._radius = _radius;

    lighPntLR1._sector = sectorR;
    lighPntLR2._sector = sectorR;
    lighPntLW1._sector = sectorW;
    lighPntLW2._sector = sectorW;
    lighPntMR1._sector = sectorR;
    lighPntMR2._sector = sectorR;
    lighPntMW1._sector = sectorW;
    lighPntMW2._sector = sectorW;
    lighPntHR1._sector = sectorR;
    lighPntHR2._sector = sectorR;
    lighPntHW1._sector = sectorW;
    lighPntHW2._sector = sectorW;

    lightPointNode->addLightPoint( lighPntLR1 );
    lightPointNode->addLightPoint( lighPntLR2 );
    lightPointNode->addLightPoint( lighPntLW1 );
    lightPointNode->addLightPoint( lighPntLW2 );
    lightPointNode->addLightPoint( lighPntMR1 );
    lightPointNode->addLightPoint( lighPntMR2 );
    lightPointNode->addLightPoint( lighPntMW1 );
    lightPointNode->addLightPoint( lighPntMW2 );
    lightPointNode->addLightPoint( lighPntHR1 );
    lightPointNode->addLightPoint( lighPntHR2 );
    lightPointNode->addLightPoint( lighPntHW1 );
    lightPointNode->addLightPoint( lighPntHW2 );
}
