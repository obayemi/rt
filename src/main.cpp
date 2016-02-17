/*!
 * \file main.cpp
 * \author obayemi
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <SFML/Graphics.hpp>

#include "Coordinates.hpp"
#include "Scene.hh"
#include "Color.hh"
#include "Exceptions.hh"
#include "TypesInit.hh"

std::mutex				mtx;

void					renderWorker(const Scene *scene, sf::Image &image, std::list<CameraRay *> &rays) {
    CameraRay		*ray;
        while (true) {
        mtx.lock();
        if (rays.empty()) {
            mtx.unlock();
            return ;
        }
        ray = rays.front();
        rays.pop_front();
        std::cout << rays.size() << std::endl;
        mtx.unlock();

        try {
            Color color = ray->render(*scene);

            for (Pixel pixel : ray->getPixels()) {
                image.setPixel(pixel.x, pixel.y,
                        sf::Color(
                            color.getR(),
                            color.getG(),
                            color.getB(),
                            color.getA()));
            }
        } catch (const RenderException &e) {
        }
        delete ray;
    }
}

void					renderTask(const Scene *scene, sf::Image &image) {
    Camera				&camera = *scene->getCamera().front();
    std::list<CameraRay *> rays = camera.getRays();

    image.create(camera.getResolution().x, camera.getResolution().y);

    std::cout << "init worker" << std::endl;
    renderWorker(scene, image, rays);
}

sf::Image				renderman(const Scene &scene, const Camera &camera) {
    sf::Image			image;
    int i = 0;

    image.create(camera.getResolution().x, camera.getResolution().y);
    std::cout << "starting render" << std::endl;
    for (CameraRay *cameraRay : camera.getRays()) {
        if (++i % 10000 == 0)
            std::cout << i << " pixels rendered\r" << std::flush;
        try {
            Color color = cameraRay->render(scene);

            for (Pixel pixel : cameraRay->getPixels()) {
                image.setPixel(pixel.x, pixel.y,
                        sf::Color(
                            color.getR(),
                            color.getG(),
                            color.getB(),
                            color.getA()));
            }
        } catch (const RenderException &e) {
        }
        delete cameraRay;
    }
    std::cout << std::endl << "render finished" << std::endl;
    return image;
}

int						main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage:" << std::endl
            << av[0] << " <scene.json>" << std::endl;
        return 1;
    }
    typesInit();
    Scene scene(av[1]);
    std::cout << "Hello world!" << std::endl;
    sf::Image image = renderman(scene, *scene.getCamera().front());
    //sf::Image image;
    //renderTask(&scene, image);
    //std::thread(renderTask, &scene, image);
    sf::RenderWindow window(sf::VideoMode(image.getSize().x, image.getSize().y), "RailTracer");

    sf::Texture		texture;
    sf::Sprite		sprite;

    texture.loadFromImage(image);
    texture.setSmooth(true);
    sprite.setTexture(texture);

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
