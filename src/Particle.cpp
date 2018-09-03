#include "cinder/app/App.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "Particle.h"

using namespace ci;

Particle::Particle(vec2 loc) :
    mRad_initial(5.0f),
    mScale(7.0f),
    mDecay(0.99f),
    mAge(0)
{
  mLoc = loc;
  mDir = Rand::randVec2();
  mVel = Rand::randVec2();
  mRad = mRad_initial;
}


void Particle::update(const Channel32f &channel, const vec2 &mouseLoc) {
    // check that the particle is still alive
    mIsDead = mAge >= mLifespan;
    mAge++;

    // update location with the particles velocity
    mLoc += mVel;
    mVel *= mDecay;

    // distortion logic
    vec2 dirToCursor = mouseLoc - mLoc;
    // time and distance used to attenuate the wave motion
    float time = float(app::getElapsedSeconds()) * 4.0f;
    float dist = length(dirToCursor) * 0.05f;
    float sin_offset = 50.0f * sinf(0.20f * (dist - time));

    // calculate an offset to get the channel value in a neighborhood around the particle location, which
    // will result in a distorted image
    mDirToCursor = normalize(mouseLoc - mLoc);
    vec2 loc_offset = mLoc + mDirToCursor * sin_offset;

    // constraint the offsets to the canvas
    loc_offset.x = constrain(loc_offset.x, 0.0f, channel.getWidth() - 1.0f);
    loc_offset.y = constrain(loc_offset.y, 0.0f, channel.getHeight() - 1.0f);

    // apply the distortion and attenuate by the age of the Particle
    mRad = channel.getValue(mLoc) * mRad_initial * (1.0f - mAge/(float)mLifespan);
    mDirToCursor *= sin_offset * 15.0f;

}



void Particle::draw() {
    gl::drawSolidCircle(mLoc, mRad);
}
