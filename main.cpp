#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <math.h>

// Global variables for animation and interaction
int animationStatus = 1;
float mosquitoX = 0;
float mosquitoY = 0;
float humanX = 0;
float humanY = 0;
float cloudX1 = 200, cloudX2 = 400, cloudX3 = 600, cloudX4 = 800;
float sunY = 700;
float waterLevel = 0;
int sceneState = 1; // 1-9: Number scenes, a,e,i,o,u,r: Letter scenes
int selectedTip = 0;
bool isDay = true;
float flowerAngle = 0;

// Rain variables
struct RainDrop {
	float x, y;
	float speed;
	float size;
	float brightness;
	bool isSplashing;
	float splashTime;
};

struct Splash {
	float x, y;
	float size;
	float alpha;
	float time;
};

RainDrop raindrops[200];  // Increased number of raindrops
Splash splashes[50];      // Added splash effects
float rainIntensity = 1.0;
float windEffect = 0.0;

// Men wacking variables
float man1X = 200, man2X = 400;
float wackAngle = 0;

// Birds variables
struct Bird {
	float x, y;
	float speed;
	float wingAngle;
};
Bird birds[3];

// Cows variables
struct Cow {
	float x, y;
	float mouthAngle;
};
Cow cows[4];

// People going home variables
struct Person {
	float x, y;
	float speed;
};
Person people[5];

// Scene 6: Fish swimming
struct Fish {
	float x, y;
	float speed;
	float tailAngle;
};
Fish fishes[6];

// Scene 7: Butterflies
struct Butterfly {
	float x, y;
	float speed;
	float wingAngle;
};
Butterfly butterflies[7];

// Scene 8: Cars moving
struct Car {
	float x, y;
	float speed;
	float wheelAngle;
};
Car cars[8];

// Scene 9: Stars twinkling
struct Star {
	float x, y;
	float brightness;
	float twinkleSpeed;
};
Star stars[50];

// Scene A: Airplane flying
struct Airplane {
	float x, y;
	float speed;
	float angle;
};
Airplane airplane;

// Scene E: Elephant walking
struct Elephant {
	float x, y;
	float speed;
	float trunkAngle;
};
Elephant elephant;

// Scene I: Ice skating
struct Skater {
	float x, y;
	float speed;
	float spinAngle;
};
Skater skater;

// Scene O: Ocean waves
struct Wave {
	float x, y;
	float amplitude;
	float speed;
};
Wave waves[5];

// Scene U: Umbrella moving
struct Umbrella {
	float x, y;
	float angle;
	float openAmount;
};
Umbrella umbrella;

// Scene R: Robot dancing
struct Robot {
	float x, y;
	float armAngle;
	float legAngle;
	float headAngle;
};
Robot robot;

// Add to global variables section
float dayNightTransition = 1.0; // 1.0 for day, 0.0 for night
float starBrightness[50];
float moonPhase = 0.0;
float sunPosition = 0.0; // 0.0 to 1.0 for sun/moon position
float ambientLight = 1.0;
float cloudOpacity = 1.0;
float groundBrightness = 1.0;

// Function declarations
void drawMosquito(float x, float y);
void drawHuman(float x, float y);
void drawTree(float x, float y);
void drawHouse();
void drawWaterContainer();
void drawPreventionTips();
void drawSymptoms();
void drawBackground();
void drawText(const char* text, float x, float y);
void drawCloud(float x, float y);
void drawSun();
void drawGrass();
void drawFlower(float x, float y);
void drawMoon();
void drawStars();
void drawRain();
void drawManWacking(float x, float y);
void drawBird(float x, float y, float wingAngle);
void drawCow(float x, float y, float mouthAngle);
void drawPerson(float x, float y);
void drawFish(float x, float y, float tailAngle);
void drawButterfly(float x, float y, float wingAngle);
void drawCar(float x, float y, float wheelAngle);
void drawStar(float x, float y, float brightness);
void drawAirplane(float x, float y, float angle);
void drawElephant(float x, float y, float trunkAngle);
void drawSkater(float x, float y, float spinAngle);
void drawWave(float x, float y, float amplitude);
void drawUmbrella(float x, float y, float angle, float openAmount);
void drawRobot(float x, float y, float armAngle, float legAngle, float headAngle);

void DrawCircle(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_TRIANGLE_FAN);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component

		glVertex2f(x + cx, y + cy);//output vertex

	}
	glEnd();
}

void drawMosquito(float x, float y) {
	glPushMatrix();
	glTranslatef(x, y, 0);

	// Mosquito body
	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, 10);
	glEnd();

	// Wings with animation
	float wingAngle = sin(glutGet(GLUT_ELAPSED_TIME) * 0.01) * 30;
	glPushMatrix();
	glRotatef(wingAngle, 0, 0, 1);
	glColor3f(0.3, 0.3, 0.3);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 5);
	glVertex2f(-5, 8);
	glVertex2f(0, 7);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-wingAngle, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 5);
	glVertex2f(5, 8);
	glVertex2f(0, 7);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}

void drawHuman(float x, float y) {
	glPushMatrix();
	glTranslatef(x, y, 0);

	// Head
	glColor3f(0.9, 0.8, 0.7);
	DrawCircle(0, 0, 10, 20);

	// Body
	glBegin(GL_LINES);
	glVertex2f(0, -10);
	glVertex2f(0, -30);
	glEnd();

	// Arms
	glBegin(GL_LINES);
	glVertex2f(0, -20);
	glVertex2f(-15, -25);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(0, -20);
	glVertex2f(15, -25);
	glEnd();

	// Legs
	glBegin(GL_LINES);
	glVertex2f(0, -30);
	glVertex2f(-10, -40);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(0, -30);
	glVertex2f(10, -40);
	glEnd();

	glPopMatrix();
}

void drawTree(float x, float y) {
	glPushMatrix();
	glTranslatef(x, y, 0);

	// Trunk
	glColor3f(0.6, 0.4, 0.2);
	glBegin(GL_POLYGON);
	glVertex2f(-5, 0);
	glVertex2f(5, 0);
	glVertex2f(5, 40);
	glVertex2f(-5, 40);
	glEnd();

	// Main foliage
	glColor3f(0.0, 0.7, 0.1);
	DrawCircle(0, 50, 20, 20);
	DrawCircle(-15, 45, 15, 20);
	DrawCircle(15, 45, 15, 20);
	DrawCircle(0, 35, 15, 20);

	// Add some flowers at the base
	drawFlower(-10, 0);
	drawFlower(10, 0);

	glPopMatrix();
}

void drawWaterContainer() {
	// Container
	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_POLYGON);
	glVertex2f(100, 100);
	glVertex2f(150, 100);
	glVertex2f(150, 150);
	glVertex2f(100, 150);
	glEnd();

	// Water with animated ripple effect
	glColor3f(0.2, 0.4, 0.8);
	glBegin(GL_POLYGON);
	glVertex2f(105, 105);
	glVertex2f(145, 105);
	glVertex2f(145, 145);
	glVertex2f(105, 145);
	glEnd();

	// Animated ripples
	float time = glutGet(GLUT_ELAPSED_TIME) * 0.001;
	glColor3f(0.3, 0.5, 0.9);
	DrawCircle(125, 125, 5 + sin(time * 2) * 2, 20);
	DrawCircle(125, 125, 3 + sin(time * 2) * 1, 20);
}

void drawPreventionTips() {
	glColor3f(1.0, 1.0, 1.0);
	drawText("Dengue Prevention Tips:", 50, 700);
	drawText("1. Remove standing water", 50, 650);
	drawText("2. Use mosquito nets", 50, 600);
	drawText("3. Wear protective clothing", 50, 550);
	drawText("4. Use mosquito repellent", 50, 500);
}

void drawSymptoms() {
	glColor3f(1.0, 1.0, 1.0);
	drawText("Dengue Symptoms:", 50, 700);
	drawText("1. High fever", 50, 650);
	drawText("2. Severe headache", 50, 600);
	drawText("3. Joint and muscle pain", 50, 550);
	drawText("4. Nausea and vomiting", 50, 500);
}

void drawCloud(float x, float y) {
	glColor3f(1.0, 1.0, 1.0);
	DrawCircle(x, y, 20, 20);
	DrawCircle(x + 15, y, 15, 20);
	DrawCircle(x + 30, y, 20, 20);
	DrawCircle(x + 15, y + 10, 15, 20);
}

void drawSun() {
	// Sun rays
	glColor3f(1.0, 0.9, 0.0);
	for(int i = 0; i < 360; i += 45) {
		float angle = i * 3.14159 / 180;
		glBegin(GL_LINES);
		glVertex2f(1000 + 40 * cos(angle), 700 + 40 * sin(angle));
		glVertex2f(1000 + 60 * cos(angle), 700 + 60 * sin(angle));
		glEnd();
	}
	// Sun body
	DrawCircle(1000, 700, 40, 20);
}

void drawGrass() {
	glColor3f(0.0, 0.8, 0.0);
	for(int i = 0; i < 1200; i += 20) {
		glBegin(GL_TRIANGLES);
		glVertex2f(i, 200);
		glVertex2f(i + 10, 220);
		glVertex2f(i + 20, 200);
		glEnd();
	}
}

void drawFlower(float x, float y) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	glRotatef(flowerAngle, 0, 0, 1);

	// Petals
	glColor3f(1.0, 0.4, 0.7);
	for(int i = 0; i < 360; i += 60) {
		float angle = i * 3.14159 / 180;
		DrawCircle(5 * cos(angle), 5 * sin(angle), 3, 10);
	}

	// Center
	glColor3f(1.0, 1.0, 0.0);
	DrawCircle(0, 0, 3, 10);

	glPopMatrix();

	// Stem
	glColor3f(0.0, 0.6, 0.0);
	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(x, y - 15);
	glEnd();
}

void drawMoon() {
	glColor3f(0.9, 0.9, 0.9);
	DrawCircle(1000, 700, 40, 20);
	// Moon craters
	glColor3f(0.8, 0.8, 0.8);
	DrawCircle(990, 710, 5, 10);
	DrawCircle(1010, 690, 7, 10);
	DrawCircle(1000, 680, 4, 10);
}

void drawStars() {
	glColor3f(1.0, 1.0, 1.0);
	for(int i = 0; i < 50; i++) {
		float x = rand() % 1200;
		float y = rand() % 800;
		float size = 1 + (rand() % 3);
		glPointSize(size);
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
	}
}

void drawRainDrop(float x, float y, float size, float brightness) {
	glColor4f(0.7, 0.7, 1.0, brightness);
	glLineWidth(size);
	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(x - windEffect * 2, y - 10);
	glEnd();
}

void drawSplash(float x, float y, float size, float alpha) {
	glColor4f(0.7, 0.7, 1.0, alpha);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for(int i = 0; i <= 360; i += 10) {
		float angle = i * 3.14159 / 180;
		glVertex2f(x + cos(angle) * size, y + sin(angle) * size);
	}
	glEnd();
}

void drawRain() {
	// Draw raindrops
	for(int i = 0; i < 200; i++) {
		if (!raindrops[i].isSplashing) {
			drawRainDrop(raindrops[i].x, raindrops[i].y,
						raindrops[i].size, raindrops[i].brightness);
		}
	}

	// Draw splashes
	for(int i = 0; i < 50; i++) {
		if (splashes[i].alpha > 0) {
			drawSplash(splashes[i].x, splashes[i].y,
					  splashes[i].size, splashes[i].alpha);
		}
	}

	// Draw rain mist
	glColor4f(0.7, 0.7, 1.0, 0.1);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(1200, 0);
	glVertex2f(1200, 200);
	glVertex2f(0, 200);
	glEnd();
}

void drawManWacking(float x, float y) {
	glPushMatrix();
	glTranslatef(x, y, 0);

	// Body
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, 40);
	glEnd();

	// Head
	glColor3f(1.0, 0.8, 0.6);
	DrawCircle(0, 45, 10, 20);

	// Arms
	glBegin(GL_LINES);
	glVertex2f(0, 30);
	glVertex2f(-20, 20);
	glEnd();

	// Wacking arm
	glPushMatrix();
	glTranslatef(0, 30, 0);
	glRotatef(wackAngle, 0, 0, 1);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(30, 0);
	glEnd();
	glPopMatrix();

	// Legs
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(-10, -20);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(10, -20);
	glEnd();

	glPopMatrix();
}

void drawBird(float x, float y, float wingAngle) {
	glPushMatrix();
	glTranslatef(x, y, 0);

	// Body
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(20, 0);
	glEnd();

	// Wings
	glPushMatrix();
	glTranslatef(10, 0, 0);
	glRotatef(wingAngle, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(-10, 10);
	glVertex2f(0, 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 0, 0);
	glRotatef(-wingAngle, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(-10, -10);
	glVertex2f(0, -5);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}

void drawCow(float x, float y, float mouthAngle) {
	glPushMatrix();
	glTranslatef(x, y, 0);

	// Body
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_POLYGON);
	glVertex2f(-20, 0);
	glVertex2f(20, 0);
	glVertex2f(20, 30);
	glVertex2f(-20, 30);
	glEnd();

	// Head
	glBegin(GL_POLYGON);
	glVertex2f(20, 20);
	glVertex2f(40, 20);
	glVertex2f(40, 35);
	glVertex2f(20, 35);
	glEnd();

	// Mouth
	glPushMatrix();
	glTranslatef(40, 25, 0);
	glRotatef(mouthAngle, 0, 0, 1);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(10, 0);
	glEnd();
	glPopMatrix();

	// Legs
	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_LINES);
	glVertex2f(-15, 0);
	glVertex2f(-15, -20);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(15, 0);
	glVertex2f(15, -20);
	glEnd();

	glPopMatrix();
}

void drawPerson(float x, float y) {
	glPushMatrix();
	glTranslatef(x, y, 0);

	// Body
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, 40);
	glEnd();

	// Head
	glColor3f(1.0, 0.8, 0.6);
	DrawCircle(0, 45, 10, 20);

	// Arms
	glBegin(GL_LINES);
	glVertex2f(0, 30);
	glVertex2f(-15, 20);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(0, 30);
	glVertex2f(15, 20);
	glEnd();

	// Legs
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(-10, -20);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(10, -20);
	glEnd();

	glPopMatrix();
}

void drawFish(float x, float y, float tailAngle) {
	glPushMatrix();
	glTranslatef(x, y, 0);

	// Body
	glColor3f(1.0, 0.5, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(30, 0);
	glVertex2f(30, 10);
	glVertex2f(0, 10);
	glEnd();

	// Tail
	glPushMatrix();
	glTranslatef(0, 5, 0);
	glRotatef(tailAngle, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(-20, -10);
	glVertex2f(-20, 10);
	glEnd();
	glPopMatrix();

	// Eye
	glColor3f(0.0, 0.0, 0.0);
	DrawCircle(25, 5, 2, 10);

	glPopMatrix();
}

void drawButterfly(float x, float y, float wingAngle) {
	glPushMatrix();
	glTranslatef(x, y, 0);

	// Body
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, 20);
	glEnd();

	// Wings
	glColor3f(1.0, 0.4, 0.7);
	glPushMatrix();
	glRotatef(wingAngle, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 10);
	glVertex2f(-20, 0);
	glVertex2f(-20, 20);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-wingAngle, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 10);
	glVertex2f(20, 0);
	glVertex2f(20, 20);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}

void drawCar(float x, float y, float wheelAngle) {
	glPushMatrix();
	glTranslatef(x, y, 0);

	// Body
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(60, 0);
	glVertex2f(60, 30);
	glVertex2f(0, 30);
	glEnd();

	// Windows
	glColor3f(0.7, 0.7, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(10, 15);
	glVertex2f(50, 15);
	glVertex2f(50, 25);
	glVertex2f(10, 25);
	glEnd();

	// Wheels
	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();
	glTranslatef(15, 0, 0);
	glRotatef(wheelAngle, 0, 0, 1);
	DrawCircle(0, 0, 8, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(45, 0, 0);
	glRotatef(wheelAngle, 0, 0, 1);
	DrawCircle(0, 0, 8, 20);
	glPopMatrix();

	glPopMatrix();
}

void drawStar(float x, float y, float brightness) {
	glColor3f(brightness, brightness, brightness);
	glBegin(GL_POLYGON);
	for(int i = 0; i < 5; i++) {
		float angle = i * 72 * 3.14159 / 180;
		glVertex2f(x + 10 * cos(angle), y + 10 * sin(angle));
		angle += 36 * 3.14159 / 180;
		glVertex2f(x + 5 * cos(angle), y + 5 * sin(angle));
	}
	glEnd();
}

void drawAirplane(float x, float y, float angle) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	glRotatef(angle, 0, 0, 1);

	// Body
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(60, 0);
	glVertex2f(60, 10);
	glVertex2f(0, 10);
	glEnd();

	// Wings
	glBegin(GL_TRIANGLES);
	glVertex2f(20, 10);
	glVertex2f(40, 10);
	glVertex2f(30, 30);
	glEnd();

	// Tail
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 10);
	glVertex2f(20, 10);
	glVertex2f(10, 25);
	glEnd();

	glPopMatrix();
}

void drawElephant(float x, float y, float trunkAngle) {
	glPushMatrix();
	glTranslatef(x, y, 0);

	// Body
	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(40, 0);
	glVertex2f(40, 30);
	glVertex2f(0, 30);
	glEnd();

	// Head
	glBegin(GL_POLYGON);
	glVertex2f(40, 20);
	glVertex2f(60, 20);
	glVertex2f(60, 35);
	glVertex2f(40, 35);
	glEnd();

	// Trunk
	glPushMatrix();
	glTranslatef(60, 25, 0);
	glRotatef(trunkAngle, 0, 0, 1);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(20, 0);
	glEnd();
	glPopMatrix();

	// Legs
	glBegin(GL_LINES);
	glVertex2f(10, 0);
	glVertex2f(10, -20);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(30, 0);
	glVertex2f(30, -20);
	glEnd();

	glPopMatrix();
}

void drawSkater(float x, float y, float spinAngle) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	glRotatef(spinAngle, 0, 0, 1);

	// Body
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, 30);
	glEnd();

	// Head
	glColor3f(1.0, 0.8, 0.6);
	DrawCircle(0, 35, 8, 20);

	// Arms
	glBegin(GL_LINES);
	glVertex2f(0, 25);
	glVertex2f(-20, 15);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(0, 25);
	glVertex2f(20, 15);
	glEnd();

	// Skates
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(-10, -10);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(10, -10);
	glEnd();

	glPopMatrix();
}

void drawWave(float x, float y, float amplitude) {
	glColor3f(0.0, 0.0, 0.8);
	glBegin(GL_LINE_STRIP);
	for(int i = 0; i < 100; i++) {
		float waveX = x + i * 5;
		float waveY = y + sin(i * 0.1) * amplitude;
		glVertex2f(waveX, waveY);
	}
	glEnd();
}

void drawUmbrella(float x, float y, float angle, float openAmount) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	glRotatef(angle, 0, 0, 1);

	// Handle
	glColor3f(0.5, 0.3, 0.1);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, 40);
	glEnd();

	// Canopy
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 40);
	for(int i = 0; i <= 360; i += 10) {
		float rad = i * 3.14159 / 180;
		glVertex2f(cos(rad) * 30 * openAmount, 40 + sin(rad) * 30 * openAmount);
	}
	glEnd();

	glPopMatrix();
}

void drawRobot(float x, float y, float armAngle, float legAngle, float headAngle) {
	glPushMatrix();
	glTranslatef(x, y, 0);

	// Body
	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_POLYGON);
	glVertex2f(-20, 0);
	glVertex2f(20, 0);
	glVertex2f(20, 40);
	glVertex2f(-20, 40);
	glEnd();

	// Head
	glPushMatrix();
	glTranslatef(0, 40, 0);
	glRotatef(headAngle, 0, 0, 1);
	glBegin(GL_POLYGON);
	glVertex2f(-15, 0);
	glVertex2f(15, 0);
	glVertex2f(15, 20);
	glVertex2f(-15, 20);
	glEnd();

	// Eyes
	glColor3f(1.0, 0.0, 0.0);
	DrawCircle(-5, 10, 3, 10);
	DrawCircle(5, 10, 3, 10);
	glPopMatrix();

	// Arms
	glPushMatrix();
	glTranslatef(-20, 30, 0);
	glRotatef(armAngle, 0, 0, 1);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(-20, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20, 30, 0);
	glRotatef(-armAngle, 0, 0, 1);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(20, 0);
	glEnd();
	glPopMatrix();

	// Legs
	glPushMatrix();
	glTranslatef(-10, 0, 0);
	glRotatef(legAngle, 0, 0, 1);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, -20);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 0, 0);
	glRotatef(-legAngle, 0, 0, 1);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, -20);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}

void drawBackground() {
	// Sky gradient
	glBegin(GL_POLYGON);
	if (isDay) {
		// Fixed day sky colors
		glColor3f(0.4, 0.6, 1.0);
		glVertex2f(0, 800);
		glVertex2f(1200, 800);
		glColor3f(0.7, 0.8, 1.0);
		glVertex2f(1200, 0);
		glVertex2f(0, 0);
	} else {
		// Fixed night sky colors
		glColor3f(0.1, 0.1, 0.3);
		glVertex2f(0, 800);
		glVertex2f(1200, 800);
		glColor3f(0.2, 0.2, 0.4);
		glVertex2f(1200, 0);
		glVertex2f(0, 0);
	}
	glEnd();

	// Sun/Moon
	if (isDay) {
		// Fixed sun position and color
		glColor3f(1.0, 0.9, 0.0);
		for(int i = 0; i < 360; i += 45) {
			float angle = i * 3.14159 / 180;
			glBegin(GL_LINES);
			glVertex2f(1000 + 40 * cos(angle), 700 + 40 * sin(angle));
			glVertex2f(1000 + 60 * cos(angle), 700 + 60 * sin(angle));
			glEnd();
		}
		DrawCircle(1000, 700, 40, 20);
	} else {
		// Fixed moon position and color
		glColor3f(0.9, 0.9, 0.9);
		DrawCircle(1000, 700, 40, 20);
		// Moon craters
		glColor3f(0.8, 0.8, 0.8);
		DrawCircle(990, 710, 5, 10);
		DrawCircle(1010, 690, 7, 10);
		DrawCircle(1000, 680, 4, 10);
	}

	// Stars (only visible at night)
	if (!isDay) {
		for(int i = 0; i < 50; i++) {
			float brightness = starBrightness[i] *
							 (0.5 + sin(glutGet(GLUT_ELAPSED_TIME) * stars[i].twinkleSpeed) * 0.5);
			glColor3f(brightness, brightness, brightness);
			glPointSize(1 + (rand() % 3));
			glBegin(GL_POINTS);
			glVertex2f(stars[i].x, stars[i].y);
			glEnd();
		}
	}

	// Ground
	glBegin(GL_POLYGON);
	if (isDay) {
		glColor3f(0.0, 0.7, 0.0);
	} else {
		glColor3f(0.0, 0.3, 0.0);
	}
	glVertex2f(0, 0);
	glVertex2f(1200, 0);
	glVertex2f(1200, 200);
	glVertex2f(0, 200);
	glEnd();

	// Clouds
	for(int i = 0; i < 4; i++) {
		float cloudX = cloudX1 + i * 200;
		if (isDay) {
			glColor3f(1.0, 1.0, 1.0);
		} else {
			glColor3f(0.3, 0.3, 0.3);
		}
		drawCloud(cloudX, 700 - i * 50);
	}
}

void drawText(const char* text, float x, float y) {
	glRasterPos2f(x, y);
	for (const char* c = text; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}

void drawHouse() {
	// House body
	glColor3f(0.9, 0.7, 0.1);
	glBegin(GL_POLYGON);
	glVertex2f(350, 200);
	glVertex2f(350, 300);
	glVertex2f(450, 300);
	glVertex2f(450, 200);
	glEnd();

	// Roof
	glColor3f(0.9, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(340, 300);
	glVertex2f(400, 350);
	glVertex2f(460, 300);
	glEnd();

	// Door
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(380, 200);
	glVertex2f(380, 280);
	glVertex2f(420, 280);
	glVertex2f(420, 200);
	glEnd();

	// Window
	glColor3f(0.8, 0.8, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(360, 250);
	glVertex2f(360, 280);
	glVertex2f(390, 280);
	glVertex2f(390, 250);
	glEnd();
}

void initRain() {
	for(int i = 0; i < 200; i++) {
		raindrops[i].x = rand() % 1200;
		raindrops[i].y = rand() % 800 + 800;
		raindrops[i].speed = 5 + rand() % 10;
		raindrops[i].size = 1 + (rand() % 3);
		raindrops[i].brightness = 0.7 + (rand() % 30) / 100.0;
		raindrops[i].isSplashing = false;
		raindrops[i].splashTime = 0;
	}

	for(int i = 0; i < 50; i++) {
		splashes[i].x = 0;
		splashes[i].y = 0;
		splashes[i].size = 0;
		splashes[i].alpha = 0;
		splashes[i].time = 0;
	}
}

void initBirds() {
	for(int i = 0; i < 3; i++) {
		birds[i].x = rand() % 1200;
		birds[i].y = 500 + rand() % 200;
		birds[i].speed = 2 + rand() % 3;
		birds[i].wingAngle = 0;
	}
}

void initCows() {
	for(int i = 0; i < 4; i++) {
		cows[i].x = 200 + i * 200;
		cows[i].y = 150;
		cows[i].mouthAngle = 0;
	}
}

void initPeople() {
	for(int i = 0; i < 5; i++) {
		people[i].x = -100 - i * 100;
		people[i].y = 200;
		people[i].speed = 2 + rand() % 2;
	}
}

void initFish() {
	for(int i = 0; i < 6; i++) {
		fishes[i].x = rand() % 1200;
		fishes[i].y = 100 + rand() % 200;
		fishes[i].speed = 2 + rand() % 3;
		fishes[i].tailAngle = 0;
	}
}

void initButterflies() {
	for(int i = 0; i < 7; i++) {
		butterflies[i].x = rand() % 1200;
		butterflies[i].y = 300 + rand() % 300;
		butterflies[i].speed = 1 + rand() % 2;
		butterflies[i].wingAngle = 0;
	}
}

void initCars() {
	for(int i = 0; i < 8; i++) {
		cars[i].x = -100 - i * 150;
		cars[i].y = 150;
		cars[i].speed = 3 + rand() % 2;
		cars[i].wheelAngle = 0;
	}
}

void initStars() {
	for(int i = 0; i < 50; i++) {
		stars[i].x = rand() % 1200;
		stars[i].y = rand() % 800;
		stars[i].brightness = 0.5 + (rand() % 50) / 100.0;
		stars[i].twinkleSpeed = 0.01 + (rand() % 100) / 1000.0;
		starBrightness[i] = stars[i].brightness;
	}
}

void updateRain() {
	// Update raindrops
	for(int i = 0; i < 200; i++) {
		if (!raindrops[i].isSplashing) {
			raindrops[i].x += windEffect;
			raindrops[i].y -= raindrops[i].speed * rainIntensity;

			// Check for ground collision
			if (raindrops[i].y < 200) {
				raindrops[i].isSplashing = true;
				raindrops[i].splashTime = glutGet(GLUT_ELAPSED_TIME);

				// Create splash effect
				for(int j = 0; j < 50; j++) {
					if (splashes[j].alpha <= 0) {
						splashes[j].x = raindrops[i].x;
						splashes[j].y = 200;
						splashes[j].size = 2;
						splashes[j].alpha = 0.5;
						splashes[j].time = glutGet(GLUT_ELAPSED_TIME);
						break;
					}
				}
			}

			// Reset raindrop if it goes off screen
			if (raindrops[i].x < -50 || raindrops[i].x > 1250 ||
				raindrops[i].y < -50) {
				raindrops[i].x = rand() % 1200;
				raindrops[i].y = 800 + rand() % 200;
				raindrops[i].speed = 5 + rand() % 10;
				raindrops[i].size = 1 + (rand() % 3);
				raindrops[i].brightness = 0.7 + (rand() % 30) / 100.0;
				raindrops[i].isSplashing = false;
			}
		}
	}

	// Update splashes
	for(int i = 0; i < 50; i++) {
		if (splashes[i].alpha > 0) {
			float currentTime = glutGet(GLUT_ELAPSED_TIME);
			float timeDiff = (currentTime - splashes[i].time) / 1000.0;

			splashes[i].size += timeDiff * 10;
			splashes[i].alpha -= timeDiff * 2;

			if (splashes[i].alpha <= 0) {
				splashes[i].alpha = 0;
				splashes[i].size = 0;
			}
		}
	}

	// Update wind effect
	windEffect = sin(glutGet(GLUT_ELAPSED_TIME) * 0.001) * 2;

	// Update rain intensity
	rainIntensity = 0.8 + sin(glutGet(GLUT_ELAPSED_TIME) * 0.0005) * 0.2;
}

void updateDayNight() {
	// No transitions needed for fixed states
	if (isDay) {
		ambientLight = 1.0;
		cloudOpacity = 1.0;
		groundBrightness = 1.0;
	} else {
		ambientLight = 0.3;
		cloudOpacity = 0.3;
		groundBrightness = 0.3;
	}
}

void update(int value) {
	if (animationStatus == 1) {
		// Day/Night transition
		updateDayNight();

		// Rain animation
		if (sceneState == 1) {
			updateRain();
		}

		// Men wacking animation
		if (sceneState == 2) {
			wackAngle = sin(glutGet(GLUT_ELAPSED_TIME) * 0.01) * 45;
		}

		// Birds flying animation
		if (sceneState == 3) {
			for(int i = 0; i < 3; i++) {
				birds[i].x += birds[i].speed;
				birds[i].wingAngle = sin(glutGet(GLUT_ELAPSED_TIME) * 0.01) * 30;
				if (birds[i].x > 1300) {
					birds[i].x = -100;
					birds[i].y = 500 + rand() % 200;
				}
			}
		}

		// Cows eating animation
		if (sceneState == 4) {
			for(int i = 0; i < 4; i++) {
				cows[i].mouthAngle = sin(glutGet(GLUT_ELAPSED_TIME) * 0.005) * 15;
			}
		}

		// People going home animation
		if (sceneState == 5) {
			for(int i = 0; i < 5; i++) {
				people[i].x += people[i].speed;
				if (people[i].x > 1300) {
					people[i].x = -100;
				}
			}
		}

		// Fish swimming
		if (sceneState == 6) {
			for(int i = 0; i < 6; i++) {
				fishes[i].x += fishes[i].speed;
				fishes[i].tailAngle = sin(glutGet(GLUT_ELAPSED_TIME) * 0.01) * 30;
				if (fishes[i].x > 1300) {
					fishes[i].x = -100;
					fishes[i].y = 100 + rand() % 200;
				}
			}
		}

		// Butterflies flying
		if (sceneState == 7) {
			for(int i = 0; i < 7; i++) {
				butterflies[i].x += butterflies[i].speed;
				butterflies[i].y += sin(glutGet(GLUT_ELAPSED_TIME) * 0.01 + i) * 2;
				butterflies[i].wingAngle = sin(glutGet(GLUT_ELAPSED_TIME) * 0.02) * 45;
				if (butterflies[i].x > 1300) {
					butterflies[i].x = -100;
					butterflies[i].y = 300 + rand() % 300;
				}
			}
		}

		// Cars moving
		if (sceneState == 8) {
			for(int i = 0; i < 8; i++) {
				cars[i].x += cars[i].speed;
				cars[i].wheelAngle += 5;
				if (cars[i].x > 1300) {
					cars[i].x = -100;
				}
			}
		}

		// Stars twinkling
		if (sceneState == 9) {
			for(int i = 0; i < 9; i++) {
				stars[i].brightness = 0.5 + sin(glutGet(GLUT_ELAPSED_TIME) * stars[i].twinkleSpeed) * 0.5;
			}
		}

		// Airplane flying
		if (sceneState == 10) { // 'a' key
			airplane.x += airplane.speed;
			airplane.y += sin(glutGet(GLUT_ELAPSED_TIME) * 0.001) * 2;
			if (airplane.x > 1300) {
				airplane.x = -100;
			}
		}

		// Elephant walking
		if (sceneState == 11) { // 'e' key
			elephant.x += elephant.speed;
			elephant.trunkAngle = sin(glutGet(GLUT_ELAPSED_TIME) * 0.005) * 15;
			if (elephant.x > 1300) {
				elephant.x = -100;
			}
		}

		// Ice skating
		if (sceneState == 12) { // 'i' key
			skater.x += skater.speed;
			skater.spinAngle += 5;
			if (skater.x > 1300) {
				skater.x = -100;
				skater.spinAngle = 0;
			}
		}

		// Ocean waves
		if (sceneState == 13) { // 'o' key
			for(int i = 0; i < 5; i++) {
				waves[i].x += waves[i].speed;
				waves[i].amplitude = 10 + sin(glutGet(GLUT_ELAPSED_TIME) * 0.001 + i) * 5;
				if (waves[i].x > 1300) {
					waves[i].x = -100;
				}
			}
		}

		// Umbrella moving
		if (sceneState == 14) { // 'u' key
			umbrella.x += 2;
			umbrella.angle = sin(glutGet(GLUT_ELAPSED_TIME) * 0.01) * 10;
			umbrella.openAmount = 0.5 + sin(glutGet(GLUT_ELAPSED_TIME) * 0.005) * 0.5;
			if (umbrella.x > 1300) {
				umbrella.x = -100;
			}
		}

		// Robot dancing
		if (sceneState == 15) { // 'r' key
			robot.armAngle = sin(glutGet(GLUT_ELAPSED_TIME) * 0.01) * 45;
			robot.legAngle = sin(glutGet(GLUT_ELAPSED_TIME) * 0.01 + 1.57) * 30;
			robot.headAngle = sin(glutGet(GLUT_ELAPSED_TIME) * 0.005) * 15;
		}
	}
	glutTimerFunc(16, update, 0);
}

void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	drawBackground();

	switch(sceneState) {
		case 1: // Rain scene
			drawRain();
			break;
		case 2: // Men wacking scene
			drawManWacking(man1X, 200);
			drawManWacking(man2X, 200);
			break;
		case 3: // Birds flying scene
			for(int i = 0; i < 3; i++) {
				drawBird(birds[i].x, birds[i].y, birds[i].wingAngle);
			}
			break;
		case 4: // Cows eating scene
			for(int i = 0; i < 4; i++) {
				drawCow(cows[i].x, cows[i].y, cows[i].mouthAngle);
			}
			break;
		case 5: // People going home scene
			for(int i = 0; i < 5; i++) {
				drawPerson(people[i].x, people[i].y);
			}
			break;
		case 6: // Fish swimming scene
			for(int i = 0; i < 6; i++) {
				drawFish(fishes[i].x, fishes[i].y, fishes[i].tailAngle);
			}
			break;
		case 7: // Butterflies scene
			for(int i = 0; i < 7; i++) {
				drawButterfly(butterflies[i].x, butterflies[i].y, butterflies[i].wingAngle);
			}
			break;
		case 8: // Cars scene
			for(int i = 0; i < 8; i++) {
				drawCar(cars[i].x, cars[i].y, cars[i].wheelAngle);
			}
			break;
		case 9: // Stars scene
			for(int i = 0; i < 9; i++) {
				drawStar(stars[i].x, stars[i].y, stars[i].brightness);
			}
			break;
		case 10: // Airplane scene (a)
			drawAirplane(airplane.x, airplane.y, airplane.angle);
			break;
		case 11: // Elephant scene (e)
			drawElephant(elephant.x, elephant.y, elephant.trunkAngle);
			break;
		case 12: // Ice skating scene (i)
			drawSkater(skater.x, skater.y, skater.spinAngle);
			break;
		case 13: // Ocean waves scene (o)
			for(int i = 0; i < 5; i++) {
				drawWave(waves[i].x, waves[i].y, waves[i].amplitude);
			}
			break;
		case 14: // Umbrella scene (u)
			drawUmbrella(umbrella.x, umbrella.y, umbrella.angle, umbrella.openAmount);
			break;
		case 15: // Robot scene (r)
			drawRobot(robot.x, robot.y, robot.armAngle, robot.legAngle, robot.headAngle);
			break;
	}

	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case '1':
			sceneState = 1;
			initRain();
			break;
		case '2':
			sceneState = 2;
			break;
		case '3':
			sceneState = 3;
			initBirds();
			break;
		case '4':
			sceneState = 4;
			initCows();
			break;
		case '5':
			sceneState = 5;
			initPeople();
			break;
		case '6':
			sceneState = 6;
			initFish();
			break;
		case '7':
			sceneState = 7;
			initButterflies();
			break;
		case '8':
			sceneState = 8;
			initCars();
			break;
		case '9':
			sceneState = 9;
			initStars();
			break;
		case 'a':
		case 'A':
			sceneState = 10;
			airplane.x = -100;
			airplane.y = 400;
			airplane.speed = 3;
			airplane.angle = 0;
			break;
		case 'e':
		case 'E':
			sceneState = 11;
			elephant.x = -100;
			elephant.y = 150;
			elephant.speed = 2;
			elephant.trunkAngle = 0;
			break;
		case 'i':
		case 'I':
			sceneState = 12;
			skater.x = -100;
			skater.y = 200;
			skater.speed = 3;
			skater.spinAngle = 0;
			break;
		case 'o':
		case 'O':
			sceneState = 13;
			for(int i = 0; i < 5; i++) {
				waves[i].x = -100 - i * 200;
				waves[i].y = 300;
				waves[i].amplitude = 10;
				waves[i].speed = 2;
			}
			break;
		case 'u':
		case 'U':
			sceneState = 14;
			umbrella.x = -100;
			umbrella.y = 300;
			umbrella.angle = 0;
			umbrella.openAmount = 1.0;
			break;
		case 'r':
		case 'R':
			sceneState = 15;
			robot.x = 600;
			robot.y = 300;
			robot.armAngle = 0;
			robot.legAngle = 0;
			robot.headAngle = 0;
			break;
		case 'm':
		case 'M':
			animationStatus = !animationStatus;
			break;
		case 'd':
		case 'D':
			isDay = true;
			dayNightTransition = 1.0;
			break;
		case 'n':
		case 'N':
			isDay = false;
			dayNightTransition = 0.0;
			break;
	}
}

void myInit(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1200.0, 0.0, 800.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1200, 800);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Interactive Animation");
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(myDisplay);
	glutTimerFunc(0, update, 0);

	// Initialize all scenes
	initRain();
	initBirds();
	initCows();
	initPeople();
	initFish();
	initButterflies();
	initCars();
	initStars();

	myInit();
	glutMainLoop();
	return 0;
}
