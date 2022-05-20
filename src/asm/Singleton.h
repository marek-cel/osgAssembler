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
#ifndef SINGLETON_H
#define SINGLETON_H

////////////////////////////////////////////////////////////////////////////////

/** Singleton template. */
template < class TYPE >
class Singleton
{
public:

    static TYPE* getInstance()
    {
        if ( !_instance )
        {
            _instance = new TYPE();
        }

        return _instance;
    }

private:

    static TYPE *_instance;
};

////////////////////////////////////////////////////////////////////////////////

template < class TYPE > TYPE* Singleton< TYPE >::_instance = 0;

////////////////////////////////////////////////////////////////////////////////

#endif // SINGLETON_H
