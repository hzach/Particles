#ifndef PARTICLECONTROLLER_H
#define PARTICLECONTROLLER_H
#include "cinder/app/App.h"
#include "Particle.h"
#include <list>

using namespace ci;

class ParticleController {

    public:
        ParticleController() = default;

        explicit ParticleController(Channel32f channel);

        /**
        * makes changes to the controller state.
        */
        void update(vec2 mouseLoc);

        /**
        * Draws the particles controlled by this.
        */
        void draw();


        /**
         * Draws zero or many particles at some location on the canvas
         *
         * @param amt the amount of particles to draw.
         * @param loc the location on the canvas
         */
        void addParticles(uint amt, const vec2 &loc, const vec2 &vel);


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
         * Adds a single particle to mParticles with a starting position at (x_i, y_i)
         *
         * @param int x_i the x-coordinate of the starting position
         * @param int y_1 the y-coordinate of the starting position
         */
        void addParticle(float x_i, float y_i, const vec2 &vel);

};


#endif
