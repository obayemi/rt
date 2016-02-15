#ifndef _LIGHT_HH
#define _LIGHT_HH

/*!
 * \file Light.hh
 * \author obayemi
 */

#include "Object.hh"
#include "Color.hh"

/*!
 * \file Light.hh
 * \author obayemi
 */

class							Light : public Object {
    public:
        static Color			defaultColor;

    private:
        Color					_color;

    public:
        Light();
        Light(const Light &other);
        Light(const Position &position, const Rotation &rotation,
                const Color &color = Light::defaultColor);
        virtual ~Light();

        const Color				&getColor(const Direction &origin = Direction(),
                double distance = 0) const;

        static Light					*fromJson(const Json::Value &light);
};

#endif // _LIGHT_HH
