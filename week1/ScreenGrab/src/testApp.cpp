#include "testApp.h"

extern "C" {
#include "macGlutfix.h"
}

//--------------------------------------------------------------
void testApp::setup(){

	finder.setup("haarcascade_frontalface_default.xml");
	//CGContextRef cgctx = NULL;
	//ofSetVerticalSync(true);
	//tex.allocate(300,300, GL_RGBA);
	image.allocate(300, 300, OF_IMAGE_COLOR);
	//pixels.allocate(300, 300, OF_IMAGE_COLOR);
	
	ofSetFrameRate(30);

}

//--------------------------------------------------------------
void testApp::update(){
	
	int w = 300;
	int h = 300;
	
	unsigned char * data = pixelsBelowWindow(ofGetWindowPositionX(),ofGetWindowPositionY(),w,h);
	
	// now, let's get the R and B data swapped, so that it's all OK:
	for (int i = 0; i < w*h; i++){
		
		unsigned char r = data[i*4]; // mem A  
		
		data[i*4]   = data[i*4+1];   
		data[i*4+1] = data[i*4+2];   
		data[i*4+2] = data[i*4+3];   
		data[i*4+3] = r; 
	}
	
	
	if (data!= NULL) {
		//tex.loadData(data, 300, 300, GL_RGBA);
		//tex.readToPixels(pixels);
		//image = pixels;
		image.setFromPixels(data, 300, 300, OF_IMAGE_COLOR_ALPHA, true);
		image.setImageType(OF_IMAGE_COLOR);
		image.update();
		finder.findHaarObjects(image.getPixelsRef());
		
	}
	//cout << imageBelowWindow()[0] << endl;
	
	

}

//--------------------------------------------------------------
void testApp::draw(){
	image.draw(0,0, ofGetWidth(), ofGetHeight());
	
	ofNoFill();
	
	//for each face "blob" we found, draw a rectangle around the face
    //#2
	for(int i = 0; i < finder.blobs.size(); i++) {
//		ofRect(finder.blobs[i].boundingRect);
        ofImage tempFace, tempFace2;
        int tX,tY,tW,tH,s;
        tX = finder.blobs[i].boundingRect.x;
        tY = finder.blobs[i].boundingRect.y;
        tW = finder.blobs[i].boundingRect.width;
        tH = finder.blobs[i].boundingRect.height;
        s = tW * tH;
        tempFace.grabScreen(tX, tY, tW, tH);
        
        unsigned char * tempFaceArr = tempFace.getPixels();
        unsigned char * tempFlipFace = new unsigned char[s*3];
        ourProcessImage(tempFaceArr, tempFlipFace, tW, tH);
        
        tempFace2.setFromPixels(tempFlipFace, tW, tH, OF_IMAGE_COLOR);
        tempFace2.draw(tX, tW);
	}
	
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

void testApp::ourProcessImage(unsigned char ourImagePixels[],unsigned char ourResultPixels[], int width, int height){	
	unsigned char R,G,B;																																	
	for(int  horizontal = 0; horizontal < width ;horizontal ++){								// visit every pixel 
		for( int vertical = 0; vertical < height;vertical ++){
			
			int sourceHorizontal = horizontal;													// calculating the source for every pixel, to achieve a flip we subtarct from the width or height
//			if (flipH) sourceHorizontal= width-horizontal;
			
			int sourceVertical = vertical;										
            sourceVertical= height-vertical;
            
			ourGetPixel(sourceHorizontal,sourceVertical,&R,&G,&B,width,ourImagePixels);			// getting the pixel from the image array
			ourSetPixel(horizontal,vertical,R,G,B,width,ourResultPixels);						// setting it in the results aray			
		}	
	}						
}

//**********************  Pixel by Pixel course method that sets a pixel RGB in an x, y position in a pixel array ***********************

void testApp::ourSetPixel(int horizontal,int vertical,unsigned char R,unsigned char G,unsigned char B,int w, unsigned char pixels[]){
	int thisPixel;
	thisPixel = 3*(w * vertical +horizontal);
	pixels[thisPixel]=R;
	pixels[thisPixel+1]=G;
	pixels[thisPixel+2]=B;
}

//**********************  Pixel by Pixel course method that sets a pixel RGB in an x, y position in a pixel array ************************

void testApp::ourGetPixel(int horizontal,int vertical,unsigned char* R,unsigned char* G,unsigned char* B,int w, unsigned char pixels[]){
	int thisPixel;
	thisPixel = 3*(w * vertical +horizontal);
	*R= pixels[thisPixel];
	*G= pixels[thisPixel+1];
	*B= pixels[thisPixel+2];
}