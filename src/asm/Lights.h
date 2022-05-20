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
#ifndef LIGHTS_H
#define LIGHTS_H

////////////////////////////////////////////////////////////////////////////////

#include <osgSim/LightPointNode>

#include <asm/Gaps.h>

////////////////////////////////////////////////////////////////////////////////

class Lights
{
public:

    static const float _sectorDegFromFN;    ///< light point sector - foreward narrow from
    static const float _sectorDegUntoFN;    ///< light point sector - foreward narrow unto
    static const float _sectorDegFromBN;    ///< light point sector - backward narrow from
    static const float _sectorDegUntoBN;    ///< light point sector - backward narrow unto
    static const float _sectorDegFromFW;    ///< light point sector - foreward wide from
    static const float _sectorDegUntoFW;    ///< light point sector - foreward wide unto
    static const float _sectorDegFromBW;    ///< light point sector - backward wide from
    static const float _sectorDegUntoBW;    ///< light point sector - backward wide unto

    static const float _sectorDegFromFVN;   ///< light point sector - foreward very narrow from
    static const float _sectorDegUntoFVN;   ///< light point sector - foreward very narrow unto
    static const float _sectorDegFromBVN;   ///< light point sector - backward very narrow from
    static const float _sectorDegUntoBVN;   ///< light point sector - backward very narrow unto

    /** */
    static void setTexture( osgSim::LightPointNode *lightPointNode,
                            const std::string &textureFile );

    /** Runway Approach Lighting System. */
    class RALS
    {
    public:

        static const float _height;
        static const float _radius;
        static const float _intensity;

        static void createALSF1( osg::Group *group, float runwayWidth,
                                 float xdel );

        static void createALSF2( osg::Group *group, float runwayWidth,
                                 float xdel );

        static void createMALS( osg::Group *group, float runwayWidth,
                                float xdel );

        static void createMALSF( osg::Group *group, float runwayWidth,
                                 float xdel );

        static void createMALSR( osg::Group *group, float runwayWidth,
                                 float xdel );

        static void createALSF1( osgSim::LightPointNode *lightPointNode,
                                 float xdel );

        static void createALSF2( osgSim::LightPointNode *lightPointNode,
                                 float xdel );

        static void createMALS( osgSim::LightPointNode *lightPointNode,
                                float xdel );

        static void createMALSF( osgSim::LightPointNode *lightPointNode,
                                 float xdel );

        static void createMALSR( osgSim::LightPointNode *lightPointNode,
                                 float xdel );

        static void createSSP1( osgSim::LightPointNode *lightPointNode, float runwayLength );
    };

    /** Runway Centerline Lighting System. */
    class RCLS
    {
    public:

        static const float _height;
        static const float _radius;
        static const float _intensity;

        static void createRCLS( osg::Group *group, float runwayLength );

        static void createRCLS( osgSim::LightPointNode *lightPointNode,
                                float xdel );
    };

    /** Runway Edge Light Systems. */
    class RELS
    {
    public:

        static const float _height;
        static const float _radius;
        static const float _intensity;
        static const float _offset;

        static void createRELS( osg::Group *group, float runwayWidth, float runwayLength,
                                const Gaps &gaps );

        static void createRELS( osgSim::LightPointNode *lightPointNode, float runwayWidth,
                                float xdel, const Gaps &gaps );

        static void createSSP1( osgSim::LightPointNode *lightPointNode, float runwayWidth, float runwayLength );
    };

    /** Runway Threshold and End Lights. */
    class RTEL
    {
    public:

        static const float _height;
        static const float _radius;
        static const float _intensity;
        static const float _offset;

        static void createRTEL_Base( osgSim::LightPointNode *lightPointNode, float runwayWidth,
                                     float xdel );

        static void createRTEL_Cat2( osgSim::LightPointNode *lightPointNode, float runwayWidth,
                                     float xdel );

        static void createRTEL_Bars( osgSim::LightPointNode *lightPointNode, float runwayWidth,
                                     float xdel );

        static void createSSP1( osgSim::LightPointNode *lightPointNode, float runwayWidth, float runwayLength );
    };

    /** Touchdown Zone Lights. */
    class TDZL
    {
    public:

        static const float _height;
        static const float _radius;
        static const float _intensity;

        static void createTDZL( osg::Group *groupL, osg::Group *groupH, float runwayLength );

        static void createTDZL( osgSim::LightPointNode *lightPointNode,
                                float xdel, float spacing );
    };

    /** Visual Glide Slope Indicator. */
    class VGSI
    {
    public:

        static const float _height;
        static const float _radius;
        static const float _intensity;

        static void createPAPI( osg::Group *group, float xdel, float ydel );
        static void createVASI( osg::Group *group, float xdel, float ydel );
        static void createVASI3( osg::Group *group, float xdel, float ydel );

        static void createPAPI( osgSim::LightPointNode *lightPointNode,
                                float xdel, float ydel );

        static void createVASI( osgSim::LightPointNode *lightPointNode,
                                float xdel, float ydel );

        static void createVASI3( osgSim::LightPointNode *lightPointNode,
                                 float xdel, float ydel );
    };

    /** Luch-2MU SSP-1 */
    class SSP1
    {
    public:

        static void createSSP1( osg::Group *group, float runwayWidth, float runwayLength );
    };
};

////////////////////////////////////////////////////////////////////////////////

#endif // LIGHTS_H
