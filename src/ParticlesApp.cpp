#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "ParticleController.h"

using namespace ci;
using namespace ci::app;

const int HEIGHT = 1600;
const int WIDTH  = 896;



// We'll create a new Cinder Application by deriving from the App class.
class ParticleApp : public App {
  public:
    Channel32f mChannel;
    vec2 mMouseLoc;
    vec2 mPrevMouseLoc;
    bool mIsPressed = false;

    // Cinder will call 'draw' each time the contents of the window need to be redrawn.
    void draw() override;

    void setup() override;

    void update() override;

    void mouseUp(MouseEvent event) override;

    void mouseMove(MouseEvent event) override;

    void mouseDrag(MouseEvent event) override;


  private:
    ParticleController mParticleController;

    void updateLocation(const vec2 &newLoc);
};



void prepareSettings( ParticleApp::Settings* settings )
{
	settings->setMultiTouchEnabled( false );
    settings->setWindowSize(WIDTH, HEIGHT);
    settings->setFrameRate(60);
}



void ParticleApp::setup()
{
    mChannel = Channel32f(loadImage(loadAsset("../assets/forest4.png")));
    mParticleController = ParticleController(mChannel);
}



void ParticleApp::draw()
{
	// Clear the contents of the window. This call will clear
	// both the color and depth buffers. 
	gl::clear( Color(0, 0, 0), true);
    mParticleController.draw();
}



void ParticleApp::update() {

    if (mIsPressed) {
        // calculate the mouse's velocity
        vec2 mouse_vel = length(mMouseLoc) == 0 ? mPrevMouseLoc : mMouseLoc - mPrevMouseLoc;
        mParticleController.addParticles(5, mMouseLoc, mouse_vel);
    }
    mParticleController.update(mMouseLoc);
}



void ParticleApp::mouseMove(MouseEvent event) {
    updateLocation(event.getPos());
}



void ParticleApp::mouseUp(MouseEvent event) {
    mIsPressed = false;
}



void ParticleApp::mouseDrag(MouseEvent event) {
    mIsPressed = true;
    updateLocation(event.getPos());
}



void ParticleApp::updateLocation(const vec2 &newLoc) {
    mPrevMouseLoc = mMouseLoc;
    mMouseLoc = newLoc;
}


// This line tells Cinder to actually create and run the application.
CINDER_APP( ParticleApp, RendererGl, prepareSettings )
