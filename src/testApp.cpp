#include "testApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);

    vidPlayer.loadMovie("vid/teenconv.mp4");
    
	contourFinder.setMinAreaRadius(1);
	contourFinder.setMaxAreaRadius(70);
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
	stepSize = 8;
	ySteps = vidPlayer.getHeight() / stepSize;
	xSteps = vidPlayer.getWidth() / stepSize;
    
    for(int y = 0; y < ySteps; y++) {
		for(int x = 0; x < xSteps; x++) {
			mesh.addVertex(ofVec2f(x * stepSize, y * stepSize));
			mesh.addTexCoord(ofVec2f(x * stepSize, y * stepSize));
		}
	}
	for(int y = 0; y + 1< ySteps; y++) {
		for(int x = 0; x + 1 < xSteps; x++) {
			int nw = y * xSteps + x;
			int ne = nw + 1;
			int sw = nw + xSteps;
			int se = sw + 1;
			mesh.addIndex(nw);
			mesh.addIndex(ne);
			mesh.addIndex(se);
			mesh.addIndex(nw);
			mesh.addIndex(se);
			mesh.addIndex(sw);
		}
	}

    
    sampleRate = 44100;
    channels = 2;
    ofSetLogLevel(OF_LOG_VERBOSE);
    fileName = "testMovie";
    fileExt = ".mp4";
    
    
    ofSetWindowShape(vidPlayer.getWidth(), vidPlayer.getHeight());
    
    bRecording = false;
    ofEnableAlphaBlending();

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
    if(vidPlayer.getCurrentFrame() <= vidPlayer.getTotalNumFrames()) {
        vidPlayer.nextFrame();
		flow.setWindowSize(8);
		flow.calcOpticalFlow(vidPlayer);
		int i = 0;
		float distortionStrength = 4;
		for(int y = 1; y + 1 < ySteps; y++) {
			for(int x = 1; x + 1 < xSteps; x++) {
				int i = y * xSteps + x;
				ofVec2f position(x * stepSize, y * stepSize);
				ofRectangle area(position - ofVec2f(stepSize, stepSize) / 2, stepSize, stepSize);
				ofVec2f offset = flow.getAverageFlowInRegion(area);
				mesh.setVertex(i, position + distortionStrength * offset);
				i++;
			}
		}
        
        ofBackground(0);
        
        ofPixelsRef pixels = vidPlayer.getPixelsRef();

    
        for(int threshold = 127; threshold >=0; threshold-=30){
            contourFinder.setThreshold(threshold);
            contourFinder.setInvert(true);
            contourFinder.findContours(vidPlayer);
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
            contourFinder.findContours(vidPlayer);
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
            contourFinder.findContours(vidPlayer);
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
            contourFinder.findContours(vidPlayer);
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
        
        ofImage grab;
        grab.allocate(ofGetWidth(),ofGetHeight(),OF_IMAGE_COLOR);
        grab.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    
        grab.bind();
        mesh.draw();
        vidRecorder.addFrame(grab.getPixelsRef());
        grab.unbind();
        //vidRecorder.addFrame(grab.getPixelsRef());
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
void testApp::audioIn(float *input, int bufferSize, int nChannels){
    if(bRecording)
        vidRecorder.addAudioSamples(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void testApp::exit() {
    vidRecorder.close();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    if(key=='r'){
        bRecording = !bRecording;
        if(bRecording && !vidRecorder.isInitialized()) {
            //vidRecorder.setup(fileName+ofGetTimestampString()+fileExt, ofGetWidth(), ofGetHeight(), 25, sampleRate, channels);
                      vidRecorder.setup(fileName+ofGetTimestampString()+fileExt, ofGetWidth(),ofGetHeight(), 25); // no audio
            //            vidRecorder.setup(fileName+ofGetTimestampString()+fileExt, 0,0,0, sampleRate, channels); // no video
            //          vidRecorder.setupCustomOutput(vidGrabber.getWidth(), vidGrabber.getHeight(), 30, sampleRate, channels, "-vcodec mpeg4 -b 1600k -acodec mp2 -ab 128k -f mpegts udp://localhost:1234"); // for custom ffmpeg output string (streaming, etc)
        }
    }
    if(key=='c'){
        bRecording = false;
        vidRecorder.close();
    }

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

