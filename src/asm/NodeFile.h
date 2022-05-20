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
#ifndef NODEFILE_H
#define NODEFILE_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Group>

#include "Component.h"

////////////////////////////////////////////////////////////////////////////////

class NodeFile : public Component
{
public:

    static const char tagName[];

    static Component *read( QDomElement *node );

    NodeFile();

    NodeFile( QDomElement *xmlNode );

    virtual ~NodeFile();

    virtual void save( QDomDocument *doc, QDomElement *parentNode );

    bool setFile( std::string file );

    std::string getFile() const { return _file; }

protected:

    osg::ref_ptr<osg::Group> _group;
    osg::ref_ptr<osg::Node> _fileNode;

    std::string _file;

    virtual void saveParameters( QDomDocument *doc, QDomElement *xmlNode );
};

////////////////////////////////////////////////////////////////////////////////

#endif // NODEFILE_H
