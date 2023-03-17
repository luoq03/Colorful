# Series 1

## Series 1 was the first project where I started thinking about combining color and graphics. I saw an interesting base code on a website and modified it, adding fun and colorful mouse interactions and music to try to create a multiplicity of colors. I tried to emulate the example by adding a base image after the generated graphics, but it seemed to conflict with the previous code, causing the screen to go black. Overall it was very inspiring to me and made me more interested in creative programming.

<img width="200" alt="截屏2023-03-17 14 23 42" src="https://user-images.githubusercontent.com/57748663/225968311-93c46573-6ea9-42d2-9b75-72026c8535e2.png">

## **code comments**

>include "ofApp.h"
void ofApp::setup(){

// load the sound file
 
>mySound.load("music.mp3");

// set the background color to black

>ofSetBackgroundColor(0, 0, 0);

// set the initial hue value to 0

>hue = 0;

// set the frame rate to 60 fps
    
> ofSetFrameRate(60);
   
// set the window title to "openframeworks"

> ofSetWindowTitle("openframeworks");

// set the background color to a light gray

> ofBackground(239);

// set the line width to 2 pixels

> ofSetLineWidth(2);}


>void ofApp::update(){

// loop through all the 'particle' objects in the 'particles' vector and instruct each one to 'update' itself

>for (int i=0; i<particles.size();i++){
particles[i].update();
}

// seed the random number generator with a fixed value

>ofSeedRandom(39);
}

>void ofApp::draw(){

// set the drawing color to white

>ofSetColor(255);

// loop through all the 'particle' objects in the 'particles' vector and instruct each one to 'draw' itself

>for (int i=0; i<particles.size();i++){
        particles[i].draw();
    }

// define a list of colors

>vector<ofColor> color_list;

// define a list of hexadecimal values

>vector<int> hex_list = { 0x00f6fe, 0xc6e2ff, 0xB55A30, 0x065535, 0x896DDE };

// loop through the hexadecimal values and convert them to RGB colors

>for (auto hex : hex_list) {
        ofColor color;
        color.setHex(hex);
        color_list.push_back(color);
    }
    
// translate the coordinate system to the center of the screen
    
>ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
    
// loop through 200 iterations
    
>for (int k = 0; k < 200; k++) {

// generate a random seed value for the Perlin noise function

>auto noise_seed = glm::vec2(ofRandom(3000), ofRandom(3000));
        
// create a mesh object
        
>ofMesh mesh;
        
// define vectors to store the vertices for the left and right sides of the mesh

>vector<glm::vec3> right, left;

// define a vector to store the vertices for the frame of the mesh

 >vector<glm::vec3> frame;
        
// initialize variables to store the last location and angle
        
 >glm::vec3 last_location;
        
 float last_theta;
        
// loop through 50 iterations
       
 >for (int i = 0; i < 50; i++) {
          
// calculate the current location using Perlin noise
            
>auto location = glm::vec3(ofMap(ofNoise(noise_seed.x, (ofGetFrameNum() + i) * 0.0035), 0, 1, -350, 350), 
 
 ofMap(ofNoise(noise_seed.y, (ofGetFrameNum() + i) * 0.0035), 0, 1, -350, 350), 0);
            
 // calculate the next location using Perlin noise
           
 >auto next = glm::vec3(ofMap(ofNoise(noise_seed.x, (ofGetFrameNum() + i + 1) * 0.0035), 0, 1, -350, 350),
                               
 ofMap(ofNoise(noise_seed.y, (ofGetFrameNum() + i + 1) * 0.0035), 0, 1, -350, 350), 0);
        
// calculate the direction of the line segment
        
 >auto direction = next - location;
 auto theta = atan2(direction.y, direction.x);
        
// calculate the left and right points of the line segment
        
>right.push_back(location + glm::vec3(ofMap(i, 0, 25, 0, 8) * cos(theta + PI * 0.5),
                                             ofMap(i, 0, 25, 0, 8) * sin(theta + PI * 0.5), 0));

 left.push_back(location + glm::vec3(ofMap(i, 0, 25, 0, 8) * cos(theta - PI * 0.5),
                                            ofMap(i, 0, 25, 0, 8) * cos(theta - PI * 0.5), 0));
        
// store the last location and theta for later use
        
>last_location = location;
        
 last_theta = theta;
    }
    
// add the left and right points to the mesh
   
 >for (int i = 0; i < right.size(); i++) {
        mesh.addVertex(left[i]);
        mesh.addVertex(right[i]);
    }
    
// add the indices of the mesh triangles
    
>for (int i = 0; i < mesh.getNumVertices() - 2; i += 2) {
        mesh.addIndex(i + 0);
        mesh.addIndex(i + 1);
        mesh.addIndex(i + 3);
        mesh.addIndex(i + 0);
        mesh.addIndex(i + 2);
        mesh.addIndex(i + 3);
    }
    
// add the last location to the mesh
    
>mesh.addVertex(last_location);
    int index = mesh.getNumVertices();
    
// add the points around the last location to the mesh
    
>for (auto theta = last_theta - PI * 0.5; theta <= last_theta + PI * 0.5; theta += PI / 20) {
        mesh.addVertex(last_location + glm::vec3(8 * cos(theta), 8 * sin(theta), 0));
        frame.push_back(last_location + glm::vec3(8 * cos(theta), 8 * sin(theta), 0));
    }
   
>void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(0);
    mySound.load("sound.wav"); // Load a sound file into the program
}

// Call the update() function for each particle object in the 'particles' vector

>void ofApp::update(){
    for (int i = 0; i < particles.size(); i++) {
        particles[i].update(); 
    }
}

// Call the draw() function for each particle object in the 'particles' vector

>void ofApp::draw(){
    for (int i = 0; i < particles.size(); i++) {
        particles[i].draw(); 
    }
    
// Define a mesh object to store and draw shapes
    
>ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    int index = 0;
    
// For each vertex in the mesh, add a series of indices to connect the vertices together
    
 >for (int i = index; i < mesh.getNumVertices() - 1; i++) {
        mesh.addIndex(index); mesh.addIndex(i + 0); mesh.addIndex(i + 1);
    }
    
// Set the color of the mesh to a random color from a list
    
>ofSetColor(color_list[(int)ofRandom(color_list.size())]);
 
// Draw the mesh object   
 
>mesh.draw(); 
    
// Set the color of the following shapes to a light grey color
    
>ofSetColor(239);
    ofNoFill();
    ofBeginShape();
    ofVertices(frame);
    reverse(right.begin(), right.end());
    ofVertices(right);
    ofVertices(left);
    ofEndShape();
}
 
 // Play the sound file when the 'p' key is pressed

 >void ofApp::keyPressed(int key){
    if(key == 'p'){
        mySound.play(); 
    }

 // Toggle full-screen mode when the 'f' or 'F' key is pressed   
 
 >switch (key) {
        case 'f':
        case 'F':
            ofToggleFullscreen(); 
            break;
        default:
            break;
    }
}


>void ofApp::mouseMoved(int x, int y ){
}


>void ofApp::mouseDragged(int x, int y, int button){
    // This function is called when the mouse is clicked and dragged
    // Create a new particle object with the current mouse position and a random hue value
    particle newParticle( mouseX, mouseY , hue );
    // Add the new particle object to the 'particles' vector
    particles.push_back(newParticle);
}


>void ofApp::mousePressed(int x, int y, int button){
    hue = ofRandom( 255); // Pick a random hue value when the mouse is pressed
}

>particle::particle(int startX, int startY, int hue){
    // Constructor routine for particle object, called when we make a new object of our particle class defined in the header
    // Initializes the particle's starting position, force, direction, size and color
    position = glm::vec2(startX, startY); // particle's starting position in 2D space
    force = glm::vec2(0, 0.02); // particle's force in x,y direction
    direction = glm::vec2( ofRandom( -2.0, 2.0), ofRandom( -2.0, 2.0) ); // particle's direction with random x,y values within a range
    size = 30; // particle's initial size
    color.setHsb(hue,  255,  255, 200); // particle's initial color, set using hue value and alpha value
}

>particle::~particle(){
    // Destructor
    // Not doing anything in this code, can be used to deallocate resources if needed
}

>void particle::update(){
    // Update the particle's position and direction based on its current force
    position += direction ; // increment the particle's position based on its direction
    direction += force; // update the particle's direction based on its force
    
// Gradually decrease the particle's size and hue brightness
    
>if (size > 1){
        size -=0.07; // decrease the particle's size
    }
    float brightness = color.getBrightness(); // get the current brightness of the particle's color
    float myHue = color.getHue(); // get the current hue of the particle's color
    
>if (brightness >20){ // if the brightness is greater than 20
        color.setHue( myHue -=0.5 ); // decrease the particle's hue by 0.5
    }
}

// Draw the particle with its current color and size

>void particle::draw(){
   
ofSetColor(color); // set the color for the particle
ofDrawCircle(position, size); // draw the particle as a circle using its position and size
}

Reference：https://junkiyoshi.com/
           
https://openframeworks.cc/learning/04_sound/play_a_sound/（sound）
 
https://pixabay.com/sound-effects/search/mp3/(sound)
 
https://www.color-hex.com/(hex color sheet)
