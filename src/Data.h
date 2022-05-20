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
#ifndef DATA_H
#define DATA_H

////////////////////////////////////////////////////////////////////////////////

#define MAX_BLADES 11

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Simulation data access class.
 */
class Data
{
public:

    struct Blade
    {
        double beta;                ///< [rad] flapping angle
        double theta;               ///< [rad] feathering angle
    };

    /** Rotor data. */
    struct Rotor
    {
        double azimuth;             ///< [rad] main rotor rotation angle (azimuth)
        double coningAngle;         ///< [rad] main rotor coning angle
        double diskRoll;            ///< [rad] main rotor disk roll angle
        double diskPitch;           ///< [rad] main rotor disk pitch angle
        double collective;          ///< [rad] main rotor collective pitch angle
        double cyclicLon;           ///< [rad] main rotor longitudinal cyclic pitch angle
        double cyclicLat;           ///< [rad] main rotor lateral cyclic pitch angle
    };

    /** Data struct. */
    struct DataBuf
    {
        Blade blade[ MAX_BLADES ];  ///<
        Rotor rotor;                ///<
    };

private:

    /**
     * You should use static function instance() due to get refernce
     * to Data class instance.
     */
    Data() {}

    /** Using this constructor is forbidden. */
    Data( const Data & ) {}

public:

    /** Returns pointer to the common data object. */
    static inline DataBuf* get() { return &_data; }

    /** Destructor. */
    virtual ~Data() {}

private:

    static DataBuf _data;   ///< data
};

////////////////////////////////////////////////////////////////////////////////

#endif // DATA_H
