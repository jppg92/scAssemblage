#pragma once

#include "ofMain.h"
#include "pointCloud.h"

#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxGui.h"
#include "ofxOsc.h"

#define PORT 8000

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void getMessages();

//    KeyPressed function for Debugging osc messages
//    void keyPressed(int button);
    
    ofxKinect video;
    ofxOscReceiver receive;

    // Declare pointCloud Class
    pointCloud pointcloud;

    // Mesh & mesh vector with pointer
    ofMesh * mesh;
    vector <ofMesh*> meshList;
    ofImage depthImg;
    
    bool saveMesh = false;
    bool exportMesh = false;
    
    ofxPanel gui;
    ofParameter <int> maxDepthSlider;
    ofParameter <int> minDepthSlider;
    ofParameter <float> rotateSlider;
    ofParameter <float> zoomSlider;
    
    int maxDepth;
    int minDepth;
    float zoom;
    float rotate;

    
};



