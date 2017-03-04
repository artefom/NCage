//
// Created by artef on 27.02.2017.
//

#include "glutUtils.h"

Color::Color(unsigned char i_r, unsigned char i_g, unsigned char i_b, unsigned char i_a) :
        b(i_b),
        g(i_g),
        r(i_r),
        a(i_a){
}

Color::Color() :
        b(128),
        g(128),
        r(128),
        a(128){

}

Color::Color(const char *str) {
    from_string(str);
}

Color::Color(std::string str) {
    from_string( str.c_str() );
}
