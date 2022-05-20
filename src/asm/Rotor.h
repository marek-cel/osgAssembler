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
#ifndef ROTOR_H
#define ROTOR_H

////////////////////////////////////////////////////////////////////////////////

#include "PAT.h"

////////////////////////////////////////////////////////////////////////////////

/** Helicopter Main Rotor. */
class Rotor : public PAT
{
public:

    typedef std::vector< osg::ref_ptr<osg::PositionAttitudeTransform> > Blades;

    static const char tagName[];

    enum Direction
    {
        CW  = 0,
        CCW = 1
    };

    Rotor();

    Rotor( QDomElement *xmlNode );

    virtual ~Rotor();

    virtual void save( QDomDocument *doc, QDomElement *parentNode );

    virtual void update();

    void setBladesCount( unsigned int bladesCount );
    void setBladesOffset( double bladesOffset );
    void setDirection( Direction direction );
    void setFileBlade( std::string fileBlade );
    void setFileShaft( std::string fileShaft );

    inline unsigned int getBladesCount() const { return _bladesCount; }
    inline double getBladesOffset() const { return _bladesOffset; }
    inline Direction getDirection() const { return _direction; }
    inline std::string getFileBlade() const { return _fileBlade; }
    inline std::string getFileShaft() const { return _fileShaft; }

protected:

    osg::ref_ptr<osg::PositionAttitudeTransform> _mainRotor;

    Blades _blades;

    unsigned int _bladesCount;
    double _bladesOffset;
    Direction _direction;

    std::string _fileBlade;
    std::string _fileShaft;

    void create();
    void createBlades();
    void createShaft();

    void removeAllChildren();

    virtual void saveParameters( QDomDocument *doc, QDomElement *xmlNode );
};

////////////////////////////////////////////////////////////////////////////////

#endif // ROTOR_H
