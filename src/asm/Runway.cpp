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

#include <asm/Runway.h>

#include <iostream>

#include <asm/Lights.h>

////////////////////////////////////////////////////////////////////////////////

const char Runway::tagName[] = "runway";

////////////////////////////////////////////////////////////////////////////////

Runway::Runway() :
    PAT(),

    _rals_lo ( RALS_NONE ),
    _rals_hi ( RALS_NONE ),
    _vgsi_lo ( VGSI_NONE ),
    _vgsi_hi ( VGSI_NONE ),
    _length ( 1000.0 ),
    _width ( 45.0 ),
    _vgsi_x_lo ( 300.0 ),
    _vgsi_x_hi ( 300.0 ),
    _rcls ( false ),
    _tdzl ( false )
{}

////////////////////////////////////////////////////////////////////////////////

Runway::Runway( QDomElement *xmlNode ) :
    PAT( xmlNode )
{
    setLength( xmlNode->attributeNode( "length" ).value().toFloat() );
    setWidth( xmlNode->attributeNode( "width" ).value().toFloat() );

    setRALS_Lo( (RALS)(xmlNode->attributeNode( "rals_lo" ).value().toInt()) );
    setRALS_Hi( (RALS)(xmlNode->attributeNode( "rals_hi" ).value().toInt()) );

    setVGSI_Lo( (VGSI)(xmlNode->attributeNode( "vgsi_lo" ).value().toInt()) );
    setVGSI_Hi( (VGSI)(xmlNode->attributeNode( "vgsi_hi" ).value().toInt()) );

    setVGSI_X_Lo( xmlNode->attributeNode( "vgsi_x_lo" ).value().toFloat() );
    setVGSI_X_Hi( xmlNode->attributeNode( "vgsi_x_hi" ).value().toFloat() );

    setRCLS( (bool)(xmlNode->attributeNode( "rcls" ).value().toInt()) );
    setTDZL( (bool)(xmlNode->attributeNode( "tdzl" ).value().toInt()) );

    // gaps
    QDomElement gapNode = xmlNode->firstChildElement( "gap" );

    while ( gapNode.tagName() == "gap" )
    {
        Gap gap;

        gap.from = gapNode.attributeNode( "from" ).value().toFloat();
        gap.to = gapNode.attributeNode( "to" ).value().toFloat();

        switch ( gapNode.attributeNode( "side" ).value().toInt() )
        {
            default:
            case Gap::Left:  gap.side = Gap::Left;  break;
            case Gap::Right: gap.side = Gap::Right; break;
            case Gap::Both:  gap.side = Gap::Both;  break;
        }

        _gaps.push_back( gap );

        gapNode = gapNode.nextSiblingElement( "gap" );
    }

    //std::cout << __FILE__ << "(" << __LINE__ << ") " << _node->getName() << " " << _gaps.size() << std::endl;

    removeAllRunwayChildren();
    create();
}

////////////////////////////////////////////////////////////////////////////////

Runway::~Runway() {}

////////////////////////////////////////////////////////////////////////////////

void Runway::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomElement node = doc->createElement( Runway::tagName );
    parentNode->appendChild( node );

    saveParameters( doc, &node );
}

////////////////////////////////////////////////////////////////////////////////

void Runway::setRALS_Lo( RALS rals_lo )
{
    removeAllRunwayChildren();
    _rals_lo = rals_lo;
    create();
}

////////////////////////////////////////////////////////////////////////////////

void Runway::setRALS_Hi( RALS rals_hi )
{
    removeAllRunwayChildren();
    _rals_hi = rals_hi;
    create();
}

////////////////////////////////////////////////////////////////////////////////

void Runway::setVGSI_Lo( VGSI vgsi_lo )
{
    removeAllRunwayChildren();
    _vgsi_lo = vgsi_lo;
    create();
}

////////////////////////////////////////////////////////////////////////////////

void Runway::setVGSI_Hi( VGSI vgsi_hi )
{
    removeAllRunwayChildren();
    _vgsi_hi = vgsi_hi;
    create();
}

////////////////////////////////////////////////////////////////////////////////

void Runway::setLength( float length )
{
    removeAllRunwayChildren();
    _length = length;
    create();
}

////////////////////////////////////////////////////////////////////////////////

void Runway::setWidth( float width )
{
    removeAllRunwayChildren();
    _width = width;
    create();
}

////////////////////////////////////////////////////////////////////////////////

void Runway::setVGSI_X_Lo( float vgsi_x_lo )
{
    removeAllRunwayChildren();
    _vgsi_x_lo = vgsi_x_lo;
    create();
}

////////////////////////////////////////////////////////////////////////////////

void Runway::setVGSI_X_Hi( float vgsi_x_hi )
{
    removeAllRunwayChildren();
    _vgsi_x_hi = vgsi_x_hi;
    create();
}

////////////////////////////////////////////////////////////////////////////////

void Runway::setGaps( Gaps gaps )
{
    removeAllRunwayChildren();
    //_gaps.clear();
    _gaps = gaps;
    create();
}

////////////////////////////////////////////////////////////////////////////////

void Runway::setRCLS( bool rcls )
{
    removeAllRunwayChildren();
    _rcls = rcls;
    create();
}

////////////////////////////////////////////////////////////////////////////////

void Runway::setTDZL( bool tdzl )
{
    removeAllRunwayChildren();
    _tdzl = tdzl;
    create();
}

////////////////////////////////////////////////////////////////////////////////

void Runway::create()
{
    _runway = new osg::Group();
    _pat->addChild( _runway.get() );

    _switchRALS_H = new osg::Switch();
    _switchTDZL_H = new osg::Switch();
    _switchVGSI_H = new osg::Switch();

    _switchRALS_L = new osg::Switch();
    _switchTDZL_L = new osg::Switch();
    _switchVGSI_L = new osg::Switch();

    _switchRCLS = new osg::Switch();
    _switchRELS = new osg::Switch();

    _switchRALS_H->setName( "RALS_H" );
    _switchTDZL_H->setName( "TDZL_H" );
    _switchVGSI_H->setName( "VGSI_H" );

    _switchRALS_L->setName( "RALS_L" );
    _switchTDZL_L->setName( "TDZL_L" );
    _switchVGSI_L->setName( "VGSI_L" );

    _switchRCLS->setName( "RCLS" );
    _switchRELS->setName( "RELS" );

    _runway->addChild( _switchRALS_H.get() );
    _runway->addChild( _switchTDZL_H.get() );
    _runway->addChild( _switchVGSI_H.get() );

    _runway->addChild( _switchRALS_L.get() );
    _runway->addChild( _switchTDZL_L.get() );
    _runway->addChild( _switchVGSI_L.get() );

    _runway->addChild( _switchRCLS.get() );
    _runway->addChild( _switchRELS.get() );

    float xdel = _length / 2.0f;

    switch ( _rals_lo )
    {
        default: /* do nothing */ break;
        case RALS_ALSF1: Lights::RALS::createALSF1 ( _switchRALS_L.get(), _width, -xdel ); break;
        case RALS_ALSF2: Lights::RALS::createALSF2 ( _switchRALS_L.get(), _width, -xdel ); break;
        case RALS_MALS:  Lights::RALS::createMALS  ( _switchRALS_L.get(), _width, -xdel ); break;
        case RALS_MALSF: Lights::RALS::createMALSF ( _switchRALS_L.get(), _width, -xdel ); break;
        case RALS_MALSR: Lights::RALS::createMALSR ( _switchRALS_L.get(), _width, -xdel ); break;
    }

    switch ( _rals_hi )
    {
        default: /* do nothing */ break;
        case RALS_ALSF1: Lights::RALS::createALSF1 ( _switchRALS_H.get(), _width,  xdel ); break;
        case RALS_ALSF2: Lights::RALS::createALSF2 ( _switchRALS_H.get(), _width,  xdel ); break;
        case RALS_MALS:  Lights::RALS::createMALS  ( _switchRALS_H.get(), _width,  xdel ); break;
        case RALS_MALSF: Lights::RALS::createMALSF ( _switchRALS_H.get(), _width,  xdel ); break;
        case RALS_MALSR: Lights::RALS::createMALSR ( _switchRALS_H.get(), _width,  xdel ); break;
    }

    float xdel_lo = -_length / 2.0f + _vgsi_x_lo;
    float xdel_hi =  _length / 2.0f - _vgsi_x_hi;

    float ydel = _width  / 2.0f + 15.0f;

    switch ( _vgsi_lo )
    {
        default: /* do nothing */ break;
        case VGSI_P4L: Lights::VGSI::createPAPI( _switchVGSI_L.get(), xdel_lo,  ydel ); break;
        case VGSI_P4R: Lights::VGSI::createPAPI( _switchVGSI_L.get(), xdel_lo, -ydel ); break;
        case VGSI_V4L: Lights::VGSI::createVASI( _switchVGSI_L.get(), xdel_lo,  ydel ); break;
        case VGSI_V4R: Lights::VGSI::createVASI( _switchVGSI_L.get(), xdel_lo, -ydel ); break;
        case VGSI_V6L: Lights::VGSI::createVASI3( _switchVGSI_L.get(), xdel_lo,  ydel ); break;
        case VGSI_V6R: Lights::VGSI::createVASI3( _switchVGSI_L.get(), xdel_lo, -ydel ); break;
    }

    switch ( _vgsi_hi )
    {
        default: /* do nothing */ break;
        case VGSI_P4L: Lights::VGSI::createPAPI( _switchVGSI_H.get(), xdel_hi,  ydel ); break;
        case VGSI_P4R: Lights::VGSI::createPAPI( _switchVGSI_H.get(), xdel_hi, -ydel ); break;
        case VGSI_V4L: Lights::VGSI::createVASI( _switchVGSI_H.get(), xdel_hi,  ydel ); break;
        case VGSI_V4R: Lights::VGSI::createVASI( _switchVGSI_H.get(), xdel_hi, -ydel ); break;
        case VGSI_V6L: Lights::VGSI::createVASI3( _switchVGSI_H.get(), xdel_hi,  ydel ); break;
        case VGSI_V6R: Lights::VGSI::createVASI3( _switchVGSI_H.get(), xdel_hi, -ydel ); break;
    }

    if ( _rcls )
    {
        Lights::RCLS::createRCLS( _switchRCLS.get(), _length );
    }

    if ( _tdzl )
    {
        Lights::TDZL::createTDZL( _switchTDZL_L.get(), _switchTDZL_H.get(), _length );
    }

    //std::cout << __FILE__ << "(" << __LINE__ << ") " << _node->getName() << " " << _gaps.size() << std::endl;
    Lights::RELS::createRELS( _switchRELS.get(), _width, _length, _gaps );
}

////////////////////////////////////////////////////////////////////////////////

void Runway::removeAllRunwayChildren()
{
    if ( _runway.valid() )
    {
        if ( _runway->getNumChildren() > 0 )
        {
            _runway->removeChild( 0, _runway->getNumChildren() );
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void Runway::saveParameters( QDomDocument *doc, QDomElement *xmlNode )
{
    ////////////////////////////////////
    PAT::saveParameters( doc, xmlNode );
    ////////////////////////////////////

    QDomAttr nodeLength = doc->createAttribute( "length" );
    QDomAttr nodeWidth  = doc->createAttribute( "width"  );

    QDomAttr nodeRALS_Lo = doc->createAttribute( "rals_lo" );
    QDomAttr nodeRALS_Hi = doc->createAttribute( "rals_hi" );

    QDomAttr nodeVGSI_Lo = doc->createAttribute( "vgsi_lo" );
    QDomAttr nodeVGSI_Hi = doc->createAttribute( "vgsi_hi" );

    QDomAttr nodeVGSI_X_Lo = doc->createAttribute( "vgsi_x_lo" );
    QDomAttr nodeVGSI_X_Hi = doc->createAttribute( "vgsi_x_hi" );

    QDomAttr nodeRCLS = doc->createAttribute( "rcls" );
    QDomAttr nodeTDZL = doc->createAttribute( "tdzl" );

    nodeLength.setValue( QString::number( _length ) );
    nodeWidth.setValue( QString::number( _width ) );

    nodeRALS_Lo.setValue( QString::number( _rals_lo ) );
    nodeRALS_Hi.setValue( QString::number( _rals_hi ) );

    nodeVGSI_Lo.setValue( QString::number( _vgsi_lo ) );
    nodeVGSI_Hi.setValue( QString::number( _vgsi_hi ) );

    nodeVGSI_X_Lo.setValue( QString::number( _vgsi_x_lo ) );
    nodeVGSI_X_Hi.setValue( QString::number( _vgsi_x_hi ) );

    nodeRCLS.setValue( QString::number( _rcls ? 1 : 0 ) );
    nodeTDZL.setValue( QString::number( _tdzl ? 1 : 0 ) );

    xmlNode->setAttributeNode( nodeLength );
    xmlNode->setAttributeNode( nodeWidth );

    xmlNode->setAttributeNode( nodeRALS_Lo );
    xmlNode->setAttributeNode( nodeRALS_Hi );

    xmlNode->setAttributeNode( nodeVGSI_Lo );
    xmlNode->setAttributeNode( nodeVGSI_Hi );

    xmlNode->setAttributeNode( nodeVGSI_X_Lo );
    xmlNode->setAttributeNode( nodeVGSI_X_Hi );

    xmlNode->setAttributeNode( nodeRCLS );
    xmlNode->setAttributeNode( nodeTDZL );

    for ( Gaps::iterator it = _gaps.begin(); it != _gaps.end(); ++it )
    {
        QDomElement gapNode = doc->createElement( "gap" );

        QDomAttr nodeFrom = doc->createAttribute( "from" );
        QDomAttr nodeTo   = doc->createAttribute( "to" );
        QDomAttr nodeSide = doc->createAttribute( "side" );

        nodeFrom .setValue( QString::number( (*it).from ) );
        nodeTo   .setValue( QString::number( (*it).to ) );
        nodeSide .setValue( QString::number( (*it).side ) );

        gapNode.setAttributeNode( nodeFrom );
        gapNode.setAttributeNode( nodeTo );
        gapNode.setAttributeNode( nodeSide );

        xmlNode->appendChild( gapNode );
    }
}

