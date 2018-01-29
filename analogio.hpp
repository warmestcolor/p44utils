//
//  Copyright (c) 2014-2017 plan44.ch / Lukas Zeller, Zurich, Switzerland
//
//  Author: Lukas Zeller <luz@plan44.ch>
//
//  This file is part of p44utils.
//
//  p44utils is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  p44utils is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with p44utils. If not, see <http://www.gnu.org/licenses/>.
//

#ifndef __p44utils__analogio__
#define __p44utils__analogio__

#include "p44utils_common.hpp"

#include "iopin.hpp"

using namespace std;

namespace p44 {

  /// Generic digital I/O
  class AnalogIo : public P44Obj
  {
    AnalogIOPinPtr ioPin; ///< the actual hardware interface to the pin

    string pinspec;
    bool output;
    
  public:
    /// Create general purpose analog I/O, such as PWM or D/A output, or A/D input
    /// @param aPinSpec specification of the IO; form is usually [busX.device.]pin
    /// @param aOutput use as output
    /// @param aInitialValue initial value (to set for output, to expect without triggering change for input)
    /// @note possible pin types are
    ///   "i2cN.DEVICE@i2caddr.pinNumber" : numbered pin of DEVICE at i2caddr on i2c bus N
    ///     (DEVICE is name of chip, such as PCA9685)
    AnalogIo(const char* aPinSpec, bool aOutput, double aInitialValue);
    virtual ~AnalogIo();

    /// get name
    string getName() { return pinspec.c_str(); };

    /// check for output
    bool isOutput() { return output; };

    /// get state of GPIO
    /// @return current value (from actual pin for inputs, from last set value for outputs)
    double value();

    /// set state of output (NOP for inputs)
    /// @param aValue new state to set output to
    void setValue(double aValue);

    /// get range and resolution of this input
    /// @param aMin minimum value
    /// @param aMax maximum value
    /// @param aResolution resolution (LSBit value)
    /// @return false if no range information is available (arguments are not touched then)
    bool getRange(double &aMin, double &aMax, double &aResolution);


  };
  typedef boost::intrusive_ptr<AnalogIo> AnalogIoPtr;

  
} // namespace p44

#endif /* defined(__p44utils__analogio__) */
