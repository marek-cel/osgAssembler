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
#ifndef GROUP_H
#define GROUP_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Group>

#include "Component.h"

////////////////////////////////////////////////////////////////////////////////

class Group : public Component
{
public:

    typedef std::vector< Component* > Children;

    static const char tagName[];

    Group( osg::Node *osgNode = 0 );

    Group( QDomElement *xmlNode, osg::Node *osgNode = 0 );

    virtual ~Group();

    virtual void save( QDomDocument *doc, QDomElement *parentNode );

    virtual void update();

    virtual bool addChild( Component *child );

    inline unsigned int getNumChildren() { return _children.size(); }

    bool removeChild( unsigned int i );

    Component* getChild( unsigned int i );

protected:

    osg::ref_ptr<osg::Group> _group;

    Children _children;

    void removeAllChildren();

    virtual void saveParameters( QDomDocument *doc, QDomElement *xmlNode );
};

////////////////////////////////////////////////////////////////////////////////

#endif // GROUP_H
