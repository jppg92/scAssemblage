#pragma once
#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxGui.h"
#include "ofxOsc.h"

class pointCloud {
    
public:
    
    void addMesh( ofMesh * newMesh);
    void save();
    void draw();
    
    ofMesh mesh;
    
};

