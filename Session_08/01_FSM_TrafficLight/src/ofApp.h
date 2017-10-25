#pragma once


#include "ofMain.h"


class ofApp : public ofBaseApp
{
public:
    void setup() override;
    void update() override;
    void draw() override;

    // 1) In this enumeration we identify our valid finite states.
    enum State
    {
        STATE_RED,
        STATE_YELLOW,
        STATE_GREEN
    };

    State currentState = STATE_RED;
    uint64_t lastTransitionTime = 0; // Time of our last transition.

};
