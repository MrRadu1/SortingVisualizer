#include "menu.h"
#include "SDL_events.h"
#include <SDL.h>

static int handleMenuEvents(Context* context, unsigned distance)
{
    int w = context->window->width/(2 * context->menuSize);
    int h = w - w/6;
    int y = context->window->height - context->window->height/4;
    int center = distance / 4;
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
           case SDL_MOUSEBUTTONDOWN : 
            if(event.button.clicks == 1)
            {
                for(unsigned i = 0; i < context->menuSize; i++)
                {
                        if(event.button.x > (i * distance + center) && event.button.x < (i * distance + center + w) &&
                                event.button.y > y && event.button.y < (y + h))
                        {
                            context->SortChoose = i;
                            return i;
                        }

                    }

                }
            break;
            case SDL_QUIT :
               context->ProgramState = 0;
               return -1;
            break;
            default:
            break;

        }
       
    }
    return -1;
}
static int handleBackButtonEvents(Context *context, unsigned x,unsigned y, unsigned ButtonWidth, unsigned ButtonHeight)
{
    SDL_Event mouse;
    while (SDL_PollEvent(&mouse))
    {
        if(mouse.button.clicks == 1)
            if(mouse.button.x <= x + ButtonWidth && mouse.button.x > x && mouse.button.y <= y + ButtonHeight && mouse.button.y > y)
            {
                return 1;
            }
    }
    return 0;
}
int drawBackButton(Context *context){


/*
    TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24); //this opens a font style and sets a size

    SDL_Color White = {255, 255, 255,255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "put your text here", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

    SDL_Texture* Message = SDL_CreateTextureFromSurface(context->window->renderer, surfaceMessage); //now you can convert it into a texture

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = 100; // controls the width of the rect
    Message_rect.h = 100; // controls the height of the rect

//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understand

//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

    SDL_RenderCopy(context->window->renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

//Don't forget to free your surface and texture


*/


    unsigned ButtonWidth = context->window->width / 8;
    unsigned ButtonHeight = context->window->height / 15;
    SDL_FRect button;
    button.h= ButtonHeight;
    button.w = ButtonWidth;
    button.x = 10;
    button.y = 10;
    SDL_SetRenderDrawColor(context->window->renderer, 0, 255, 0, 255);
    SDL_RenderFillRectF(context->window->renderer,&button);
    SDL_SetRenderDrawColor(context->window->renderer, 0, 0, 0, 255);
    return handleBackButtonEvents(context,button.x, button.y, ButtonWidth,ButtonHeight);


}
static void drawMenuButtons(Context* context, int h,int w, int x,int y)
{
    SDL_FRect button;
    button.h = h;
    button.w = w;
    button.x = x;
    button.y = y;
    SDL_SetRenderDrawColor(context->window->renderer, 0, 255, 0, 255);
    SDL_RenderFillRectF(context->window->renderer,&button);
    SDL_SetRenderDrawColor(context->window->renderer, 0, 0, 0, 255);
}

int drawMenu(Context* context){
    SDL_RenderClear(context->window->renderer);
    SDL_FRect title;
    title.h = context->window->height/10;
    title.w = context->window->width/3;
    title.x = context->window->width/2 - title.w/2;
    title.y = context->window->height/5;
    SDL_SetRenderDrawColor(context->window->renderer, 0, 0, 100, 255);
    SDL_RenderFillRectF(context->window->renderer,&title);
    SDL_SetRenderDrawColor(context->window->renderer, 0, 0, 0, 255);

    int w = context->window->width/(2 * context->menuSize);
    int h = w - w/6;
    int distance = 2 * w;
    unsigned center = w/2;
    int y = context->window->height - context->window->height/4;
    int x;
    for(unsigned i = 0 ; i < context->menuSize ; i++)
    {
        x = distance * i + center;
        drawMenuButtons(context, h, w, x, y);
    }
    SDL_RenderPresent(context->window->renderer);
    return handleMenuEvents(context,distance);

}