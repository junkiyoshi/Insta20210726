#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();

	this->font_size = 80;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(90);

	string word = "ABCDEFGHEJKLMNOPQRSTUVWXYZ!";
	int sample_count = 100;
	vector<glm::vec3> base_location;
	for (int y = -500; y <= 500; y += 100) {

		base_location.push_back(glm::vec3(0, y, 0));
	}

	for (int k = 0; k < base_location.size(); k++) {

		auto noise_param = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
		for (int i = 0; i < 24; i++) {

			auto rotation = glm::rotate(glm::mat4(), (i * 15.f) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
			auto noise_location = glm::vec4(this->font_size * 0.5, base_location[k].y + this->font_size * -0.5, 320, 0) * rotation;

			int word_index = (int)ofMap(ofNoise(noise_location.x * 0.0001, noise_location.y * 0.0001 - ofGetFrameNum() * 0.005, noise_location.z * 0.0001), 0, 1, 0, word.size() * 2) % word.size();

			ofPath chara_path = this->font.getCharacterAsPoints(word[word_index], true, false);
			vector<ofPolyline> outline = chara_path.getOutline();

			ofFill();
			ofSetColor(239);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				if (outline_index != 0) { ofNextContour(true); }

				auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
				for (auto& vertex : vertices) {

					auto location = vertex - glm::vec3(this->font_size * 0.5, this->font_size * -0.5, 350);
					auto rotation = glm::rotate(glm::mat4(), (i * 15.f) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
					location = glm::vec4(location, 0) * rotation;
					location += base_location[k];

					ofVertex(location);
				}
			}
			ofEndShape();

			ofNoFill();
			ofSetColor(39);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				if (outline_index != 0) { ofNextContour(true); }

				auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
				for (auto& vertex : vertices) {

					auto location = vertex - glm::vec3(this->font_size * 0.5, this->font_size * -0.5, 350);
					auto rotation = glm::rotate(glm::mat4(), (i * 15.f) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
					location = glm::vec4(location, 0) * rotation;
					location += base_location[k];

					ofVertex(location);
				}
			}
			ofEndShape();
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}