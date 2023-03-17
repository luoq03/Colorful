#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    bikers.load("picture1.jpg");
    myModel.loadModel("ball.dae", 200);
   myModel.setPosition(ofGetWidth() * 0.45, (float)ofGetHeight() * 0.5 , 0);
    myModel.setScale(0.7, 0.7, 0.7);
    mySound.load("music.mp3");
    mySound.play();
    hue = 0;
    ofSetFrameRate(60);
        ofSetWindowTitle("openFrameworks");
     
    ofBackground( 240);
        ofNoFill();
        ofEnableDepthTest();
        ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_MULTIPLY);
        
        ofColor color;
        vector<int> hex_list = { 0xE7197E, 0xf07800, 0x00A170, 0xB55A30, 0x0072B5,0xA0DAA9 };
        for (auto hex : hex_list) {
     
            color.setHex(hex);
            this->base_color_list.push_back(color);
        }
     
        for (int x = -300; x <= 300; x += 2) {
     
            this->base_location_list.push_back(glm::vec3(x, -300, -300));
            this->base_location_list.push_back(glm::vec3(x, -300, 300));
            this->base_location_list.push_back(glm::vec3(x, 300, -300));
            this->base_location_list.push_back(glm::vec3(x, 300, 300));
        }
     
        for (int y = -300; y <= 300; y += 2) {
     
            this->base_location_list.push_back(glm::vec3(-300, y, -300));
            this->base_location_list.push_back(glm::vec3(-300, y, 300));
            this->base_location_list.push_back(glm::vec3(300, y, -300));
            this->base_location_list.push_back(glm::vec3(300, y, 300));
        }
     
        for (int z = -300; z <= 300; z += 2) {
     
            this->base_location_list.push_back(glm::vec3(-300, -300, z));
            this->base_location_list.push_back(glm::vec3(-300, 300, z));
            this->base_location_list.push_back(glm::vec3(300, -300, z));
            this->base_location_list.push_back(glm::vec3(300, 300, z));
        }
}

//--------------------------------------------------------------
void ofApp::update(){
    // look through all the 'particle' objects in the 'particles' vector and instruct each one to 'update' itself
    for (int i=0; i<particles.size();i++){
        particles[i].update();
    }
    int radius = 10;
        while (this->log_list.size() < 3000) {
     
            int font_location_index = ofRandom(this->base_location_list.size());
            vector<glm::vec3> log;
            log.push_back(this->base_location_list[font_location_index]);
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
     
            auto deg = ofMap(ofNoise(glm::vec4(this->log_list[i].back() * 0.0035, ofGetFrameNum() * 0.006)), 0, 1, -360, 360);
            auto theta = ofMap(ofNoise(glm::vec4(this->log_list[i].back() * 0.0035, (ofGetFrameNum() + 10000) * 0.006)), 0, 1, -360, 360);
            this->log_list[i].push_back(this->log_list[i].back() + glm::vec3(radius * cos(deg * DEG_TO_RAD) * sin(theta * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD) * sin(theta * DEG_TO_RAD), radius * cos(theta * DEG_TO_RAD)));
            while (this->log_list[i].size() > 100) {
     
                this->log_list[i].erase(this->log_list[i].begin());
            }
        }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //ofBackground(ofColor::black);
    
    // draw the original image
    
    bikers.draw(0, 0);
    bikeIcon.draw(0, 0, 1024, 768);
   // myModel.drawVertices();
    this->cam.begin();
        ofRotateY(ofGetFrameNum() * 2);
     
        for (int i = 0; i < this->log_list.size(); i++) {
     
            ofSetColor(this->color_list[i]);
     
            if (this->life_list[i] > 50) {
     
                ofSetLineWidth(3);
            }
            else {
     
                ofSetLineWidth(ofMap(this->life_list[i], 0, 50, 0, 10));
            }
     
            ofBeginShape();
            ofVertices(this->log_list[i]);
            ofEndShape();
        }
     
        this->cam.end();
    ofSetColor(255);
    for (int i=0; i<particles.size();i++){
        particles[i].draw();
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
        
//        glm::vec3 modelPosition(ofGetWidth() * 0.6, (float)ofGetHeight() * 0.7, 0);
//
//
//        switch (key) {
//            case '1':
//                model.loadModel("ball.dae");
//                model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
//                model.setScale(0.5, 0.5, 0.5);
//                ofEnableSeparateSpecularLight();
//                break;
//            case '2':
//                model.loadModel("ball3.dae");
//                model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
//                model.setScale(0.5, 0.5, 0.5);
//                ofEnableSeparateSpecularLight();
//                break;
//
//    }
        
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
