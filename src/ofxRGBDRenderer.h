/*
 *  ofxRGBDRenderer.h
 *  ofxRGBDepthCaptureOpenNI
 *
 *  Created by Jim on 12/17/11.
 *  
 *  The ofxRGBDRenderer is capable of actually rendering a depth image aligned to a
 *  an RGB image from an external camera.
 *
 *  It requres a calibration file generated by a ofxRGBDAlignment from a series of checkerboard calibration pairs,
 *  a depth image and an rgb image from cameras from the same perspective
 *  
 *
 */

#pragma once
#include "ofMain.h"
#include "ofxCv.h"
#include "ofRange.h"

using namespace ofxCv;
using namespace cv;

class ofxRGBDRenderer {
  public:
	ofxRGBDRenderer();
	~ofxRGBDRenderer();
	
	bool setup(string calibrationDirectory);
	
	void setRGBTexture(ofBaseHasTexture& rgbTexture); 
	void setDepthImage(unsigned short* depthPixelsRaw);

	//used for supplying a preview texture that is smaller than the image was calibrated on.
	//helps for playback vs rendering
	void setTextureScale(float xTextureScale, float yTextureScale);
	
	void update();

	//fudge factors to apply during alignment
	float xshift;
	float yshift;
	float xmult;
	float ymult;
	float xscale;
	float yscale;
	float rotationCompensation;
	
	float edgeCull;
	float farClip;
	
	float fadeToWhite; //0 to 1
	bool mirror;
	
	//sets a level of simplification, 
	//should be either 1 for none
	//2 for half, or 4 for quarter;
	void setSimplification(int level);
	int getSimplification();
	
	void drawMesh();
	void drawPointCloud();
	void drawWireFrame();
	
	//populated with vertices, texture coords, and indeces
	ofMesh& getMesh();
	ofTexture& getTextureReference();
	
	Calibration& getRGBCalibration();
	Calibration& getDepthCalibration();
	
  protected:
	
	ofShader colorShader;
	int simplify;

	float xTextureScale;
	float yTextureScale;

	Calibration depthCalibration, rgbCalibration;    
	Mat rotationDepthToRGB, translationDepthToRGB;

	bool hasDepthImage;
	bool hasRGBImage;
	
	ofBaseHasTexture* currentRGBImage;
	unsigned short* currentDepthImage;
	
	vector<Point2f> imagePoints;    
	ofMesh simpleMesh;
    vector<ofIndexType> baseIndeces;
    vector<ofVec2f> texcoords;
    vector<ofVec3f> vertices;
	
	ofVec3f meshCenter;
	float meshDistance;
	
};