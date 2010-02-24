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

#ifndef APPLICATION_STATE_STATEALIAS_H
#define APPLICATION_STATE_STATEALIAS_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// STL includes
#include <string>

// boost includes
#include <boost/smart_ptr.hpp>

// Utils includes
#include <Utils/Converter/StringConverter.h>

// Application includes
#include <Application/State/StateBase.h>
#include <Application/State/StateEngine.h>

namespace Seg3D {

// STATEALIAS:
// This class is a specification of State that is used to hold the name of layer
// The reason this state is not only a string, is the requirement that the
// layer name needs to be unique
 
class StateAlias;
typedef boost::shared_ptr<StateAlias> StateAliasHandle;


class StateAlias : public StateBase {

// -- constructor/destructor --
  public:

    // CONSTRUCTOR
    StateAlias();

    StateAlias(const std::string default_value);
           
    // DESTRUCTOR
    virtual ~StateAlias();

// -- functions for accessing data --

  public:
    // EXPORT_TO_STRING:
    // Convert the contents of the State into a string
    virtual std::string export_to_string() const;
    
    // IMPORT_FROM_STRING:
    // Set the State from a string
    virtual bool import_from_string(const std::string& str,
                                    ActionSource source = ACTION_SOURCE_NONE_E);
                                    
  protected:    
    // EXPORT_TO_VARIANT
    // Export the state data to a variant parameter
    virtual void export_to_variant(ActionParameterVariant& variant) const;
    
    // IMPORT_FROM_VARIANT:
    // Import the state data from a variant parameter.
    virtual bool import_from_variant(ActionParameterVariant& variant,
                                     ActionSource source = ACTION_SOURCE_NONE_E);
          
    // VALIDATE_VARIANT:
    // Validate a variant parameter
    // This function returns false if the parameter is invalid or cannot be 
    // converted and in that case error will describe the error.
    virtual bool validate_variant(ActionParameterVariant& variant, 
                                  std::string& error);                                  
                                    
// -- signals describing the state --
  public:
    // VALUE_CHANGED_SIGNAL:
    // Signal when the data in the state is changed, the second parameter
    // indicates the source of the change

    typedef boost::signals2::signal<void (std::string, ActionSource)> 
                                                      value_changed_signal_type;
    value_changed_signal_type value_changed_signal_;

// -- access value --
  public:
   // GET:
   // Get the value of the state variable
    const std::string& get() const { return value_; }

    // SET:
    // Set the value of the state variable
    // NOTE: this function by passes the action mechanism and should only be used
    // to enforce a constraint from another action.
    bool set(const std::string& value, 
             ActionSource source = ACTION_SOURCE_NONE_E); 

// -- storage of the view --
  protected:
    // Storage for the actual view
    std::string value_;
  };

} // end namespace Seg3D

#endif