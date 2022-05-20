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

#include <osgParticle/ModularEmitter>
#include <osgParticle/ParticleSystemUpdater>

#include <asm/Smoke.h>

////////////////////////////////////////////////////////////////////////////////

const char Smoke::tagName[] = "smoke";

////////////////////////////////////////////////////////////////////////////////

Smoke::Smoke() :
    PAT()
{
    createSmoke();
}

////////////////////////////////////////////////////////////////////////////////

Smoke::Smoke( QDomElement *xmlNode ) :
    PAT( xmlNode )
{
    createSmoke();
}

////////////////////////////////////////////////////////////////////////////////

Smoke::~Smoke()
{
    removeAllChildren();
}

////////////////////////////////////////////////////////////////////////////////

void Smoke::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomElement node = doc->createElement( Smoke::tagName );
    parentNode->appendChild( node );

    saveParameters( doc, &node );
}

////////////////////////////////////////////////////////////////////////////////

void Smoke::updatePositionAndAttitude()
{
    /////////////////////////////////
    //PAT::updatePositionAndAttitude();
    /////////////////////////////////

    _smoke->setPosition( osg::Vec3d( _px, _py, _pz ) );
}

////////////////////////////////////////////////////////////////////////////////

void Smoke::createSmoke()
{
    osg::ref_ptr<osgParticle::ParticleSystemUpdater> updater = new osgParticle::ParticleSystemUpdater();
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();

    osg::ref_ptr<osgParticle::ParticleSystem> flame = createFlame( _pat.get() );
    updater->addParticleSystem( flame );
    geode->addDrawable( flame );

    _pat->addChild( updater.get() );
    _pat->addChild( geode.get() );

    /////////////////////

//    m_smoke = new osgParticle::SmokeEffect();
//    m_smoke->setTextureFileName( "data/textures/smoke.rgb" );
//    m_smoke->setScale( 10.0f );
//    m_smoke->setIntensity( 10.0f );
//    m_smoke->setEmitterDuration( 1000.0 );

//    m_pat->addChild( m_smoke.get() );
}

////////////////////////////////////////////////////////////////////////////////

osgParticle::ParticleSystem* Smoke::createFlame( osg::Group* parent )
{
    osg::ref_ptr<osgParticle::ParticleSystem> ps = new osgParticle::ParticleSystem();
    ps->getDefaultParticleTemplate().setLifeTime( 60.0f );
    ps->getDefaultParticleTemplate().setShape( osgParticle::Particle::QUAD );
    ps->getDefaultParticleTemplate().setSizeRange( osgParticle::rangef(10.0f, 150.0f) );
    ps->getDefaultParticleTemplate().setAlphaRange( osgParticle::rangef(1.0f, 0.0f) );
    ps->getDefaultParticleTemplate().setColorRange(
        osgParticle::rangev4(osg::Vec4(1.0f,1.0f,1.0f,1.0f), osg::Vec4(1.0f,1.0f,1.0f,0.0f)) );
    ps->setDefaultAttributes( "data/textures/smoke.rgb", false, false );

    osg::ref_ptr<osgParticle::RandomRateCounter> rrc = new osgParticle::RandomRateCounter();
    rrc->setRateRange( 1, 1 );

    osg::ref_ptr<osgParticle::RadialShooter> shooter = new osgParticle::RadialShooter();
    shooter->setThetaRange( -osg::PI_4*0.5, osg::PI_4*0.5 );
    shooter->setPhiRange( -osg::PI_4*0.5, osg::PI_4*0.5 );
    shooter->setInitialSpeedRange( 4.0f, 8.0f );

    osg::ref_ptr<osgParticle::ModularEmitter> emitter = new osgParticle::ModularEmitter();
    emitter->setParticleSystem( ps.get() );
    emitter->setCounter( rrc.get() );
    emitter->setShooter( shooter.get() );

    parent->addChild( emitter.get() );

    return ps.get();
}

////////////////////////////////////////////////////////////////////////////////

void Smoke::saveParameters( QDomDocument *doc, QDomElement *xmlNode )
{
    ////////////////////////////////////
    PAT::saveParameters( doc, xmlNode );
    ////////////////////////////////////

//    QDomAttr nodePx = doc->createAttribute( "px" );
//    QDomAttr nodePy = doc->createAttribute( "py" );
//    QDomAttr nodePz = doc->createAttribute( "pz" );

//    nodePx.setValue( QString::number( getPx() ) );
//    nodePy.setValue( QString::number( getPy() ) );
//    nodePz.setValue( QString::number( getPz() ) );

//    xmlNode->setAttributeNode( nodePx );
//    xmlNode->setAttributeNode( nodePy );
//    xmlNode->setAttributeNode( nodePz );
}
