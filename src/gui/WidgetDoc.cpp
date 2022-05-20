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

#include <iostream>

#include "WidgetDoc.h"
#include "ui_WidgetDoc.h"

////////////////////////////////////////////////////////////////////////////////

WidgetDoc::WidgetDoc( QWidget *parent ) :
    QWidget ( parent ),
    _ui ( new Ui::WidgetDoc ),

    _doc ( nullptr ),

    _dialogEditGroup    ( new DialogEditGroup    ( this ) ),
    _dialogEditLOD      ( new DialogEditLOD      ( this ) ),
    _dialogEditNodeFile ( new DialogEditNodeFile ( this ) ),
    _dialogEditPAT      ( new DialogEditPAT      ( this ) ),
    _dialogEditSwitch   ( new DialogEditSwitch   ( this ) ),
    _dialogEditSmoke    ( new DialogEditSmoke    ( this ) ),
    _dialogEditRotor    ( new DialogEditRotor    ( this ) ),
    _dialogEditFLOLS    ( new DialogEditFLOLS    ( this ) ),
    _dialogEditRunway   ( new DialogEditRunway   ( this ) ),
    _dialogEditWorld    ( new DialogEditWorld    ( this ) ),
    _dialogEditNozzle   ( new DialogEditNozzle   ( this ) ),

    _timedId ( 0 )
{
    _ui->setupUi( this );

    _doc = new Document();

    connect( _dialogEditGroup    , SIGNAL(accepted()), this, SLOT(dialogEditGroup_accepted())    );
    connect( _dialogEditLOD      , SIGNAL(accepted()), this, SLOT(dialogEditLOD_accepted())      );
    connect( _dialogEditNodeFile , SIGNAL(accepted()), this, SLOT(dialogEditNodeFile_accepted()) );
    connect( _dialogEditPAT      , SIGNAL(accepted()), this, SLOT(dialogEditPAT_accepted())      );
    connect( _dialogEditSwitch   , SIGNAL(accepted()), this, SLOT(dialogEditSwitch_accepted())   );
    connect( _dialogEditSmoke    , SIGNAL(accepted()), this, SLOT(dialogEditSmoke_accepted())    );
    connect( _dialogEditRotor    , SIGNAL(accepted()), this, SLOT(dialogEditRotor_accepted())    );
    connect( _dialogEditFLOLS    , SIGNAL(accepted()), this, SLOT(dialogEditFLOLS_accepted())    );
    connect( _dialogEditRunway   , SIGNAL(accepted()), this, SLOT(dialogEditRunway_accepted())   );
    connect( _dialogEditWorld    , SIGNAL(accepted()), this, SLOT(dialogEditWorld_accepted())    );
    connect( _dialogEditNozzle   , SIGNAL(accepted()), this, SLOT(dialogEditNozzle_accepted())   );

    _timedId = startTimer( 17 ); // ca. 60Hz
}

////////////////////////////////////////////////////////////////////////////////

WidgetDoc::~WidgetDoc()
{
    killTimer( _timedId );

    if ( _dialogEditGroup ) delete _dialogEditGroup;
    _dialogEditGroup = nullptr;

    if ( _dialogEditLOD ) delete _dialogEditLOD;
    _dialogEditLOD = nullptr;

    if ( _dialogEditNodeFile ) delete _dialogEditNodeFile;
    _dialogEditNodeFile = nullptr;

    if ( _dialogEditPAT ) delete _dialogEditPAT;
    _dialogEditPAT = nullptr;

    if ( _dialogEditSwitch ) delete _dialogEditSwitch;
    _dialogEditSwitch = nullptr;

    if ( _dialogEditSmoke ) delete _dialogEditSmoke;
    _dialogEditSmoke = nullptr;

    if ( _dialogEditRotor ) delete _dialogEditRotor;
    _dialogEditRotor = nullptr;

    if ( _dialogEditFLOLS ) delete _dialogEditFLOLS;
    _dialogEditFLOLS = nullptr;

    if ( _dialogEditRunway ) delete _dialogEditRunway;
    _dialogEditRunway = nullptr;

    if ( _dialogEditWorld ) delete _dialogEditWorld;
    _dialogEditWorld = nullptr;

    if ( _dialogEditNozzle ) delete _dialogEditNozzle;
    _dialogEditNozzle = nullptr;

    if ( _doc ) delete _doc;
    _doc = nullptr;

    if ( _ui ) delete _ui;
    _ui = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void WidgetDoc::newEmpty()
{
    _doc->newEmpty();

    updateGUI();
}

////////////////////////////////////////////////////////////////////////////////

bool WidgetDoc::readFile( QString file )
{
    bool result = _doc->readFile( file );

    if ( result ) updateGUI();

    return result;
}

////////////////////////////////////////////////////////////////////////////////

bool WidgetDoc::saveFile( QString file )
{
    return _doc->saveFile( file );
}

////////////////////////////////////////////////////////////////////////////////

bool WidgetDoc::exportAs( QString file )
{
    return _doc->exportAs( file );
}

////////////////////////////////////////////////////////////////////////////////

osg::Node* WidgetDoc::getRootNode()
{
    return _doc->getRootNode();
}

////////////////////////////////////////////////////////////////////////////////

osg::Node* WidgetDoc::getCurrentNode()
{
    return getNode( _ui->treeWidget->currentIndex() )->getNode();
}

////////////////////////////////////////////////////////////////////////////////

void WidgetDoc::timerEvent( QTimerEvent *event )
{
    /////////////////////////////
    QWidget::timerEvent( event );
    /////////////////////////////

    if ( _doc )
    {
        _doc->update();
    }
}

////////////////////////////////////////////////////////////////////////////////

void WidgetDoc::addTreeWidgetItem( Component *node, int index,
                                           QTreeWidgetItem *parent )
{
    if ( node )
    {
        QTreeWidgetItem *item = 0;

        if ( parent )
        {
            item = new QTreeWidgetItem( parent );
        }
        else
        {
            item = new QTreeWidgetItem( _ui->treeWidget );
        }

        item->setText( 0, node->getName().c_str() );

        Group *group = dynamic_cast<Group*>( node );

        if ( group )
        {
            for ( size_t i = 0; i < group->getNumChildren(); i++ )
            {
                Component *child = group->getChild( i );

                if ( child ) addTreeWidgetItem( child, index, item );
            }
        }

        if ( parent )
        {
            parent->insertChild( index, item );
            _ui->treeWidget->expandItem( parent );
        }
        else
        {
            _ui->treeWidget->insertTopLevelItem( 0, item );
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

Component* WidgetDoc::getNode( QModelIndex index )
{
    Component *node = _doc->getRootGroup();

    if ( node )
    {
        std::vector< int > indecies;
        indecies.clear();

        QModelIndex temp = index;

        while ( temp.parent().isValid() )
        {
            indecies.push_back( temp.row() );
            temp = temp.parent();
        }

        for ( int i = indecies.size() - 1; i >= 0; i-- )
        {
            Group *group = dynamic_cast<Group*>( node );

            if ( group )
            {
                node = group->getChild( indecies.at( i ) );
            }
            else
            {
                break;
            }
        }
    }

    return node;
}

////////////////////////////////////////////////////////////////////////////////

void WidgetDoc::removeNode( QModelIndex index )
{
    Component *node = _doc->getRootGroup();

    std::vector< int > indecies;
    indecies.clear();

    QModelIndex temp = index;

    while ( temp.parent().isValid() )
    {
        indecies.push_back( temp.row() );
        temp = temp.parent();
    }

    for ( int i = indecies.size() - 1; i >= 0; i-- )
    {
        Group *group = dynamic_cast<Group*>( node );

        if ( group )
        {
            if ( i == 0 )
            {
                group->removeChild( indecies.at( i ) );
                emit( changed() );
            }
            else
            {
                node = group->getChild( indecies.at( i ) );
            }
        }
        else
        {
            break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void WidgetDoc::addComponent()
{
    Component *component = 0;

    if ( _ui->comboBoxComponents->currentIndex() == 0 )
    {
        component = new NodeFile();
        component->setName( "File" );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 1 )
    {
        component = new Group();
        component->setName( "Group" );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 2 )
    {
        component = new LOD();
        component->setName( "LOD" );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 3 )
    {
        component = new PAT();
        component->setName( "PAT" );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 4 )
    {
        component = new Switch();
        component->setName( "Switch" );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 5 )
    {
        component = new Smoke();
        component->setName( "Smoke" );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 6 )
    {
        component = new Rotor();
        component->setName( "Rotor" );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 7 )
    {
        component = new FLOLS();
        component->setName( "FLOLS" );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 8 )
    {
        component = new Runway();
        component->setName( "Runway" );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 9 )
    {
        component = new World();
        component->setName( "World" );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 10 )
    {
        component = new Nozzle();
        component->setName( "Nozzle" );
    }


    if ( component )
    {
        Group *parent = dynamic_cast<Group*>( getNode( _ui->treeWidget->currentIndex() ) );

        if ( parent )
        {
            parent->addChild( component );
            emit( changed() );
        }
        else
        {
            Group *group = dynamic_cast<Group*>( component );

            if ( group )
            {
                _doc->setRootGroup( group );
                emit( changed() );
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void WidgetDoc::editComponent()
{
    Component *node = getNode( _ui->treeWidget->currentIndex() );

    NodeFile *file  = dynamic_cast< NodeFile * >( node );
    Group    *group = dynamic_cast< Group    * >( node );
    LOD      *lod   = dynamic_cast< LOD      * >( node );
    PAT      *pat   = dynamic_cast< PAT      * >( node );
    Switch   *sw    = dynamic_cast< Switch   * >( node );

    Smoke  *smoke  = dynamic_cast< Smoke  * >( node );
    Rotor  *rotor  = dynamic_cast< Rotor  * >( node );
    FLOLS  *flols  = dynamic_cast< FLOLS  * >( node );
    Runway *runway = dynamic_cast< Runway * >( node );
    World  *world  = dynamic_cast< World  * >( node );
    Nozzle *nozzle = dynamic_cast< Nozzle * >( node );



    if      ( file   ) _dialogEditNodeFile ->edit( file   );
    else if ( nozzle ) _dialogEditNozzle   ->edit( nozzle );
    else if ( world  ) _dialogEditWorld    ->edit( world  );
    else if ( runway ) _dialogEditRunway   ->edit( runway );
    else if ( flols  ) _dialogEditFLOLS    ->edit( flols  );
    else if ( rotor  ) _dialogEditRotor    ->edit( rotor  );
    else if ( smoke  ) _dialogEditSmoke    ->edit( smoke  );
    else if ( pat    ) _dialogEditPAT      ->edit( pat    );
    else if ( lod    ) _dialogEditLOD      ->edit( lod    );
    else if ( sw     ) _dialogEditSwitch   ->edit( sw     );
    else if ( group  ) _dialogEditGroup    ->edit( group  );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetDoc::updateGUI()
{
    _ui->treeWidget->setCurrentIndex( QModelIndex() );
    _ui->treeWidget->clear();

    addTreeWidgetItem( _doc->getRootGroup() );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetDoc::dialogEditGroup_accepted()
{
    _dialogEditGroup->save();
    updateGUI();
    emit( changed() );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetDoc::dialogEditLOD_accepted()
{
    _dialogEditLOD->save();
    updateGUI();
    emit( changed() );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetDoc::dialogEditNodeFile_accepted()
{
    _dialogEditNodeFile->save();
    updateGUI();
    emit( changed() );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetDoc::dialogEditPAT_accepted()
{
    _dialogEditPAT->save();
    updateGUI();
    emit( changed() );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetDoc::dialogEditSwitch_accepted()
{
    _dialogEditSwitch->save();
    updateGUI();
    emit( changed() );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetDoc::dialogEditSmoke_accepted()
{
    _dialogEditSmoke->save();
    updateGUI();
    emit( changed() );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetDoc::dialogEditRotor_accepted()
{
    _dialogEditRotor->save();
    updateGUI();
    emit( changed() );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetDoc::dialogEditFLOLS_accepted()
{
    _dialogEditFLOLS->save();
    updateGUI();
    emit( changed() );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetDoc::dialogEditRunway_accepted()
{
    _dialogEditRunway->save();
    updateGUI();
    emit( changed() );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetDoc::dialogEditWorld_accepted()
{
    _dialogEditWorld->save();
    updateGUI();
    emit( changed() );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetDoc::dialogEditNozzle_accepted()
{
    _dialogEditNozzle->save();
    updateGUI();
    emit( changed() );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetDoc::on_pushButtonAdd_clicked()
{
    addComponent();
    updateGUI();
}

////////////////////////////////////////////////////////////////////////////////

void WidgetDoc::on_pushButtonEdit_clicked()
{
    editComponent();
}

////////////////////////////////////////////////////////////////////////////////

void WidgetDoc::on_pushButtonRemove_clicked()
{
    removeNode( _ui->treeWidget->currentIndex() );
    updateGUI();
}

////////////////////////////////////////////////////////////////////////////////

void WidgetDoc::on_treeWidget_currentItemChanged( QTreeWidgetItem *current,
                                                  QTreeWidgetItem * )
{
    _ui->comboBoxComponents ->setEnabled( false );
    _ui->pushButtonAdd      ->setEnabled( false );
    _ui->pushButtonEdit     ->setEnabled( false );
    _ui->pushButtonRemove   ->setEnabled( false );

    Component *node = getNode( _ui->treeWidget->currentIndex() );
    Group *group = dynamic_cast<Group*>( node );

    if ( current && node  )
    {
        _ui->pushButtonEdit->setEnabled( true );

        if ( group )
        {
            _ui->comboBoxComponents ->setEnabled( true );
            _ui->pushButtonAdd      ->setEnabled( true );
            _ui->pushButtonRemove   ->setEnabled( true );
        }
        else
        {
            _ui->comboBoxComponents ->setEnabled( false );
            _ui->pushButtonAdd      ->setEnabled( false );
            _ui->pushButtonRemove   ->setEnabled( true );
        }
    }
    else if ( _ui->treeWidget->currentIndex().row() == -1 )
    {
        _ui->pushButtonEdit     ->setEnabled( true );
        _ui->comboBoxComponents ->setEnabled( true );
        _ui->pushButtonAdd      ->setEnabled( true );
        _ui->pushButtonRemove   ->setEnabled( true );
    }

    //std::cout << _ui->treeWidget->currentIndex().row() << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

void WidgetDoc::on_treeWidget_doubleClicked( const QModelIndex & )
{
    editComponent();
}
