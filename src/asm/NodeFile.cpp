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

#include <asm/NodeFile.h>

#include <asm/Models.h>

////////////////////////////////////////////////////////////////////////////////

const char NodeFile::tagName[] = "node_file";

////////////////////////////////////////////////////////////////////////////////

NodeFile::NodeFile() :
    Component( new osg::Group() ),

    _group ( dynamic_cast< osg::Group* >( _node.get() ) )
{
    _file = "";
}

////////////////////////////////////////////////////////////////////////////////

NodeFile::NodeFile( QDomElement *xmlNode ) :
    Component( xmlNode, new osg::Group() ),

    _group ( dynamic_cast< osg::Group* >( _node.get() ) )
{
    setFile( xmlNode->attributeNode( "file" ).value().toLatin1().data() );
}

////////////////////////////////////////////////////////////////////////////////

NodeFile::~NodeFile()
{
    _group->removeChild( 0, _group->getNumChildren() );
}

////////////////////////////////////////////////////////////////////////////////

void NodeFile::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomElement node = doc->createElement( NodeFile::tagName );
    parentNode->appendChild( node );

    saveParameters( doc, &node );
}

////////////////////////////////////////////////////////////////////////////////

bool NodeFile::setFile( std::string file )
{
    _group->removeChild( 0, _group->getNumChildren() );

    _file = file;

    _fileNode = Models::get( _file );

    if ( _fileNode.valid() )
    {
        _group->addChild( _fileNode.get() );
        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////

void NodeFile::saveParameters( QDomDocument *doc, QDomElement *xmlNode )
{
    Component::saveParameters( doc, xmlNode );

    QDomAttr nodeFile = doc->createAttribute( "file" );
    nodeFile.setValue( getFile().c_str() );
    xmlNode->setAttributeNode( nodeFile );
}
