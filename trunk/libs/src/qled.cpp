/***************************************************************************
 *   Copyright (C) 2008 by P. Sereno                                       *
 *   http://www.sereno-online.com                                          *
 *   http://www.qt4lab.org                                                 *
 *   http://www.qphoton.org                                                *
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
  
#include <QColor>
#include <QtGlobal>
#include <QtGui>
#include <QPolygon>


#include "qled.h"

QLed::QLed(QWidget *parent)
    : QWidget(parent)
{
   m_value=false;
   m_color=Qt::red;
   setMinimumSize(QSize(5,5)); 
}

void QLed::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setWindow( -55,-55,110,110);

	// Paint the grey outter circle
	QRadialGradient radialGrad1(QPointF(0, 0), 11);
	radialGrad1.setColorAt(0, Qt::black);
	radialGrad1.setColorAt(1, Qt::lightGray);
	radialGrad1.setSpread(QGradient::RepeatSpread);
	QBrush brush(radialGrad1);
	painter.setBrush(brush);
	painter.drawEllipse(-30,-30,60,60);

    if(m_value)
    {
      QRadialGradient radialGrad(QPointF(-4, -4), 20);
      radialGrad.setColorAt(0, m_color.lighter(175));
      radialGrad.setColorAt(1, m_color);
   	  QBrush brush(radialGrad);
      painter.setBrush(brush);
	  painter.drawEllipse(-25,-25,50,50);
    }
    else
    {
      QRadialGradient radialGrad(QPointF(-8, -8), 20);
      radialGrad.setColorAt(0, m_color);
      radialGrad.setColorAt(1, m_color.darker(200));
   	  QBrush brush(radialGrad);
      painter.setBrush(brush);
	  painter.drawEllipse(-25,-25,50,50);
    }	
}

void QLed::setColor(QColor newColor)
{
   m_color=newColor;
   update();
}


void QLed::setValue(bool value)
{
   m_value=value;
   update();
}


void QLed::toggleValue()
{ 
	m_value=!m_value;
	update();
	return; 
}
