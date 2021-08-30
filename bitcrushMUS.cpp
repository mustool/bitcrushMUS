/*

Copyright MUS 2020

This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/



#include <lv2plugin.hpp>
#include <math.h>
#include <lv2lib00_MUS/mainMUS.h>

using namespace LV2;

class BitcrushMUS : public Plugin<BitcrushMUS> {
public:

  BitcrushMUS(double rate)
    : Plugin<BitcrushMUS>(5) {

      bc = new BitCrush00(24.0);

  }

  void run(uint32_t nframes) {

    float bits = *p(2);

    bits = bits < 1 ? 1 : bits;
    bits = bits > 24 ? 24 : bits;

    float mix = *p(3);

    mix = mix < 0 ? 0 : mix;
    mix = mix > 1 ? 1 : mix;

    float rmix = 1.0 - mix;



    float amp = *p(4);

    amp = amp < 0 ? 0 : amp;
    amp = amp > 1 ? 1 : amp;

    bc->setBits(bits);




    for (uint32_t i = 0; i < nframes; ++i) {

      float in = p(0)[i];

      float crushed = bc->ar(in);

      float out = (crushed * mix) + (in * rmix);


      p(1)[i] = out * amp;


    }

  }

protected:
BitCrush00* bc;


};

static int _ = BitcrushMUS::register_class("http://musens.pluggar/lv2/lv2pftci/bitcrushMUS");
