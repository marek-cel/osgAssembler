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

#include <gui/DialogEditRunway.h>
#include <ui_DialogEditRunway.h>

#include <QFileDialog>

#include <gui/DialogEditGap.h>

////////////////////////////////////////////////////////////////////////////////

DialogEditRunway::DialogEditRunway(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::DialogEditRunway),
    _runway( nullptr )
{
    _ui->setupUi( this );
}

////////////////////////////////////////////////////////////////////////////////

DialogEditRunway::~DialogEditRunway()
{
    if ( _ui ) delete _ui;
    _ui = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditRunway::edit( Runway *runway )
{
    _runway = runway;

    _gaps.clear();
    _gaps = _runway->getGaps();

    _ui->lineEditName->setText( _runway->getName().c_str() );

    _ui->checkBoxDepthSortedBin->setChecked( _runway->getDepthSortedBinState() );
    _ui->spinBoxDepthSortedBin->setValue( _runway->getDepthSortedBinValue() );

    _ui->spinBoxPositionX->setValue( _runway->getPx() );
    _ui->spinBoxPositionY->setValue( _runway->getPy() );
    _ui->spinBoxPositionZ->setValue( _runway->getPz() );

    _ui->spinBoxAttitudeX->setValue( _runway->getAx() );
    _ui->spinBoxAttitudeY->setValue( _runway->getAy() );
    _ui->spinBoxAttitudeZ->setValue( _runway->getAz() );

    if ( _runway->getConvention() == PAT::XYZ )
    {
        _ui->radioButtonXYZ->setChecked( true );
    }
    else
    {
        _ui->radioButtonZYX->setChecked( true );
    }

    ///////////

    _ui->spinBoxLength->setValue( _runway->getLength() );
    _ui->spinBoxWidth->setValue( _runway->getWidth() );

    _ui->comboBoxRALS_Lo->setCurrentIndex( _runway->getRALS_Lo() );
    _ui->comboBoxRALS_Hi->setCurrentIndex( _runway->getRALS_Hi() );

    _ui->comboBoxVGSI_Lo->setCurrentIndex( _runway->getVGSI_Lo() );
    _ui->comboBoxVGSI_Hi->setCurrentIndex( _runway->getVGSI_Hi() );

    _ui->spinBoxVGSI_X_Lo->setValue( _runway->getVGSI_X_Lo() );
    _ui->spinBoxVGSI_X_Hi->setValue( _runway->getVGSI_X_Hi() );

    _ui->checkBoxRCLS->setChecked( _runway->getRCLS() );
    _ui->checkBoxTDZL->setChecked( _runway->getTDZL() );

    updateListWidgetGaps();

    ///////////

    show();
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditRunway::save()
{
    _runway->setName( _ui->lineEditName->text().toLatin1().data() );

    _runway->setDepthSortedBinValue( _ui->spinBoxDepthSortedBin->value() );
    _runway->setDepthSortedBinState( _ui->checkBoxDepthSortedBin->isChecked() );

    double px = _ui->spinBoxPositionX->value();
    double py = _ui->spinBoxPositionY->value();
    double pz = _ui->spinBoxPositionZ->value();

    double ax = _ui->spinBoxAttitudeX->value();
    double ay = _ui->spinBoxAttitudeY->value();
    double az = _ui->spinBoxAttitudeZ->value();

    _runway->setPx( px );
    _runway->setPy( py );
    _runway->setPz( pz );

    _runway->setAx( ax );
    _runway->setAy( ay );
    _runway->setAz( az );

    PAT::Convention convention = PAT::XYZ;

    if ( _ui->radioButtonZYX->isChecked() )
    {
        convention = PAT::ZYX;
    }

    _runway->setConvention( convention );

    ///////////

    _runway->setLength( _ui->spinBoxLength->value() );
    _runway->setWidth( _ui->spinBoxWidth->value() );

    _runway->setRALS_Lo( getRALS( _ui->comboBoxRALS_Lo->currentIndex() ) );
    _runway->setRALS_Hi( getRALS( _ui->comboBoxRALS_Hi->currentIndex() ) );

    _runway->setVGSI_Lo( getVGSI( _ui->comboBoxVGSI_Lo->currentIndex() ) );
    _runway->setVGSI_Hi( getVGSI( _ui->comboBoxVGSI_Hi->currentIndex() ) );

    _runway->setVGSI_X_Lo( _ui->spinBoxVGSI_X_Lo->value() );
    _runway->setVGSI_X_Hi( _ui->spinBoxVGSI_X_Hi->value() );

    _runway->setRCLS( _ui->checkBoxRCLS->isChecked() );
    _runway->setTDZL( _ui->checkBoxTDZL->isChecked() );

    _runway->setGaps( _gaps );
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditRunway::on_checkBoxDepthSortedBin_toggled( bool checked )
{
    _ui->spinBoxDepthSortedBin->setEnabled( checked );
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditRunway::on_pushButtonGapAdd_clicked()
{
    Gap gap;

    gap.from = 0.0;
    gap.to = 0.0;
    gap.side = Gap::Left;

    _gaps.push_back( gap );

    updateListWidgetGaps();
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditRunway::on_pushButtonGapEdit_clicked()
{
    editGap();
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditRunway::on_pushButtonGapRemove_clicked()
{
    if ( _ui->listWidgetGaps->currentRow() > -1
      && _ui->listWidgetGaps->currentRow() < _gaps.size() )
    {
        _gaps.erase( _gaps.begin() + _ui->listWidgetGaps->currentRow() );
    }

    updateListWidgetGaps();
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditRunway::on_listWidgetGaps_doubleClicked( const QModelIndex & )
{
    editGap();
}

////////////////////////////////////////////////////////////////////////////////

Runway::RALS DialogEditRunway::getRALS( int index )
{
    switch ( index )
    {
        default:
        case 0: return Runway::RALS_NONE;  break;
        case 1: return Runway::RALS_ALSF1; break;
        case 2: return Runway::RALS_ALSF2; break;
        case 3: return Runway::RALS_MALS;  break;
        case 4: return Runway::RALS_MALSF; break;
        case 5: return Runway::RALS_MALSR; break;
    }
}

////////////////////////////////////////////////////////////////////////////////

Runway::VGSI DialogEditRunway::getVGSI( int index )
{
    switch ( index )
    {
        default:
        case 0: return Runway::VGSI_NONE; break;
        case 1: return Runway::VGSI_P4L;  break;
        case 2: return Runway::VGSI_P4R;  break;
        case 3: return Runway::VGSI_V4L;  break;
        case 4: return Runway::VGSI_V4R;  break;
        case 5: return Runway::VGSI_V6L;  break;
        case 6: return Runway::VGSI_V6R;  break;
    }
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditRunway::editGap()
{
    if ( _ui->listWidgetGaps->currentRow() > -1
      && _ui->listWidgetGaps->currentRow() < _gaps.size() )
    {
        Gap gap = _gaps.at( _ui->listWidgetGaps->currentRow() );

        gap = DialogEditGap::edit( gap );

        _gaps[ _ui->listWidgetGaps->currentRow() ] = gap;
    }

    updateListWidgetGaps();
}

////////////////////////////////////////////////////////////////////////////////

void DialogEditRunway::updateListWidgetGaps()
{
    _ui->listWidgetGaps->clear();

    for ( int i = 0; i < _gaps.size(); i++ )
    {
        QString text = "Gap #" + QString::number( i + 1 ) + ": ";

        text += " from " + QString::number( _gaps.at( i ).from );
        text += " to "   + QString::number( _gaps.at( i ).to   );
        text += " on ";

        switch ( _gaps.at( i ).side )
        {
            case Gap::Left:  text += "LEFT";  break;
            case Gap::Right: text += "RIGHT"; break;
            case Gap::Both:  text += "BOTH";  break;
        }

        _ui->listWidgetGaps->addItem( new QListWidgetItem( text, _ui->listWidgetGaps ) );
    }
}
