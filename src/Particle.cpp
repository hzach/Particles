#include <cinder/Perlin.h>
#include "cinder/app/App.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "Particle.h"

using namespace ci;


Particle::Particle(vec2 loc, vec2 vel) :
    mRad_initial(5.0f),
    mScale(7.0f),
    mDecay(Rand::randFloat(0.15f, .19f)),
    mVel(vel),
    mAcc(Rand::randVec2()),
    mAge(0)
{
  mLoc = loc;
  mDir = Rand::randVec2();
  mRad = mRad_initial;
  mMass = mRad * mRad * 0.005f;
}


void Particle::update(const Channel32f &channel, const vec2 &mouseLoc, const Perlin &perlin) {
    // check that the particle is still alive
    mIsDead = mAge >= mLifespan;
    mAge++;

    float noise = current_noise_value(perlin);
    vec2 dirToCursor = mouseLoc - mLoc;
    mDirToCursor = normalize(dirToCursor);

    Distortion offsets = distort(
            mouseLoc,
            dirToCursor,
            noise,
            vec2(channel.getWidth() - 1.0f, channel.getHeight() - 1.0f)
    );

    // update location with the particles velocity

    float speed = length(mVel);
    if (speed < 0.25f) {
        mVel -= mAcc;
    }
    mLoc += mVel;
    mVel += offsets.perlin_offset * mDecay * (1.0f -  mAge/(float)mLifespan);
    mAcc = vec2(0,0);
    // apply the distortion and attenuate by the age of the Particle
    mRad = channel.getValue(offsets.loc_offset) * mRad_initial * (1.0f - mAge/(float)mLifespan);

}



void Particle::draw() {
    gl::drawSolidCircle(mLoc, mRad);
}


float Particle::current_noise_value(const Perlin &perlin) {
    // get perlin noise value for the current location and time
    float nX = mLoc.x * 0.005f;
    float nY = mLoc.y * 0.005f;
    float nZ = (float)app::getElapsedSeconds() * 0.1f;

    vec3 perlin_vec(nX, nY, nZ);
    return perlin.fBm(perlin_vec);
}


Distortion Particle::distort(
        const vec2  &loc,
        const vec2  &relativeLoc,
        const float &noise,
        const vec2  &boundary)
{
    // time and distance used to attenuate the wave motion
    float time = float(app::getElapsedSeconds()) * 4.0f;
    float dist = length(relativeLoc) * 0.05f;
    float sin_offset = 50.0f * sinf(0.20f * (dist - time));
    vec2 loc_offset = mLoc + mDirToCursor * sin_offset;

    // constraint the offsets to the canvas
    loc_offset.x = constrain(loc_offset.x, 0.0f, boundary.x);
    loc_offset.y = constrain(loc_offset.y, 0.0f, boundary.y);

    float angle = noise * 15.0f;
    vec2 perlin_offset = vec2(cosf(angle), sinf(angle));

    return {
        loc_offset,
        perlin_offset,
    };

}
