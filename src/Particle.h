#ifndef PARTICLE_H
#define PARTICLE_H
#include "cinder/app/App.h"

using namespace ci;

class Particle {
  public:
    Particle(vec2 loc);
    void draw();
    void update(const Channel32f &channel, const vec2 &mouseLoc);

  private:
    cinder::vec2 mLoc;
    vec2 mDir;
    float mVel;
    float mRad;
    Colorf mColor;
    vec2 dirToCursor;
    const float mRad_initial;
};

#endif
