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

#include <asm/ManipulatorOrbit.h>

////////////////////////////////////////////////////////////////////////////////

ManipulatorOrbit::ManipulatorOrbit() :
    osgGA::NodeTrackerManipulator()
{
    setTrackerMode( NODE_CENTER );

    setWheelZoomFactor( -getWheelZoomFactor() );
}

////////////////////////////////////////////////////////////////////////////////

bool ManipulatorOrbit::handleFrame( const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &us )
{
    ///////////////////////////////////////////////////////////////////
    bool result = osgGA::NodeTrackerManipulator::handleFrame( ea, us );
    ///////////////////////////////////////////////////////////////////

    boundDistance();

    return result;
}

////////////////////////////////////////////////////////////////////////////////

bool ManipulatorOrbit::performMovementRightMouseButton( const double /*eventTimeDelta*/,
                                                        const double /*dx*/,
                                                        const double /*dy*/ )
{
    return true;
}

////////////////////////////////////////////////////////////////////////////////

void ManipulatorOrbit::boundDistance()
{
    if ( getDistance() > 1.0e8 )
    {
        setDistance( 1.0e8 );
    }
    else if ( getDistance() < 0.1 )
    {
        setDistance( 0.1 );
    }
}
