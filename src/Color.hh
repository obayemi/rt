#ifndef _COLOR_HH
#define _COLOR_HH

/*!
 * \file Color.hh
 * \author obayemi
 */

#include <iostream>
#include <list>

typedef unsigned char uint8;
typedef unsigned long uint32;


class					Color {

    private:
        uint32			_r;
        uint32			_g;
        uint32			_b;
        uint32			_a;

    private:

    public:
        Color();
        Color(uint32 color);
        Color(const Color &other);
        Color(uint8 r,uint8 g,uint8 b, uint8 a = 255);
        ~Color();

        uint32			getColor() const;
        uint8			getR() const;
        uint8			getG() const;
        uint8			getB() const;
        uint8			getA() const;

        Color			&operator*=(double scalar);
        Color			operator*(double scalar) const;

        Color			&operator*=(const Color &other);
        Color			operator*(const Color &other) const;

        Color			&operator+=(const Color &other);
        Color			operator+(const Color &other) const;

        static Color	merge(const std::list<Color> &colors);

        friend std::ostream& operator<<(std::ostream& out, const Color& color);
};


#endif // _COLOR_HH
