//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// height and width of game's paddle in pixels
#define PADDLEHEIGHT 10
#define PADDLEWIDTH 60

// paddle's starting x and y coordinates
#define PADDLEX (WIDTH - PADDLEWIDTH) / 2
#define PADDLEY HEIGHT - 80

// height and width of bricks
#define BRICKHEIGHT 10
#define BRICKWIDTH 35

// height and width of ball
#define BALLHEIGHT RADIUS * 2
#define BALLWIDTH RADIUS * 2

// ball starting x and y coordinates to center
#define BALLX (WIDTH - BALLWIDTH) / 2
#define BALLY (HEIGHT - BALLHEIGHT) / 2

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

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

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
    
    // velocity of ball for x and y coordinates
    double xVelocity = drand48() * 2;
    double yVelocity = 5.0;

    // wait for click to begin gameplay
    waitForClick();
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // TODO
        // get MOUSE_EVENT and set paddle to move along x axis only
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                int x = getX(event) - getWidth(paddle) / 2;
                
                // move paddle being sure not to move beyond limits of window
                if (x <= 0)
                {
                    setLocation(paddle, 0, PADDLEY);
                }
                else if (x + PADDLEWIDTH >= WIDTH)
                {
                    setLocation(paddle, WIDTH - PADDLEWIDTH, PADDLEY);
                }
                else
                {
                    setLocation(paddle, x, PADDLEY);
                }  
            }  
        }
        
        if (ball != NULL)
        {
            // move the ball
            move(ball, xVelocity, yVelocity);
            
            // have ball bounce off left wall
            if (getX(ball) + BALLWIDTH >= WIDTH)
            {
                xVelocity = -xVelocity;
            }
            // have ball bounce off right wall
            else if (getX(ball) <= 0)
            {
                xVelocity = -xVelocity;
            }
            // have ball bounce off top wall
            else if (getY(ball) <= 0)
            {
                yVelocity = -yVelocity;
            }
            // decrement life and pause gameplay
            else if (getY(ball) + BALLHEIGHT >= HEIGHT)
            {
                // return ball to center
                setLocation(ball, BALLX, BALLY);
                
                // decrement lives
                lives = lives - 1;
                
                // pause game until user clicks
                waitForClick();
            }
        }
        
        pause(10);
        
        // create variable to hold object ball collies with
        GObject colObj = detectCollision(window, ball);
        
        if (colObj != NULL)
        {
            // detect collision with paddle
            if (colObj == paddle)
            {
                if (yVelocity > 0)
                {
                    yVelocity = -yVelocity;
                }
            }
            else if (strcmp(getType(colObj), "GRect") == 0)
            {
                // remove brick
                removeGWindow(window, colObj);
                bricks = bricks - 1;
                // bounce ball other direction
                yVelocity = -yVelocity;
                // increment points
                points++;
                // update scoreboard
                updateScoreboard(window, label, points);
            }
        }
        
    }
    
    // center the ball upon winning
    setLocation(ball, BALLX, BALLY);
    
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
    
    // create array of character strings for colors
    char* colors[5] = {"RED", "ORANGE", "YELLOW", "GREEN", "CYAN"};
    
    // set y value for first row
    double y = 40;
    
    // nested loop
    for (int i = 0; i < ROWS; i++)
    {
        // set starting x value for row
        double x = 2;
        
        for (int j = 0; j < COLS; j++)
        {
            // create a GRect template
            GRect brick = newGRect(x, y, BRICKWIDTH, BRICKHEIGHT);
            
            // set color for row
            setFilled(brick, true);
            setColor(brick, colors[i]);
            
            // add brick to window
            add(window, brick);
            
            // increment x value for next brick
            x = x + BRICKWIDTH + 5;
        }
        // increment y value for next row
        y = y + 15;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    GOval ball = newGOval(BALLX, BALLY, BALLHEIGHT, BALLWIDTH);
    setFilled(ball, true);
    setColor(ball, "BLACK");
    
    // add ball to window
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
    // instantiate a paddle
    GRect paddle = newGRect(PADDLEX, PADDLEY, PADDLEWIDTH, PADDLEHEIGHT);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    
    // add paddle to window
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    // create label and set formatting
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-42");
    setColor(label, "GRAY");
    
    // set coordinates for label
    double x = (WIDTH - getWidth(label)) / 2;
    double y = (HEIGHT - getFontAscent(label)) / 2;
    setLocation(label, x, y);
    
    // add label to window
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
