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
#ifndef NOZZLE_H
#define NOZZLE_H

////////////////////////////////////////////////////////////////////////////////

#include "PAT.h"

#include <osg/Switch>

////////////////////////////////////////////////////////////////////////////////

/** Nozzle afterburner effect. */
class Nozzle : public PAT
{
public:

    static const char tagName[];

    Nozzle();

    Nozzle( QDomElement *xmlNode );

    virtual ~Nozzle();

    virtual void save( QDomDocument *doc, QDomElement *parentNode );

    virtual void update();

    void setFileGlow( std::string fileGlow );
    void setFileExhaust( std::string fileExhaust );

    void setSuffix( std::string suffix );

    inline std::string getFileGlow() const { return _fileGlow; }
    inline std::string getFileExhaust() const { return _fileExhaust; }

    inline std::string getSuffix() const { return _suffix; }

protected:

    osg::ref_ptr<osg::Switch> _switch;
    osg::ref_ptr<osg::PositionAttitudeTransform> _exhaust;

    std::string _fileGlow;
    std::string _fileExhaust;

    std::string _suffix;

    void create();
    void createGlow();
    void createExhaust();

    void removeAllChildren();

    virtual void saveParameters( QDomDocument *doc, QDomElement *xmlNode );
};

////////////////////////////////////////////////////////////////////////////////

#endif // NOZZLE_H
