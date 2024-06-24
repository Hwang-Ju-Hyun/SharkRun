#include "Game.h"
#include "Collision.h"
CP_Color white;

CP_Image bgImg;
CP_Image tile[3];

struct Platforms* mP;
//struct Platforms platforms;
struct Shark shark;
struct Player player;
struct Camera camera;
struct Item item;
float time = 0;
float AccTime = 0.f;
float CamTexAccTime = 0.f;
int CamTexAccTimeInt = 0;
bool AccTimeAdd = true;
float texTime = 0.f;
int AcctexTimeInt = 0;
bool IsdeathSound = false;

//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
//털끝 하나 건들지 말것
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
void handleCollision(struct Player* p, struct Platform* plat)
{
    float dt = CP_System_GetDt();

    // 플레이어가 플랫폼의 윗면에 충돌한 경우
    if (p->velocityY > 0 &&
        p->Pos.y + p->height <= plat->col.Pos.y + p->velocityY * dt &&
        p->Pos.y + p->height > plat->col.Pos.y) 
    {
        p->Pos.y = plat->col.Pos.y - p->height;
        p->velocityY = 0;
        p->IsGrounded = GROUND;
    }
    // 플레이어가 플랫폼의 아랫면에 충돌한 경우
    else if (p->velocityY < 1.f &&
        p->Pos.y >= plat->col.Pos.y + plat->col.h + p->velocityY * dt)
    {
        p->Pos.y = plat->col.Pos.y + plat->col.h;
        p->velocityY = 0;
    }
    // 플레이어가 플랫폼의 오른쪽 면에 충돌한 경우
    else if (p->velocityX < 1.f &&
        p->Pos.x <= plat->col.Pos.x + plat->col.w - p->velocityX * dt)
    {
        p->Pos.x = plat->col.Pos.x + plat->col.w;
        p->velocityX = 0;
    }
    // 플레이어가 플랫폼의 왼쪽 면에 충돌한 경우
    else if (p->velocityX > 0 &&
        p->Pos.x + p->width <= plat->col.Pos.x + p->velocityX * dt)
    {
        p->Pos.x = plat->col.Pos.x - p->width;
        p->velocityX = 0;
    }
}
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
//털끝 하나 건들지 말것
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑

//폰트
CP_Font myFont;

//사운드
CP_Sound jump_sound1 = NULL;
CP_Sound jump_sound2 = NULL;
CP_Sound jump_sound3 = NULL;
CP_Sound death_sound = NULL;




void game_init(void)
{
    white = CP_Color_Create(255, 255, 255, 255);
	bgImg = CP_Image_Load("Assets\\bg.png");
   


    //폰트 로드
    myFont=CP_Font_Load("Assets/upheavtt.ttf");
    if (myFont == NULL)
    {
        printf("凸");
        return;
    }
    //사운드 로드
    death_sound = CP_Sound_Load("./Assets/death.wav");
    jump_sound1 = CP_Sound_Load("./Assets/jump1.wav");
    jump_sound2 = CP_Sound_Load("./Assets/jump2.wav");
    jump_sound3 = CP_Sound_Load("./Assets/jump3.wav");
    //플렛폼 로드
    InitTileImg(tile);

    //플레이어 초기로드
    PlayerInit(&player);
    //샤크 초기로드
    SharkInit(&shark);
    //카메라 초기로드
    Camera_Init(&camera);

    //플랫폼 초기화
    if (mP != NULL)
    {
        DeallocatePlatform(mP);
        free(mP);
    }
    mP = malloc(sizeof(struct Platforms));
    mP->pf = NULL;
    int ch = LoadPlatformFromFile(mP, &player);
    printf("ch = %d\n", ch);
    AccTime = 0.f;	
}

void PlatColliderDraw()
{
    for (int i = 0; i < mP->total; i++)
    {
        CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
        CP_Graphics_DrawRect(mP->pf[i].col.Pos.x, mP->pf[i].col.Pos.y, mP->pf[i].col.w, mP->pf[i].col.h);
    }
}

void PlayerColliderDraw()
{
    CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
    CP_Graphics_DrawRect(player.Pos.x, player.Pos.y, player.width, player.height);
}


void game_update(void)
{    
    CP_Graphics_ClearBackground(white);    
    CP_Settings_Fill(CP_Color_Create(0, 255, 255, 255));
    CP_Font_Set(myFont);
    /*if (CP_Input_MouseTriggered(MOUSE_BUTTON_RIGHT))
    {
        CP_Engine_SetNextGameState(main_init, main_update, main_exit);
    }    */

    // Delta Time 받기    
    time = CP_System_GetDt();
    if(AccTimeAdd==true)
        AccTime += time;
    // Render first
    {
        CP_Image_Draw(bgImg, (float)CP_Image_GetWidth(bgImg) / 2, (float)CP_Image_GetHeight(bgImg) / 2, (float)CP_Image_GetWidth(bgImg), (float)CP_Image_GetHeight(bgImg), 255);

        CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
        /*CP_Settings_TextSize(50.0f);
        CP_Font_DrawText("Game", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);*/
    }

    //카메라 업데이트
    {
        CameraUpdate(&camera, &player);
    }
    
    // 플레이어 이동input 처리와 상어 이동   
    {
        Move_Player(&player, mP, time);
        SharkMove(&shark, time, &player);
    }
    if (player.soundOccur)
    {
        int rand = CP_Random_RangeInt(0, 2);
        switch (rand)
        {
        case 0:
            CP_Sound_Play(jump_sound1);
            break;
        case 1:
            CP_Sound_Play(jump_sound2);
            break;
        case 2:
            CP_Sound_Play(jump_sound3);
            break;
        }
        player.soundOccur = false;
    }

    // 중력 처리
    {
        player.velocityY += 981.f * time;
    }
    
    // 위치 업데이트
    {
        player.Pos.x += player.velocityX * time;
        player.Pos.y += player.velocityY * time;
    }
    
    struct Platform* p = GetFirstDeadPlatform(mP);
    if (p != NULL)
        InitPlatformRandom(mP, p, &player, Alive);

    UpdateAllPlatforms(mP,&player);
    DrawAllPlatforms(mP, tile, &camera);
    Draw_Player(&player, &camera);
    SharkDraw(&shark, &camera, &player);

    // 플레이어와 플랫폼 간의 충돌 체크 및 처리
    {
        for (int i = 0; i < mP->total; i++)
        {
            if (checkCollision(&player, &mP->pf[i]))
            {
                handleCollision(&player, &mP->pf[i]);
            }
        }
    }
    
    if (AccTime >= 15.f&&AccTime<=30.f)
    {
        shark.speed = 250.f;
        for (int i = 0; i < mP->total; i++)
        {
            mP->pf[i].lifeTime = (mP->pf[i].Pos.x) / 600;
        }
        camera.cameraChange = false;
        CamTexAccTime = 0.f;
        CamTexAccTimeInt = 0;
    }
    else if (AccTime >= 30.f && AccTime < 50.f)
    {
        shark.speed = 265.f;
        for (int i = 0; i < mP->total; i++)
        {
            mP->pf[i].lifeTime = (mP->pf[i].Pos.x) / 1600;
        }
        camera.cameraChange = true;
    }
    else if (AccTime > 50.f&&AccTime<=75.f)
    {
        //printf("\n\n\n50second acc\n\n\n");
        shark.speed = 280.f;
        for (int i = 0; i < mP->total; i++)
        {
            mP->pf[i].lifeTime = (mP->pf[i].Pos.x) / 2800;        
        }
        camera.cameraChange =false;
        CamTexAccTime = 0.f;
        CamTexAccTimeInt = 0;
    } 
    else if (AccTime > 75.f && AccTime < 120.f)
    {
        camera.cameraChange = true;        
    }
    else if (AccTime > 120.f)
    {
        //printf("\n\n\n50second acc\n\n\n");
        shark.speed = 300.f;
        camera.cameraChange = false;
        CamTexAccTime =0.f;
        CamTexAccTimeInt = 0;
        for (int i = 0; i < mP->total; i++)
        {
            mP->pf[i].lifeTime = (mP->pf[i].Pos.x) / 2800;
        }
    }
   
    if (CP_Input_KeyTriggered(KEY_Q))//플레이어 포지션 따라가기
    {
        camera.cameraPos.x = player.Pos.x;
        camera.cameraPos.y = player.Pos.y;
        //SharkSpeedUp(&shark, 100.f);
    }
    

    //Alive Texture draw
    {
        if (player.IsAlive == true)
        {   
            CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
            CP_Settings_TextSize(50.f);
            CP_Font_DrawText("TIME : ", 225, 650);

            CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
            char buffer[50] = { 0 };            
            sprintf_s(buffer, 50, "%f", AccTime);            
            CP_Font_DrawText(buffer, 460, 650);
        }        
    }       
    
    
    if (camera.cameraChange == true)
    {
        CamTexAccTime += CP_System_GetDt();
        CamTexAccTimeInt =(int)CamTexAccTime;
        CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
        CP_Settings_TextSize(40.f);
        CP_Font_DrawText("!!ARROW KEY REVERSED!!", 750, 640);        
    }
    if (CamTexAccTimeInt % 3 == 0&& camera.cameraChange == true)
    {
        CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
        CP_Settings_TextSize(40.f);
        CP_Font_DrawText("!!ARROW KEY REVERSED!!", 750, 640);
    }
    


    //플레이어가 땅아래로 추락할시 게임 종료
    if ((WINDOW_HEIGHT <= GetRenderPlayerPos(&player,&camera).y)&& player.velocityY>=1000
        || sharkCollision(&player, &shark))
    {
        time = 0.0;
        CP_Settings_Fill(CP_Color_Create(250, 180, 0, 100));
        CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
        CP_Graphics_DrawRect((WINDOW_WIDTH / 2) - 250, (WINDOW_HEIGHT / 2) - 120, 500, 300);
        CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
        
        if (IsdeathSound == false)
        {
            CP_Sound_Play(death_sound); //으르르르를~ 깨개깽
            IsdeathSound = true;
        }
        
        
        texTime += CP_System_GetDt()+0.f;
        AcctexTimeInt =(int)texTime;
        char buffer[50] = { 0 };
        if (AcctexTimeInt % 2 != 0)
        {
            CP_Settings_Fill(CP_Color_Create(CP_Random_RangeInt(150,255),0, CP_Random_RangeInt(0, 255), 255));
            sprintf_s(buffer, 50, "TIME : %f", AccTime);
            CP_Settings_TextSize(50.0f);
            //CP_Font_DrawText(buffer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 20.f);
            CP_Font_DrawText(buffer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 5.f);
        }
        else
        {
            CP_Settings_Fill(CP_Color_Create(CP_Random_RangeInt(150, 255), 0, CP_Random_RangeInt(0, 255), 255));
            sprintf_s(buffer, 50, "TIME : %f", AccTime);
            CP_Settings_TextSize(50.0f);
            CP_Font_DrawText(buffer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 5.f);
        }
        
        CP_Settings_Fill(CP_Color_Create(240, 0, 0, 255));
        CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
        CP_Settings_TextSize(50.0f);
        CP_Font_DrawText("GAME OVER", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2-80.f);
        CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
        CP_Settings_TextSize(30.0f);        
        CP_Font_DrawText("Restart Press 'R' Button", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2+60 );
        CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
        CP_Settings_TextSize(30.0f);
        CP_Font_DrawText("Quit 'Q' Button", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 +100);
        player.IsAlive = false;
        AccTimeAdd = false;
    }
    if (player.IsAlive == false)
    {
        mP->total = 0;             
        //재시작
        if (CP_Input_KeyTriggered(KEY_R))
        {          
            game_init();
            player.IsAlive = true;
            AccTimeAdd = true;
            IsdeathSound = false;
        }
        if (CP_Input_KeyTriggered(KEY_Q))
        {
            game_exit();
            CP_Engine_SetNextGameState(main_init, main_update, main_exit);
        }
    }
}

void game_exit(void)
{
    if (mP != NULL)
    {
        DeallocatePlatform(mP);
        free(mP);
    }

	SharkFree(&shark);
	FreeImg(tile);
    CP_Sound_Free(&jump_sound1);
    CP_Sound_Free(&jump_sound2);
    CP_Sound_Free(&jump_sound3);
    CP_Sound_Free(&death_sound);
}