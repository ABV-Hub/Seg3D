/*
 For more information, please see: http://software.sci.utah.edu
 
 The MIT License
 
 Copyright (c) 2009 Scientific Computing and Imaging Institute,
 University of Utah.
 
 
 Permission is hereby granted, free of charge, to any person obtaining a
 copy of this software and associated documentation files (the "Software"),
 to deal in the Software without restriction, including without limitation
 the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included
 in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 DEALINGS IN THE SOFTWARE.
 */

#include <Interface/AppPreferences/ColorButton.h>

namespace Seg3D
{
  
  
  ColorButton::ColorButton( QWidget *parent, int index, Core::Color button_color  ) :
    QToolButton( parent ),
    index_( index )
  {
    this->set_color( button_color );
    this->setCheckable( true );
  }
  
  ColorButton::~ColorButton()
  {
  }
  
  void ColorButton::set_color( Core::Color button_color )
  {
    if ( this->button_color_ == button_color ) {
      return;
    }
    
    this->button_color_ = button_color;
    
    QString style_sheet = QString::fromUtf8( 
      "background-color: rgb(" ) + QString::number( this->button_color_.r() ) +
      QString::fromUtf8( ", " ) + QString::number( this->button_color_.g() ) +
      QString::fromUtf8( ", " ) + QString::number( this->button_color_.b() ) +
      QString::fromUtf8( "); }" );
        
    this->setStyleSheet( style_sheet );
    
    Q_EMIT color_changed( this->button_color_ );
  }

  void ColorButton::mousePressEvent( QMouseEvent *event )
  {
    this->toggle();
    Q_EMIT this->clicked( this->button_color_, this->isChecked() );
    Q_EMIT this->clicked( this->index_ );
    Q_EMIT this->clicked();
  }
  
} // end namespace Seg3D


