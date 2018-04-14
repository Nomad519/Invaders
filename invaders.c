#include <ncurses.h>
#include <stdio.h>
#include <time.h>

int main()
{
	int key; //store key press
	int score = 0;
	srand(time(NULL)); //Generate random number value for invader firing
	int invader_decision = rand() %50;
	bool game_end = false; //check for game end
	
	
	//store player position
	int xship = 40;
	int yship = 22;
	int next_xship = 0; //next x of player

	
	//store player projectile position
	int xship_projectile = xship;
	int yship_projectile = yship-1;
	
	//Check if projectile is fired
	int ship_projectile_fired = 0;

	
	//store invader position
	int xinvader = 1;
	int yinvader = 0;
	int direction = 1; //direction of invader
	int invader_alive = 1; //Check if invader is alive
	
	//store invader projectile position
	int xinvader_projectile = xinvader;
	int yinvader_projectile = yinvader + 1;
	int invader_projectile_fired = 0;
	
	
	int next_x = 0; //next x of object
	int next_y = 0; //next y of object
	
	int max_y = 24, max_x = 80; //store edges of screen
	
	int i = 0; //Loop counter
	
	
	
	
	
	initscr();
	
	
	curs_set(false);  //hide cursor
	raw();				// Line buffering disabled	
	
	move(12,36);
	printw("Press any key to start!");
	mvprintw(14, 20, "Controls: F1 to exit game, PgUp to fire, arrow keys to move");
	getch();
	keypad(stdscr, TRUE);		// We get F1, F2 etc..	
	nodelay(stdscr,TRUE); //make sure getch() doesnt block the while loop
	noecho();			// Don't echo() while we do getch 
	
	
	 while(game_end == false) //main game loop
	 {		
		clear();
		mvprintw(25, 78, "SCORE: %d", score); //Print score
		
		
		//Print current status of objects on window
		mvprintw(yship, xship, "{-^¬}"); 
		if(invader_alive == 1)
		{
			mvprintw(yinvader, xinvader, "[|,,|]"); 
		} else {
			xinvader = 0;
			yinvader = 0;
			invader_alive = 1; // Respawn invader
		}
 
		
		//Collision detection
			                
		if (yship_projectile == yinvader && ship_projectile_fired == 1)   //for invader
		{
				if (xship_projectile >= xinvader && xship_projectile < xinvader + 6)																
				{
					mvprintw(yinvader, xinvader, "BOOOOM");
					xinvader = -1;
					yinvader = -1;
					invader_alive = 0; //kill invader
					ship_projectile_fired = 0;
					score++;	
				}
		}
		
		if(yinvader_projectile == 22 && invader_projectile_fired == 1) //for player
		{
			if(xinvader_projectile >= xship && xinvader_projectile < xship + 5)
			{
				//game_end = true;
				mvprintw(yship, xship, "R.I.P.");
				refresh();
				sleep(2);
				game_end = true;
			}
		}
		
		
		//Handle projectile movement
		if (ship_projectile_fired == 1)
		{
			mvprintw(yship_projectile, xship_projectile, "S");
			yship_projectile--;
		}
		
		if (yship_projectile < 0) //ready to fire again
		{
			ship_projectile_fired = 0;
		}
		
		if(invader_projectile_fired == 1)
		{
			mvprintw(yinvader_projectile, xinvader_projectile, "#");
			yinvader_projectile++;
		}
			
		if(yinvader_projectile > 24)
		{
			invader_projectile_fired = 0;
		}
		
		
		refresh();
		
		//Handle Invader Movement and decision
		next_x = xinvader + direction; // update next_x  
		
		invader_decision = rand() % 100;
		if(invader_decision > 95 && invader_projectile_fired == 0) // decrease this number to fire more often (95-97 is good)
		{
			invader_projectile_fired = 1;
			yinvader_projectile = yinvader + 1;
			xinvader_projectile = xinvader + 3;
		}
		
		
		if (next_x >= max_x || next_x < 0){ //If invader reaches end of screen, move one row down
			yinvader = yinvader + 1;
			direction = -direction;
		 } else {
			xinvader += direction;  // move the invader next time around the loop
		 }	
		 
 
		usleep(60000); //increase to slow down the game, decrease to speed up
		
		key = getch(); //get the key press and store it into int key
		
		
		if(key == KEY_RIGHT) //move player right
		{	
			next_xship = xship + 1; //stop player from going off edge of screen
			if (next_xship >= max_x) { 
				//do nothing
			} else {
				xship = xship + 2;
			}	
		}
		

		if(key == KEY_LEFT) //move player left
		{	
			next_xship = xship - 1; //stop player from going off edge of screen
			if (next_xship <= 0) { 
				//do nothing
			} else {
				xship = xship - 2;
			}
		}
		
		
		if(key == KEY_PPAGE) //Fire projectile!(using pgUp button)
		{
			if (ship_projectile_fired == 0) { 
				clear(); 
				xship_projectile = xship + 2;
				yship_projectile = yship - 1;
				mvprintw(yship_projectile, xship_projectile, "S"); //prints player projectile above ship
				ship_projectile_fired = 1;	
				refresh();
			} else {
				//do nothing
			}
			
		}
		
		
			if(key == KEY_F(1) || yinvader >= 21 || game_end == TRUE) //exit game
		{	
			nodelay(stdscr,FALSE);
			clear();
			move(12,40);
			printw("Game Over!");
			printw("Score: %d", score);
			mvprintw(14, 36, "Press any key to continue...");
			getch();
			game_end = TRUE;
		}
	 }
	 
	endwin(); 
	printf("\n"); 
	printf("\n"); 
	 
}