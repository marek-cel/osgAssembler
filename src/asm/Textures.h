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
#ifndef TEXTURES_H
#define TEXTURES_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Texture2D>

#include "Singleton.h"

////////////////////////////////////////////////////////////////////////////////

/** Textures. */
class Textures : public Singleton< Textures >
{
    friend class Singleton< Textures >;

public:

    typedef std::vector< osg::ref_ptr<osg::Texture2D> > List;

    /** */
    static osg::Texture2D* get( std::string textureFile, float maxAnisotropy = 1.0f );

    static void reset();

    /** Destructor. */
    virtual ~Textures();

private:

    List _textures;
    std::vector< std::string > _fileNames;

    /**
     * You should use static function getInstance() due to get refernce
     * to Textures class instance.
     */
    Textures();

    /** Using this constructor is forbidden. */
    Textures( const Textures & ) {}
};

////////////////////////////////////////////////////////////////////////////////

#endif // TEXTURES_H
