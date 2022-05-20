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
#ifndef WIDGETDOC_H
#define WIDGETDOC_H

////////////////////////////////////////////////////////////////////////////////

#include <QTreeWidgetItem>
#include <QWidget>

#include <asm/Document.h>

#include "DialogEditGroup.h"
#include "DialogEditLOD.h"
#include "DialogEditNodeFile.h"
#include "DialogEditPAT.h"
#include "DialogEditSwitch.h"

#include "DialogEditSmoke.h"
#include "DialogEditRotor.h"
#include "DialogEditFLOLS.h"
#include "DialogEditRunway.h"
#include "DialogEditWorld.h"
#include "DialogEditNozzle.h"

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class WidgetDoc;
}

////////////////////////////////////////////////////////////////////////////////

class WidgetDoc : public QWidget
{
    Q_OBJECT

public:

    explicit WidgetDoc( QWidget *parent = nullptr );

    ~WidgetDoc();

    void newEmpty();

    bool readFile( QString file );
    bool saveFile( QString file );
    bool exportAs( QString file );

    osg::Node* getRootNode();

    osg::Node* getCurrentNode();

signals:

    void changed();

protected:

    void timerEvent( QTimerEvent *event );

private:

    Ui::WidgetDoc *_ui;

    Document *_doc;

    DialogEditGroup    *_dialogEditGroup;      ///<
    DialogEditLOD      *_dialogEditLOD;        ///<
    DialogEditNodeFile *_dialogEditNodeFile;   ///<
    DialogEditPAT      *_dialogEditPAT;        ///<
    DialogEditSwitch   *_dialogEditSwitch;     ///<

    DialogEditSmoke    *_dialogEditSmoke;      ///<
    DialogEditRotor    *_dialogEditRotor;      ///<
    DialogEditFLOLS    *_dialogEditFLOLS;      ///<
    DialogEditRunway   *_dialogEditRunway;     ///<
    DialogEditWorld    *_dialogEditWorld;      ///<
    DialogEditNozzle   *_dialogEditNozzle;     ///<

    int _timedId;

    void addTreeWidgetItem( Component *node, int index = 0,
                            QTreeWidgetItem *parent = 0 );

    Component* getNode( QModelIndex index );
    void removeNode( QModelIndex index );

    void addComponent();
    void editComponent();

    void updateGUI();

private slots:

    void dialogEditGroup_accepted();
    void dialogEditLOD_accepted();
    void dialogEditNodeFile_accepted();
    void dialogEditPAT_accepted();
    void dialogEditSwitch_accepted();
    void dialogEditSmoke_accepted();
    void dialogEditRotor_accepted();
    void dialogEditFLOLS_accepted();
    void dialogEditRunway_accepted();
    void dialogEditWorld_accepted();
    void dialogEditNozzle_accepted();


    void on_pushButtonAdd_clicked();
    void on_pushButtonEdit_clicked();
    void on_pushButtonRemove_clicked();

    void on_treeWidget_currentItemChanged( QTreeWidgetItem *current,
                                           QTreeWidgetItem * );

    void on_treeWidget_doubleClicked( const QModelIndex & );
};

////////////////////////////////////////////////////////////////////////////////

#endif // WIDGETDOC_H
