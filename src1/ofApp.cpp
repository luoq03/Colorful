#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    mySound.load("music.mp3");
    ofSetBackgroundColor(0, 0, 0);
    hue = 0;
    ofSetFrameRate(60);
        ofSetWindowTitle("openframeworks");
     
        ofBackground(239);
        ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update(){
    // look through all the 'particle' objects in the 'particles' vector and instruct each one to 'update' itself
    for (int i=0; i<particles.size();i++){
        particles[i].update();
    }
    ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    
    // look through all the 'particle' objects in the 'particles' vector and instruct each one to 'draw' itself
    for (int i=0; i<particles.size();i++){
        particles[i].draw();
    }
        ofColor color;
            vector<ofColor> color_list;
            vector<int> hex_list = { 0x00f6fe, 0xc6e2ff, 0xB55A30, 0x065535, 0x896DDE };
            for (auto hex : hex_list) {
         
                color.setHex(hex);
                color_list.push_back(color);
            }
         
            ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
            
            for (int k = 0; k < 200; k++) {
         
                auto noise_seed = glm::vec2(ofRandom(3000), ofRandom(3000));
         
                ofMesh mesh;
                vector<glm::vec3> right, left, frame;
         
                glm::vec3 last_location;
                float last_theta;
         
                for (int i = 0; i < 50; i++) {
         
                    auto location = glm::vec3(ofMap(ofNoise(noise_seed.x, (ofGetFrameNum() + i) * 0.0035), 0, 1, -350, 350), ofMap(ofNoise(noise_seed.y, (ofGetFrameNum() + i) * 0.0035), 0, 1, -350, 350), 0);
                    auto next = glm::vec3(ofMap(ofNoise(noise_seed.x, (ofGetFrameNum() + i + 1) * 0.0035), 0, 1, -350, 350), ofMap(ofNoise(noise_seed.y, (ofGetFrameNum() + i + 1) * 0.0035), 0, 1, -350, 350), 0);
         
                    auto direction = next - location;
                    auto theta = atan2(direction.y, direction.x);
         
                    right.push_back(location + glm::vec3(ofMap(i, 0, 25, 0, 8) * cos(theta + PI * 0.5), ofMap(i, 0, 25, 0, 8) * sin(theta + PI * 0.5), 0));
                    left.push_back(location + glm::vec3(ofMap(i, 0, 25, 0, 8) * cos(theta - PI * 0.5), ofMap(i, 0, 25, 0, 8) * cos(theta - PI * 0.5), 0));
         
                    last_location = location;
                    last_theta = theta;
                }
         
                for (int i = 0; i < right.size(); i++) {
         
                    mesh.addVertex(left[i]);
                    mesh.addVertex(right[i]);
                }
         
         
                for (int i = 0; i < mesh.getNumVertices() - 2; i += 2) {
         
                    mesh.addIndex(i + 0); mesh.addIndex(i + 1); mesh.addIndex(i + 3);
                    mesh.addIndex(i + 0); mesh.addIndex(i + 2); mesh.addIndex(i + 3);
                }
         
                mesh.addVertex(last_location);
                int index = mesh.getNumVertices();
                for (auto theta = last_theta - PI * 0.5; theta <= last_theta + PI * 0.5; theta += PI / 20) {
         
                    mesh.addVertex(last_location + glm::vec3(8 * cos(theta), 8 * sin(theta), 0));
                    frame.push_back(last_location + glm::vec3(8 * cos(theta), 8 * sin(theta), 0));
                }
         
                for (int i = index; i < mesh.getNumVertices() - 1; i++) {
         
                    mesh.addIndex(index); mesh.addIndex(i + 0); mesh.addIndex(i + 1);
                }
         
                ofSetColor(color_list[(int)ofRandom(color_list.size())]);
                mesh.draw();
         
                ofSetColor(239);
                ofNoFill();
                ofBeginShape();
                ofVertices(frame);
                reverse(right.begin(), right.end());
                ofVertices(right);
                ofVertices(left);
                ofEndShape();
            
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'p'){
            mySound.play();
        }
    switch (key) {
        case 'f':
        case 'F':
            ofToggleFullscreen();
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    // when the mouse is clicked and dragged make a new particle object
    // and set it's initial x,y position to the mouse x,y position by
    // passing the mouseX and mouseY to the constructor routine as parameters
    particle newParticle( mouseX, mouseY , hue );
    // push the new particle we just made onto the back of the vector 'particles'
    particles.push_back(newParticle);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
     hue = ofRandom( 255); // pick random hue on each button press
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}


//--------------------------------------------------------------

particle::particle(int startX, int startY, int hue){
    // this is the constructor routine, called when we make a new object of our particle class defined in the header
    position = glm::vec2(startX, startY);
    force = glm::vec2(0, 0.02);
    direction = glm::vec2( ofRandom( -2.0, 2.0), ofRandom( -2.0, 2.0) );
    size = 30;
    color.setHsb(hue,  255,  255, 200);
}
//--------------------------------------------------------------

particle::~particle(){
    // destructor
}
//--------------------------------------------------------------

void particle::update(){
    // update the particle x,y position by incrementing each by the velocity vx and vy
    position += direction ;
    direction +=  force;
        if (size > 1){
            size -=0.07;
        }
        float brightness = color.getBrightness();
        float myHue = color.getHue();
    
        if (brightness >20){
           // color.setBrightness( brightness -=0.5 );
            color.setHue( myHue -=0.5 );
    
        }
}

//--------------------------------------------------------------

void particle::draw(){
    ofSetColor(color);
    ofDrawCircle(position, size);
}
