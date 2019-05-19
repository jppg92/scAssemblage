#include "ofApp.h"
using namespace cv;
#include "opencv2/opencv.hpp"

// Uterii_Machine 001 is a code prototype for a custom "random assemblage 3D scanner". It is part of Juliette Pépin's research on machine vision and uterus gynaecological image acquisition protocols. More about the project can be find here: https://uterii.hotglue.me/

// The concept is that of a 3D scanner (using kinect) which creates pointclouds from Uterii artifacts later "merged" together into a random assamblage of acquired pointclouds. It uses osc messaging to make it easier for the user to choose when she/he wants to capture each pointcloud.

// The code doesn't borrow any specific codes from other developpers, although it was developped thanks to the advices of Georges Wyman (he helped me to use OSCulator combined with oscReceiver) and Jayson Kym Haebich (He explained me how to use pointers).


//--------------------------------------------------------------
void ofApp::setup(){

    // setup oscReceiver
    receive.setup(PORT);
    
    ofBackground(100, 100, 100);
    ofSetFrameRate(60);

    // set-up new mesh
    mesh = new ofMesh();
    mesh->setMode(OF_PRIMITIVE_POINTS);

    // Acquire video source
    video.setRegistration(true);
    video.init();
    video.open();
    
    // Define Gui control pannel for 3D scann threshold and zoom angle definition.
    gui.setup();
    gui.add(maxDepthSlider.set("maxDepth", 255, 0, 255));
    gui.add(minDepthSlider.set("minDepth", 233, 0, 255));
    gui.add(rotateSlider.set("rotate", 0,0,360));
    gui.add(zoomSlider.set("zoom", 0,-5000,5000));
    maxDepth = 0;
    minDepth = 0;
    zoom = 0;
    rotate = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    video.update();
    
    // osc message function
    getMessages();
    
    // Gui update
    zoom = zoom + zoomSlider;
    rotate = rotate + rotateSlider;
    
    // Generate mesh from depthImage double threshold
    if ( video.isFrameNew() )
    {
        // Creat pixel object
        ofPixels depthPixs = video.getDepthPixels();
        // make sure mesh is empty
        mesh->clear();
        // loops over pixels
        int numPixels = depthPixs.size();
        int step = 1;
        for(int i = 0; i < numPixels; i+=step)
        {   // store thresholded depth pixels (x,y,z)
            if(depthPixs[i] > minDepthSlider && depthPixs[i] < maxDepthSlider)
            {   // Here I asked for help to code the equivalent of getWorldCoordinateAt(...)
                int x = i % depthPixs.getWidth();
                int y = i / depthPixs.getWidth();
                // Here I multiply by 5 (or something else) to accentuate depth
                int z = depthPixs[i]* 5;
                // Allocates pixel coordinates to mesh
                mesh->addVertex( glm::vec3(x,y,z) );
                // Allocates pixel color to mesh
                ofColor color;
                color = video.getColorAt(x, y);
                mesh->addColor( color );
                //              Here add code to get color from pixel location:
            } else { depthPixs[i]=0;}
        } depthImg.setFromPixels(depthPixs);
    }
    
    // Store mesh in vector of meshes (with pointer)
    if(saveMesh) {
        meshList.push_back( mesh );
        // bool for adding or not;
        pointcloud.addMesh( mesh );
        mesh = new ofMesh();
        mesh->setMode(OF_PRIMITIVE_POINTS);
        saveMesh = false;
    }
    
     if (exportMesh = true){
         pointcloud.save();
         
     }
    
    
}

//--------------------------------------------------------------
void ofApp::draw()
{
    // Translate style and coordinates for GUI and original Depth image
    // Draw depth image
    ofPushMatrix();
    ofPushStyle();
    ofSetColor( 255, 255, 255 );
    depthImg.draw(10,10);
    gui.draw();
    ofPopStyle();
    ofPopMatrix();
    
    // Translate mesh coordinates to enable rotation and zoom
    // Draw assembled mesh
    ofPushMatrix();
    ofTranslate(660 ,500, zoomSlider);
    ofRotateY(ofGetElapsedTimef()*2);
    ofRotateX(ofGetElapsedTimef()*3);
    pointcloud.draw();
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofApp::getMessages(){

    while (receive.hasWaitingMessages()){
    ofxOscMessage m;
    receive.getNextMessage(&m);
    if (m.getAddress() == "/uterii/capView"){
        if(m.getArgAsFloat(0)==1 && saveMesh==false){saveMesh=true;}
        
    } else if (m.getAddress() == "/uterii/exportScan"){
        if(m.getArgAsFloat(0)==1 && exportMesh==false){exportMesh=true;}
        
    }
        
}
}

// Keyboard for debugging osc messages
////--------------------------------------------------------------
//void ofApp::keyPressed(int button){
//
//    if ( button == ' ')
//    {
//        saveMesh = true;
//
//    }
//    if ( button == 'e')
//    {
//        exportMesh = true;
//    }
