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
#ifndef COMPONENT_H
#define COMPONENT_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Node>

#include <QDomElement>

////////////////////////////////////////////////////////////////////////////////

class Component
{
public:

    Component( osg::Node *osgNode );

    Component( QDomElement *xmlNode, osg::Node *osgNode );

    virtual ~Component();

    virtual void save( QDomDocument *doc, QDomElement *parentNode ) = 0;

    virtual void update();

    inline std::string getName() const { return _node->getName(); }
    inline osg::Node* getNode() { return _node.get(); }

    inline void setName( const char* name ) { _node->setName( name ); }

    inline int  getDepthSortedBinValue() const { return _depthSortedBinValue; }
    inline bool getDepthSortedBinState() const { return _depthSortedBinState; }

    void setDepthSortedBinValue( int depthSortedBinValue );
    void setDepthSortedBinState( int depthSortedBinState );

    virtual void setSelected( bool );

protected:

    Component *_parent;

    osg::ref_ptr<osg::Node> _node;

    int  _depthSortedBinValue;
    bool _depthSortedBinState;

    virtual void saveParameters( QDomDocument *doc, QDomElement *xmlNode );

    void setTransparencyMode();
};

////////////////////////////////////////////////////////////////////////////////

#endif // COMPONENT_H
