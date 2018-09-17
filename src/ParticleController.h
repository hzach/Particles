#ifndef PARTICLECONTROLLER_H
#define PARTICLECONTROLLER_H
#include "cinder/app/App.h"
#include "cinder/Perlin.h"
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

        int mSpacing;

        Perlin mPerlin;

        Channel32f mChannel;

        /**
        * This list of Particles managed by this controller.
        */
        std::list<Particle> mParticles;

        void repelParticles();
};


#endif
