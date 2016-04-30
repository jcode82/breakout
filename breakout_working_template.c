//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// height and width of bricks
#define BRICK_H 7.5
#define BRICK_W 35

// radius of ball in  pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // GEvent event = getNextEvent(MOUSE_CLICKED);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);
    //double velocity1 = 2.0;
    //double velocity2 = 2.0;

     double velocity1 = 1;//drand48() * 5 + 0.5;
     double velocity2 = 1;//drand48 () * 5 + 0.7;
    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    waitForClick();
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
      // TODO
      //updateScoreboard(GWindow window, GLabel label, int points)
      // Moving the ball.
      move(ball, velocity1, velocity2);
      pause (10);

      //listen for mouse event
      GEvent event = getNextEvent(MOUSE_EVENT);

      //Make paddle follow mouse when mouse clicked
      if ( event != NULL)
      {
        if (getEventType(event) == MOUSE_MOVED)
        {
          double x = getX(event) - getWidth(paddle) / 2;
          double y = HEIGHT - 160;
          setLocation(paddle, x, y);
        }
      }
       
      // Make sure there is a collision.
    
      if (getX(ball) + getWidth(ball) >= getWidth(window))
      {
          velocity1 = -velocity1;
      }
      else if (getX(ball) <= 0)
      {
          velocity1 = -velocity1;
      }
      if (getY(ball) + getHeight(ball) >= getHeight(window))
      {
          velocity2 = -velocity2;
      }
      else if (getY(ball) <= 0)
      {
          velocity2 = -velocity2;
      }
      
      GObject object = detectCollision(window, ball);

      if (object != NULL)
        //when ball hits the paddle reverse direction
        if (object == paddle)
        {
            velocity2 = -velocity2;
        }
        // when ball hits left wall
        if (getX(ball) <= 0)
        {
            velocity1 = -velocity1;
        }
        
        // when the ball hits the top wall.
        if (getY(ball) <= 0)
        {
            velocity2 = -velocity2;
        }
   
        // when ball hits the right wall
        if (getX(ball) + getWidth(ball) >= WIDTH)
        {
            velocity1 = -velocity1;
        }
        
        // bottom wall below paddle
        if (getY(ball) + getHeight(ball) >= 600)
        {
            lives = lives - 1;
            // reset
            setLocation(ball, WIDTH / 2 - RADIUS, HEIGHT / 2 + RADIUS);
            setLocation(paddle, 160, 500);
            waitForClick();
        }
      
        // end of game, winner!
        if (points == 25)
        {
            GLabel win = newGLabel("Your a G!");
            setFont(win, "SansSerif-50");
            setColor(win, "RED");
            setLocation(win, 15, 300);
            add(window, win);
       
        }
    }

    // wait for click before exiting
    waitForClick();
    

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // TODO
    // set initial brick coordinates
    int x_coord = 2;

    for (int i = 0; i < ROWS; i++)
    {
    int y_coord = 30;
        // Create 10 columns of bricks
        for (int j = 0; j < COLS; j++)
        {
            // create a brick
            GRect brick = newGRect(x_coord, y_coord, BRICK_W, BRICK_H);
            setFilled(brick, true);
            setColor(brick, "RED");
            add(window, brick);

            // increment x coordinate for column spacing
            x_coord += 40;
        } 
        // increment y coordinate for row spacing
        y_coord += 40;  
    }

    int x_orange = 2;

    for (int i = 0; i < ROWS; i++)
    {
    int y_orange = 45;
        // Create 10 columns of bricks
        for (int j = 0; j < COLS; j++)
        {
            // create a brick
            GRect brick = newGRect(x_orange, y_orange, BRICK_W, BRICK_H);
            setFilled(brick, true);
            setColor(brick, "ORANGE");
            add(window, brick);

            // increment x coordinate for column spacing
            x_orange += 40;
        } 
        // increment y coordinate for row spacing
        y_orange += 40;  
    }

    int x_yellow = 2;

    for (int i = 0; i < ROWS; i++)
    {
    int y_yellow = 60;
        // Create 10 columns of bricks
        for (int j = 0; j < COLS; j++)
        {
            // create a brick
            GRect brick = newGRect(x_yellow, y_yellow, BRICK_W, BRICK_H);
            setFilled(brick, true);
            setColor(brick, "YELLOW");
            add(window, brick);

            // increment x coordinate for column spacing
            x_yellow += 40;
        } 
        // increment y coordinate for row spacing
        y_yellow += 40;  
    }

    int x_green = 2;

    for (int i = 0; i < ROWS; i++)
    {
    int y_green = 75;
        // Create 10 columns of bricks
        for (int j = 0; j < COLS; j++)
        {
            // create a brick
            GRect brick = newGRect(x_green, y_green, BRICK_W, BRICK_H);
            setFilled(brick, true);
            setColor(brick, "GREEN");
            add(window, brick);

            // increment x coordinate for column spacing
            x_green += 40;
        } 
        // increment y coordinate for row spacing
        y_green += 40;  
    }

    int x_blue = 2;

    for (int i = 0; i < ROWS; i++)
    {
    int y_blue = 90;
        // Create 10 columns of bricks
        for (int j = 0; j < COLS; j++)
        {
            // create a brick
            GRect brick = newGRect(x_blue, y_blue, BRICK_W, BRICK_H);
            setFilled(brick, true);
            setColor(brick, "BLUE");
            add(window, brick);

            // increment x coordinate for column spacing
            x_blue += 40;
        } 
        // increment y coordinate for row spacing
        y_blue += 40;  
    }

}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
      printf("This program draws a black oval filling the window.\n");
      GOval ball = newGOval(200, 350, 20, 20);
      setFilled(ball, true);
      setColor(ball, "BLACK");
      add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
    printf("This program draws a red rectangle at (0, 0).\n");
          GRect paddle = newGRect(160, 450, 80, 10);
          setFilled(paddle, true);
          setColor(paddle, "RED");
          add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
          GLabel label;
          double x, y;

          label = newGLabel("0");
          setFont(label, "SansSerif-60");
          x = (getWidth(window) - getWidth(label)) / 2;
          y = (getHeight(window) + getFontAscent(label)) / 2;
          setColor(label, "BLACK");
          setLocation(label, x, y);
          add(window, label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
