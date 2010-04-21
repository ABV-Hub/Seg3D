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


#include <Application/LayerManager/LayerManager.h>
#include <Application/Filters/Actions/ActionBinaryDialateErode.h>

namespace Seg3D
{
  
// REGISTER ACTION:
// Define a function that registers the action. The action also needs to be
// registered in the CMake file.
CORE_REGISTER_ACTION( BinaryDialateErode );

bool ActionBinaryDialateErode::validate( ActionContextHandle& context )
{
  if( !( StateEngine::Instance()->is_stateid( this->layer_alias_ ) ) )
  {
    context->report_error( std::string( "LayerID '" ) + this->layer_alias_ + "' is invalid" );
    return false;
  }
  if( this->dialate_ < 0 )
  {
    return false;
  }
  if( this->erode_ < 0 )
  {
    return false;
  }
  return true;
}

bool ActionBinaryDialateErode::run( ActionContextHandle& context, ActionResultHandle& result )
{
  if ( StateEngine::Instance()->is_stateid( this->layer_alias_ ) )
  {
    // TODO: run filter
    return true;
  }
    
  return false;
}


void ActionBinaryDialateErode::Dispatch(  std::string layer_alias, int dialate, int erode, bool replace  )
{
  ActionBinaryDialateErode* action = new ActionBinaryDialateErode;
  action->layer_alias_ = layer_alias;
  action->dialate_ = dialate;
  action->erode_ = erode;
  action->replace_ = replace;
  
  Interface::PostAction( ActionHandle( action ) );
}
  
} // end namespace Seg3D
