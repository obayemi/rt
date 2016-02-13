/*!
 * \file main.cpp
 * \author obayemi
 */

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Coordinates.hpp"
#include "Scene.hh"
#include "Color.hh"
#include "Exceptions.hh"

sf::Image				renderman(const Scene &scene, const Camera &camera) {
    sf::Image		image;

    image.create(camera.getResolution().x, camera.getResolution().y);
    std::cout << "starting render" << std::endl;
    for (CameraRay cameraRay : camera.getRays()) {
        try {
            Color color = cameraRay.render(scene);

            for (Pixel pixel : cameraRay.getPixels()) {
                image.setPixel(pixel.x, pixel.y,
                        sf::Color(
                            color.getR(),
                            color.getG(),
                            color.getB(),
                            color.getA()));
            }
        } catch (const RenderException &e) {
            /*
             *std::cerr << e.what() << std::endl;
             */
        }
    }
    return image;
}

int					main(int ac, char **av)
{
    (void)ac;
    (void)av;
/*
 *
 *
 *    Rotation3	rotvector;
 *    Rotation3	vector(1, 0, 0);
 *    Rotation	quaternion(rotvector);
 *    RotMatrix	matrix(quaternion);
 *
 *    std::cout << "vector" << rotvector << std::endl;
 *    std::cout << "matrix" << quaternion << std::endl;
 *
 *    std::cout << "rotated vector "
 *        << vector << " to "
 *        << matrix * vector << std::endl;
 *
 *
 */

    Scene scene("");
    std::cout << "Hello world!" << std::endl;
    sf::Image image = renderman(scene, *scene.getCamera().front());
    sf::RenderWindow window(sf::VideoMode(image.getSize().x, image.getSize().y), "RailTracer");
    sf::Texture		texture;
    sf::Sprite		sprite;
    std::cout << "rendered" << std::endl;

    texture.loadFromImage(image);
    texture.setSmooth(true);
    sprite.setTexture(texture);
    std::cout << "imaged" << std::endl;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        texture.update(image);

        window.clear();
        window.draw(sprite);
        window.display();
    }
    return 0;
}
