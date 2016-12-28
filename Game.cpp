#include "Game.h"
#include "ResourceManager.h"
#include "AnimationManager.h"
#include "EventManager.h"
#include "xbutton.h"
#include "sensor.h"

#define DEF_FPS 24

#define PNAME(pictureType,pictureID) _pic_##pictureType##_##pictureID
#define PIC(pictureType,pictureID) int PNAME(pictureType,pictureID)=-1;
#define PLOAD(pictureType,pictureID) PNAME(pictureType,pictureID)=resmanager.LoadPicture("img\\" #pictureType "\\" #pictureType "_" #pictureID ".png");
#define PLOADX(pictureType,pictureID) PNAME(pictureType,pictureID)=resmanager.LoadPicture("img\\" #pictureType "\\" #pictureType "_" #pictureID ".jpg");

#include "resources_list.hpp"

#define vtt(lux,luy,rdx,rdy,ow,oh) (int)((double)lux/ow*WIN_WIDTH),(int)((double)luy/oh*WIN_HEIGHT),(int)((double)rdx/ow*WIN_WIDTH),(int)((double)rdy/oh*WIN_HEIGHT)
#define vyy(lux,luy,rdx,rdy) vtt(lux,luy,rdx,rdy,sz_w,sz_h)

namespace Game
{
    int procInit(void* args)
    {
        int* pRunning=(int*)args;
        #include "resources_load.hpp"
        *pRunning=0;
        return 0;
    }
    void Init()
    {
        resmanager.LoadPicture("img\\loading\\loading_anim_01.png",1);
        resmanager.LoadPicture("img\\loading\\loading_anim_02.png",1);
        resmanager.LoadPicture("img\\loading\\loading_anim_03.png",1);
        resmanager.LoadPicture("img\\loading\\loading_anim_04.png",1);
        resmanager.LoadPicture("img\\loading\\loading_anim_05.png",1);
        resmanager.LoadPicture("img\\loading\\loading_anim_06.png",1);
        resmanager.LoadPicture("img\\loading\\loading_anim_07.png",1);
        resmanager.LoadPicture("img\\loading\\loading_anim_08.png",1);
        resmanager.LoadPicture("img\\loading\\loading_anim_09.png",1);
        resmanager.LoadPicture("img\\loading\\loading_anim_10.png",1);
        resmanager.LoadPicture("img\\loading\\loading_anim_11.png",1);
        resmanager.LoadPicture("img\\loading\\loading_anim_12.png",1);

        int _tw=resmanager.GetSize(0).w;
        int _th=resmanager.GetSize(0).h;

        AnimationCallback loadcallback=[&](Stage& stg,int frame)->int
        {
            stg.draw(resmanager.GetPicture(frame),0,0,_tw,_th);
            return 0;
        };
        animemanager.add(AnimationCallbackPack(loadcallback,12));

        PlayList ls;
        ls.addplay(0,WIN_WIDTH/2-_tw/2,WIN_HEIGHT/2-_th/2,0,0);
        ls.addplay([&](SDL_Renderer* rnd)->int{return 0;});

        EventManager em;
        int running=1;
        int need_update=1;

        SDL_Thread* td=SDL_CreateThread(procInit,"Init Thread",&running);

        while(ls.playNext()>=0&&running)
        {
            em.pollNext(running,need_update);
            SDL_Delay(1000/DEF_FPS);
        }

        int ret;
        SDL_WaitThread(td,&ret);

        //for(int i=0;i<12;i++) resmanager.NotInUse(i);
    }
    /**
    // This Example of Event Loop use only 2% CPU.
    void Test()
    {
        EventManager evm;
        xbutton b;
        b.attachEventManager(evm);
        int running;
        int need_update;
        while(1)
        {
            if(evm.pollNext(running,need_update)>0);
            else SDL_Delay(1);
        }
    }
    */

    auto DrawRobot=[&](int& mode,int& cx,int& cy)
    {
        SDL_Texture* rtt=NULL;

        switch(mode)
        {
        case 0:
        case 1:
            cy=cy+5;
            break;
        case 3:
        case 4:
            cx=cx-5;
            break;
        case 6:
        case 7:
            cy=cy-5;
            break;
        case 9:
        case 10:
            cx=cx+5;
            break;
        }

        switch(mode)
        {
        case 0:
            rtt=resmanager.GetPicture(PNAME(robot,down_move_1));
            ++mode;
            break;
        case 1:
            rtt=resmanager.GetPicture(PNAME(robot,down_move_2));
            ++mode;
            break;
        case 2:
            rtt=resmanager.GetPicture(PNAME(robot,down_stand));
            break;
        case 3:
            rtt=resmanager.GetPicture(PNAME(robot,left_move_1));
            ++mode;
            break;
        case 4:
            rtt=resmanager.GetPicture(PNAME(robot,left_move_2));
            ++mode;
            break;
        case 5:
            rtt=resmanager.GetPicture(PNAME(robot,left_stand));
            break;
        case 6:
            rtt=resmanager.GetPicture(PNAME(robot,up_move_1));
            ++mode;
            break;
        case 7:
            rtt=resmanager.GetPicture(PNAME(robot,up_move_2));
            ++mode;
            break;
        case 8:
            rtt=resmanager.GetPicture(PNAME(robot,up_stand));
            break;
        case 9:
            rtt=resmanager.GetPicture(PNAME(robot,right_move_1));
            ++mode;
            break;
        case 10:
            rtt=resmanager.GetPicture(PNAME(robot,right_move_2));
            ++mode;
            break;
        case 11:
            rtt=resmanager.GetPicture(PNAME(robot,right_stand));
            break;
        }

        SDL_Rect dest;
        SDL_QueryTexture(rtt,NULL,NULL,&dest.w,&dest.h);
        dest.x=cx-dest.w/2;
        dest.y=cy-dest.h/2;
        SDL_RenderCopy(rnd,rtt,NULL,&dest);
    };

    #define _tool_automobile(id) _tool_automobile_jump(id) _tool_automobile_main(id)
    #define _tool_automobilex(id) _tool_automobile_jumpx(id) _tool_automobile_main(id)

    #define _tool_automobile_jump(id) \
    int LoopGameAutomobile##id##_Arg() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(automobile,id##_argument))); \
        return 1;\
    } \
    int LoopGameAutomobile##id##_His() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(automobile,id##_1_history)),resmanager.GetPicture(PNAME(automobile,id##_2_history))); \
        return 1; \
    }

    #define _tool_automobile_jumpx(id) \
    int LoopGameAutomobile##id##_Arg() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(automobile,id##_argument))); \
        return 1;\
    } \
    int LoopGameAutomobile##id##_His() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(automobile,id##_history)));\
        return 1; \
    }

    #define _tool_automobile_main(id) \
    int LoopGameAutomobile##id() \
    { \
        int running=1; \
        SDL_Event e;\
        int update=1;\
        int quit_flag=1;\
        int w,h;\
        int w2,h2;\
        xbutton check_argument;\
        check_argument.setNormal(PNAME(button,argument),empty_call);\
        check_argument.setMouseover(PNAME(button,argument_highlight),empty_call);\
        check_argument.setPressed(PNAME(button,argument),[&]()->int{return LoopGameAutomobile##id##_Arg();});\
        SDL_QueryTexture(resmanager.GetPicture(PNAME(button,argument)),NULL,NULL,&w,&h);\
        check_argument.setRange(WIN_WIDTH/4*3,WIN_HEIGHT/2,w,h);\
        xbutton check_history;\
        check_history.setNormal(PNAME(button,history),empty_call);\
        check_history.setMouseover(PNAME(button,history_highlight),empty_call);\
        check_history.setPressed(PNAME(button,history),[&]()->int{return LoopGameAutomobile##id##_His();});\
        SDL_QueryTexture(resmanager.GetPicture(PNAME(button,history)),NULL,NULL,&w2,&h2);\
        check_history.setRange(WIN_WIDTH/4*3,WIN_HEIGHT/2+h+20,w2,h2);\
        while(running)\
        {\
            while(!update&&SDL_WaitEvent(&e))\
            {\
                switch(e.type)\
                {\
                case SDL_QUIT:\
                    running=0;\
                    quit_flag=0;\
                    update=1;\
                    break;\
                case SDL_MOUSEMOTION:\
                case SDL_MOUSEBUTTONDOWN:\
                case SDL_MOUSEBUTTONUP:\
                    update=1;\
                    running=check_argument.deal(e);\
                    running=check_history.deal(e);\
                    break;\
                case SDL_KEYDOWN:\
                    if(e.key.keysym.sym==SDLK_ESCAPE)\
                    {\
                        running=0;\
                        update=1;\
                    }\
                    break;\
                }\
            }\
            SDL_RenderClear(rnd);\
            SDL_RenderCopy(rnd,resmanager.GetPicture(PNAME(automobile,id)),NULL,NULL);\
            check_argument.draw();\
            check_history.draw();\
            SDL_RenderPresent(rnd);\
            update=0;\
        }\
        return quit_flag;\
    }

    _tool_automobile(1);
    _tool_automobile(2);
    _tool_automobile(3);
    _tool_automobile(4);
    _tool_automobile(5);
    _tool_automobile(6);
    _tool_automobile(7);
    _tool_automobilex(8);
    _tool_automobilex(9);
    _tool_automobilex(10);

    int LoopGameAutomobile()
    {
        int running=1;
        SDL_Event e;
        int update=1;

        int quit_flag=1;

        int mode=2;

        int cx,cy;

        int sz_w,sz_h;
        SDL_QueryTexture(resmanager.GetPicture(PNAME(board,game2)),NULL,NULL,&sz_w,&sz_h);

        /// temp
        {
            sensor temp(vyy(74,240,153,330));
            temp.setMiddle(&cx,&cy);
        }

        sensor pos_backblock(vyy(0,240,74,331));

        sensor pos1_pic(vyy(148,94,244,172));
        sensor pos1_gate(vyy(148,172,244,239));

        sensor pos2_pic(vyy(307,94,404,172));
        sensor pos2_gate(vyy(307,172,404,239));

        sensor pos3_pic(vyy(466,94,561,172));
        sensor pos3_gate(vyy(466,172,561,239));

        sensor pos4_pic(vyy(637,94,722,172));
        sensor pos4_gate(vyy(637,172,722,239));

        sensor pos5_pic(vyy(776,94,867,172));
        sensor pos5_gate(vyy(776,177,867,240));

        sensor pos6_pic(vyy(709,407,786,487));
        sensor pos6_gate(vyy(709,332,786,407));

        sensor pos7_pic(vyy(551,407,632,487));
        sensor pos7_gate(vyy(551,332,632,407));

        sensor pos8_pic(vyy(395,407,478,487));
        sensor pos8_gate(vyy(395,332,478,407));

        sensor pos9_pic(vyy(235,405,315,487));
        sensor pos9_gate(vyy(235,332,315,407));

        sensor pos10_pic(vyy(74,405,153,487));
        sensor pos10_gate(vyy(74,332,153,407));

        while(running)
        {
            while(!update&&SDL_WaitEventTimeout(&e,10))
            {
                switch(e.type)
                {
                case SDL_QUIT:
                    running=0;
                    update=1;
                    quit_flag=0;
                    break;
                case SDL_KEYDOWN:
                {
                    update=1;
                    switch(e.key.keysym.sym)
                    {
                    case SDLK_RIGHT:
                    {
                        mode=9;
                        break;
                    }
                    case SDLK_UP:
                    {
                        mode=6;
                        break;
                    }
                    case SDLK_LEFT:
                        {
                            mode=3;
                            break;
                        }
                    case SDLK_DOWN:
                        {
                            mode=0;
                            break;
                        }
                    }
                }
                }
            }

            SDL_RenderClear(rnd);
            SDL_RenderCopy(rnd,resmanager.GetPicture(PNAME(board,game2)),NULL,NULL);
            DrawRobot(mode,cx,cy);
            SDL_RenderPresent(rnd);

            update=0;

            #define _tool_pos(CallID) else if(pos##CallID##_pic.inrange(cx,cy)) { running=LoopGameAutomobile##CallID(); pos##CallID##_gate.setMiddle(cx,cy); }

            if(pos_backblock.inrange(cx,cy))
            {
                running=0;
            }
            _tool_pos(1)
            _tool_pos(2)
            _tool_pos(3)
            _tool_pos(4)
            _tool_pos(5)
            _tool_pos(6)
            _tool_pos(7)
            _tool_pos(8)
            _tool_pos(9)
            _tool_pos(10)
        }
        return quit_flag;
    }


    #define _tool_pickup(id) _tool_pickup_jump(id) _tool_pickup_main(id)
    #define _tool_pickupx(id) _tool_pickup_jumpx(id) _tool_pickup_main(id)

    #define _tool_pickup_jump(id) \
    int LoopGamePickup##id##_Arg() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(pick_up,id##_argument))); \
        return 1;\
    } \
    int LoopGamePickup##id##_His() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(pick_up,id##_1_history)),resmanager.GetPicture(PNAME(pick_up,id##_2_history))); \
        return 1; \
    }

    #define _tool_pickup_jumpx(id) \
    int LoopGamePickup##id##_Arg() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(pick_up,id##_argument))); \
        return 1;\
    } \
    int LoopGamePickup##id##_His() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(pick_up,id##_history)));\
        return 1; \
    }

    #define _tool_pickup_main(id) \
    int LoopGamePickup##id() \
    { \
        int running=1; \
        SDL_Event e;\
        int update=1;\
        int quit_flag=1;\
        int w,h;\
        int w2,h2;\
        xbutton check_argument;\
        check_argument.setNormal(PNAME(button,argument),empty_call);\
        check_argument.setMouseover(PNAME(button,argument_highlight),empty_call);\
        check_argument.setPressed(PNAME(button,argument),[&]()->int{return LoopGamePickup##id##_Arg();});\
        SDL_QueryTexture(resmanager.GetPicture(PNAME(button,argument)),NULL,NULL,&w,&h);\
        check_argument.setRange(WIN_WIDTH/4*3,WIN_HEIGHT/2,w,h);\
        xbutton check_history;\
        check_history.setNormal(PNAME(button,history),empty_call);\
        check_history.setMouseover(PNAME(button,history_highlight),empty_call);\
        check_history.setPressed(PNAME(button,history),[&]()->int{return LoopGamePickup##id##_His();});\
        SDL_QueryTexture(resmanager.GetPicture(PNAME(button,history)),NULL,NULL,&w2,&h2);\
        check_history.setRange(WIN_WIDTH/4*3,WIN_HEIGHT/2+h+20,w2,h2);\
        while(running)\
        {\
            while(!update&&SDL_WaitEvent(&e))\
            {\
                switch(e.type)\
                {\
                case SDL_QUIT:\
                    running=0;\
                    quit_flag=0;\
                    update=1;\
                    break;\
                case SDL_MOUSEMOTION:\
                case SDL_MOUSEBUTTONDOWN:\
                case SDL_MOUSEBUTTONUP:\
                    update=1;\
                    running=check_argument.deal(e);\
                    running=check_history.deal(e);\
                    break;\
                case SDL_KEYDOWN:\
                    if(e.key.keysym.sym==SDLK_ESCAPE)\
                    {\
                        running=0;\
                        update=1;\
                    }\
                    break;\
                }\
            }\
            SDL_RenderClear(rnd);\
            SDL_RenderCopy(rnd,resmanager.GetPicture(PNAME(pick_up,id)),NULL,NULL);\
            check_argument.draw();\
            check_history.draw();\
            SDL_RenderPresent(rnd);\
            update=0;\
        }\
        return quit_flag;\
    }

    _tool_pickup(2)
    _tool_pickup(5);
    _tool_pickup(9);

    _tool_pickupx(1);
    _tool_pickupx(3);
    _tool_pickupx(4);
    _tool_pickupx(6);
    _tool_pickupx(7);
    _tool_pickupx(8);
    _tool_pickupx(10);

    int LoopGamePickup()
    {
        int running=1;
        SDL_Event e;
        int update=1;

        int quit_flag=1;

        int mode=2;

        int cx,cy;

        int sz_w,sz_h;
        SDL_QueryTexture(resmanager.GetPicture(PNAME(board,game2)),NULL,NULL,&sz_w,&sz_h);

        /// temp
        {
            sensor temp(vyy(74,240,153,330));
            temp.setMiddle(&cx,&cy);
        }

        sensor pos_backblock(vyy(0,240,74,331));

        sensor pos1_pic(vyy(148,94,244,172));
        sensor pos1_gate(vyy(148,172,244,239));

        sensor pos2_pic(vyy(307,94,404,172));
        sensor pos2_gate(vyy(307,172,404,239));

        sensor pos3_pic(vyy(466,94,561,172));
        sensor pos3_gate(vyy(466,172,561,239));

        sensor pos4_pic(vyy(637,94,722,172));
        sensor pos4_gate(vyy(637,172,722,239));

        sensor pos5_pic(vyy(776,94,867,172));
        sensor pos5_gate(vyy(776,177,867,240));

        sensor pos6_pic(vyy(709,407,786,487));
        sensor pos6_gate(vyy(709,332,786,407));

        sensor pos7_pic(vyy(551,407,632,487));
        sensor pos7_gate(vyy(551,332,632,407));

        sensor pos8_pic(vyy(395,407,478,487));
        sensor pos8_gate(vyy(395,332,478,407));

        sensor pos9_pic(vyy(235,405,315,487));
        sensor pos9_gate(vyy(235,332,315,407));

        sensor pos10_pic(vyy(74,405,153,487));
        sensor pos10_gate(vyy(74,332,153,407));

        while(running)
        {
            while(!update&&SDL_WaitEventTimeout(&e,10))
            {
                switch(e.type)
                {
                case SDL_QUIT:
                    running=0;
                    update=1;
                    quit_flag=0;
                    break;
                case SDL_KEYDOWN:
                {
                    update=1;
                    switch(e.key.keysym.sym)
                    {
                    case SDLK_RIGHT:
                    {
                        mode=9;
                        break;
                    }
                    case SDLK_UP:
                    {
                        mode=6;
                        break;
                    }
                    case SDLK_LEFT:
                        {
                            mode=3;
                            break;
                        }
                    case SDLK_DOWN:
                        {
                            mode=0;
                            break;
                        }
                    }
                }
                }
            }

            SDL_RenderClear(rnd);
            SDL_RenderCopy(rnd,resmanager.GetPicture(PNAME(board,game2)),NULL,NULL);
            DrawRobot(mode,cx,cy);
            SDL_RenderPresent(rnd);

            update=0;

            #undef _tool_pos
            #define _tool_pos(CallID) else if(pos##CallID##_pic.inrange(cx,cy)) { running=LoopGamePickup##CallID(); pos##CallID##_gate.setMiddle(cx,cy); }

            if(pos_backblock.inrange(cx,cy))
            {
                running=0;
            }
            _tool_pos(1)
            _tool_pos(2)
            _tool_pos(3)
            _tool_pos(4)
            _tool_pos(5)
            _tool_pos(6)
            _tool_pos(7)
            _tool_pos(8)
            _tool_pos(9)
            _tool_pos(10)
        }
        return quit_flag;
    }



    #define _tool_suv(id) _tool_suv_jump(id) _tool_suv_main(id)
    #define _tool_suvx(id) _tool_suv_jumpx(id) _tool_suv_main(id)
    #define _tool_suvxx(id) _tool_suv_jumpxx(id) _tool_suv_main(id)

    #define _tool_suv_jump(id) \
    int LoopGamesuv##id##_Arg() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(SUV,id##_argument))); \
        return 1;\
    } \
    int LoopGamesuv##id##_His() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(SUV,id##_1_history)),resmanager.GetPicture(PNAME(SUV,id##_2_history))); \
        return 1; \
    }

    #define _tool_suv_jumpxx(id) \
    int LoopGamesuv##id##_Arg() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(SUV,id##_argument))); \
        return 1;\
    } \
    int LoopGamesuv##id##_His() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(SUV,id##_1_history)),resmanager.GetPicture(PNAME(SUV,id##_2_history)),resmanager.GetPicture(PNAME(SUV,id##_3_history))); \
        return 1; \
    }

    #define _tool_suv_jumpx(id) \
    int LoopGamesuv##id##_Arg() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(SUV,id##_argument))); \
        return 1;\
    } \
    int LoopGamesuv##id##_His() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(SUV,id##_history)));\
        return 1; \
    }

    #define _tool_suv_main(id) \
    int LoopGamesuv##id() \
    { \
        int running=1; \
        SDL_Event e;\
        int update=1;\
        int quit_flag=1;\
        int w,h;\
        int w2,h2;\
        xbutton check_argument;\
        check_argument.setNormal(PNAME(button,argument),empty_call);\
        check_argument.setMouseover(PNAME(button,argument_highlight),empty_call);\
        check_argument.setPressed(PNAME(button,argument),[&]()->int{return LoopGamesuv##id##_Arg();});\
        SDL_QueryTexture(resmanager.GetPicture(PNAME(button,argument)),NULL,NULL,&w,&h);\
        check_argument.setRange(WIN_WIDTH/4*3,WIN_HEIGHT/2,w,h);\
        xbutton check_history;\
        check_history.setNormal(PNAME(button,history),empty_call);\
        check_history.setMouseover(PNAME(button,history_highlight),empty_call);\
        check_history.setPressed(PNAME(button,history),[&]()->int{return LoopGamesuv##id##_His();});\
        SDL_QueryTexture(resmanager.GetPicture(PNAME(button,history)),NULL,NULL,&w2,&h2);\
        check_history.setRange(WIN_WIDTH/4*3,WIN_HEIGHT/2+h+20,w2,h2);\
        while(running)\
        {\
            while(!update&&SDL_WaitEvent(&e))\
            {\
                switch(e.type)\
                {\
                case SDL_QUIT:\
                    running=0;\
                    quit_flag=0;\
                    update=1;\
                    break;\
                case SDL_MOUSEMOTION:\
                case SDL_MOUSEBUTTONDOWN:\
                case SDL_MOUSEBUTTONUP:\
                    update=1;\
                    running=check_argument.deal(e);\
                    running=check_history.deal(e);\
                    break;\
                case SDL_KEYDOWN:\
                    if(e.key.keysym.sym==SDLK_ESCAPE)\
                    {\
                        running=0;\
                        update=1;\
                    }\
                    break;\
                }\
            }\
            SDL_RenderClear(rnd);\
            SDL_RenderCopy(rnd,resmanager.GetPicture(PNAME(SUV,id)),NULL,NULL);\
            check_argument.draw();\
            check_history.draw();\
            SDL_RenderPresent(rnd);\
            update=0;\
        }\
        return quit_flag;\
    }

    _tool_suv(2)
    _tool_suv(3);
    _tool_suv(4);
    _tool_suv(5);
    _tool_suv(6);
    _tool_suv(7);
    _tool_suv(10);

    _tool_suvx(1)
    _tool_suvx(8)

    _tool_suvxx(9)

    int LoopGameSUV()
    {
        int running=1;
        SDL_Event e;
        int update=1;

        int quit_flag=1;

        int mode=2;

        int cx,cy;

        int sz_w,sz_h;
        SDL_QueryTexture(resmanager.GetPicture(PNAME(board,game2)),NULL,NULL,&sz_w,&sz_h);

        /// temp
        {
            sensor temp(vyy(74,240,153,330));
            temp.setMiddle(&cx,&cy);
        }

        sensor pos_backblock(vyy(0,240,74,331));

        sensor pos1_pic(vyy(148,94,244,172));
        sensor pos1_gate(vyy(148,172,244,239));

        sensor pos2_pic(vyy(307,94,404,172));
        sensor pos2_gate(vyy(307,172,404,239));

        sensor pos3_pic(vyy(466,94,561,172));
        sensor pos3_gate(vyy(466,172,561,239));

        sensor pos4_pic(vyy(637,94,722,172));
        sensor pos4_gate(vyy(637,172,722,239));

        sensor pos5_pic(vyy(776,94,867,172));
        sensor pos5_gate(vyy(776,177,867,240));

        sensor pos6_pic(vyy(709,407,786,487));
        sensor pos6_gate(vyy(709,332,786,407));

        sensor pos7_pic(vyy(551,407,632,487));
        sensor pos7_gate(vyy(551,332,632,407));

        sensor pos8_pic(vyy(395,407,478,487));
        sensor pos8_gate(vyy(395,332,478,407));

        sensor pos9_pic(vyy(235,405,315,487));
        sensor pos9_gate(vyy(235,332,315,407));

        sensor pos10_pic(vyy(74,405,153,487));
        sensor pos10_gate(vyy(74,332,153,407));

        while(running)
        {
            while(!update&&SDL_WaitEventTimeout(&e,10))
            {
                switch(e.type)
                {
                case SDL_QUIT:
                    running=0;
                    update=1;
                    quit_flag=0;
                    break;
                case SDL_KEYDOWN:
                {
                    update=1;
                    switch(e.key.keysym.sym)
                    {
                    case SDLK_RIGHT:
                    {
                        mode=9;
                        break;
                    }
                    case SDLK_UP:
                    {
                        mode=6;
                        break;
                    }
                    case SDLK_LEFT:
                        {
                            mode=3;
                            break;
                        }
                    case SDLK_DOWN:
                        {
                            mode=0;
                            break;
                        }
                    }
                }
                }
            }

            SDL_RenderClear(rnd);
            SDL_RenderCopy(rnd,resmanager.GetPicture(PNAME(board,game2)),NULL,NULL);
            DrawRobot(mode,cx,cy);
            SDL_RenderPresent(rnd);

            update=0;

            #undef _tool_pos
            #define _tool_pos(CallID) else if(pos##CallID##_pic.inrange(cx,cy)) { running=LoopGamesuv##CallID(); pos##CallID##_gate.setMiddle(cx,cy); }

            if(pos_backblock.inrange(cx,cy))
            {
                running=0;
            }
            _tool_pos(1)
            _tool_pos(2)
            _tool_pos(3)
            _tool_pos(4)
            _tool_pos(5)
            _tool_pos(6)
            _tool_pos(7)
            _tool_pos(8)
            _tool_pos(9)
            _tool_pos(10)
        }
        return quit_flag;
    }

    #define _tool_bus(id) _tool_bus_jump(id) _tool_bus_main(id)
    #define _tool_busx(id) _tool_bus_jumpx(id) _tool_bus_main(id)

    #define _tool_bus_jump(id) \
    int LoopGamebus##id##_Arg() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(bus,id##_argument))); \
        return 1;\
    } \
    int LoopGamebus##id##_His() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(bus,id##_1_history)),resmanager.GetPicture(PNAME(bus,id##_2_history))); \
        return 1; \
    }

    #define _tool_bus_jumpx(id) \
    int LoopGamebus##id##_Arg() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(bus,id##_argument))); \
        return 1;\
    } \
    int LoopGamebus##id##_His() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(bus,id##_history)));\
        return 1; \
    }

    #define _tool_bus_main(id) \
    int LoopGamebus##id() \
    { \
        int running=1; \
        SDL_Event e;\
        int update=1;\
        int quit_flag=1;\
        int w,h;\
        int w2,h2;\
        xbutton check_argument;\
        check_argument.setNormal(PNAME(button,argument),empty_call);\
        check_argument.setMouseover(PNAME(button,argument_highlight),empty_call);\
        check_argument.setPressed(PNAME(button,argument),[&]()->int{return LoopGamebus##id##_Arg();});\
        SDL_QueryTexture(resmanager.GetPicture(PNAME(button,argument)),NULL,NULL,&w,&h);\
        check_argument.setRange(WIN_WIDTH/4*3,WIN_HEIGHT/2,w,h);\
        xbutton check_history;\
        check_history.setNormal(PNAME(button,history),empty_call);\
        check_history.setMouseover(PNAME(button,history_highlight),empty_call);\
        check_history.setPressed(PNAME(button,history),[&]()->int{return LoopGamebus##id##_His();});\
        SDL_QueryTexture(resmanager.GetPicture(PNAME(button,history)),NULL,NULL,&w2,&h2);\
        check_history.setRange(WIN_WIDTH/4*3,WIN_HEIGHT/2+h+20,w2,h2);\
        while(running)\
        {\
            while(!update&&SDL_WaitEvent(&e))\
            {\
                switch(e.type)\
                {\
                case SDL_QUIT:\
                    running=0;\
                    quit_flag=0;\
                    update=1;\
                    break;\
                case SDL_MOUSEMOTION:\
                case SDL_MOUSEBUTTONDOWN:\
                case SDL_MOUSEBUTTONUP:\
                    update=1;\
                    running=check_argument.deal(e);\
                    running=check_history.deal(e);\
                    break;\
                case SDL_KEYDOWN:\
                    if(e.key.keysym.sym==SDLK_ESCAPE)\
                    {\
                        running=0;\
                        update=1;\
                    }\
                    break;\
                }\
            }\
            SDL_RenderClear(rnd);\
            SDL_RenderCopy(rnd,resmanager.GetPicture(PNAME(bus,id)),NULL,NULL);\
            check_argument.draw();\
            check_history.draw();\
            SDL_RenderPresent(rnd);\
            update=0;\
        }\
        return quit_flag;\
    }

    _tool_bus(1);
    _tool_bus(4);

    _tool_busx(2);
    _tool_busx(3);
    _tool_busx(5);


    int LoopGameBus()
    {
        int running=1;
        SDL_Event e;
        int update=1;

        int quit_flag=1;

        int mode=2;

        int cx,cy;

        int sz_w,sz_h;
        SDL_QueryTexture(resmanager.GetPicture(PNAME(board,game2)),NULL,NULL,&sz_w,&sz_h);

        /// temp
        {
            sensor temp(vyy(74,240,153,330));
            temp.setMiddle(&cx,&cy);
        }

        sensor pos_backblock(vyy(0,240,74,331));

        sensor pos1_pic(vyy(148,94,244,172));
        sensor pos1_gate(vyy(148,172,244,239));

        sensor pos2_pic(vyy(307,94,404,172));
        sensor pos2_gate(vyy(307,172,404,239));

        sensor pos3_pic(vyy(466,94,561,172));
        sensor pos3_gate(vyy(466,172,561,239));

        sensor pos4_pic(vyy(637,94,722,172));
        sensor pos4_gate(vyy(637,172,722,239));

        sensor pos5_pic(vyy(776,94,867,172));
        sensor pos5_gate(vyy(776,177,867,240));

        sensor pos6_pic(vyy(709,407,786,487));
        sensor pos6_gate(vyy(709,332,786,407));

        sensor pos7_pic(vyy(551,407,632,487));
        sensor pos7_gate(vyy(551,332,632,407));

        sensor pos8_pic(vyy(395,407,478,487));
        sensor pos8_gate(vyy(395,332,478,407));

        sensor pos9_pic(vyy(235,405,315,487));
        sensor pos9_gate(vyy(235,332,315,407));

        sensor pos10_pic(vyy(74,405,153,487));
        sensor pos10_gate(vyy(74,332,153,407));

        while(running)
        {
            while(!update&&SDL_WaitEventTimeout(&e,10))
            {
                switch(e.type)
                {
                case SDL_QUIT:
                    running=0;
                    update=1;
                    quit_flag=0;
                    break;
                case SDL_KEYDOWN:
                {
                    update=1;
                    switch(e.key.keysym.sym)
                    {
                    case SDLK_RIGHT:
                    {
                        mode=9;
                        break;
                    }
                    case SDLK_UP:
                    {
                        mode=6;
                        break;
                    }
                    case SDLK_LEFT:
                        {
                            mode=3;
                            break;
                        }
                    case SDLK_DOWN:
                        {
                            mode=0;
                            break;
                        }
                    }
                }
                }
            }

            SDL_RenderClear(rnd);
            SDL_RenderCopy(rnd,resmanager.GetPicture(PNAME(board,game2)),NULL,NULL);
            DrawRobot(mode,cx,cy);
            SDL_RenderPresent(rnd);

            update=0;

            #undef _tool_pos
            #define _tool_pos(CallID) else if(pos##CallID##_pic.inrange(cx,cy)) { running=LoopGamebus##CallID(); pos##CallID##_gate.setMiddle(cx,cy); }

            if(pos_backblock.inrange(cx,cy))
            {
                running=0;
            }
            _tool_pos(1)
            _tool_pos(2)
            _tool_pos(3)
            _tool_pos(4)
            _tool_pos(5)
        }
        return quit_flag;
    }


    #define _tool_minibus(id) _tool_minibus_jump(id) _tool_minibus_main(id)
    #define _tool_minibusx(id) _tool_minibus_jumpx(id) _tool_minibus_main(id)

    #define _tool_minibus_jump(id) \
    int LoopGameminibus##id##_Arg() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(minibus,id##_argument))); \
        return 1;\
    } \
    int LoopGameminibus##id##_His() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(minibus,id##_1_history)),resmanager.GetPicture(PNAME(minibus,id##_2_history))); \
        return 1; \
    }

    #define _tool_minibus_jumpx(id) \
    int LoopGameminibus##id##_Arg() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(minibus,id##_argument))); \
        return 1;\
    } \
    int LoopGameminibus##id##_His() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(minibus,id##_history)));\
        return 1; \
    }

    #define _tool_minibus_main(id) \
    int LoopGameminibus##id() \
    { \
        int running=1; \
        SDL_Event e;\
        int update=1;\
        int quit_flag=1;\
        int w,h;\
        int w2,h2;\
        xbutton check_argument;\
        check_argument.setNormal(PNAME(button,argument),empty_call);\
        check_argument.setMouseover(PNAME(button,argument_highlight),empty_call);\
        check_argument.setPressed(PNAME(button,argument),[&]()->int{return LoopGameminibus##id##_Arg();});\
        SDL_QueryTexture(resmanager.GetPicture(PNAME(button,argument)),NULL,NULL,&w,&h);\
        check_argument.setRange(WIN_WIDTH/4*3,WIN_HEIGHT/2,w,h);\
        xbutton check_history;\
        check_history.setNormal(PNAME(button,history),empty_call);\
        check_history.setMouseover(PNAME(button,history_highlight),empty_call);\
        check_history.setPressed(PNAME(button,history),[&]()->int{return LoopGameminibus##id##_His();});\
        SDL_QueryTexture(resmanager.GetPicture(PNAME(button,history)),NULL,NULL,&w2,&h2);\
        check_history.setRange(WIN_WIDTH/4*3,WIN_HEIGHT/2+h+20,w2,h2);\
        while(running)\
        {\
            while(!update&&SDL_WaitEvent(&e))\
            {\
                switch(e.type)\
                {\
                case SDL_QUIT:\
                    running=0;\
                    quit_flag=0;\
                    update=1;\
                    break;\
                case SDL_MOUSEMOTION:\
                case SDL_MOUSEBUTTONDOWN:\
                case SDL_MOUSEBUTTONUP:\
                    update=1;\
                    running=check_argument.deal(e);\
                    running=check_history.deal(e);\
                    break;\
                case SDL_KEYDOWN:\
                    if(e.key.keysym.sym==SDLK_ESCAPE)\
                    {\
                        running=0;\
                        update=1;\
                    }\
                    break;\
                }\
            }\
            SDL_RenderClear(rnd);\
            SDL_RenderCopy(rnd,resmanager.GetPicture(PNAME(minibus,id)),NULL,NULL);\
            check_argument.draw();\
            check_history.draw();\
            SDL_RenderPresent(rnd);\
            update=0;\
        }\
        return quit_flag;\
    }

    _tool_minibusx(1);
    _tool_minibusx(2);
    _tool_minibusx(4);
    _tool_minibusx(5);
    _tool_minibusx(7);

    _tool_minibus(3);
    _tool_minibus(6);
    _tool_minibus(8);
    _tool_minibus(9);
    _tool_minibus(10);

    int LoopGameMinibus()
    {
        int running=1;
        SDL_Event e;
        int update=1;

        int quit_flag=1;

        int mode=2;

        int cx,cy;

        int sz_w,sz_h;
        SDL_QueryTexture(resmanager.GetPicture(PNAME(board,game2)),NULL,NULL,&sz_w,&sz_h);

        /// temp
        {
            sensor temp(vyy(74,240,153,330));
            temp.setMiddle(&cx,&cy);
        }

        sensor pos_backblock(vyy(0,240,74,331));

        sensor pos1_pic(vyy(148,94,244,172));
        sensor pos1_gate(vyy(148,172,244,239));

        sensor pos2_pic(vyy(307,94,404,172));
        sensor pos2_gate(vyy(307,172,404,239));

        sensor pos3_pic(vyy(466,94,561,172));
        sensor pos3_gate(vyy(466,172,561,239));

        sensor pos4_pic(vyy(637,94,722,172));
        sensor pos4_gate(vyy(637,172,722,239));

        sensor pos5_pic(vyy(776,94,867,172));
        sensor pos5_gate(vyy(776,177,867,240));

        sensor pos6_pic(vyy(709,407,786,487));
        sensor pos6_gate(vyy(709,332,786,407));

        sensor pos7_pic(vyy(551,407,632,487));
        sensor pos7_gate(vyy(551,332,632,407));

        sensor pos8_pic(vyy(395,407,478,487));
        sensor pos8_gate(vyy(395,332,478,407));

        sensor pos9_pic(vyy(235,405,315,487));
        sensor pos9_gate(vyy(235,332,315,407));

        sensor pos10_pic(vyy(74,405,153,487));
        sensor pos10_gate(vyy(74,332,153,407));

        while(running)
        {
            while(!update&&SDL_WaitEventTimeout(&e,10))
            {
                switch(e.type)
                {
                case SDL_QUIT:
                    running=0;
                    update=1;
                    quit_flag=0;
                    break;
                case SDL_KEYDOWN:
                {
                    update=1;
                    switch(e.key.keysym.sym)
                    {
                    case SDLK_RIGHT:
                    {
                        mode=9;
                        break;
                    }
                    case SDLK_UP:
                    {
                        mode=6;
                        break;
                    }
                    case SDLK_LEFT:
                        {
                            mode=3;
                            break;
                        }
                    case SDLK_DOWN:
                        {
                            mode=0;
                            break;
                        }
                    }
                }
                }
            }

            SDL_RenderClear(rnd);
            SDL_RenderCopy(rnd,resmanager.GetPicture(PNAME(board,game2)),NULL,NULL);
            DrawRobot(mode,cx,cy);
            SDL_RenderPresent(rnd);

            update=0;

            #undef _tool_pos
            #define _tool_pos(CallID) else if(pos##CallID##_pic.inrange(cx,cy)) { running=LoopGameminibus##CallID(); pos##CallID##_gate.setMiddle(cx,cy); }

            if(pos_backblock.inrange(cx,cy))
            {
                running=0;
            }
            _tool_pos(1)
            _tool_pos(2)
            _tool_pos(3)
            _tool_pos(4)
            _tool_pos(5)
            _tool_pos(6)
            _tool_pos(7)
            _tool_pos(8)
            _tool_pos(9)
            _tool_pos(10)
        }
        return quit_flag;
    }



    #define _tool_sports_car(id) _tool_sports_car_jump(id) _tool_sports_car_main(id)
    #define _tool_sports_carx(id) _tool_sports_car_jumpx(id) _tool_sports_car_main(id)

    #define _tool_sports_car_jump(id) \
    int LoopGamesports_car##id##_Arg() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(sports_car,id##_argument))); \
        return 1;\
    } \
    int LoopGamesports_car##id##_His() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(sports_car,id##_1_history)),resmanager.GetPicture(PNAME(sports_car,id##_2_history))); \
        return 1; \
    }

    #define _tool_sports_car_jumpx(id) \
    int LoopGamesports_car##id##_Arg() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(sports_car,id##_argument))); \
        return 1;\
    } \
    int LoopGamesports_car##id##_His() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(sports_car,id##_history)));\
        return 1; \
    }

    #define _tool_sports_car_main(id) \
    int LoopGamesports_car##id() \
    { \
        int running=1; \
        SDL_Event e;\
        int update=1;\
        int quit_flag=1;\
        int w,h;\
        int w2,h2;\
        xbutton check_argument;\
        check_argument.setNormal(PNAME(button,argument),empty_call);\
        check_argument.setMouseover(PNAME(button,argument_highlight),empty_call);\
        check_argument.setPressed(PNAME(button,argument),[&]()->int{return LoopGamesports_car##id##_Arg();});\
        SDL_QueryTexture(resmanager.GetPicture(PNAME(button,argument)),NULL,NULL,&w,&h);\
        check_argument.setRange(WIN_WIDTH/4*3,WIN_HEIGHT/2,w,h);\
        xbutton check_history;\
        check_history.setNormal(PNAME(button,history),empty_call);\
        check_history.setMouseover(PNAME(button,history_highlight),empty_call);\
        check_history.setPressed(PNAME(button,history),[&]()->int{return LoopGamesports_car##id##_His();});\
        SDL_QueryTexture(resmanager.GetPicture(PNAME(button,history)),NULL,NULL,&w2,&h2);\
        check_history.setRange(WIN_WIDTH/4*3,WIN_HEIGHT/2+h+20,w2,h2);\
        while(running)\
        {\
            while(!update&&SDL_WaitEvent(&e))\
            {\
                switch(e.type)\
                {\
                case SDL_QUIT:\
                    running=0;\
                    quit_flag=0;\
                    update=1;\
                    break;\
                case SDL_MOUSEMOTION:\
                case SDL_MOUSEBUTTONDOWN:\
                case SDL_MOUSEBUTTONUP:\
                    update=1;\
                    running=check_argument.deal(e);\
                    running=check_history.deal(e);\
                    break;\
                case SDL_KEYDOWN:\
                    if(e.key.keysym.sym==SDLK_ESCAPE)\
                    {\
                        running=0;\
                        update=1;\
                    }\
                    break;\
                }\
            }\
            SDL_RenderClear(rnd);\
            SDL_RenderCopy(rnd,resmanager.GetPicture(PNAME(sports_car,id)),NULL,NULL);\
            check_argument.draw();\
            check_history.draw();\
            SDL_RenderPresent(rnd);\
            update=0;\
        }\
        return quit_flag;\
    }

    _tool_sports_carx(1);
    _tool_sports_carx(2);
    _tool_sports_carx(5);
    _tool_sports_carx(9);
    _tool_sports_carx(10);

    _tool_sports_car(3);
    _tool_sports_car(4);
    _tool_sports_car(6);
    _tool_sports_car(7);
    _tool_sports_car(8);

    int LoopGameSportscar()
    {
        int running=1;
        SDL_Event e;
        int update=1;

        int quit_flag=1;

        int mode=2;

        int cx,cy;

        int sz_w,sz_h;
        SDL_QueryTexture(resmanager.GetPicture(PNAME(board,game2)),NULL,NULL,&sz_w,&sz_h);

        /// temp
        {
            sensor temp(vyy(74,240,153,330));
            temp.setMiddle(&cx,&cy);
        }

        sensor pos_backblock(vyy(0,240,74,331));

        sensor pos1_pic(vyy(148,94,244,172));
        sensor pos1_gate(vyy(148,172,244,239));

        sensor pos2_pic(vyy(307,94,404,172));
        sensor pos2_gate(vyy(307,172,404,239));

        sensor pos3_pic(vyy(466,94,561,172));
        sensor pos3_gate(vyy(466,172,561,239));

        sensor pos4_pic(vyy(637,94,722,172));
        sensor pos4_gate(vyy(637,172,722,239));

        sensor pos5_pic(vyy(776,94,867,172));
        sensor pos5_gate(vyy(776,177,867,240));

        sensor pos6_pic(vyy(709,407,786,487));
        sensor pos6_gate(vyy(709,332,786,407));

        sensor pos7_pic(vyy(551,407,632,487));
        sensor pos7_gate(vyy(551,332,632,407));

        sensor pos8_pic(vyy(395,407,478,487));
        sensor pos8_gate(vyy(395,332,478,407));

        sensor pos9_pic(vyy(235,405,315,487));
        sensor pos9_gate(vyy(235,332,315,407));

        sensor pos10_pic(vyy(74,405,153,487));
        sensor pos10_gate(vyy(74,332,153,407));

        while(running)
        {
            while(!update&&SDL_WaitEventTimeout(&e,10))
            {
                switch(e.type)
                {
                case SDL_QUIT:
                    running=0;
                    update=1;
                    quit_flag=0;
                    break;
                case SDL_KEYDOWN:
                {
                    update=1;
                    switch(e.key.keysym.sym)
                    {
                    case SDLK_RIGHT:
                    {
                        mode=9;
                        break;
                    }
                    case SDLK_UP:
                    {
                        mode=6;
                        break;
                    }
                    case SDLK_LEFT:
                        {
                            mode=3;
                            break;
                        }
                    case SDLK_DOWN:
                        {
                            mode=0;
                            break;
                        }
                    }
                }
                }
            }

            SDL_RenderClear(rnd);
            SDL_RenderCopy(rnd,resmanager.GetPicture(PNAME(board,game2)),NULL,NULL);
            DrawRobot(mode,cx,cy);
            SDL_RenderPresent(rnd);

            update=0;

            #undef _tool_pos
            #define _tool_pos(CallID) else if(pos##CallID##_pic.inrange(cx,cy)) { running=LoopGamesports_car##CallID(); pos##CallID##_gate.setMiddle(cx,cy); }

            if(pos_backblock.inrange(cx,cy))
            {
                running=0;
            }
            _tool_pos(1)
            _tool_pos(2)
            _tool_pos(3)
            _tool_pos(4)
            _tool_pos(5)
            _tool_pos(6)
            _tool_pos(7)
            _tool_pos(8)
            _tool_pos(9)
            _tool_pos(10)
        }
        return quit_flag;
    }

    #define _tool_truck(id) _tool_truck_jump(id) _tool_truck_main(id)
    #define _tool_truckx(id) _tool_truck_jumpx(id) _tool_truck_main(id)
    #define _tool_truckxx(id) _tool_truck_jumpxx(id) _tool_truck_main(id)

    #define _tool_truck_jump(id) \
    int LoopGametruck##id##_Arg() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(truck,id##_argument))); \
        return 1;\
    } \
    int LoopGametruck##id##_His() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(truck,id##_1_history)),resmanager.GetPicture(PNAME(truck,id##_2_history))); \
        return 1; \
    }

    #define _tool_truck_jumpxx(id) \
    int LoopGametruck##id##_Arg() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(truck,id##_argument))); \
        return 1;\
    } \
    int LoopGametruck##id##_His() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(truck,id##_1_history)),resmanager.GetPicture(PNAME(truck,id##_2_history)),resmanager.GetPicture(PNAME(truck,id##_3_history))); \
        return 1; \
    }

    #define _tool_truck_jumpx(id) \
    int LoopGametruck##id##_Arg() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(truck,id##_argument))); \
        return 1;\
    } \
    int LoopGametruck##id##_His() \
    { \
        PictureScoller(resmanager.GetPicture(PNAME(truck,id##_history)));\
        return 1; \
    }

    #define _tool_truck_main(id) \
    int LoopGametruck##id() \
    { \
        int running=1; \
        SDL_Event e;\
        int update=1;\
        int quit_flag=1;\
        int w,h;\
        int w2,h2;\
        xbutton check_argument;\
        check_argument.setNormal(PNAME(button,argument),empty_call);\
        check_argument.setMouseover(PNAME(button,argument_highlight),empty_call);\
        check_argument.setPressed(PNAME(button,argument),[&]()->int{return LoopGametruck##id##_Arg();});\
        SDL_QueryTexture(resmanager.GetPicture(PNAME(button,argument)),NULL,NULL,&w,&h);\
        check_argument.setRange(WIN_WIDTH/4*3,WIN_HEIGHT/2,w,h);\
        xbutton check_history;\
        check_history.setNormal(PNAME(button,history),empty_call);\
        check_history.setMouseover(PNAME(button,history_highlight),empty_call);\
        check_history.setPressed(PNAME(button,history),[&]()->int{return LoopGametruck##id##_His();});\
        SDL_QueryTexture(resmanager.GetPicture(PNAME(button,history)),NULL,NULL,&w2,&h2);\
        check_history.setRange(WIN_WIDTH/4*3,WIN_HEIGHT/2+h+20,w2,h2);\
        while(running)\
        {\
            while(!update&&SDL_WaitEvent(&e))\
            {\
                switch(e.type)\
                {\
                case SDL_QUIT:\
                    running=0;\
                    quit_flag=0;\
                    update=1;\
                    break;\
                case SDL_MOUSEMOTION:\
                case SDL_MOUSEBUTTONDOWN:\
                case SDL_MOUSEBUTTONUP:\
                    update=1;\
                    running=check_argument.deal(e);\
                    running=check_history.deal(e);\
                    break;\
                case SDL_KEYDOWN:\
                    if(e.key.keysym.sym==SDLK_ESCAPE)\
                    {\
                        running=0;\
                        update=1;\
                    }\
                    break;\
                }\
            }\
            SDL_RenderClear(rnd);\
            SDL_RenderCopy(rnd,resmanager.GetPicture(PNAME(truck,id)),NULL,NULL);\
            check_argument.draw();\
            check_history.draw();\
            SDL_RenderPresent(rnd);\
            update=0;\
        }\
        return quit_flag;\
    }

    _tool_truckx(4);
    _tool_truckx(5);

    _tool_truck(1);
    _tool_truck(3);

    _tool_truckxx(2);

    int LoopGameTruck()
    {
        int running=1;
        SDL_Event e;
        int update=1;

        int quit_flag=1;

        int mode=2;

        int cx,cy;

        int sz_w,sz_h;
        SDL_QueryTexture(resmanager.GetPicture(PNAME(board,game2)),NULL,NULL,&sz_w,&sz_h);

        /// temp
        {
            sensor temp(vyy(74,240,153,330));
            temp.setMiddle(&cx,&cy);
        }

        sensor pos_backblock(vyy(0,240,74,331));

        sensor pos1_pic(vyy(148,94,244,172));
        sensor pos1_gate(vyy(148,172,244,239));

        sensor pos2_pic(vyy(307,94,404,172));
        sensor pos2_gate(vyy(307,172,404,239));

        sensor pos3_pic(vyy(466,94,561,172));
        sensor pos3_gate(vyy(466,172,561,239));

        sensor pos4_pic(vyy(637,94,722,172));
        sensor pos4_gate(vyy(637,172,722,239));

        sensor pos5_pic(vyy(776,94,867,172));
        sensor pos5_gate(vyy(776,177,867,240));

        sensor pos6_pic(vyy(709,407,786,487));
        sensor pos6_gate(vyy(709,332,786,407));

        sensor pos7_pic(vyy(551,407,632,487));
        sensor pos7_gate(vyy(551,332,632,407));

        sensor pos8_pic(vyy(395,407,478,487));
        sensor pos8_gate(vyy(395,332,478,407));

        sensor pos9_pic(vyy(235,405,315,487));
        sensor pos9_gate(vyy(235,332,315,407));

        sensor pos10_pic(vyy(74,405,153,487));
        sensor pos10_gate(vyy(74,332,153,407));

        while(running)
        {
            while(!update&&SDL_WaitEventTimeout(&e,10))
            {
                switch(e.type)
                {
                case SDL_QUIT:
                    running=0;
                    update=1;
                    quit_flag=0;
                    break;
                case SDL_KEYDOWN:
                {
                    update=1;
                    switch(e.key.keysym.sym)
                    {
                    case SDLK_RIGHT:
                    {
                        mode=9;
                        break;
                    }
                    case SDLK_UP:
                    {
                        mode=6;
                        break;
                    }
                    case SDLK_LEFT:
                        {
                            mode=3;
                            break;
                        }
                    case SDLK_DOWN:
                        {
                            mode=0;
                            break;
                        }
                    }
                }
                }
            }

            SDL_RenderClear(rnd);
            SDL_RenderCopy(rnd,resmanager.GetPicture(PNAME(board,game2)),NULL,NULL);
            DrawRobot(mode,cx,cy);
            SDL_RenderPresent(rnd);

            update=0;

            #undef _tool_pos
            #define _tool_pos(CallID) else if(pos##CallID##_pic.inrange(cx,cy)) { running=LoopGametruck##CallID(); pos##CallID##_gate.setMiddle(cx,cy); }

            if(pos_backblock.inrange(cx,cy))
            {
                running=0;
            }
            _tool_pos(1)
            _tool_pos(2)
            _tool_pos(3)
            _tool_pos(4)
            _tool_pos(5)
        }
        return quit_flag;
    }


    /// Main Game
    void LoopGameMain()
    {
        SDL_SetRenderDrawColor(rnd,255,255,255,0);

        /*
        SDL_RenderClear(rnd);
        SDL_RenderCopy(rnd,resmanager.GetPicture(PNAME(board,game1)),NULL,NULL);
        SDL_RenderPresent(rnd);
        */

        int ow=2149;
        int oh=1038;

        sensor automobile_pic(vtt(381,0,630,84,ow,oh));
        sensor automobile_gate(vtt(381,84,630,401,ow,oh));

        sensor pick_up_pic(vtt(793,0,1042,182,ow,oh));
        sensor pick_up_gate(vtt(793,182,1042,401,ow,oh));

        sensor suv_pic(vtt(1211,0,1455,187,ow,oh));
        sensor suv_gate(vtt(1211,187,1455,404,ow,oh));

        sensor bus_pic(vtt(1837,404,2149,634,ow,oh));
        sensor bus_gate(vtt(1638,404,1837,634,ow,oh));

        sensor minibus_pic(vtt(1037,854,1246,1038,ow,oh));
        sensor minibus_gate(vtt(1037,642,1246,854,ow,oh));

        sensor sports_car_pic(vtt(605,860,820,1038,ow,oh));
        sensor sports_car_gate(vtt(605,636,820,860,ow,oh));

        sensor truck_pic(vtt(194,865,399,1038,ow,oh));
        sensor truck_gate(vtt(194,636,399,865,ow,oh));

        int cx=85;
        int cy=523;

        int running=1;
        int need_update=1;
        SDL_Event e;
        int mode=2;

        while(running)
        {
            while(!need_update&&SDL_WaitEventTimeout(&e,10))
            {
                switch(e.type)
                {
                case SDL_QUIT:
                    running=0;
                    need_update=1;
                    break;
                case SDL_KEYDOWN:
                {
                    need_update=1;
                    switch(e.key.keysym.sym)
                    {
                    case SDLK_RIGHT:
                    {
                        mode=9;
                        break;
                    }
                    case SDLK_UP:
                    {
                        mode=6;
                        break;
                    }
                    case SDLK_LEFT:
                        {
                            mode=3;
                            break;
                        }
                    case SDLK_DOWN:
                        {
                            mode=0;
                            break;
                        }
                    }
                }
                }
            }

            SDL_RenderClear(rnd);
            SDL_RenderCopy(rnd,resmanager.GetPicture(PNAME(board,game1)),NULL,NULL);
            DrawRobot(mode,cx,cy);
            SDL_RenderPresent(rnd);

            need_update=0;

            if(automobile_pic.inrange(cx,cy))
            {
                running=LoopGameAutomobile();
                automobile_gate.setMiddle(&cx,&cy);
            }
            else if(pick_up_pic.inrange(cx,cy))
            {
                running=LoopGamePickup();
                pick_up_gate.setMiddle(&cx,&cy);
            }
            else if(suv_pic.inrange(cx,cy))
            {
                running=LoopGameSUV();
                suv_gate.setMiddle(&cx,&cy);
            }
            else if(bus_pic.inrange(cx,cy))
            {
                running=LoopGameBus();
                bus_gate.setMiddle(&cx,&cy);
            }
            else if(minibus_pic.inrange(cx,cy))
            {
                running=LoopGameMinibus();
                minibus_gate.setMiddle(&cx,&cy);
            }
            else if(sports_car_pic.inrange(cx,cy))
            {
                running=LoopGameSportscar();
                sports_car_gate.setMiddle(&cx,&cy);
            }
            else if(truck_pic.inrange(cx,cy))
            {
                running=LoopGameTruck();
                truck_gate.setMiddle(&cx,&cy);
            }
        }
    }

    void Main()
    {
        Init();
        LoopGameMain();
    }
}
