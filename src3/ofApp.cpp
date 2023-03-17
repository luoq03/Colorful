#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    mySound.load("music.mp3");
    mySound.setVolume(1.00f);
    mySound.play();
       hue = 0;
    ofSetFrameRate(30);
        ofSetWindowTitle("openFrameworks");
     
        ofBackground(239);
        ofSetLineWidth(2);
        ofNoFill();
        ofEnableDepthTest();
        ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_MULTIPLY);
     
        int radius = 250;
        ofIcoSpherePrimitive ico_sphere;
        ico_sphere = ofIcoSpherePrimitive(radius, 7);
     
        for (auto& triangle : ico_sphere.getMesh().getUniqueFaces()) {
     
            glm::vec3 avg = (triangle.getVertex(0) + triangle.getVertex(1) + triangle.getVertex(2)) / 3;
            this->location_list.push_back(avg);
        }
     
        ofColor color;
        vector<int> hex_list = { 0xef476f, 0xffd166, 0x06d6a0, 0x118ab2, 0x073b4c };
        for (auto hex : hex_list) {
     
            color.setHex(hex);
            this->base_color_list.push_back(color);
        }
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSoundUpdate();
    // look through all the 'particle' objects in the 'particles' vector and instruct each one to 'update' itself
    for (int i=0; i<particles.size();i++){
        particles[i].update();
    }
    while (this->log_list.size() < 2000) {
     
            int font_location_index = ofRandom(this->location_list.size());
            vector<glm::vec3> log;
            log.push_back(this->location_list[font_location_index]);
            this->log_list.push_back(log);
            this->color_list.push_back(this->base_color_list[(int)ofRandom(this->base_color_list.size())]);
            this->life_list.push_back(ofRandom(60, 120));
        }
     
        for (int i = this->log_list.size() - 1; i >= 0; i--) {
     
            this->life_list[i] -= 1;
            if (this->life_list[i] < 0) {
     
                this->log_list.erase(this->log_list.begin() + i);
                this->color_list.erase(this->color_list.begin() + i);
                this->life_list.erase(this->life_list.begin() + i);
     
                continue;
            }
     
            int radius = 5;
            auto deg = ofMap(ofNoise(glm::vec4(this->log_list[i].back() * 0.003, ofGetFrameNum() * 0.006)), 0, 1, -360, 360);
            auto theta = ofMap(ofNoise(glm::vec4(this->log_list[i].back() * 0.003, (ofGetFrameNum() + 10000) * 0.006)), 0, 1, -360, 360);
            this->log_list[i].push_back(this->log_list[i].back() + glm::vec3(radius * cos(deg * DEG_TO_RAD) * sin(theta * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD) * sin(theta * DEG_TO_RAD), radius * cos(theta * DEG_TO_RAD)));
            while (this->log_list[i].size() > 100) {
     
                this->log_list[i].erase(this->log_list[i].begin());
            }
        }
}

//--------------------------------------------------------------
void ofApp::draw(){
        ofSetColor(255);
    
    // look through all the 'particle' objects in the 'particles' vector and instruct each one to 'draw' itself
    for (int i=0; i<particles.size();i++){
        particles[i].draw();
    }
    this->cam.begin();
        ofRotateY(ofGetFrameNum() * 0.2);
     
        for (int i = 0; i < this->log_list.size(); i++) {
     
            ofSetColor(this->color_list[i]);
     
            if (this->life_list[i] > 50) {
     
                ofSetLineWidth(3);
            }
            else {
     
                ofSetLineWidth(ofMap(this->life_list[i], 0, 60, 0, 10));
            }
     
            ofBeginShape();
            ofVertices(this->log_list[i]);
            ofEndShape();
        }
     
        ofSetColor(ofRandom(180, 240));
        ofDrawSphere(200);
     
        this->cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'p'){
           mySound.play();
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
