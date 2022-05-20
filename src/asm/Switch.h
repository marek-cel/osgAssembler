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
#ifndef SWITCH_H
#define SWITCH_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Switch>

#include "Group.h"

////////////////////////////////////////////////////////////////////////////////

class Switch : public Group
{
public:

    static const char tagName[];

    Switch();

    Switch( QDomElement *xmlNode );

    virtual ~Switch();

    virtual void save( QDomDocument *doc, QDomElement *parentNode );

    bool getVisible() const { return _visible; }
    void setVisible( bool visible );

protected:

    osg::ref_ptr<osg::Switch> _switch;

    bool _visible;

    virtual void saveParameters( QDomDocument *doc, QDomElement *xmlNode );
};

////////////////////////////////////////////////////////////////////////////////

#endif // SWITCH_H
