#line 1 "ParticleSystem3D"

#include "ofMain.h"
#include "BaseParticle.h"


class ofApp: public ofBaseApp
{
public:

#line 2 "ParticleSystem3D"

/// \brief Our collection of particles.
std::vector<BaseParticle> particles;

/// \brief The size of the particle in the x, y and z direction.
///
/// The size of the particle and the position constitute a 3D bounding cube.
ofPoint boxSize;

/// \brief A camera that can respond to mouse pan, zoom and rotation.
ofEasyCam camera;

/// \brief The standard setup function.
void setup() {
    // Set the background to zero / black.
    ofBackground(0);
    
    // Enable alpha blending.
    ofEnableAlphaBlending();
    
    // Enable anti-aliasing.
    ofEnableAntiAliasing();

     // Set the size of the window.
    ofSetWindowShape(1000, 1000);
    
    // Enable depth tests to ensure that correct 3D rendering.
    ofEnableDepthTest(); 

    // The size of the box in the x, y and z dimension.    
    boxSize = ofPoint(600, 600, 300);

    // Create particles.
    for (int i = 0; i < 100; i++)
    {
        // Create a half-sized box for calculations.
        ofPoint halfBoxSize = boxSize / 2;
        
        // Instantiate our base particle.
        BaseParticle aParticle;
        
        // Set the initial position to a random point inside our bounding box.
        aParticle.position = ofPoint(ofRandom(-halfBoxSize.x, halfBoxSize.x),
                                     ofRandom(-halfBoxSize.y, halfBoxSize.y),
                                     ofRandom(-halfBoxSize.z, halfBoxSize.z));
        
        // Set a random velocity.
        aParticle.velocity = ofPoint(ofRandom(-10, 10),
                                     ofRandom(-10, 10),
                                     ofRandom(-10, 10));

        // Set a random drag.
        float drag = ofRandom(0.9, 0.99);
        
        // Our drag is the same in the x, y and z directions.
        aParticle.drag = ofPoint(drag, drag, drag);
        
        // Create a random size for our particle.
        float size = 3;
        
        // Our particle size is the same in the x, y and z directions.
        aParticle.size = ofPoint(size, size, size);

        // Assign a random color to the particle.
        aParticle.color = ofColor(255, 127);
        
        // Add the particle to our collection.
        particles.push_back(aParticle);
    }
}


void update() {
    
    // Iterate through all particles and do various things to them.
    for (std::size_t i = 0; i < particles.size(); i++)
    {
        // Update the particle.
        particles[i].update();

        // Here we pass our particle "by reference".  
        // This means that the applyAccelerations function can modify the particle.
        applyAccelerations(particles[i]);
        
        // Here we pass our particle "by reference".  
        // This means that the checkCollisions function can modify the particle.
        checkCollisions(particles[i]);
    
    }
}


void draw() {
    
    // The camera will modify the view of everything between camera.being()
    // and camera.end().  
    camera.begin();
    
    // Draw the bounding box.
    drawBoundingBox();
    
    // Draw the particles.
    drawParticles();
    
    // Draw lines connecting the particles.
    drawParticleLines();
    
    // End the camera.
    camera.end();
    
}

void drawBoundingBox()
{
    ofFill();
    ofSetColor(127);
    ofDrawAxis(100);
    ofNoFill();
    ofDrawBox(0, 0, 0, boxSize.x, boxSize.y, boxSize.z);
}


void drawParticles()
{
    for (std::size_t i = 0; i < particles.size(); i++)
    {
        particles[i].draw();
    }
}


void drawParticleLines()
{
    float minimumLineDistance = 100;
    
    for (std::size_t i = 0; i < particles.size(); i++)
    {
        for (std::size_t j = 0; j < i; j++)
        {
            float particleParticleDistance = particles[i].position.distance(particles[j].position);
            
            if (particleParticleDistance < minimumLineDistance)
            {
                // Scale the line color based on the distance distance 
                float alpha = ofMap(particleParticleDistance, 0, minimumLineDistance, 255, 0);
                
                ofSetColor(255, alpha);
                
                ofLine(particles[i].position, particles[j].position);    
            }
        }
    }
}


void keyPressed(int key)
{
    if ('e' == key)
    {
        // Add random forces to all particles.
        for (std::size_t i = 0; i < particles.size(); i++)
        {
            particles[i].acceleration += ofPoint(ofRandom(-40, 40), 
                                                 ofRandom(-4, 4), 
                                                 ofRandom(-4, 4));
        }
    }
}


void applyAccelerations(BaseParticle& particle)
{
    // Modify this to change gravity.
    ofPoint gravity(0, .1, 0); 

    // Rotate the gravity vector in accordance with the camera.
    gravity = gravity * camera.getOrientationQuat();
    
    // Our only force is gravity.
    // Add other accelerations to create additional forces.
    particle.acceleration += gravity;        

    // What other forces could we use?
}


void checkCollisions(BaseParticle& particle)
{
    // Create a half-sized particle for calculations.
    ofPoint halfParticleSize = particle.size / 2.0;
    
    // Create a half-sized box for calculations.
    ofPoint halfBoxSize = boxSize / 2.0;
 
    // We must check for collisions in the x, y and z dimensions.
    
    // First check the x dimension.
    if (particle.position.x + halfParticleSize.x > halfBoxSize.x)
    {
        particle.velocity.x *= -1.0; // Send the velocity in the other direction.
        particle.velocity.x *= particle.restitution.x; // Remove some of the velocity because of the bounce.
        particle.position.x = halfBoxSize.x - halfParticleSize.x; // Set it back from the wall.
    }
    else if (particle.position.x - halfParticleSize.x < -halfBoxSize.x)
    {
        particle.velocity.x *= -1.0; // Send the velocity in the other direction.
        particle.velocity.x *= particle.restitution.x; // Remove some of the velocity because of the bounce.
        particle.position.x = - halfBoxSize.x + halfParticleSize.x; // Set it back from the wall.
    }
    
    // First check the y dimension.
    if (particle.position.y + halfParticleSize.y > halfBoxSize.y)
    {
        particle.velocity.y *= -1.0; // Send the velocity in the other direction.
        particle.velocity.y *= particle.restitution.y; // Remove some of the velocity because of the bounce.
        particle.position.y = halfBoxSize.y - halfParticleSize.y; // Set it back from the wall.
    }
    else if (particle.position.y - halfParticleSize.y < -halfBoxSize.y)
    {
        particle.velocity.y *= -1.0; // Send the velocity in the other direction.
        particle.velocity.y *= particle.restitution.y; // Remove some of the velocity because of the bounce.
        particle.position.y = - halfBoxSize.y + halfParticleSize.y; // Set it back from the wall.
    }

    // First check the z dimension.
    if (particle.position.z + halfParticleSize.z > halfBoxSize.z)
    {
        particle.velocity.z *= -1.0; // Send the velocity in the other direction.
        particle.velocity.z *= particle.restitution.z; // Remove some of the velocity because of the bounce.
        particle.position.z = halfBoxSize.z - halfParticleSize.z; // Set it back from the wall.
    }
    else if (particle.position.z - halfParticleSize.z < -halfBoxSize.z)
    {
        particle.velocity.z *= -1.0; // Send the velocity in the other direction.
        particle.velocity.z *= particle.restitution.z; // Remove some of the velocity because of the bounce.
        particle.position.z = - halfBoxSize.z + halfParticleSize.z; // Set it back from the wall.
    }
     
}


};

int main()
{
    ofSetupOpenGL(320, 240, OF_WINDOW);
    ofRunApp(new ofApp());
}

