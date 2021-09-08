/******************************************
*
*   C-portals
*
*   Made by Fl1pNatic using raylib (www.raylib.com)
*
******************************************/

#include "raylib.h"

int main(void){
    
    int screenWidth = 800;
    int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "C-portals");
    SetTargetFPS(60);
    
    const int maxSpeed = 10;//Maximum speed the circle can reach
    //Starting X and Y positions of the circle
    int x = 64;
    int y = 32;
    const float startSpeed = 2.0;//Starting speed
    const float accelAmount = 0.1;//If enableAccel is true this var will be used to define how fast the circle should accelerate
    float Speed = startSpeed; /*Sets speed to the starting speed
    Speed does change and all the other functions use it
    Starting speed doesn't change and speed uses it as a starting value(thx cap)
    */
    const bool debug = true; //Debug mode(being made)
    const bool enableAccel = true;//Enable acceleration(Broken for the time being
    const bool enableVert = true;
    const bool enableFake = false; //Fake portal reflections(they are yet to be implemented)
    
    
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        if(IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT)){ //Makes the circle go right
          x = x+Speed;
          //Makes the circle accelerate if the var is true
          if(enableAccel == true){
            Speed = Speed + accelAmount; 
          }
        }
        if(IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)) { //Makes the circle go left
          x = x-Speed;
          //Makes the circle accelerate if the var is true
          if(enableAccel == true){
            Speed = Speed + accelAmount; 
          }
        }
        if(IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_RIGHT)) { //Makes the circle stop if both of the keys are down
          Speed = 0;
        }
        
        //"Portals" | Basically just teleports ball to the opposite side
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
        //Makes the ball move down if enableVert is true
        if(IsKeyDown(KEY_DOWN) && enableVert == true){
          y = y+Speed;
          //Makes the circle accelerate if the var is true
          if(enableAccel == true){
            Speed = Speed+accelAmount; 
          }
        }
        //Makes the ball move up if enableVert is true
        if(IsKeyDown(KEY_UP) && enableVert == true){
          y = y-Speed;
          //Makes the circle accelerate if the var is true
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
        
        
        BeginDrawing();
        
        ClearBackground(BLACK);
        if(IsKeyPressed(KEY_F12)){
            TakeScreenshot(1);
        }
        
        if(debug == true){
            DrawFPS(10, 20);
            DrawText("Debug mode: On", 10, 10, 10, GREEN);
            
            /*DrawText("X:", 10, 4
            0, 10, GREEN); // Crashes the game for some reason    
            DrawText(x, 15, 40, 10, GREEN);*/
            
            switch(enableVert){
            case true:
                DrawText("Vertical movement: On", 10, 40, 10, GREEN);
                break;
            case false:
                DrawText("Vertical movement: Off", 10, 40, 10, RED);
                break;
            }
            
            switch(enableAccel){
            case true:
                DrawText("Acceleration: On", 10, 50, 10, GREEN);
                break;
            case false:
                DrawText("Acceleration: Off", 10, 50, 10, RED);
                break;
            }
            
        }
        
        
        DrawCircle(x, y, 5, WHITE); //Draws a circle(player)
        //Draws lines to represent portals
        DrawLineEx((Vector2){1, screenHeight}, (Vector2){0, 0}, 3, DARKBLUE); // Left portal
        DrawLineEx((Vector2){screenWidth, screenHeight}, (Vector2){screenWidth, 0}, 3, ORANGE); // Right portal
        DrawLineEx((Vector2){1, screenHeight}, (Vector2){screenWidth, screenHeight}, 3, SKYBLUE); // Down portal
        DrawLineEx((Vector2){1, 1}, (Vector2){screenWidth, 1}, 3, YELLOW); // Up portal

        EndDrawing();
    }
    
     CloseWindow();        // Close window and OpenGL context
     
     return 0;
}