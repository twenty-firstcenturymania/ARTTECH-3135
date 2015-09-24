#line 1 "Ball"

#include "ofMain.h"


#line 1 "Ball"
class Ball {
public:
	Ball() {
        // initialize all of the variables.	 
        // initialization list is also an option.        
        position = ofPoint(0, 0, 0);
        velocity = ofPoint(0, 0, 0);

        r = 10;
        drag = 0.99;
        color = ofColor(255);
	}	
	
	// draw the ball with the color and radius.
	void draw() {
	    ofFill();
	    ofSetColor(color);
	    ofCircle(position, r);
	}
	
	// update the position of the ball with the velocity.
	void update() {
	   // vx = vx * drag;
	   // vy = vy * drag;
	    velocity = velocity * drag;
	    
	   // x = x + vx;
	   // y = y + vy;
        position = position + velocity;
	    
	    
        // if (x > ofGetWidth() || x < 0)
        // {
        //     vx *= -1.0;
        // }
        // else if (y > ofGetHeight() || y < 0)
        // {
        //     vy *= -1.0;
        // }

	}
    
    ofPoint position;	
    ofPoint velocity;

	float r; // Ball radius.
	
	float drag; // add a drag term.
	
	ofColor color; // Ball class.
	
};

