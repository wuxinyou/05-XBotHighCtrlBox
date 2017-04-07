/***************************************************************************
 *   Copyright (C) 2006-2008 by Tomasz Ziobrowski                          *
 *   http://www.3electrons.com                                             *
 *   e-mail: t.ziobrowski@3electrons.com                                   *
 *                                                                         *
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

#ifndef SELECT_H
#define SELECT_H

#include "abstractmeter.h"

    class Selectfalg : public AbstractMeter
    {
      Q_OBJECT 
      public:
    	Selectfalg(QWidget *parent = 0);
    	bool full_screen_flag;
    	int m_value_2;
    	int m_value_3;
    	void setValue_2(int v);
		void setValue_3(int v);
		void setFull(bool v);
		int value_2() const         { return m_value_2;}
		int value_3() const         { return m_value_3;}
      protected:
        void paintEvent(QPaintEvent *event); 	  // inherited form WidgetWithBackground
		void initCoordinateSystem(QPainter & painter);
		void paintBackground(QPainter & painter); // inherited form WidgetWithBackground
		void paintflag(QPainter & painter,int x,int y,int x1,int y1);
    };
#endif // SELECT_H
