/***************************************************************************
 *   Copyright (C) 2008 by Pouf                                            *
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

#ifndef CARDCURSE_H
#define CARDCURSE_H

#include "highnooncard.h"
#include <QMap>

class PlayingCard;

class CardCurse : public HighNoonCard
{
  Q_OBJECT
  public :
    CardCurse(Game * game, int id);
    virtual ~CardCurse();
    virtual void play();

  public slots :
	void stop();

  protected :
	QMap<PlayingCard*, CardSuit> m_cards;
};

#endif