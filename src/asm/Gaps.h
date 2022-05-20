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
#ifndef GAPS_H
#define GAPS_H

////////////////////////////////////////////////////////////////////////////////

#include <QVector>

////////////////////////////////////////////////////////////////////////////////

struct Gap
{
    enum Side
    {
        Left = 0,
        Right,
        Both
    };

    Side side;

    double from;
    double to;
};

typedef QVector< Gap > Gaps;

////////////////////////////////////////////////////////////////////////////////

#endif // GAPS_H
