#include <iostream>
#include <raylib.h>

using namespace std;
int player_score=0;
int cpu_score=0;

//Create a ball class
class Ball{
public:
float x, y;
int speed_x, speed_y;
int radius;
void Draw(){
        DrawCircle (x,y, radius, WHITE);
    }
    void Update(){ //Let's create an update object
            x+=speed_x;
            y+=speed_y;

            if(y+radius>=800|| y-radius<=0 ){ //GetScreenheight 
                speed_y*=-1;
            }
            if (x+radius>=1280){
                cpu_score++;
                ResetBall();
            }
            if (x-radius<=0){
                player_score++;
                ResetBall();
            }
        }
        void ResetBall(){
            x= GetScreenWidth()/2;
            y=GetScreenHeight()/2;
            int speed_choices[2]={-1, 1};
            speed_x*=speed_choices[GetRandomValue(0,1)];
            speed_y*=speed_choices[GetRandomValue(0,1)];

        }
};
class Paddle{
    protected:
    void LimitMovement(){
         if (y<=0){
            y=0;
        }
        if (y+height>=GetScreenHeight()){
            y=GetScreenHeight()-height;
        }
    }
    public:
    float x,y;
    float width, height;
    int speed;

    void Draw(){
        DrawRectangle (x, y,width, height,WHITE);
    }
    void Update(){
        if(IsKeyDown(KEY_UP)){
            y=y-speed;
        }
        if (IsKeyDown(KEY_DOWN)){
            y=y+speed;

        }
        LimitMovement();
    }
};
class CpuPaddle: public Paddle{
    public:
    void Update(int ball_y){
        //AI algorithm
        if(y+height/2>ball_y){
            y=y-speed;
        }
        if(y+height/2<=ball_y){
            y=y+speed;
        }
        LimitMovement(); //to avoid duplicate code 
                      
    }
};

Ball ball;
Paddle player; //paddle player 
CpuPaddle cpu;
int main () {
    cout <<"Starting the game"<<endl;
    const int screen_width=1280;
    const int screen_height=800;
    InitWindow(screen_width,screen_height, "My Pong Game!");
    SetTargetFPS(60);
    ball.radius= 20;
    ball.x =screen_width/2;
    ball.y=screen_height/2;
    ball.speed_x=7;
    ball.speed_y=7;

    player.width=25;
    player.height=120;
    player.x=screen_width-player.width-10;
    player.y=screen_height/2-player.height/2;
    player.speed=6;

    cpu.height=120;
    cpu.width=25;
    cpu.x=10;
    cpu.y=screen_height/2-cpu.height/2;
    cpu.speed=6;

    while (WindowShouldClose()==false){ //WindowShouldClose is a function
        //Update the poitions of the game objects
        BeginDrawing();
        ball.Update();
        player.Update();
        cpu.Update(ball.y);
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius, Rectangle{player.x, player.y, player.width, player.height})){
            ball.speed_x*=-1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.y, cpu.width, cpu.height})){
            ball.speed_x*=-1;
        }
        ClearBackground(BLACK);
        DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);
        ball.Draw();
        cpu.Draw();
        //DrawCircle (screen_width/2, screen_height/2, 20, WHITE); 
       // DrawRectangle(10, screen_height/2-60, 25, 120, WHITE);
       // DrawRectangle (screen_width-35, screen_height/2-60, 25, 120, WHITE); //DrawRectang;e (int posX, posY, int width, int height, Color color)
        player.Draw();
        DrawText(TextFormat("%i",cpu_score), screen_width/4-20, 20, 80, WHITE);
         DrawText(TextFormat("%i",player_score), 3*screen_width/4-20, 20, 80, WHITE);
        EndDrawing();
        //Check for collisions at the end
    if(player_score>=15||cpu_score>=15){
        break;
    }
    }
    CloseWindow();

    

    
    return 0;
}