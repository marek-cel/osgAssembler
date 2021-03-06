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

#include <asm/WGS84.h>

////////////////////////////////////////////////////////////////////////////////

const double WGS84::_a  = osg::WGS_84_RADIUS_EQUATOR;
const double WGS84::_b  = osg::WGS_84_RADIUS_POLAR;
const double WGS84::_e2 = ( WGS84::_a*WGS84::_a - WGS84::_b*WGS84::_b ) / ( WGS84::_a*WGS84::_a );
const double WGS84::_e  = sqrt( WGS84::_e2 );

const osg::EllipsoidModel WGS84::_em = osg::EllipsoidModel();

const osg::Quat WGS84::_enu2ned = osg::Matrixd( 0.0,  1.0,  0.0,  0.0,
                                                1.0,  0.0,  0.0,  0.0,
                                                0.0,  0.0, -1.0,  0.0,
                                                0.0,  0.0,  0.0,  1.0 ).getRotate();

////////////////////////////////////////////////////////////////////////////////

double WGS84::getRadiusEquatorial()
{
    return _a;
}

////////////////////////////////////////////////////////////////////////////////

double WGS84::getRadiusPolar()
{
    return _b;
}

////////////////////////////////////////////////////////////////////////////////

osg::Vec3d WGS84::geo2wgs( double lat, double lon, double alt )
{
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    _em.convertLatLongHeightToXYZ( lat, lon, alt, x, y, z );

    return osg::Vec3d( x, y, z );
}

////////////////////////////////////////////////////////////////////////////////

void WGS84::wgs2geo( const osg::Vec3d &r_wgs, double &lat, double &lon, double &alt )
{
    _em.convertXYZToLatLongHeight( r_wgs.x(), r_wgs.y(), r_wgs.z(),
                                   lat, lon, alt );
}

////////////////////////////////////////////////////////////////////////////////

osg::Vec3d WGS84::ned2wgs( const osg::Vec3d &r0_wgs, const osg::Vec3d &v_ned )
{
    double lat = 0.0;
    double lon = 0.0;
    double alt = 0.0;

    wgs2geo( r0_wgs, lat, lon, alt );

    double cosLat = cos( lat );
    double cosLon = cos( lon );
    double sinLat = sin( lat );
    double sinLon = sin( lon );

    osg::Matrix mat_ned2wgs;

    // WGS to NED
    mat_ned2wgs(0,0) = -cosLon * sinLat;
    mat_ned2wgs(0,1) = -sinLon * sinLat;
    mat_ned2wgs(0,2) =  cosLat;
    mat_ned2wgs(0,3) = 0.0;

    mat_ned2wgs(1,0) = -sinLon;
    mat_ned2wgs(1,1) =  cosLon;
    mat_ned2wgs(1,2) =  0.0;
    mat_ned2wgs(1,3) = 0.0;

    mat_ned2wgs(2,0) = -cosLon * cosLat;
    mat_ned2wgs(2,1) = -sinLon * cosLat;
    mat_ned2wgs(2,2) = -sinLat;
    mat_ned2wgs(2,3) = 0.0;

    mat_ned2wgs(3,0) = 0.0;
    mat_ned2wgs(3,1) = 0.0;
    mat_ned2wgs(3,2) = 0.0;
    mat_ned2wgs(3,3) = 1.0;

    return mat_ned2wgs.getRotate() * v_ned;
}

////////////////////////////////////////////////////////////////////////////////

osg::Vec3d WGS84::wgs2ned( const osg::Vec3d &r0_wgs, const osg::Vec3d &v_wgs )
{
    double lat = 0.0;
    double lon = 0.0;
    double alt = 0.0;

    wgs2geo( r0_wgs, lat, lon, alt );

    double cosLat = cos( lat );
    double cosLon = cos( lon );
    double sinLat = sin( lat );
    double sinLon = sin( lon );

    osg::Matrix mat_wgs2ned;

    mat_wgs2ned(0,0) = -cosLon*sinLat;
    mat_wgs2ned(0,1) = -sinLon;
    mat_wgs2ned(0,2) = -cosLon*cosLat;
    mat_wgs2ned(0,3) = 0.0;

    mat_wgs2ned(1,0) = -sinLon*sinLat;
    mat_wgs2ned(1,1) =  cosLon;
    mat_wgs2ned(1,2) = -sinLon*cosLat;
    mat_wgs2ned(1,3) = 0.0;

    mat_wgs2ned(2,0) =  cosLat;
    mat_wgs2ned(2,1) =  0.0;
    mat_wgs2ned(2,2) = -sinLat;
    mat_wgs2ned(2,3) = 0.0;

    mat_wgs2ned(3,0) = 0.0;
    mat_wgs2ned(3,1) = 0.0;
    mat_wgs2ned(3,2) = 0.0;
    mat_wgs2ned(3,3) = 1.0;

    return mat_wgs2ned.getRotate() * v_wgs;
}

////////////////////////////////////////////////////////////////////////////////

osg::Vec3d WGS84::r_ned2wgs( const osg::Vec3d &r0_wgs, const osg::Vec3d &r_ned )
{
    return r0_wgs + ned2wgs( r0_wgs, r_ned );
}

////////////////////////////////////////////////////////////////////////////////

osg::Vec3d WGS84::r_wgs2ned( const osg::Vec3d &r0_wgs, const osg::Vec3d &r_wgs )
{
    return wgs2ned( r0_wgs, r_wgs - r0_wgs );
}

////////////////////////////////////////////////////////////////////////////////

WGS84::WGS84()
{
    set( 0.0, 0.0, 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

WGS84::WGS84( double lat, double lon, double alt )
{
    set( lat, lon, alt );
}

////////////////////////////////////////////////////////////////////////////////

WGS84::WGS84( const osg::Vec3d &position )
{
    set( position );
}

////////////////////////////////////////////////////////////////////////////////

WGS84::~WGS84() {}

////////////////////////////////////////////////////////////////////////////////

void WGS84::set( double lat, double lon, double alt )
{
    _lat = lat;
    _lon = lon;
    _alt = alt;

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    osg::Matrixd localToWorld;

    _em.convertLatLongHeightToXYZ( lat, lon, alt, x, y, z );
    _em.computeLocalToWorldTransformFromXYZ( x, y, z, localToWorld );

    osg::Quat wgs2enu = localToWorld.getRotate();

    _position = osg::Vec3( x, y, z );
    _attitude = _enu2ned * wgs2enu;
}

////////////////////////////////////////////////////////////////////////////////

void WGS84::set( const osg::Vec3d &position )
{
    double lat = 0.0;
    double lon = 0.0;
    double alt = 0.0;

    osg::Matrixd localToWorld;

    _em.convertXYZToLatLongHeight( position.x(), position.y(), position.z(),
                                   lat, lon, alt );
    _em.computeLocalToWorldTransformFromXYZ( position.x(), position.y(), position.z(),
                                             localToWorld );

    _lat = lat;
    _lon = lon;
    _alt = alt;

    osg::Quat wgs2enu = localToWorld.getRotate();

    _position = position;
    _attitude = _enu2ned * wgs2enu;
}
