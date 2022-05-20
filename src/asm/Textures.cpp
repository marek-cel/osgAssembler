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

#include <asm/Textures.h>

////////////////////////////////////////////////////////////////////////////////

osg::Texture2D* Textures::get( std::string textureFile, float maxAnisotropy )
{
    for ( unsigned int i = 0; i < getInstance()->_fileNames.size(); i++ )
    {
        if ( textureFile == getInstance()->_fileNames.at( i ) )
        {
            getInstance()->_textures.at( i )->setMaxAnisotropy( maxAnisotropy );
            return getInstance()->_textures.at( i );
        }
    }

    osg::ref_ptr<osg::Image> image = osgDB::readImageFile( textureFile );

    if ( image.valid() )
    {
        osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();
        texture->setImage( image.get() );

        texture->setWrap( osg::Texture2D::WRAP_S, osg::Texture2D::CLAMP_TO_EDGE );
        texture->setWrap( osg::Texture2D::WRAP_T, osg::Texture2D::CLAMP_TO_EDGE );
        texture->setWrap( osg::Texture2D::WRAP_R, osg::Texture2D::CLAMP_TO_EDGE );

        //texture->setNumMipmapLevels( 4 );
        texture->setMaxAnisotropy( maxAnisotropy );

        texture->setFilter( osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_NEAREST );
        texture->setFilter( osg::Texture::MAG_FILTER, osg::Texture::LINEAR );

        texture->setUnRefImageDataAfterApply( false );

        getInstance()->_textures.push_back( texture.get() );
        getInstance()->_fileNames.push_back( textureFile );

        return texture.get();
    }
    else
    {
        std::cerr << "ERROR! Cannot open texture file: " << textureFile << std::endl;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

void Textures::reset()
{
    getInstance()->_fileNames.clear();
    getInstance()->_textures.clear();
}

////////////////////////////////////////////////////////////////////////////////

Textures::Textures()
{
    _fileNames.clear();
    _textures.clear();
}

////////////////////////////////////////////////////////////////////////////////

Textures::~Textures() {}
