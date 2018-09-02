#include "cinder/app/App.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "Particle.h"

using namespace ci;

Particle::Particle(vec2 loc) :
    mRad_initial(5.0f),
    mScale(7.0f)
{
  mLoc = loc;
  mDir = Rand::randVec2();
  mVel = Rand::randFloat(5.0f);
  mRad = mRad_initial;
}


void Particle::update(const Channel32f &channel, const vec2 &mouseLoc) {
    vec2 dirToCursor = mouseLoc - mLoc;
    float time = float(app::getElapsedSeconds()) * 4.0f;
    float dist = length(dirToCursor) * 0.05f;
    float sin_offset = 50.0f * sinf(0.20f * (dist - time));

    mDirToCursor = normalize(mouseLoc - mLoc);
    vec2 loc_offset = mLoc + mDirToCursor * sin_offset;

    loc_offset.x = constrain(loc_offset.x, 0.0f, channel.getWidth() - 1.0f);
    loc_offset.y = constrain(loc_offset.y, 0.0f, channel.getHeight() - 1.0f);

    mRad = channel.getValue(loc_offset) * mRad_initial;
    mDirToCursor *= sin_offset * 15.0f;

}



void Particle::draw() {
    gl::drawSolidCircle(mLoc, mRad);
}
