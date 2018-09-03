#ifndef PARTICLE_H
#define PARTICLE_H
#include "cinder/app/App.h"

using namespace ci;

class Particle {
  public:
    explicit Particle(vec2 loc);
    void draw();
    void update(const Channel32f &channel, const vec2 &mouseLoc);
    bool mIsDead;

  private:
    cinder::vec2 mLoc;
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
};

#endif
