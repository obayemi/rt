#ifndef _SCENE_HH
#define _SCENE_HH

/*!
 * \file Scene.hh
 * \author obayemi
 */

#include "Object.hh"
#include "Color.hh"

/*!
 * \file Light.hh
 * \author obayemi
 */

class			Light : public Object {
    private:
        Color		_color;

    public:
        virtual ~Light();
}

#endif // _SCENE_HH
