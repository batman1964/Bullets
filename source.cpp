#include <allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5\allegro_primitives.h>
#include<vector>
using namespace std;
//constants: variables that shouldn't change once the game starts
const float FPS = 60;
const int SCREEN_W = 800;
const int SCREEN_H = 800;
//enumeration to help you remember what numbers represent which directions
enum MYKEYS {
KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE
};


class Bullets {

private:
double xpos;
double ypos;
double angle;
double radius;
int color;
int size;
bool alive;
ALLEGRO_BITMAP* pic;



public:

Bullets(int x, int y); //constructor
void reposition();
void movement();
void draw();
void kill();

bool isAlive();
bool offScreen();
float getx();
float gety();

void shoot(int x, int y);
float  collide(float x1, float y1);
};


int main()
{


//set up allegro
al_init();
al_install_keyboard();
al_init_image_addon();
al_init_primitives_addon();
//goes at the top of main where you creare your game display
ALLEGRO_BITMAP* shipPic = al_load_bitmap("player2.png");
//set up game screen, event queue, and timer

ALLEGRO_DISPLAY* display = al_create_display(SCREEN_W, SCREEN_H);
ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
al_start_timer(timer);
//position of player
double xPos = 400;
double yPos = 700;
//game variables
bool key[5] = { false, false, false, false, false }; //holds key clicks
bool redraw = true; //variable needed for render section
bool doexit = false; //handles game loop

//tell event queue what to look for
al_register_event_source(event_queue, al_get_display_event_source(display));
al_register_event_source(event_queue, al_get_timer_event_source(timer));
al_register_event_source(event_queue, al_get_keyboard_event_source());
int JustShot = 0;

//vector to hold missles
vector<Bullets*>BulletsBag;
vector<Bullets*>::iterator iter2;
for (int i = 0; i < 5; i++) {
Bullets* newBullets = new Bullets(0, 0);
BulletsBag.push_back(newBullets);
}
while (!doexit)//game loop!
{
ALLEGRO_EVENT ev;

al_wait_for_event(event_queue, &ev);

//timer (physics) section////////////////////////////////////////
JustShot++;
if (ev.type == ALLEGRO_EVENT_TIMER) {
//move player 4 pixels in a direction when key is pressed
if (key[KEY_UP]) {
yPos -= 4.0;
}
if (key[KEY_DOWN]) {
yPos += 4.0;
}
if (key[KEY_LEFT]) {
xPos -= 4.0;
}
if (key[KEY_RIGHT]) {
xPos += 4.0;
}
if (key[KEY_SPACE]) {
for (iter2 = BulletsBag.begin(); iter2 != BulletsBag.end(); iter2++) {
if (((*iter2)->isAlive()) == false && JustShot > 5) {
(*iter2)->shoot(xPos, yPos);
JustShot = 0;

}
}
}
redraw = true;
}
//keyboard and screen sections//////////////////////////////////////////
else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
break;
}
else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
switch (ev.keyboard.keycode) {
case ALLEGRO_KEY_UP:
key[KEY_UP] = true;
break;
case ALLEGRO_KEY_DOWN:
key[KEY_DOWN] = true;
break;
case ALLEGRO_KEY_LEFT:
key[KEY_LEFT] = true;
break;
case ALLEGRO_KEY_RIGHT:
key[KEY_RIGHT] = true;
break;
}


}
else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
switch (ev.keyboard.keycode) {
case ALLEGRO_KEY_UP:
key[KEY_UP] = false;
break;
case ALLEGRO_KEY_DOWN:
key[KEY_DOWN] = false;
break;
case ALLEGRO_KEY_LEFT:
key[KEY_LEFT] = false;
break;
case ALLEGRO_KEY_RIGHT:
key[KEY_RIGHT] = false;
break;
case ALLEGRO_KEY_ESCAPE:
doexit = true;
break;
}
for (iter2 = BulletsBag.begin(); iter2 != BulletsBag.end(); iter2++) {
if ((*iter2)->isAlive())
(*iter2)->movement();
}// end of for loop
//cull the missiles
for (iter2 = BulletsBag.begin(); iter2 != BulletsBag.end(); iter2++) {
if ((*iter2)->offScreen())
(*iter2)->kill();
}//end of for loop
}
//render section//////////////////////////////////////////////////
if (redraw && al_is_event_queue_empty(event_queue)) {
redraw = false;
al_clear_to_color(al_map_rgb(0, 0, 0)); //wipe screen black between drawing

//(without this things smear)
//replaces the draw circle function in the render section
al_draw_bitmap_region(shipPic, 0, 0, 32, 32, xPos, yPos, NULL);
al_flip_display(); //flip everything from memory to gamescreen
//draw the missles
for (iter2 = BulletsBag.begin(); iter2 != BulletsBag.end(); iter2++) {
(*iter2)->draw();

}
}//end render

}//end game loop
//clean up memory
al_destroy_timer(timer);
al_destroy_display(display);
al_destroy_event_queue(event_queue);



return 0;
}//end of main

//Bullets::Bullets(ALLEGRO_BITMAP* player2.png) {
//
//
// if (pic == true)
// {
// y = ypos;
//
// x = xpos;
// color = rand(% 200 + 1);
// }
// size = 21;
// al_convert_mask_to_alpha(pic, al_map_rgb(255, 255, 255));
//
//}

void Bullets::movement() {
ypos -= 5;
}

Bullets::Bullets(int x, int y) { //constructor
xpos = x;
ypos = y;

}

void Bullets::draw() {
if (alive == true) {
al_draw_filled_circle(xpos, ypos, 15, al_map_rgb(100, 200, 234));
}
}

void Bullets::kill() {
alive = false;
}
bool Bullets::offScreen() {
if (ypos < 0) {
return true;
}
else
return false;
}
void Bullets::shoot(int x, int y) {
alive = true;
xpos = x;
ypos = y;
}

bool Bullets::isAlive() {
return alive;
}

float  Bullets::collide(float x1, float y1) {
return 0;
}
