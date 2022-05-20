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
#ifndef DIRECTIONS_H
#define DIRECTIONS_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Quat>

////////////////////////////////////////////////////////////////////////////////

class Directions
{
public:

    static const osg::Quat North;       ///< front to North
    static const osg::Quat East;        ///< front to East
    static const osg::Quat South;       ///< front to South
    static const osg::Quat West;        ///< front to West
};

////////////////////////////////////////////////////////////////////////////////

#endif // DIRECTIONS_H
