/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL OpenGL, standard IO, and, strings
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL, creates window, and initializes OpenGL
bool init();

//Initializes matrices and clear color
bool initGL();

//Input handler
void handleKeys( unsigned char key, int x, int y );

//Per frame update
void update();

//Renders quad to the screen
void render();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

//Render flag
bool gRenderQuad = true;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if(SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Use OpenGL 2.1
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create context
			gContext = SDL_GL_CreateContext( gWindow );
			if( gContext == NULL )
			{
				printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Use Vsync
				if( SDL_GL_SetSwapInterval( 1 ) < 0 )
				{
					printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
				}
				//Initialize OpenGL
				if( !initGL() )
				{
					printf( "Unable to initialize OpenGL!\n" );
					success = false;
				}
			}
		}
	}

	return success;
}

bool initGL()
{
	bool success = true;
	GLenum error = GL_NO_ERROR;

	//Initialize Projection Matrix
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	
	//Check for error
	error = glGetError();
	if( error != GL_NO_ERROR )
	{
		//printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
		success = false;
	}

	//Initialize Modelview Matrix
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	//Check for error
	error = glGetError();
	if( error != GL_NO_ERROR )
	{
		//printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
		success = false;
	}
	
	//Initialize clear color
	glClearColor( 0.f, 0.f, 0.f, 1.f );
	
	//Check for error
	error = glGetError();
	if( error != GL_NO_ERROR )
	{
		//printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
		success = false;
	}
	
	return success;
}

void handleKeys( unsigned char key, int x, int y )
{
	//是否渲染
	if( key == 'q' )
	{
		gRenderQuad = !gRenderQuad;
	}
}

void update()
{
	//No per frame update needed
}

void render()
{
	//Clear color buffer 清除颜色缓存
	glClear( GL_COLOR_BUFFER_BIT );
	//Render quad 渲染方块
	if (gRenderQuad)
	{
		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.5f, -0.55f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(-0.5f, 0.5f);
		glEnd();
	}
}

void close()
{
	// 销毁窗口	调用SDL_DestroyWindow
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	// 退出SDL子系统
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window 
	// 启动SDL并创建窗口
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Main loop flag
		bool quit = false;
		//Event handler
		SDL_Event e;
		//Enable text input 启用SDL控制输出
		SDL_StartTextInput();
		//While application is running 当程序运行之时
		while( !quit )
		{
			//Handle events on queue 处理事件队列
			while( SDL_PollEvent( &e ) != 0 )
			{
				//User requests quit 请求退出
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}
				//Handle keypress with current mouse position 处理键盘输出
				else if( e.type == SDL_TEXTINPUT )
				{
					int x = 0, y = 0;
					SDL_GetMouseState( &x, &y );
					handleKeys( e.text.text[ 0 ], x, y );
				}
			}
			//Render quad 处理方块
			render();
			//Update screen 更新屏幕
			SDL_GL_SwapWindow( gWindow );
		}
		//Disable text input 禁用文字输入
		SDL_StopTextInput();
	}
	//Free resources and close SDL 释放资源并关闭SDL
	close();
	return 0;
}