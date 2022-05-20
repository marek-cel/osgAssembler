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

#include <asm/Group.h>
#include <asm/LOD.h>
#include <asm/NodeFile.h>
#include <asm/PAT.h>
#include <asm/Switch.h>

#include <asm/Smoke.h>
#include <asm/Rotor.h>
#include <asm/FLOLS.h>
#include <asm/Runway.h>
#include <asm/World.h>
#include <asm/Nozzle.h>

////////////////////////////////////////////////////////////////////////////////

const char Group::tagName[] = "group";

////////////////////////////////////////////////////////////////////////////////

Group::Group( osg::Node *osgNode ) :
    Component( ( osgNode ) ? osgNode : new osg::Group() ),

    _group ( dynamic_cast< osg::Group* >( _node.get() ) )
{
    _children.clear();
}

////////////////////////////////////////////////////////////////////////////////

Group::Group( QDomElement *xmlNode, osg::Node *osgNode ) :
    Component( xmlNode, ( osgNode ) ? osgNode : new osg::Group() ),

    _group ( dynamic_cast< osg::Group* >( _node.get() ) )
{
    _children.clear();

    QDomElement childNode = xmlNode->firstChildElement();

    while ( !childNode.isNull() )
    {
        Component *compNode = 0;

        if ( childNode.tagName() == Group::tagName )
        {
            compNode = new Group( &childNode );
        }
        else if ( childNode.tagName() == LOD::tagName )
        {
            compNode = new LOD( &childNode );
        }
        else if ( childNode.tagName() == NodeFile::tagName )
        {
            compNode = new NodeFile( &childNode );
        }
        else if ( childNode.tagName() == PAT::tagName )
        {
            compNode = new PAT( &childNode );
        }
        else if ( childNode.tagName() == Switch::tagName )
        {
            compNode = new Switch( &childNode );
        }
        else if ( childNode.tagName() == Nozzle::tagName )
        {
            compNode = new Nozzle( &childNode );
        }
        else if ( childNode.tagName() == Smoke::tagName )
        {
            compNode = new Smoke( &childNode );
        }
        else if ( childNode.tagName() == Rotor::tagName )
        {
            compNode = new Rotor( &childNode );
        }
        else if ( childNode.tagName() == FLOLS::tagName )
        {
            compNode = new FLOLS( &childNode );
        }
        else if ( childNode.tagName() == Runway::tagName )
        {
            compNode = new Runway( &childNode );
        }

        else if ( childNode.tagName() == World::tagName )
        {
            compNode = new World( &childNode );
        }

        if ( compNode )
        {
            addChild( compNode );
        }

        childNode = childNode.nextSiblingElement();
    }
}

////////////////////////////////////////////////////////////////////////////////

Group::~Group()
{
    removeAllChildren();
}

////////////////////////////////////////////////////////////////////////////////

void Group::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomElement node = doc->createElement( Group::tagName );
    parentNode->appendChild( node );

    saveParameters( doc, &node );
}

////////////////////////////////////////////////////////////////////////////////

void Group::update()
{
    ////////////////////
    Component::update();
    ////////////////////

    for ( Children::iterator it = _children.begin(); it != _children.end(); ++it )
    {
        (*it)->update();
    }
}

////////////////////////////////////////////////////////////////////////////////

bool Group::addChild( Component *child )
{
    _children.push_back( child );
    return _group->addChild( child->getNode() );
}

////////////////////////////////////////////////////////////////////////////////

bool Group::removeChild( unsigned int i )
{
    if ( i <= _children.size() )
    {
        std::vector< Component* >::iterator iter = _children.begin();

        for ( unsigned int j = 0; j < i; j++ )
        {
            ++iter;
        }

        _children.erase( iter );
        return _group->removeChild( i );
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////

Component* Group::getChild( unsigned int i )
{
    if ( i <= _children.size() )
    {
        return _children.at( i );
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

void Group::removeAllChildren()
{
    for ( size_t i = 0; i < _children.size(); i++ )
    {
        if ( _children[ i ] != 0 )
        {
            delete _children[ i ];
            _children[ i ] = 0;
        }
    }

    if ( _group->getNumChildren() > 0 )
    {
        _group->removeChild( 0, _group->getNumChildren() );
    }
}

////////////////////////////////////////////////////////////////////////////////

void Group::saveParameters( QDomDocument *doc, QDomElement *xmlNode )
{
    Component::saveParameters( doc, xmlNode );

    for ( size_t i = 0; i < _children.size(); i++ )
    {
        if ( _children[ i ] ) _children[ i ]->save( doc, xmlNode );
    }
}
