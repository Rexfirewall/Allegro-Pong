#include <allegro5/allegro.h>

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32;
const int BOUNCER2_SIZE = 32;
bool hit(int x1, int y1, int h1, int w1, int x2, int y2, int h2, int w2);

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

enum MYKEYS2 {
	KEY_W, KEY_A, KEY_S, KEY_D
};

int main()
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *bouncer = NULL;
	ALLEGRO_BITMAP *bouncer2 = NULL;
	ALLEGRO_BITMAP *Ball = NULL;

	float bouncer_x = 600;
	float bouncer_y = 200;
	float bouncer2_x = 5;
	float bouncer2_y = 40;
	float Ball_x = 150;
	float Ball_y = 150;
	bool key[4] = { false, false, false, false };
	bool key2[4] = { false, false, false, false };
	bool redraw = true;
	bool doexit = false;

	float Ball_dx = -4.0, Ball_dy = 4.0;



	al_init();

	al_install_keyboard();
	timer = al_create_timer(1.0 / FPS);

	display = al_create_display(SCREEN_W, SCREEN_H);

	// The things on the screen
	bouncer = al_create_bitmap(32, 100);
	bouncer2 = al_create_bitmap(32, 100);
	Ball = al_create_bitmap(32, 32);

	// color for Ball
	al_set_target_bitmap(Ball);
	al_clear_to_color(al_map_rgb(158, 48, 123));
	// color for B
	al_set_target_bitmap(bouncer);
	al_clear_to_color(al_map_rgb(255, 0, 255));
	// color for B2
	al_set_target_bitmap(bouncer2);
	al_clear_to_color(al_map_rgb(25, 330, 255));

	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);



	while (!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (key[KEY_UP] && bouncer_y >= 4.0) {
				bouncer_y -= 4.0;
			}

			if (key[KEY_DOWN] && bouncer_y <= SCREEN_H - 100 - 4.0) {
				bouncer_y += 4.0;
			}

			/*if (key[KEY_LEFT] && bouncer_x >= 4.0) {
				bouncer_x -= 4.0;
			}

			if (key[KEY_RIGHT] && bouncer_x <= SCREEN_W - BOUNCER_SIZE - 4.0) {
				bouncer_x += 4.0;
			}*/
			if (key2[KEY_W] && bouncer2_y >= 4.0) {
				bouncer2_y -= 4.0;
			}

			/*if (key2[KEY_A] && bouncer2_y <= SCREEN_H - 100 - 4.0) {
				bouncer2_x -= 4.0;
			}
			*/
			if (key2[KEY_S] && bouncer2_y <= SCREEN_H - 100 - 4.0) {
				bouncer2_y += 4.0;
			}

			/*if (key2[KEY_D] && bouncer2_x <= SCREEN_W - 100 - 4.0) {
				bouncer2_x += 4.0;
			}*/

			if (Ball_x < 0 || Ball_x > 640 - 32) {
				Ball_dx = -Ball_dx;
			}

			if (Ball_y < 0 || Ball_y > 480 - 32) {
				Ball_dy = -Ball_dy;
			}
			//add the x velocity to the x position, 
			//and the y velocity to the y position
			Ball_x += Ball_dx;
			Ball_y += Ball_dy;

			if (hit(Ball_x, Ball_y, 32, 32, bouncer_x, bouncer_y, 32, 100) == true) {
				Ball_dx = -Ball_dx;
			}

			if (hit(Ball_x, Ball_y, 32, 32, bouncer2_x, bouncer2_y, 5, 40) == true) {
				Ball_dx = -Ball_dx;
			}

			redraw = true;
		}
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

			case ALLEGRO_KEY_W:
				key2[KEY_W] = true;
				break;

			case ALLEGRO_KEY_A:
				key2[KEY_A] = true;
				break;

			case ALLEGRO_KEY_S:
				key2[KEY_S] = true;
				break;

			case ALLEGRO_KEY_D:
				key2[KEY_D] = true;
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

			case ALLEGRO_KEY_W:
				key2[KEY_W] = false;
				break;

			case ALLEGRO_KEY_A:
				key2[KEY_A] = false;
				break;

			case ALLEGRO_KEY_S:
				key2[KEY_S] = false;
				break;

			case ALLEGRO_KEY_D:
				key2[KEY_D] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;


			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}


		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
			al_draw_bitmap(bouncer2, bouncer2_x, bouncer2_y, 0);
			al_draw_bitmap(Ball, Ball_x, Ball_y, 0);

			al_flip_display();
		}
	}
	al_destroy_bitmap(bouncer);
	al_destroy_bitmap(bouncer2);
	al_destroy_bitmap(Ball);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;

} // main



bool hit(int x1, int y1, int h1, int w1, int x2, int y2, int h2, int w2) {
	if (x1 + w1 > x2 && x2 + w2 > x1)
		return true;
	else
		return false;
}