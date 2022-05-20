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
#ifndef WORLD_H
#define WORLD_H

////////////////////////////////////////////////////////////////////////////////

#include "PAT.h"

////////////////////////////////////////////////////////////////////////////////

/** World. */
class World : public PAT
{
public:

    static const char tagName[];

    World();

    World( QDomElement *xmlNode );

    virtual ~World();

    virtual void save( QDomDocument *doc, QDomElement *parentNode );

    void setLat( double lat );
    void setLon( double lon );
    void setAlt( double alt );

    double getLat() const { return _lat; }
    double getLon() const { return _lon; }
    double getAlt() const { return _alt; }

    bool setFile( std::string file );

    std::string getFile() const { return _file; }

    virtual void updatePositionAndAttitude();

protected:

    osg::ref_ptr<osg::Node> _fileNode;

    double _lat;
    double _lon;
    double _alt;

    std::string _file;

    virtual void saveParameters( QDomDocument *doc, QDomElement *xmlNode );

};

////////////////////////////////////////////////////////////////////////////////

#endif // WORLD_H
