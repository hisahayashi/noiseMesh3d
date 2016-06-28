#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    int ww = ofGetWidth();
    int wh = ofGetHeight();

    ofBackground(230);
    ofEnableDepthTest();
    
    light.enable();
    light.setPosition(ww * 0.5, 200, wh * 0.5);
    light.setAmbientColor(ofFloatColor(0.2, 0.5, 1.0, 1.0));
    light.setDiffuseColor(ofFloatColor(0.2, 0.5, 0.5));
    light.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    int ww = ofGetWidth();
    int wh = ofGetHeight();
    
    int scale = 30;
    int w = ww / scale;
    int h = wh / scale;
    float timef = ofGetElapsedTimef();
    
    terrain.clear();
    
    for (int y = 0; y < h; y++){
        for (int x = 0; x < w; x++){
            
            float offsetX = 0;
            float offsetY = (x % 2 == 1)? 0.5: 0.0;
            
            float noise = ofNoise(x, y, 0, timef);
            float vx = (x + offsetX) * scale + scale * 0.5;
            float vy = noise * scale;
            float vz = (y + offsetY) * scale + scale * 0.5;
            float r = noise * 0.1;
            float g = noise * 0.3;
            float b = noise;
            terrain.addVertex(ofPoint(vx, vy, vz));
            terrain.addNormal(ofPoint(0, 0, 0));
            terrain.addColor(ofFloatColor(r, g, b));
            terrain.addTexCoord(ofVec2f((float)(x + offsetX) / (float)w, (float)(y + offsetY) / (float)h));
        }
    }
    
    for (unsigned int y = 0; y < h-1; y++) {
        for (unsigned int x = 0; x < w-1; x++) {
            
            int a = x+y*w;
            int b = (x+1)+y*w;
            int c = x+(y+1)*w;
            int d = (x+1)+(y+1)*w;
            
//            terrain.addIndex(a);
//            terrain.addIndex(b);
//            terrain.addIndex(c);
//            
//            terrain.addIndex(b);
//            terrain.addIndex(d);
//            terrain.addIndex(c);
            
            terrain.addIndex(c);
            terrain.addIndex(b);
            terrain.addIndex(a);
            
            terrain.addIndex(c);
            terrain.addIndex(d);
            terrain.addIndex(b);
        }
    }
    
    for(int i = 0; i < terrain.getIndices().size(); i += 3 ){
        
        const int a = terrain.getIndices()[i];
        const int b = terrain.getIndices()[i+1];
        const int c = terrain.getIndices()[i+2];
        
        ofVec3f e1 = terrain.getVertices()[a] - terrain.getVertices()[b];
        ofVec3f e2 = terrain.getVertices()[c] - terrain.getVertices()[b];
        ofVec3f normal = e2.cross(e1);
        
        terrain.getNormals()[a] += normal;
        terrain.getNormals()[b] += normal;
        terrain.getNormals()[c] += normal;
    }
    
    cam.begin();
    {
        ofPushMatrix();
        {
            if (ofGetKeyPressed()) {
                terrain.disableNormals();
            }
            else {
                terrain.enableNormals();
            }
            
            ofTranslate(-ww * 0.5, 0, wh * 0.5 - wh);
            ofSetColor(255);
            terrain.draw();
            
            ofSetColor(0, 0, 255);
            vector<ofMeshFace> faces = terrain.getUniqueFaces();
            ofMeshFace face;
            ofVec3f c, n;
            float normalSize = 30;
            for(unsigned int i = 0; i < faces.size(); i++){
                face = faces[i];
                c = calculateCenter(&face);
                n = face.getFaceNormal();
                ofDrawLine(c.x, c.y, c.z, c.x+n.x*normalSize, c.y+n.y*normalSize, c.z+n.z*normalSize);
            }
        }
        ofPopMatrix();
    }
    cam.end();
    
}

//--------------------------------------------------------------
ofVec3f ofApp::calculateCenter(ofMeshFace *face) {
    int lastPointIndex = 3;
    ofVec3f result;
    for (unsigned int i=0; i < 3; i++){
        result += face->getVertex(i);
    }
    result /= lastPointIndex;
    return result;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(key == 'f'){
        ofToggleFullscreen();
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