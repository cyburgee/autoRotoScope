#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxVideoRecorder.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void audioIn(float *input, int bufferSize, int nChannels);
    
        void exit();
    
        ofColor getContourAvgColor(int index, ofPixelsRef pixels);
    
        ofImage im;
    
        ofVideoPlayer vidPlayer;
        ofxCv::ContourFinder contourFinder;
        float threshold;
        ofxCv::TrackingColorMode trackingColorMode;
    
        ofxCv::FlowFarneback flow;
        ofMesh mesh;
        int stepSize, xSteps, ySteps;
    
        ofxVideoRecorder    vidRecorder;
        ofSoundStream       soundStream;
        bool bRecording;
        int sampleRate;
        int channels;
        string fileName;
        string fileExt;
    
        ofFbo recordFbo;
        ofPixels recordPixels;

		
};
