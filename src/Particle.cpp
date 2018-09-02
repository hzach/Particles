#include "cinder/app/App.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "Particle.h"

using namespace ci;

Particle::Particle(vec2 loc) :
    mRad_initial(1.0f),
    mScale(7.0f)
{
  mLoc = loc;
  mDir = Rand::randVec2();
  mVel = Rand::randFloat(5.0f);
  mRad = mRad_initial;
}


void Particle::update(const Channel32f &channel, const vec2 &mouseLoc) {
    float grey = channel.getValue(mLoc);

    dirToCursor = normalize(mouseLoc - mLoc);
    mColor = Color(grey, grey, grey);
    mRad = channel.getValue(mLoc) * 7.0f;

}



void Particle::draw() {
    Rectf rect(mLoc.x, mLoc.y, mLoc.x + mRad, mLoc.y + mRad);

    gl::color(mColor);
    gl::drawSolidRect(rect);
}
