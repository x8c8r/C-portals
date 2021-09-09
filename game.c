/******************************************
*
*   C-portals v0.3.1
*
*
*   Made by Fl1pNatic using raylib (www.raylib.com)
*
******************************************/

#include "raylib.h"

int main(void){
    
    //Variables
    int screenWidth = 800;//Screen width
    int screenHeight = 600;//Screen height
    
    typedef enum GameScreen { MENU = 0, GAME } GameScreen;//Current screen
    
    GameScreen curScreen = MENU;
    
    const int maxSpeed = 10;//Maximum speed the player can reach
    //Starting X and Y positions of the player
    int x = screenWidth/2;
    int y = screenHeight/2;
    float startSpeed = 2.0;//Starting speed
    float accelAmount = 0.1;//If enableAccel is true this var will be used to define how fast the player should accelerate
    float Speed = startSpeed; /*Sets speed to the starting speed
    Speed does change and all the other functions use it
    Starting speed doesn't change and speed uses it as a starting value(thx cap)
    */
    bool debug = true; //Debug mode(being made)
    bool enableAccel = true;//Enable acceleration
    bool enableVert = true;
    bool enableFake = false; //Fake portal reflections(they are yet to be implemented)
    bool enablePortals = true;//Enable portals lol
    //bool stopOnBothDirections = false;//Should prevent player from moving if both keys are held and this is enabled but for some reason it doesn't check and just always stops

    InitWindow(screenWidth, screenHeight, "C-portals");//Makes a window
    SetTargetFPS(60);//Sets max fps to 60
    SetExitKey(KEY_ESCAPE);//Sets an exit key to escape
    
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {   
        switch (curScreen){
        case MENU:    
                if (IsKeyPressed(KEY_ENTER))
                {
                    curScreen = GAME;
                    break;
                }            
        case GAME:
            //Moves
            if(IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT)){ //Makes the player go right
              x = x+Speed;
              //Makes the player accelerate if the var is true
              if(enableAccel == true){
                Speed = Speed + accelAmount; 
              }
            }
            if(IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)) { //Makes the player go left
              x = x-Speed;
              //Makes the player accelerate if the var is true
              if(enableAccel == true){
                Speed = Speed + accelAmount; 
              }
            }
            //Makes the player move down if enableVert is true
            if(IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_UP) && enableVert == true){
              y = y+Speed;
              //Makes the player accelerate if the var is true
              if(enableAccel == true){
                Speed = Speed+accelAmount; 
              }
            }
            //Makes the player move up if enableVert is true
            if(IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN) && enableVert == true){
              y = y-Speed;
              //Makes the player accelerate if the var is true
              if(enableAccel == true){
                Speed = Speed+accelAmount; 
              }
            }
            if(IsKeyUp(KEY_RIGHT) && IsKeyUp(KEY_LEFT) && IsKeyUp(KEY_UP) && IsKeyUp(KEY_DOWN)){
             //If all buttons are released - Speed gets set to starting speed
                Speed = startSpeed;
            }
            if(Speed > maxSpeed){//If speed exceeds max speed it gets set back to it
                Speed = maxSpeed;
            }
            if(IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_RIGHT)|| IsKeyDown(KEY_UP) && IsKeyDown(KEY_DOWN)) { //Makes the player stop if both of the keys are down
              Speed = 0;
            }        
            
            //"Portals" | Basically just teleports player to the opposite side(if enabled)
            if(enablePortals == true){
                if(x >= screenWidth){
                  x = 1;
                }
                if(x <= 0){
                  x = screenWidth;
                }
                if(y >= screenHeight){
                  y = 1;
                }
                if(y <= 0){
                  y = screenHeight;
                }
            }

            //Collision check so the player doesn't go outside
            if(CheckCollisionCircleRec((Vector2){x, y}, screenWidth, (Rectangle){0, 0, screenWidth, screenHeight}) && enablePortals == false){
                if(x > screenWidth){
                    x = screenWidth;
                }
                if(x < 0){
                    x = 0;
                }
                if(y > screenHeight){
                    y = screenHeight;
                }
                if(y < 0){
                    y = 0;
                }            
                
            }        
            
            //Misc
            if(IsKeyPressed(KEY_F12)){
                TakeScreenshot(1);//Takes a screenshot on F12
            }

            if(IsKeyPressed(KEY_D)){//If "D" key is pressed - The debug mode will toggle
                debug = !debug;
            }
            break;
        }
        BeginDrawing();//Begins drawing
        
        ClearBackground(BLACK);//Sets background to black before drawing anything
        
        switch (curScreen){
        case MENU:
            DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
            DrawText("C-portals", screenWidth/3, screenHeight/3, 40, WHITE);
            DrawText("Press ENTER to PLAY", screenWidth/3, screenHeight/3+50, 20, WHITE); 
            DrawText("Press ESCAPE to QUIT", screenWidth/3, screenHeight/3+75, 20, WHITE); 
            break;
        case GAME:
            //Debug mode
            if(debug == true){
                DrawFPS(10, 20);//Draws FPS
                DrawText("Debug mode: On", 10, 10, 10, GREEN);//Draws text that says that debug mode is on
                
                /*DrawText("X:", 10, 4
                0, 10, GREEN); // Crashes the game for some reason    
                DrawText(x, 15, 40, 10, GREEN);*/
                
                switch(enableVert){//Checks if vertical movement is on
                case true:
                    DrawText("Vertical movement: On", 10, 40, 10, GREEN);
                    break;
                case false:
                    DrawText("Vertical movement: Off", 10, 40, 10, RED);
                    break;
                }
                
                switch(enableAccel){//Checks if acceleration is on
                case true:
                    DrawText("Acceleration: On", 10, 50, 10, GREEN);
                    break;
                case false:
                    DrawText("Acceleration: Off", 10, 50, 10, RED);
                    break;
                }
                
                switch(enablePortals){//Checks if portals are on
                case true:
                    DrawText("Portals: On", 10, 60, 10, GREEN);
                    break;
                case false:
                    DrawText("Portals: Off", 10, 60, 10, RED);
                    break;
                }            
                
            }
            //Draws a player(as a circle))
            DrawCircle(x, y, 5, WHITE); 
            //Draws lines to represent portals(if enabled)
            if(enablePortals == true){
                DrawLineEx((Vector2){1, screenHeight}, (Vector2){0, 0}, 3, DARKBLUE); // Left portal
                DrawLineEx((Vector2){screenWidth, screenHeight}, (Vector2){screenWidth, 0}, 3, ORANGE); // Right portal
                DrawLineEx((Vector2){1, screenHeight}, (Vector2){screenWidth, screenHeight}, 3, SKYBLUE); // Down portal
                DrawLineEx((Vector2){1, 1}, (Vector2){screenWidth, 1}, 3, YELLOW); // Up portal
                
            }        
            break;
        }
        
        
        EndDrawing();
    }
    
     CloseWindow();        // Close window and OpenGL context
     
     return 0;
}