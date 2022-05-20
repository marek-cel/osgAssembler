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
#ifndef FLOLS_H
#define FLOLS_H

////////////////////////////////////////////////////////////////////////////////

#include <osgSim/LightPointNode>

#include "PAT.h"

////////////////////////////////////////////////////////////////////////////////

/** Fresnel Lens Optical Landing System - FLOLS */
class FLOLS : public PAT
{
public:

    static const char tagName[];

    static const float _sectorDegFrom;      ///< light point sector - foreward narrow from
    static const float _sectorDegUnto;      ///< light point sector - foreward narrow unto

    FLOLS();

    FLOLS( QDomElement *xmlNode );

    virtual ~FLOLS();

    virtual void save( QDomDocument *doc, QDomElement *parentNode );

protected:

    void create();

    void createIFLOLS( osgSim::LightPointNode *lightPointNode );

    void createIFLOLS_Datum( osgSim::LightPointNode *lightPointNode );
    void createIFLOLS_Ball( osgSim::LightPointNode *lightPointNode );
    void createIFLOLS_WaveOff( osgSim::LightPointNode *lightPointNode );
    void createIFLOLS_CutOff( osgSim::LightPointNode *lightPointNode );

    virtual void saveParameters( QDomDocument *doc, QDomElement *xmlNode );

};

////////////////////////////////////////////////////////////////////////////////

#endif // FLOLS_H
