#ifndef PARTICLECONTROLLER_H
#define PARTICLECONTROLLER_H
#include "cinder/app/App.h"
#include "Particle.h"
#include <list>

using namespace ci;

class ParticleController {

    public:
        ParticleController() = default;

        ParticleController(Channel32f channel);

        /**
        * makes changes to the controller state.
        */
        void update(vec2 mouseLoc);

        /**
        * Draws the particles controlled by this.
        */
        void draw();

        /**
        * Adds the amount of particles equal to the parameter amount to this controller.
        *
        * @param int amt the amount of particles to add
        */
        void addParticles_random(int amt);

        /**
        * Adds a Particle centered around each lattice point (x_i, y_i) in [0,..,mXRes] X [0,..,mYRes]
        *
        */
        void addParticles_lattice();

        /**
        * Removes some amount of particles from this controller.
        *
        * @param int amt the amount of particles to remove.
        */
        void removeParticles(int amt);

    private:

        int mXRes;

        int mYRes;

        int mSpacing;

        Channel32f mChannel;

        /**
        * This list of Particles managed by this controller.
        */
        std::list<Particle> mParticles;


/**
 * Adds a single particle to mParticles with a random starting position
 */
void addParticle();


/**
 * Adds a single particle to mParticles with a starting position at (x_i, y_i)
 *
 * @param int x_i the x-coordinate of the starting position
 * @param int y_1 the y-coordinate of the starting position
 */
void addParticle(int x_i, int y_i);
};


#endif
