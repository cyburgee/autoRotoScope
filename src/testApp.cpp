#include "testApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void testApp::setup(){
    cam.initGrabber(ofGetWidth(), ofGetHeight());
    ofSetVerticalSync(true);

    
	contourFinder.setMinAreaRadius(1);
	contourFinder.setMaxAreaRadius(min(ofGetWidth(),ofGetHeight())/2.2);

    
    ofSetLogLevel(OF_LOG_VERBOSE);
}


//--------------------------------------------------------------
void testApp::update(){
    cam.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(0);
    
    if(cam.isFrameNew()) {
    
        ofPixelsRef pixels = cam.getPixelsRef();
    
        for(int threshold = 127; threshold >=0; threshold-=30){
            contourFinder.setThreshold(threshold);
            contourFinder.setInvert(true);
            contourFinder.findContours(cam);
            for (int k = 0; k < contourFinder.getPolylines().size(); k++){
                ofPath path;
                ofPolyline poly = contourFinder.getPolyline(k);
                for( int i = 0; i < poly.getVertices().size(); i++) {
                    if(i == 0) {
                    path.newSubPath();
                        path.moveTo(poly.getVertices()[i] );
                    } else {
                        path.lineTo( poly.getVertices()[i] );
                    }
                }
                path.close();
                path.simplify();
                ofColor color = getContourAvgColor(k,pixels);
                path.setColor(color);
                path.draw();
            }
    
            contourFinder.setInvert(false);
            contourFinder.findContours(cam);
            for (int k = 0; k < contourFinder.getPolylines().size(); k++){
                ofPath path;
                ofPolyline poly = contourFinder.getPolyline(k);
                for( int i = 0; i < poly.getVertices().size(); i++) {
                    if(i == 0) {
                        path.newSubPath();
                        path.moveTo(poly.getVertices()[i] );
                    } else {
                    path.lineTo( poly.getVertices()[i] );
                    }
                }
                path.close();
                path.simplify();
                ofColor color = getContourAvgColor(k,pixels);
                path.setColor(color);
                path.draw();
            }
        }
    
        for(int threshold = 127; threshold <=255; threshold+=30){
            contourFinder.setThreshold(threshold);
            contourFinder.setInvert(true);
            contourFinder.findContours(cam);
            for (int k = 0; k < contourFinder.getPolylines().size(); k++){
                ofPath path;
                ofPolyline poly = contourFinder.getPolyline(k);
                for( int i = 0; i < poly.getVertices().size(); i++) {
                    if(i == 0) {
                        path.newSubPath();
                        path.moveTo(poly.getVertices()[i] );
                    } else {
                        path.lineTo( poly.getVertices()[i] );
                    }
                }
                path.close();
                path.simplify();
                ofColor color = getContourAvgColor(k,pixels);
                path.setColor(color);
                path.draw();
            }
        
            contourFinder.setInvert(false);
            contourFinder.findContours(cam);
            for (int k = 0; k < contourFinder.getPolylines().size(); k++){
                ofPath path;
                ofPolyline poly = contourFinder.getPolyline(k);
                for( int i = 0; i < poly.getVertices().size(); i++) {
                    if(i == 0) {
                        path.newSubPath();
                        path.moveTo(poly.getVertices()[i] );
                    } else {
                        path.lineTo( poly.getVertices()[i] );
                    }
                }
                path.close();
                path.simplify();
                ofColor color = getContourAvgColor(k,pixels);
                path.setColor(color);
                path.draw();

            }
        }
    }
}

//--------------------------------------------------------------

ofColor testApp::getContourAvgColor(int index, ofPixelsRef pixels) {

    ofRectangle rect = ofRectangle(toOf(contourFinder.getBoundingRect(index)));
    ofPoint topLeft = rect.getTopLeft();
    int cx = topLeft.x;
    int cy = topLeft.y;
    int rr = 0;
    int gg = 0;
    int bb = 0;
    float cnt=0;
    //int sampStepX = (rand() % (int)ceil(rect.getWidth()/5) + 1);
    //int sampStepY = (rand() % (int)ceil(rect.getHeight()/5) + 1);
    for (int xx = cx; xx <= cx+rect.getWidth(); xx+= (rand() % (int)ceil(rect.getWidth()/5) + 1)){
        for (int yy = cy; yy <= cy+rect.getWidth(); yy+= (rand() % (int)ceil(rect.getHeight()/5) + 1)){
            int cxx = xx;
            int cyy = yy;
            rr = rr + pixels.getColor(cxx, cyy).r;
            gg = gg + pixels.getColor(cxx,cyy).g;
            bb = bb + pixels.getColor(cxx, cyy).b;
            cnt++;
        }
    }
    rr = int(rr/cnt);
    gg = int(gg/cnt);
    bb = int(bb/cnt);

    return ofColor(rr,gg,bb);
}



//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

