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

#include <osgDB/ReadFile>

#include <asm/Models.h>

////////////////////////////////////////////////////////////////////////////////

osg::Node* Models::get( std::string objectFile )
{
    for ( unsigned int i = 0; i < getInstance()->_fileNames.size(); i++ )
    {
        if ( objectFile == getInstance()->_fileNames.at( i ) )
        {
            return getInstance()->_objects.at( i );
        }
    }

    osg::ref_ptr<osg::Node> object = osgDB::readNodeFile( objectFile );

    if ( object.valid() )
    {
        getInstance()->_objects.push_back( object.get() );
        getInstance()->_fileNames.push_back( objectFile );

        return object.get();
    }
    else
    {
        std::cerr << "ERROR! Cannot open object file: " << objectFile << std::endl;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

void Models::reset()
{
    getInstance()->_fileNames.clear();
    getInstance()->_objects.clear();
}

////////////////////////////////////////////////////////////////////////////////

Models::Models()
{
    _fileNames.clear();
    _objects.clear();
}

////////////////////////////////////////////////////////////////////////////////

Models::~Models() {}
