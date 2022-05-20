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
#ifndef SCENEROOT_H
#define SCENEROOT_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Group>
#include <osg/Light>
#include <osg/Switch>

////////////////////////////////////////////////////////////////////////////////

/** */
class SceneRoot
{
public:

    /** */
    SceneRoot();

    /** */
    virtual ~SceneRoot();

    /** Returns root node. */
    inline osg::Node* getRootNode() { return _rootNode.get(); }

    /** Returns root node. */
    inline osg::Group* getSceneRoot() { return _sceneRoot.get(); }

    /** */
    void setRootNode( osg::Node *rootNode );

    void setLightingPositionX( double x );
    void setLightingPositionY( double y );
    void setLightingPositionZ( double z );

    void setLightingEnabled( bool enabled );

private:

    osg::ref_ptr<osg::Group> _sceneRoot;

    osg::ref_ptr<osg::Node> _rootNode;

    osg::ref_ptr<osg::Light> _light;
    osg::ref_ptr<osg::Switch> _lightSwitch;
    osg::Vec4d _lightPos;

    bool _lightEnabled { true };

    void createSceneLight();
};

////////////////////////////////////////////////////////////////////////////////

#endif // SCENEROOT_H
