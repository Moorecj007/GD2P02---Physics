/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Application.h
* Description : The core of the Application is run here. The link between all components.
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

// Library Files
#pragma comment(lib, "Winmm.lib")

// Defines and Macros
#define WIN32_LEAN_AND_MEAN
#define WINDOW_CLASS_NAME L"DX10 FRAMEWORK"

#ifdef _DEBUG
// Visual Leak Detector to be run only if in DEBUG mode
#pragma comment(lib, "vld.lib")
#include <vld.h>
#define D3D_DEBUG_INFO
#endif // _DEBUG

// Local Includes
#include "Utility\Utilities.h"
#include "Utility\Timer.h"
#include "DX10\DX10.h"
#include "GDI\GDI.h"
#include "Levels\Levels.h"

class Application
{
public:
	
	/***********************
	* WindowProc: Process the window
	* @author: Callan Moore
	* @Parameter: _hWnd: Handle to the Window sending the message
	* @Parameter: _uiMsg: The message ID being sent
	* @Parameter: _wParam: Additional detail about the message being sent
	* @Parameter: _lParam: Additional detail about the message being sent
	* @return: LRESULT: The resulting value
	********************/
	static LRESULT CALLBACK WindowProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam);

	/***********************
	* CreateWindowApp: Creates the window for the Application
	* @author: Callan Moore
	* @Parameter: _clientWidth: Width of the screen
	* @Parameter: _clientHeight: Height of the screen
	* @Parameter: _hInstance: The instance of the application
	* @return: bool: Successful or not
	********************/
	bool CreateWindowApp(int _clientWidth, int _clientHeight, HINSTANCE _hInstance);

	/***********************
	* Execute: Runs the main loop of the Application
	* @author: Callan Moore
	* @return: int: Integer containing details about the last message resulting it termination
	********************/
	int Execute();

	/***********************
	* GetInstance: Returns the singleton instance of the Application, if it doesn't exist creates it.
	* @author: Callan Moore
	* @return: CApplication*: The current instance of the Application
	********************/
	static Application* GetInstance();
	
	/***********************
	* Initialise: Initialise the Application
	* @author: Callan Moore
	* @parameter: _clientWidth: Width of the client window
	* @parameter: _clientHeight: Height of the client window
	* @Parameter: _hInstance: Handle to the current instance
	* @return: bool: Successful or not
	********************/
	bool Initialise(int _clientWidth, int _clientHeight, HINSTANCE _hInstance);

	/***********************
	* ~CApplication: Default Destructor for Application class
	* @author: Callan Moore
	********************/
	~Application();

	/***********************
	* DestroyInstance: Deletes the instance of the Application.
	* @author: Callan Moore
	* @return: void
	********************/
	static void DestroyInstance();

	/***********************
	* ShutDown: Shuts down and releases all memory created by Application
	* @author: Callan Moore
	* @return: void
	********************/
	void ShutDown();

	/***********************
	* ExecuteOneFrame: Executes one frame of the Application
	* @author: Callan Moore
	* @return: void
	********************/
	void ExecuteOneFrame();

	/***********************
	* Process: Process the Application
	* @author: Callan Moore
	* @parameter: _dt: The current delta tick
	* @return: bool: Successful or not
	********************/
	bool Process(float _dt);

	/***********************
	* Draw: Draw the Application components
	* @author: Callan Moore
	* @return: void
	********************/
	void Draw();

	/***********************
	* HandleInput: Handle all input for the application
	* @author: Callan Moore
	* @return: Successful or not
	********************/
	bool HandleInput();
	
	/***********************
	* CutRope: Call the CutRope function on the current Level
	* @author: Callan Moore
	* @return: void
	********************/
	void CutRope();
	
	/***********************
	* DrawCutLine: Draw the cut line on the client window
	* @author: Callan Moore
	* @return: void
	********************/
	void DrawCutLine();

	/***********************
	* SetKeyDown: Sets the Key down boolean for input Key
	* @author: Callan Moore
	* @parameter: _index: Index of the Key to set
	* @parameter: _down: True/false setting
	* @return: void
	********************/
	void SetKeyDown(int _index, bool _down) { m_pKeyDown[_index] = _down; };

	/***********************
	* SetFirstMousePos: Store the position of the mouse when first clicked
	* @author: Callan Moore
	* @parameter: _firstMousePos: Position of the mouse on the client window
	* @return: void
	********************/
	void SetFirstMousePos(v2float _firstMousePos) { m_firstMousePos = _firstMousePos; };
	
	/***********************
	* SetSecondMousePos: Store the position of the mouse when click is released
	* @author: Callan Moore
	* @parameter: _secondMousePos: Position of the mouse on the client window
	* @return: void
	********************/
	void SetSecondMousePos(v2float _secondMousePos) { m_secondMousePos = _secondMousePos; };

	/***********************
	* SetMouseDown: Set the state of the mouse button being clicked
	* @author: Callan Moore
	* @parameter: _mouseDown: The new state of the mouse button
	* @return: void
	********************/
	void SetMouseDown(bool _mouseDown) { m_mouseDown = _mouseDown; };

	/***********************
	* RenderInstructions: Render the Game Instructions to the side panel
	* @author: Callan Moore
	* @return: void
	********************/
	void RenderInstructions();

	/***********************
	* Increment: Increment an input integer by the given amount and return the new value
	* @author: Callan Moore
	* @parameter: _value: Value to increment
	* @parameter: _amount: Increment amount
	* @return: int: The result of the increment
	********************/
	int Increment(int* _value, int _amount);

private:
	// Preventing copies and extra constructions
	Application();
	Application(const Application& _kr);
	Application& operator= (const Application& _kr);

private:
	// Singleton Instance
	static Application* s_pApp;

	// Window Variables
	HWND m_hWnd;
	int m_clientWidth;
	int m_clientHeight;
	bool m_online;
	v2float m_firstMousePos;
	v2float m_secondMousePos;
	bool m_mouseDown;
	
	// Timer Variables
	Timer* m_pTimer;
	float m_deltaTick;
	int m_fps;
	float m_fpsTimer; 

	// Input Variables
	bool* m_pKeyDown;

	// Renderer Variables
	DX10_Renderer* m_pDX10_Renderer;
	GDI_Renderer* m_pGDIRenderer;

	// Camera
	DX10_Camera_FirstPerson* m_pCamera;

	// Objects
	DX10_Obj_Generic* m_pCube;

	// Meshes
	DX10_Mesh_Generic* m_pCubeMesh;
	
	// Shaders
	DX10_Shader_LitTex* m_pShader_LitTex;

	// Level Pointer
	Level_Generic* m_pCurrentLevel;
	eLevelSelection m_levelSelection;
};

#endif // __APPLICATION_H__

