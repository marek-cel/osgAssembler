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

#include <osgDB/WriteFile>
#include <osgUtil/Optimizer>

#include <QFileInfo>
#include <QTextStream>

#include <asm/Document.h>

#include <asm/Group.h>
#include <asm/LOD.h>
#include <asm/NodeFile.h>
#include <asm/PAT.h>
#include <asm/Switch.h>

#include <asm/FLOLS.h>
#include <asm/Rotor.h>

////////////////////////////////////////////////////////////////////////////////

Document::Document() :
    _root ( 0 )
{
    newEmpty();
}

////////////////////////////////////////////////////////////////////////////////

Document::Document( QString fileName ) :
    _root ( 0 )
{
    readFile( fileName );
}

////////////////////////////////////////////////////////////////////////////////

Document::~Document()
{
    if ( _root ) delete _root;
    _root = 0;
}

////////////////////////////////////////////////////////////////////////////////

void Document::update()
{
    if ( _root )
    {
        _root->update();
    }
}

////////////////////////////////////////////////////////////////////////////////

bool Document::removeNode( unsigned int i )
{
    return _root->removeChild( i );
}

////////////////////////////////////////////////////////////////////////////////

Component* Document::getNode( unsigned int i )
{
    return _root->getChild( i );
}

////////////////////////////////////////////////////////////////////////////////

void Document::newEmpty()
{
    if ( _root ) delete _root;
    _root = 0;
}

////////////////////////////////////////////////////////////////////////////////

bool Document::exportAs( QString fileName )
{
    osgUtil::Optimizer optimizer;

    int options = osgUtil::Optimizer::FLATTEN_STATIC_TRANSFORMS |
            osgUtil::Optimizer::REMOVE_REDUNDANT_NODES |
            osgUtil::Optimizer::REMOVE_LOADED_PROXY_NODES |
            osgUtil::Optimizer::COMBINE_ADJACENT_LODS |
            osgUtil::Optimizer::SHARE_DUPLICATE_STATE |
            osgUtil::Optimizer::MERGE_GEOMETRY |
            osgUtil::Optimizer::MAKE_FAST_GEOMETRY |
            osgUtil::Optimizer::CHECK_GEOMETRY |
            //osgUtil::Optimizer::OPTIMIZE_TEXTURE_SETTINGS |
            osgUtil::Optimizer::STATIC_OBJECT_DETECTION;

    optimizer.optimize( _root->getNode(), options );
    //optimizer.optimize( _root->getNode() );

    osgDB::writeNodeFile( *( _root->getNode() ), fileName.toStdString() );

    return true;
}

////////////////////////////////////////////////////////////////////////////////

bool Document::readFile( QString fileName )
{
    newEmpty();

    QFile devFile( fileName );

    if ( devFile.open( QFile::ReadOnly | QFile::Text ) )
    {
        QDomDocument doc;

        doc.setContent( &devFile, false );

        QDomElement rootNode = doc.documentElement();

        if ( rootNode.tagName() == "gen_file" )
        {
            QDomElement rootGroupNode = rootNode.firstChildElement();

            if ( _root ) delete _root;
            _root = 0;

            if ( rootGroupNode.tagName() == "group" )
            {
                _root = new Group( &rootGroupNode );
                return true;
            }
            else if ( rootGroupNode.tagName() == "lod" )
            {
                _root = new LOD( &rootGroupNode );
                return true;
            }
            else if ( rootGroupNode.tagName() == "pat" )
            {
                _root = new PAT( &rootGroupNode );
                return true;
            }
            else if ( rootGroupNode.tagName() == "switch" )
            {
                _root = new Switch( &rootGroupNode );
                return true;
            }
        }

        devFile.close();
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////

bool Document::saveFile( QString fileName )
{
    QString fileTemp = fileName;

    if ( QFileInfo( fileTemp ).suffix() != QString( "xml" ) )
    {
        fileTemp += ".xml";
    }

    QFile devFile( fileTemp );

    if ( devFile.open( QFile::WriteOnly | QFile::Truncate | QFile::Text ) )
    {
        QTextStream out;
        out.setDevice( &devFile );
        out.setCodec("UTF-8");
        out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";

        QDomDocument doc( "gen_file" );

        doc.setContent( &devFile, false );

        QDomElement rootNode = doc.createElement( "gen_file" );
        doc.appendChild( rootNode );

        _root->save( &doc, &rootNode );

        out << doc.toString();

        devFile.close();

        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////

osg::Group* Document::getRootNode()
{
    if ( _root )
    {
        return dynamic_cast< osg::Group* >( _root->getNode() );
    }

    return 0;
}
