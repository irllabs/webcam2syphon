#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    

    XML.loadFile("mySettings.xml");
    camWidth = XML.getValue("camWidth", 0);  // try to grab at this size.
    camHeight = XML.getValue("camHeight", 0);

    //we can now get back a list of devices.
    vector<ofVideoDevice> devices = vidGrabber.listDevices();

    for(int i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable){
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }

    
    alphaMaskImage.load("img_mask_720c.png");
    alphaMaskTexture = alphaMaskImage.getTexture();
    
    vidGrabber.setDeviceID(XML.getValue("cameraDeviceID", 0));
    vidGrabber.setDesiredFrameRate(60);
    vidGrabber.initGrabber(camWidth, camHeight);
    
    //set alpha mask for grabber, and for texture onto which we grab
    
    //videoTexture.setAlphaMask(alphaMaskTexture);
    
    ofSetVerticalSync(true);
    
    //setup syphon
    
    individualTextureSyphonServer.setName("webcam2syphon");
    
    
   }



//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(100, 100, 100);
    vidGrabber.update();
    vidGrabber.getTexture().setAlphaMask(alphaMaskTexture);


    if(vidGrabber.isFrameNew()){
        videoTexture = vidGrabber.getTexture();

    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetHexColor(0xffffff);
    vidGrabber.draw(0, 0, 160, 160*camHeight/camWidth);
    individualTextureSyphonServer.publishTexture(&videoTexture);

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // in fullscreen mode, on a pc at least, the 
    // first time video settings the come up
    // they come up *under* the fullscreen window
    // use alt-tab to navigate to the settings
    // window. we are working on a fix for this...

    // Video settings no longer works in 10.7
    // You'll need to compile with the 10.6 SDK for this
    // For Xcode 4.4 and greater, see this forum post on instructions on installing the SDK
    // http://forum.openframeworks.cc/index.php?topic=10343
    if(key == 's' || key == 'S'){
        vidGrabber.videoSettings();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
}
