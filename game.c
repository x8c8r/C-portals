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
    
    typedef enum GameScreen { MENU = 0, GAME, SETTINGS } GameScreen;//Current screen
    
    GameScreen curScreen = MENU;
    
    const int maxSpeed = 10;//Maximum speed the player can reach
    //Starting X and Y positions of the player
    int x = screenWidth/2;
    int y = screenHeight/2;
    int optSelect = 1;
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
                    SetExitKey(0);
                    curScreen = GAME;
                    break;
                }                            
                if (IsKeyPressed(KEY_O))
                {
                    SetExitKey(0);                    
                    curScreen = SETTINGS;
                    break;
                }
        case SETTINGS:
                if (IsKeyPressed(KEY_ESCAPE))
                {
                    SetExitKey(KEY_ESCAPE);
                    curScreen = MENU;                  
                }
                if(IsKeyPressed(KEY_DOWN)){
                    optSelect++;
                }
                if(IsKeyPressed(KEY_UP)){
                    optSelect--;
                }
                if(optSelect > 4){
                    optSelect = 4;
                }
                if(optSelect < 1){
                    optSelect = 1;
                }
                
                if(optSelect == 1){
                    if(IsKeyPressed(KEY_ENTER)){
                        enableVert = !enableVert;
                    }
                }
                 if(optSelect == 2){
                    if(IsKeyPressed(KEY_ENTER)){
                        enableAccel = !enableAccel;
                    }
                }
                 if(optSelect == 3){
                    if(IsKeyPressed(KEY_ENTER)){
                        enablePortals = !enablePortals;
                    }
                }
                 if(optSelect == 4){
                    if(IsKeyPressed(KEY_ENTER)){
                        debug = !debug;
                    }
                }
            break;
        case GAME:
                if (IsKeyPressed(KEY_ESCAPE))
                {
                    SetExitKey(KEY_ESCAPE);
                    curScreen = MENU;                  
                    break;
                }      
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
            break;
        }
        BeginDrawing();//Begins drawing
        
        ClearBackground(BLACK);//Sets background to black before drawing anything
        
        switch (curScreen){
        case MENU:
            DrawText("C-por", screenWidth/3, screenHeight/3, 40, BLUE); DrawText("tals", screenWidth/3+120, screenHeight/3, 40, ORANGE);
            DrawText("Press ENTER to PLAY", screenWidth/3, screenHeight/3+50, 20, WHITE); 
            DrawText("Press O to FOR SETTINGS", screenWidth/3, screenHeight/3+75, 20, WHITE);            
            DrawText("Press ESCAPE to QUIT", screenWidth/3, screenHeight/3+100, 20, WHITE);
            //Portals for aesthetics
            DrawLineEx((Vector2){1, screenHeight}, (Vector2){0, 0}, 3, DARKBLUE); // Left portal
            DrawLineEx((Vector2){screenWidth, screenHeight}, (Vector2){screenWidth, 0}, 3, ORANGE); // Right portal
            DrawLineEx((Vector2){1, screenHeight}, (Vector2){screenWidth, screenHeight}, 3, SKYBLUE); // Down portal
            DrawLineEx((Vector2){1, 1}, (Vector2){screenWidth, 1}, 3, YELLOW); // Up portal
            break;
        case SETTINGS:
            DrawText("Settings", screenWidth/3, screenHeight-screenHeight+10, 40, WHITE);
            switch(optSelect){
                case 1:
                    switch(enableVert){//Checks if vertical movement is on
                    case true:
                        DrawText("Vertical movement: On <", 10, 50, 20, GREEN);
                        break;
                    case false:
                        DrawText("Vertical movement: Off <", 10, 50, 20, RED);
                        break;
                    }
                    break;
                case 2:
                    switch(enableAccel){//Checks if acceleration is on
                    case true:
                        DrawText("Acceleration: On <", 10, 70, 20, GREEN);
                        break;
                    case false:
                        DrawText("Acceleration: Off <", 10, 70, 20, RED);
                        break;
                    }
                    break;
                case 3:
                    switch(enablePortals){//Checks if portals are on
                    case true:
                        DrawText("Portals: On <", 10, 90, 20, GREEN);
                        break;
                    case false:
                        DrawText("Portals: Off <", 10, 90, 20, RED);
                        break;
                    } 
                    break;
                case 4:
                    switch(debug){
                    case true:
                        DrawText("Debug mode: On <", 10, 110, 20, GREEN);
                        break;
                    case false:
                        DrawText("Debug mode: Off <", 10, 110, 20, RED);
                        break;
                    }
                    break;
            }
            switch(enableVert){//Checks if vertical movement is on
                case true:
                    DrawText("Vertical movement: On", 10, 50, 20, GREEN);
                    break;
                case false:
                    DrawText("Vertical movement: Off", 10, 50, 20, RED);
                    break;
                }
                switch(enableAccel){//Checks if acceleration is on
                case true:
                    DrawText("Acceleration: On", 10, 70, 20, GREEN);
                    break;
                case false:
                    DrawText("Acceleration: Off", 10, 70, 20, RED);
                    break;
                }
                
                switch(enablePortals){//Checks if portals are on
                case true:
                    DrawText("Portals: On", 10, 90, 20, GREEN);
                    break;
                case false:
                    DrawText("Portals: Off", 10, 90, 20, RED);
                    break;
                }            
                switch(debug){
                case true:
                    DrawText("Debug mode: On", 10, 110, 20, GREEN);
                    break;
                case false:
                    DrawText("Debug mode: Off", 10, 110, 20, RED);
                    break;
                }
            //Same portals for aesthetics
            DrawLineEx((Vector2){1, screenHeight}, (Vector2){0, 0}, 3, DARKBLUE); // Left portal
            DrawLineEx((Vector2){screenWidth, screenHeight}, (Vector2){screenWidth, 0}, 3, ORANGE); // Right portal
            DrawLineEx((Vector2){1, screenHeight}, (Vector2){screenWidth, screenHeight}, 3, SKYBLUE); // Down portal
            DrawLineEx((Vector2){1, 1}, (Vector2){screenWidth, 1}, 3, YELLOW); // Up portal
            break;
        case GAME:
            //Debug mode
            switch(debug){
                case true:
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