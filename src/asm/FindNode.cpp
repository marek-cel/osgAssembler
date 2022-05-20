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

#include <asm/FindNode.h>

////////////////////////////////////////////////////////////////////////////////

osg::Node* FindNode::findFirst( osg::Node* node, const std::string &name )
{
    if ( node )
    {
        FindNode FindNode( name );
        node->accept( FindNode );
        return dynamic_cast<osg::Node*>( FindNode.getFirst().get() );
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

FindNode::Nodes FindNode::findNodes( osg::Node* node, const std::string &name )
{
    if ( node )
    {
        FindNode FindNode( name, true );
        node->accept( FindNode );
        return FindNode.getNodes();
    }

    return Nodes();
}

////////////////////////////////////////////////////////////////////////////////

FindNode::FindNode() :
    osg::NodeVisitor( TRAVERSE_ALL_CHILDREN ),

    _findAll ( false )
{
    _name = "";
    _nodes.clear();
}

////////////////////////////////////////////////////////////////////////////////

FindNode::FindNode( const std::string &name, bool findAll ) :
    osg::NodeVisitor( TRAVERSE_ALL_CHILDREN ),

    _findAll ( findAll )
{
    _name = name;
    _nodes.clear();
}

////////////////////////////////////////////////////////////////////////////////

void FindNode::apply( osg::Node &searchNode )
{
    if ( _name == searchNode.getName() || _name.length() == 0 )
    {
        osg::ref_ptr<osg::Node> tempNode = &searchNode;

        _nodes.push_back( tempNode.get() );

        if ( _findAll ) traverse( searchNode );
    }
    else
    {
        traverse( searchNode );
    }
}

////////////////////////////////////////////////////////////////////////////////

osg::ref_ptr<osg::Node> FindNode::getFirst()
{
    if ( _nodes.empty() )
    {
        return 0;
    }
    else
    {
        return _nodes[ 0 ];
    }
}

////////////////////////////////////////////////////////////////////////////////

FindNode::Nodes FindNode::getNodes()
{
    return _nodes;
}
