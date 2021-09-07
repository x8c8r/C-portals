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
    const bool debug = true; //Debug mode(not made yet)
    const bool enableAccel = false;//Enable acceleration(Broken for the time being
    const bool enableVert = true;
    const bool enableFake = false;
    
    
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        if(IsKeyDown(KEY_RIGHT) && !IsKeyPressed(KEY_LEFT)){ //Makes the circle go right
          x = x+Speed;
          //Makes the circle accelerate if the var is true
          if(enableAccel == true){
            Speed = Speed + accelAmount; 
          }
        }
        if(IsKeyDown(KEY_LEFT) && !IsKeyPressed(KEY_RIGHT)) { //Makes the circle go left
          x = x-Speed;
          //Makes the circle accelerate if the var is true
          if(enableAccel == true){
            Speed = Speed + accelAmount; 
          }
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
        if(IsKeyReleased(KEY_RIGHT) && IsKeyReleased(KEY_LEFT) && IsKeyReleased(KEY_UP) && IsKeyReleased(KEY_DOWN)){
         //If all buttons are released - Speed gets set to starting speed
            Speed = startSpeed;
        }
        if(Speed > maxSpeed){//If speed exceeds max speed it gets set back to it
          Speed = maxSpeed;
        }
        BeginDrawing();
        
        ClearBackground(BLACK);
        
        DrawCircle(x, y, 5, WHITE); //Draws a circle(player)
        //Draws lines to represent portals
        DrawLine(1, screenHeight, 0, 0, BLUE);
        DrawLine(screenWidth, screenHeight, screenWidth, 0, ORANGE);
        DrawLine(1, screenHeight, screenWidth, screenHeight, PINK);
        DrawLine(1, 1, screenWidth, 1, GREEN);

        EndDrawing();
    }
    
     CloseWindow();        // Close window and OpenGL context
     
     return 0;
}