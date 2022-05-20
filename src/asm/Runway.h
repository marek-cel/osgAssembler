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
#ifndef RUNWAY_H
#define RUNWAY_H

////////////////////////////////////////////////////////////////////////////////

#include "PAT.h"

#include <osg/Switch>

#include <QVector>

#include <asm/Gaps.h>

////////////////////////////////////////////////////////////////////////////////

/** Runway. */
class Runway : public PAT
{
public:

    static const char tagName[];

    enum RALS
    {
        RALS_NONE = 0,
        RALS_ALSF1,         ///< Approach Lighting System with Sequenced Flashing Lights for category I operations
        RALS_ALSF2,         ///< Approach Lighting System with Sequenced Flashing Lights for category II or III operations
        RALS_MALS,          ///< Medium Intensity Approach Lighting System
        RALS_MALSF,         ///< Medium-intensity Approach Lighting System with Sequenced Flashing lights
        RALS_MALSR          ///< Medium-intensity Approach Lighting System with Runway Alignment Indicator Lights
    };

    enum VGSI
    {
        VGSI_NONE = 0,
        VGSI_P4L,           ///< PAPI P4L
        VGSI_P4R,
        VGSI_V4L,           ///< VASI V4L
        VGSI_V4R,
        VGSI_V6L,           ///< VASI V6L
        VGSI_V6R
    };

    Runway();

    Runway( QDomElement *xmlNode );

    virtual ~Runway();

    virtual void save( QDomDocument *doc, QDomElement *parentNode );

    void setRALS_Lo( RALS rals_lo );
    void setRALS_Hi( RALS rals_hi );

    void setVGSI_Lo( VGSI vgsi_lo );
    void setVGSI_Hi( VGSI vgsi_hi );

    void setLength( float length );
    void setWidth( float width );

    void setVGSI_X_Lo( float vgsi_x_lo );
    void setVGSI_X_Hi( float vgsi_x_hi );

    void setGaps( Gaps gaps );

    ////////////////////////////////////////////////////////////////////////////////

    void setRCLS( bool rcls );
    void setTDZL( bool tdzl );

    inline RALS getRALS_Lo() const { return _rals_lo; }
    inline RALS getRALS_Hi() const { return _rals_hi; }

    inline VGSI getVGSI_Lo() const { return _vgsi_lo; }
    inline VGSI getVGSI_Hi() const { return _vgsi_hi; }

    inline Gaps getGaps() const { return _gaps; }

    float getLength() const { return _length; }
    float getWidth() const { return _width; }

    float getVGSI_X_Lo() const { return _vgsi_x_lo; }
    float getVGSI_X_Hi() const { return _vgsi_x_hi; }

    inline bool getRCLS() const { return _rcls; }
    inline bool getTDZL() const { return _tdzl; }

protected:

    osg::ref_ptr<osg::Group> _runway;

    osg::ref_ptr<osg::Switch> _switchRALS_H;
    osg::ref_ptr<osg::Switch> _switchTDZL_H;
    osg::ref_ptr<osg::Switch> _switchVGSI_H;

    osg::ref_ptr<osg::Switch> _switchRALS_L;
    osg::ref_ptr<osg::Switch> _switchTDZL_L;
    osg::ref_ptr<osg::Switch> _switchVGSI_L;

    osg::ref_ptr<osg::Switch> _switchRCLS;
    osg::ref_ptr<osg::Switch> _switchRELS;

    RALS _rals_lo;
    RALS _rals_hi;

    VGSI _vgsi_lo;
    VGSI _vgsi_hi;

    Gaps _gaps;

    float _length;
    float _width;

    float _vgsi_x_lo;
    float _vgsi_x_hi;

    bool _rcls;
    bool _tdzl;

    void create();

    void removeAllRunwayChildren();

    virtual void saveParameters( QDomDocument *doc, QDomElement *xmlNode );

};

////////////////////////////////////////////////////////////////////////////////

#endif // RUNWAY_H
