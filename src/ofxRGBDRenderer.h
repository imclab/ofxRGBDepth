/*
 *  ofxRGBDRenderer.h
 *
 *  Created by James George on 12/17/11.
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

using namespace ofxCv;
using namespace cv;

class ofxRGBDRenderer {
  public:
	ofxRGBDRenderer();
	~ofxRGBDRenderer();
	
	bool setup(string rgbIntrinsicsPath, string depthIntrinsicsPath, string rotationPath, string translationPath);
	bool setup(string calibrationDirectory);

    void setRGBTexture(ofBaseHasTexture& tex);
    void setDepthImage(ofShortPixels& pix);

    ofBaseHasTexture& getRGBTexture();

	void update();

    //fudge factors to apply during alignment
    void setXYShift(ofVec2f shift);
    void setXYScale(ofVec2f scale);
    
    float xshift;
	float yshift;
	float xscale;
    float yscale;
    
	float edgeClip;
	float farClip;
    bool forceUndistortOff;
    bool addColors;
	bool mirror;
    bool calibrationSetup;
    
    ofVec3f meshRotate;

    bool bindRenderer(); //built in shader
    bool bindRenderer(ofShader& customShader); //any custom shader    
    void unbindRenderer();
    
    //called inside of bind/unbind
    void setupProjectionUniforms(ofShader& shader);
    void restortProjection();

    //fun way of visualizing the calibration
    void drawProjectionDebug(bool showDepth, bool showRGB, float rgbTexturePosition);
    
	void reloadShader();
    
	//sets a level of simplification, 
	//should be either 1 for none
	//2 for half, or 4 for quarter;
    void setSimplification(float simplification);
	void setSimplification(ofVec2f simplification);
	ofVec2f getSimplification();
	
	void drawMesh();
	void drawPointCloud();
	void drawWireFrame();

    void drawMesh(ofShader& customShader);
	void drawPointCloud(ofShader& customShader);
	void drawWireFrame(ofShader& customShader);
    
	//populated with vertices, texture coords, and indeces
	ofVboMesh& getMesh();
	
	Calibration& getRGBCalibration();
	Calibration& getDepthCalibration();
	ofMatrix4x4& getDepthToRGBTransform();
	ofMatrix4x4& getRGBMatrix();
	ofTexture& getDepthTexture();
    
	bool useTexture;
	bool flipTexture;
		
  protected:	
	ofVec2f simplify;

    //bool shaderBound;
    ofShader* currentlyBoundShader;
    bool rendererBound;
    
    Point2d principalPoint;
    cv::Size imageSize;
	Calibration depthCalibration, rgbCalibration;    
	Mat rotationDepthToRGB, translationDepthToRGB;
    float fx, fy;

	bool hasDepthImage;
	bool hasRGBImage;

    
	ofTexture depthTexture;
	
	ofBaseHasTexture* currentRGBImage;
	ofShortPixels* currentDepthImage;
    ofImage undistortedRGBImage;
	ofShortPixels undistortedDepthImage;
	
    ofVboMesh mesh; 
    
	ofMatrix4x4 depthToRGBView;
	ofMatrix4x4 rgbProjection;
    ofMatrix4x4 rgbMatrix;
	ofMatrix4x4 depthProjection;
	
	ofShader meshShader;
    ofShader pointShader;  
    
};