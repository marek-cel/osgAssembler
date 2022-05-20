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
#ifndef DOCUMENT_H
#define DOCUMENT_H

////////////////////////////////////////////////////////////////////////////////

#include <QDomDocument>
#include <QDomElement>

#include "Group.h"

////////////////////////////////////////////////////////////////////////////////

/** */
class Document
{
public:

    /** */
    Document();

    /** */
    Document( QString fileName );

    /** */
    virtual ~Document();

    /** */
    void update();

    /** */
    bool removeNode( unsigned int i );

    /** */
    Component* getNode( unsigned int i );

    /** */
    void newEmpty();

    /** */
    bool exportAs( QString fileName );

    /** */
    bool readFile( QString fileName );

    /** */
    bool saveFile( QString fileName );

    /** */
    osg::Group* getRootNode();

    /** */
    inline Group* getRootGroup() { return _root; }

    /** */
    inline void setRootGroup( Group* root ) { _root = root; }

private:

    Group *_root;   ///<
};

////////////////////////////////////////////////////////////////////////////////

#endif // DOCUMENT_H
