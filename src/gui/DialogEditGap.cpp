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

#include <gui/DialogEditGap.h>
#include <ui_DialogEditGap.h>

////////////////////////////////////////////////////////////////////////////////

Gap DialogEditGap::edit( Gap gap )
{
    DialogEditGap *dialog = new DialogEditGap();

    dialog->_ui->doubleSpinBoxFrom->setValue( gap.from );
    dialog->_ui->doubleSpinBoxTo->setValue( gap.to );
    dialog->_ui->comboBoxSide->setCurrentIndex( gap.side );

    int result = dialog->exec();

    if ( result == QDialog::Accepted )
    {
        gap.from = dialog->_ui->doubleSpinBoxFrom ->value();
        gap.to   = dialog->_ui->doubleSpinBoxTo   ->value();

        switch ( dialog->_ui->comboBoxSide->currentIndex() )
        {
            case Gap::Left:  gap.side = Gap::Left;  break;
            case Gap::Right: gap.side = Gap::Right; break;
            case Gap::Both:  gap.side = Gap::Both;  break;
        }
    }

    if ( dialog ) delete dialog;
    dialog = nullptr;

    return gap;
}

////////////////////////////////////////////////////////////////////////////////

DialogEditGap::DialogEditGap(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::DialogEditGap)
{
    _ui->setupUi( this );
}

////////////////////////////////////////////////////////////////////////////////

DialogEditGap::~DialogEditGap()
{
    if ( _ui ) delete _ui;
    _ui = nullptr;
}
