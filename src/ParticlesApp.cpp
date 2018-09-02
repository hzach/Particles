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
    // Cinder will call 'draw' each time the contents of the window need to be redrawn.
    void draw() override;

    void setup() override;

    void update() override;

    void mouseMove(MouseEvent event) override;

  private:
    ParticleController mParticleController;
    vec2  mMouseLoc;
    int mParticleCount = 50;
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
    mParticleController.addParticles_lattice();
}



void ParticleApp::draw()
{
	// Clear the contents of the window. This call will clear
	// both the color and depth buffers. 
	gl::clear( Color(0, 0, 0), true);
    mParticleController.draw();
}

void ParticleApp::update() {
  mParticleController.update(mMouseLoc);
}


void ParticleApp::mouseMove(MouseEvent event) {
    mMouseLoc = event.getPos();

}



// This line tells Cinder to actually create and run the application.
CINDER_APP( ParticleApp, RendererGl, prepareSettings )
