/***************************************************************************
 *   Copyright (C) 2004,2005 by Maximilian Hrabowski                       *
 *   maximilian@hrabowski.net                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "ProgressDialog.h"

#include <qpushbutton.h>

ProgressDialog::ProgressDialog(QWidget* parent, const char* name, bool modal, WFlags fl) :
	ScanProgressDialog(parent,name, modal,fl),
	m_canceled(false)
{
	connect( m_cancelButton, SIGNAL(clicked()), this, SLOT(canceled()) );
}

ProgressDialog::~ProgressDialog()
{
}

void ProgressDialog::canceled()
{
	m_canceled=true;
}

/*$SPECIALIZATION$*/


