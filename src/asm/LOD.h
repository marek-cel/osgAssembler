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
#ifndef LOD_H
#define LOD_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/LOD>

#include "Group.h"

////////////////////////////////////////////////////////////////////////////////

class LOD : public Group
{
public:

    static const char tagName[];

    LOD();

    LOD( QDomElement *xmlNode );

    virtual ~LOD();

    virtual bool addChild( Component *child );

    virtual void save( QDomDocument *doc, QDomElement *parentNode );

    inline double getIntervalF() const { return _interval_f; }
    inline double getIntervalS() const { return _interval_s; }
    inline double getIntervalO() const { return _interval_o; }

    virtual void setIntervalF( double interval_f );
    virtual void setIntervalS( double interval_s );
    virtual void setIntervalO( double interval_o );

protected:

    osg::ref_ptr<osg::LOD> _lod;

    double _interval_f;
    double _interval_s;
    double _interval_o;

    virtual void inflateLOD();

    virtual void saveParameters( QDomDocument *doc, QDomElement *xmlNode );
};

////////////////////////////////////////////////////////////////////////////////

#endif // LOD_H
