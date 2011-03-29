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

#ifndef HIGHNOONCARD_H
#define HIGHNOONCARD_H

#include <QObject>
#include "parser/parserstructs.h"

class Game;

class HighNoonCard : public QObject
{
  Q_OBJECT
  public :
    HighNoonCard(Game * game, int id, HighNoonCardType type);
    virtual ~HighNoonCard();

    inline int id()                 const { return m_id;    }
    inline HighNoonCardType type()  const { if(this != 0) return m_type; else return HIGHNOON_INVALID;  }

    virtual void play() = 0;
  protected :
    Game *              mp_game;
    int                 m_id;
    HighNoonCardType    m_type;
};
#endif