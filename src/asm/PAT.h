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
#ifndef PAT_H
#define PAT_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/PositionAttitudeTransform>

#include "Group.h"

////////////////////////////////////////////////////////////////////////////////

class PAT : public Group
{
public:

    static const char tagName[];

    enum Convention
    {
        XYZ = 0,
        ZYX
    };

    PAT();

    PAT( QDomElement *xmlNode );

    virtual ~PAT();

    virtual void save( QDomDocument *doc, QDomElement *parentNode );

    inline double getPx() const { return _px; }
    inline double getPy() const { return _py; }
    inline double getPz() const { return _pz; }

    inline double getAx() const { return _ax; }
    inline double getAy() const { return _ay; }
    inline double getAz() const { return _az; }

    inline Convention getConvention() const { return _convention; }

    inline void setPx( double px ) { _px = px; updatePositionAndAttitude(); }
    inline void setPy( double py ) { _py = py; updatePositionAndAttitude(); }
    inline void setPz( double pz ) { _pz = pz; updatePositionAndAttitude(); }

    inline void setAx( double ax ) { _ax = ax; updatePositionAndAttitude(); }
    inline void setAy( double ay ) { _ay = ay; updatePositionAndAttitude(); }
    inline void setAz( double az ) { _az = az; updatePositionAndAttitude(); }

    inline void setConvention( Convention convention ) { _convention = convention; updatePositionAndAttitude(); }

    void updatePositionAndAttitude();

protected:

    osg::ref_ptr<osg::PositionAttitudeTransform> _pat;

    double _px;
    double _py;
    double _pz;

    double _ax;
    double _ay;
    double _az;

    Convention _convention;

    virtual void saveParameters( QDomDocument *doc, QDomElement *xmlNode );
};

////////////////////////////////////////////////////////////////////////////////

#endif // PAT_H
