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

#include <osg/Vec3>

#include <asm/Directions.h>

////////////////////////////////////////////////////////////////////////////////

const osg::Quat Directions::North = osg::Quat( osg::DegreesToRadians(   0.0f ), osg::Vec3( 0.0f, 0.0f, 1.0f ) );
const osg::Quat Directions::East  = osg::Quat( osg::DegreesToRadians(  90.0f ), osg::Vec3( 0.0f, 0.0f, 1.0f ) );
const osg::Quat Directions::South = osg::Quat( osg::DegreesToRadians( 180.0f ), osg::Vec3( 0.0f, 0.0f, 1.0f ) );
const osg::Quat Directions::West  = osg::Quat( osg::DegreesToRadians( 270.0f ), osg::Vec3( 0.0f, 0.0f, 1.0f ) );
