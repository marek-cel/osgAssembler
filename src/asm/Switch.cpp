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

#include <asm/Switch.h>

////////////////////////////////////////////////////////////////////////////////

const char Switch::tagName[] = "switch";

////////////////////////////////////////////////////////////////////////////////

Switch::Switch() :
    Group( new osg::Switch() ),

    _switch ( dynamic_cast< osg::Switch* >( _node.get() ) )
{
    _switch = new osg::Switch();
    _group = _switch;
    _node = _group;
}

////////////////////////////////////////////////////////////////////////////////

Switch::Switch( QDomElement *xmlNode ) :
    Group( xmlNode, new osg::Switch() ),

    _switch ( dynamic_cast< osg::Switch* >( _node.get() ) )
{
    bool visible = xmlNode->attributeNode( "visible" ).value().toInt();

    setVisible( visible );
}

////////////////////////////////////////////////////////////////////////////////

Switch::~Switch()
{
    removeAllChildren();
}

////////////////////////////////////////////////////////////////////////////////

void Switch::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomElement node = doc->createElement( Switch::tagName );
    parentNode->appendChild( node );

    saveParameters( doc, &node );
}

////////////////////////////////////////////////////////////////////////////////

void Switch::setVisible( bool visible )
{
    _visible = visible;

    if ( _visible )
    {
        _switch->setAllChildrenOn();
    }
    else
    {
        _switch->setAllChildrenOff();
    }
}

////////////////////////////////////////////////////////////////////////////////

void Switch::saveParameters( QDomDocument *doc, QDomElement *xmlNode )
{
    Group::saveParameters( doc, xmlNode );

    QDomAttr nodeVisible = doc->createAttribute( "visible" );
    nodeVisible.setValue( QString::number( getVisible() ? 1 : 0 ) );
    xmlNode->setAttributeNode( nodeVisible );
}
