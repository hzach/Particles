#ifndef PARTICLE_H
#define PARTICLE_H
#include "cinder/Perlin.h"
#include "cinder/app/App.h"

using namespace ci;

struct Distortion {

    /**
     * location of the particle after wave distortion is applied
     */
    vec2 loc_offset;

    /**
     * velocity of the particle after perlin noise is applied
     */
    vec2 perlin_offset;
};


class Particle {
  public:
    cinder::vec2 mLoc;
    cinder::vec2 mAcc;
    float mMass;

    Particle(vec2 loc, vec2 vel);

    void draw();

    void update(
            const Channel32f &channel,
            const vec2 &mouseLoc,
            const Perlin &noise
    );

    bool mIsDead;

  private:
    cinder::vec2 mVel;

    float mDecay;
    int mAge;
    int const static mLifespan = 100;
    vec2 mDir;
    float mRad;
    float mScale;
    Colorf mColor;
    vec2 mDirToCursor;
    const float mRad_initial;

    /**
     * Gets a perlin noise value based on the Particles current location and the elapsed time
     */
    float current_noise_value(const Perlin &perlin);


    /**
     * Calculates distortion offsets from the provided target location and noise value. The strength of the
     * distortion is controlled by the distance between the target and the provided relative location vector and the noise value.
     *
     * the strength of the location offset is inversely proportional to the distance between the two locations. The location offset
     * will be constrained to the parallelogram described by the boundary vector.
     *
     * @param loc the target location to distort
     * @param relativeLoc a location that controls the distortion strength
     * @param noise the current noise value of the Particle.
     * @param boundary of the distortion
     */
    Distortion distort(
            const vec2  &loc,
            const vec2  &relativeLoc,
            const float &noise,
            const vec2  &boundary
    );
};

#endif
