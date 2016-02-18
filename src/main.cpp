/*!
 * \file main.cpp
 * \author obayemi
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <SFML/Graphics.hpp>

#include <unistd.h>

#include "Coordinates.hpp"
#include "Scene.hh"
#include "Color.hh"
#include "Exceptions.hh"
#include "TypesInit.hh"

std::mutex				mtx;

void					renderWorker(const Scene &scene, sf::Image &image, CameraRay **rays) {
    unsigned int		i;
    unsigned int		size;
    CameraRay			*ray;

    size = 0;
    while (rays[size++] != NULL);
    i = 0;
    while (true) {
        mtx.lock();
        while (rays[i] && rays[i]->getRendered())
            i++;
        if (rays[i] == NULL) {
            mtx.unlock();
            return ;
        }
        ray = rays[i];
        ray->setRendered();
        if ((i%10000) == 0)
        std::cout << i * 100 / size  << "% rendered\r" << std::flush;
        mtx.unlock();

        try {
            Color color = ray->render(scene);

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
        ++i;
    }

    std::cout << i * 100 / size  << "% rendered";
    std::cout << std::endl << "rendered" << std::endl;
}

void					renderTask(const Scene &scene, sf::Image &image) {
    Camera				&camera = *scene.getCamera().front();
    CameraRay			**rays = camera.getRays();

    image.create(camera.getResolution().x, camera.getResolution().y);

    std::cout << "init worker" << std::endl;
    //std::thread th = std::thread(renderWorker, std::ref(scene), std::ref(image), rays);
    renderWorker( std::ref(scene), std::ref(image), std::ref(rays));
    //std::thread(renderWorker, std::ref(scene), std::ref(image), std::ref(rays));

    while (*rays) {
        delete *(rays++);
    }
}

/*
 *sf::Image				renderman(const Scene &scene, const Camera &camera) {
 *    sf::Image			image;
 *    int i = 0;
 *
 *    image.create(camera.getResolution().x, camera.getResolution().y);
 *    std::cout << "starting render" << std::endl;
 *    for (CameraRay *cameraRay : camera.getRays()) {
 *        if (++i % 10000 == 0)
 *            std::cout << i << " pixels rendered\r" << std::flush;
 *        try {
 *            Color color = cameraRay->render(scene);
 *
 *            for (Pixel pixel : cameraRay->getPixels()) {
 *                image.setPixel(pixel.x, pixel.y,
 *                        sf::Color(
 *                            color.getR(),
 *                            color.getG(),
 *                            color.getB(),
 *                            color.getA()));
 *            }
 *        } catch (const RenderException &e) {
 *        }
 *        delete cameraRay;
 *    }
 *    std::cout << std::endl << "render finished" << std::endl;
 *    return image;
 *}
 *
 */
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
    //sf::Image image = renderman(scene, *scene.getCamera().front());
    sf::Image image;
    std::thread renderthread = std::thread(renderTask, std::ref(scene), std::ref(image));
    //renderthread.join();
    //renderTask(scene, image);
    usleep(1000000);
    sf::RenderWindow window(sf::VideoMode(image.getSize().x, image.getSize().y), "RailTracer");

    sf::Texture		texture;
    sf::Sprite		sprite;

    texture.loadFromImage(image);
    texture.setSmooth(true);
    sprite.setTexture(texture);

    while (window.isOpen())
    {
        usleep(1000);
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
