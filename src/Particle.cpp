#include "cinder/app/App.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "Particle.h"

using namespace ci;

Particle::Particle(vec2 loc) : mRad_initial(5.0f) {
  mLoc = loc;
  mDir = Rand::randVec2();
  mVel = Rand::randFloat(5.0f);
  mRad = mRad_initial;
}



//void Particle::update(const Channel32f &channel, const vec2 mouseLoc) {
//    float greyscale = channel.getValue(mLoc);
//    mColor = Color(greyscale, greyscale, greyscale,
//            sqrt(
//                    pow(mLoc.x - mouseLoc.x, 2) + pow(mLoc.y - mouseLoc.y, 2)
//            ));
//    mRad = channel.getValue(mLoc) * 7.0f;
//}

void Particle::update(const Channel32f &channel, const vec2 &mouseLoc) {
    dirToCursor = normalize(mouseLoc - mLoc);
    draw();

}



void Particle::draw() {
    float arrowLength = 20.0f;
    float headWidth   = 5.0f;
    float headRadius  = 3.0f;

    vec3 p1(mLoc, 0);         // position of particle
    vec3 p2(mLoc + dirToCursor * arrowLength, 0); // position of cursor

    gl::drawVector(p1, p2, headWidth, headRadius);

}
