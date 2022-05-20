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
#ifndef MODELS_H
#define MODELS_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Node>

#include "Singleton.h"

////////////////////////////////////////////////////////////////////////////////

/** 3D models. */
class Models : public Singleton< Models >
{
    friend class Singleton< Models >;

public:

    typedef std::vector< osg::ref_ptr<osg::Node> > List;

    /** */
    static osg::Node* get( std::string objectFile );

    static void reset();

    /** Destructor. */
    virtual ~Models();

private:

    List _objects;
    std::vector< std::string > _fileNames;

    /**
     * You should use static function getInstance() due to get refernce
     * to Models class instance.
     */
    Models();

    /** Using this constructor is forbidden. */
    Models( const Models & ) {}
};

////////////////////////////////////////////////////////////////////////////////

#endif // MODELS_H
