/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Level_Generic.cpp
* Description : Base class for all levels to be derived from
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// This Include
#include "Level_Generic.h"

Level_Generic::~Level_Generic()
{
}

bool Level_Generic::InitialSetup()
{
	// Create the points for the vectors to store all references to objects in the level
	m_pObjStatics = new std::vector < GDI_Obj_Generic* >;
	m_pObjDynamics = new std::vector < GDI_Obj_Generic* >;
	m_pObjBreakables = new std::vector < GDI_Obj_Generic* >;
	m_pRopes_Cuttable = new std::vector < GDI_Obj_Rope* >;
	m_pRopes_Unbreakable = new std::vector < GDI_Obj_Rope* >;
	m_pObjPulleys = new std::vector < GDI_Obj_Pulley* >;

	// Create the physics world
	m_pPhysWorld = new Physics_World_2D();
	VALIDATE(m_pPhysWorld->Initialise(40.0f));

	// Create Temporary points for use in object creation
	TPhysicsProperties physProps;
	v2float* pPoints;
	Physics_Body_2D* pTempBody;

	// Create a background object that is twice the size of the client window and height
	// This allows the center to be on the origin so world space coordinate are the same on this object
	m_pBackground = new GDI_Obj_Polygon(m_pGDI_Renderer);
	ZeroMemory(&physProps, sizeof(physProps));
	pPoints = new v2float[4];
	pPoints[0] = { (float)(0), (float)(0) };
	pPoints[1] = { (float)(m_clientWidth ), (float)(0) };
	pPoints[2] = { (float)(m_clientWidth), (float)(m_clientHeight) };
	pPoints[3] = { (float)(0), (float)(m_clientHeight) };
	physProps.pPoints = pPoints;
	physProps.isStatic = true;
	physProps.pos = { 0.0f, 0.0f };
	physProps.size = 4;
	physProps.collisionType = CT_BACKGROUND;
	physProps.collideWith = 0;
	Physics_Body_2D* pBackgroundBody = m_pPhysWorld->CreatePhysicsObject(physProps);
	VALIDATE(m_pBackground->Initialise(pBackgroundBody, colorRef::WHITE, colorRef::WHITE));

	/*
		Create the four walls of the level
	*/

	GDI_Obj_Generic* pNorthWall = new GDI_Obj_Polygon(m_pGDI_Renderer);
	pPoints = new v2float[4];
	pPoints[0] = { (float)(-m_clientWidth / 2), -10.0f };
	pPoints[1] = { (float)(m_clientWidth / 2), -10.0f };
	pPoints[2] = { (float)(m_clientWidth / 2), 10.0f };
	pPoints[3] = { (float)(-m_clientWidth / 2), 10.0f };
	ZeroMemory(&physProps, sizeof(physProps));
	physProps.isStatic = true;
	physProps.pPoints = pPoints;
	physProps.size = 4;
	physProps.friction = 0.3f;
	physProps.pos = { (float)(m_clientWidth / 2.0f), 0.0f };
	physProps.collisionType = CT_STANDARD;
	physProps.collideWith = (CT_STANDARD | CT_GEM | CT_BREAKABLE | CT_ENEMY);
	pTempBody = m_pPhysWorld->CreatePhysicsObject(physProps);
	VALIDATE(pNorthWall->Initialise(pTempBody, colorRef::BLACK, colorRef::BLACK));
	m_pObjStatics->push_back(pNorthWall);

	GDI_Obj_Generic* pSouthWall = new GDI_Obj_Polygon(m_pGDI_Renderer);
	pPoints = new v2float[4];
	pPoints[0] = { (float)(-m_clientWidth / 2), -10.0f };
	pPoints[1] = { (float)(m_clientWidth / 2), -10.0f };
	pPoints[2] = { (float)(m_clientWidth / 2), 10.0f };
	pPoints[3] = { (float)(-m_clientWidth / 2), 10.0f };
	ZeroMemory(&physProps, sizeof(physProps));
	physProps.isStatic = true;
	physProps.pPoints = pPoints;
	physProps.size = 4;
	physProps.friction = 0.3f;
	physProps.pos = { (float)(m_clientWidth / 2.0f), (float)(m_clientHeight)-40.0f };
	physProps.collisionType = CT_STANDARD;
	physProps.collideWith = (CT_STANDARD | CT_GEM | CT_BREAKABLE | CT_ENEMY);
	pTempBody = m_pPhysWorld->CreatePhysicsObject(physProps);
	VALIDATE(pSouthWall->Initialise(pTempBody, colorRef::BLACK, colorRef::BLACK));
	m_pObjStatics->push_back(pSouthWall);

	GDI_Obj_Generic* pEastWall = new GDI_Obj_Polygon(m_pGDI_Renderer);
	pPoints = new v2float[4];
	pPoints[0] = { -10.0f, (float)(-m_clientHeight / 2) };
	pPoints[1] = { 10.0f, (float)(-m_clientHeight / 2) };
	pPoints[2] = { 10.0f, (float)(m_clientHeight / 2) };
	pPoints[3] = { -10.0f, (float)(m_clientHeight / 2) };
	ZeroMemory(&physProps, sizeof(physProps));
	physProps.isStatic = true;
	physProps.pPoints = pPoints;
	physProps.size = 4;
	physProps.friction = 0.3f;
	physProps.pos = { 0.0f, (float)(m_clientHeight / 2.0f) };
	physProps.collisionType = CT_STANDARD;
	physProps.collideWith = (CT_STANDARD | CT_GEM | CT_BREAKABLE | CT_ENEMY);
	pTempBody = m_pPhysWorld->CreatePhysicsObject(physProps);
	VALIDATE(pEastWall->Initialise(pTempBody, colorRef::BLACK, colorRef::BLACK));
	m_pObjStatics->push_back(pEastWall);

	GDI_Obj_Generic* pWestWall = new GDI_Obj_Polygon(m_pGDI_Renderer);
	pPoints = new v2float[4];
	pPoints[0] = { -10.0f, (float)(-m_clientHeight / 2) };
	pPoints[1] = { 20.0f, (float)(-m_clientHeight / 2) };
	pPoints[2] = { 20.0f, (float)(m_clientHeight / 2) };
	pPoints[3] = { -10.0f, (float)(m_clientHeight / 2) };
	ZeroMemory(&physProps, sizeof(physProps));
	physProps.isStatic = true;
	physProps.pPoints = pPoints;
	physProps.size = 4;
	physProps.friction = 0.3f;
	physProps.pos = { (float)(m_clientWidth)-16.0f, (float)(m_clientHeight / 2.0f) };
	physProps.collisionType = CT_STANDARD;
	physProps.collideWith = (CT_STANDARD | CT_GEM | CT_BREAKABLE | CT_ENEMY);
	pTempBody = m_pPhysWorld->CreatePhysicsObject(physProps);
	VALIDATE(pWestWall->Initialise(pTempBody, colorRef::BLACK, colorRef::BLACK));
	m_pObjStatics->push_back(pWestWall);

	GDI_Obj_Generic* pPulleyDefine = new GDI_Obj_Polygon(m_pGDI_Renderer);
	pPoints = new v2float[4];
	pPoints[0] = { -5.0f, -5.0f };
	pPoints[1] = { 5.0f, -5.0f };
	pPoints[2] = { 5.0f, 5.0f };
	pPoints[3] = { -5.0f, 5.0f };
	ZeroMemory(&physProps, sizeof(physProps));
	physProps.isStatic = true;
	physProps.pPoints = pPoints;
	physProps.size = 4;
	physProps.friction = 0.3f;
	physProps.pos = { 1040, 632 };
	physProps.collisionType = CT_STANDARD;
	physProps.collideWith = (CT_STANDARD | CT_GEM | CT_BREAKABLE | CT_ENEMY);
	pTempBody = m_pPhysWorld->CreatePhysicsObject(physProps);
	VALIDATE(pPulleyDefine->Initialise(pTempBody, colorRef::GREY, colorRef::GREY));
	m_pObjStatics->push_back(pPulleyDefine);

	return true;
}

void Level_Generic::DestroyLevel()
{
	// Delete all Cuttable GDI Ropes
	if (m_pRopes_Cuttable != 0)
	{
		for (UINT i = 0; i < m_pRopes_Cuttable->size(); i++)
		{
			ReleasePtr((*m_pRopes_Cuttable)[i]);
		}
		ReleasePtr(m_pRopes_Cuttable);
	}
	
	// Delete all Unbreakable GDI Ropes
	if (m_pRopes_Unbreakable != 0)
	{
		for (UINT i = 0; i < m_pRopes_Unbreakable->size(); i++)
		{
			ReleasePtr((*m_pRopes_Unbreakable)[i]);
		}
		ReleasePtr(m_pRopes_Unbreakable);
	}
	if (m_pObjPulleys != 0)
	{
		// Delete all GDI Pulley Objects
		for (UINT i = 0; i < m_pObjPulleys->size(); i++)
		{
			ReleasePtr((*m_pObjPulleys)[i]);
		}
		ReleasePtr(m_pObjPulleys);
	}
	if (m_pObjStatics != 0)
	{
		// Delete all GDI static objects
		for (UINT i = 0; i < m_pObjStatics->size(); i++)
		{
			ReleasePtr((*m_pObjStatics)[i]);
		}
		ReleasePtr(m_pObjStatics);
	}
	// Delete all GDI dynamic objects
	if (m_pObjDynamics != 0)
	{
		for (UINT i = 0; i < m_pObjDynamics->size(); i++)
		{
			ReleasePtr((*m_pObjDynamics)[i]);
		}
		ReleasePtr(m_pObjDynamics);
	}
	// Delete all GDI breakable objects
	if (m_pObjBreakables != 0)
	{
		for (UINT i = 0; i < m_pObjBreakables->size(); i++)
		{
			ReleasePtr((*m_pObjBreakables)[i]);
		}
		ReleasePtr(m_pObjBreakables);
	}

	ReleasePtr(m_pGem);
	ReleasePtr(m_pWinZone);
	ReleasePtr(m_pBackground);
	ReleasePtr(m_pPhysWorld);
}

void Level_Generic::ResetLevel()
{
	DestroyLevel();
	ContructLevel();
}

bool Level_Generic::Process(float _dt)
{
	m_pPhysWorld->Process();
	m_pBackground->Process(_dt);
	m_pWinZone->Process(_dt);
	m_pGem->Process(_dt);

	// Check win and loss conditions on the gem
	TCollisionProperties collisionProps = *m_pGem->GetPhysicsBody()->GetCollisionProperties();
	if (collisionProps.isLevelLost == true)
	{
		ResetLevel();
		return false;
	}
	if (collisionProps.isLevelWon == true)
	{
		return true;
	}
	
	// Process all static objects
	for (UINT i = 0; i < m_pObjStatics->size(); i++)
	{
		(*m_pObjStatics)[i]->Process(_dt);
	}
	// Process all Cuttable Ropes
	for (UINT i = 0; i < m_pRopes_Cuttable->size(); i++)
	{
		(*m_pRopes_Cuttable)[i]->Process(_dt);
	}
	// Process all Unbreakable Ropes
	for (UINT i = 0; i < m_pRopes_Unbreakable->size(); i++)
	{
		(*m_pRopes_Unbreakable)[i]->Process(_dt);
	}
	// Process all Pulleys
	for (UINT i = 0; i < m_pObjPulleys->size(); i++)
	{
		(*m_pObjPulleys)[i]->Process(_dt);
	}
	// Process all dynamic objects
	for (UINT i = 0; i < m_pObjDynamics->size(); i++)
	{
		(*m_pObjDynamics)[i]->Process(_dt);
	}

	// Create vectors to store references to created and deleted objects to safely add and remove them later
	std::vector<UINT> deletedObjectIndices;
	std::vector<GDI_Obj_Generic*> createdObjects;

	// Process all breakable objects
	for (UINT i = 0; i < m_pObjBreakables->size(); i++)
	{
		// Process and retrieve the collision properties of the breakable object
		(*m_pObjBreakables)[i]->Process(_dt);
		TCollisionProperties* collisionProps = (*m_pObjBreakables)[i]->GetPhysicsBody()->GetCollisionProperties();

		// Determine if the object needs to be broken
		if (collisionProps->isBreaking == true)
		{
			// Break the object in the physics world
			std::vector<Physics_Body_2D*>* pNewBodies = m_pPhysWorld->BreakObject((*m_pObjBreakables)[i]->GetPhysicsBody());

			COLORREF colorFill = (*m_pObjBreakables)[i]->GetColorFill();
			COLORREF colorOutline = (*m_pObjBreakables)[i]->GetColorOutline();

			// Save the index of the object that broke so it can be deleted safely later
			deletedObjectIndices.push_back(i);

			// Create new GDI objects for all the new created bodies of the broken object
			for (UINT newIndex = 0; newIndex < pNewBodies->size(); newIndex++)
			{
				GDI_Obj_Generic* pTempObject = new GDI_Obj_Polygon(m_pGDI_Renderer);
				pTempObject->Initialise((*pNewBodies)[newIndex], colorFill, colorOutline);
				createdObjects.push_back(pTempObject);
			}

			ReleasePtr(pNewBodies);
		}
	}

	// If a object was broken
	if (deletedObjectIndices.size() > 0)
	{
		// Delete all the objects in backwards order to safely use indices
		for (int i = (int)deletedObjectIndices.size() - 1; i >= 0; i--)
		{
			ReleasePtr((*m_pObjBreakables)[i]);
			m_pObjBreakables->erase(m_pObjBreakables->begin() + i);
		}

		// Add all created objects to the dynamics objects vector
		for (UINT i = 0; i < createdObjects.size(); i++)
		{
			m_pObjDynamics->push_back(createdObjects[i]);
		}
	}

	return false;
}

void Level_Generic::Render()
{
	m_pBackground->Render();
	m_pWinZone->Render();

	// Render all Cuttable Ropes
	for (UINT i = 0; i < m_pRopes_Cuttable->size(); i++)
	{
		(*m_pRopes_Cuttable)[i]->Render();
	}
	// Render all Unbreakable Ropes
	for (UINT i = 0; i < m_pRopes_Unbreakable->size(); i++)
	{
		(*m_pRopes_Unbreakable)[i]->Render();
	}
	// Render all static objects
	for (UINT i = 0; i < m_pObjStatics->size(); i++)
	{
		(*m_pObjStatics)[i]->Render();
	}	
	// Render all Pulley objects
	for (UINT i = 0; i < m_pObjPulleys->size(); i++)
	{
		(*m_pObjPulleys)[i]->Render();
	}
	// Render all dynamic objects
	for (UINT i = 0; i < m_pObjDynamics->size(); i++)
	{
		(*m_pObjDynamics)[i]->Render();
	}
	// Render all breakable objects
	for (UINT i = 0; i < m_pObjBreakables->size(); i++)
	{
		(*m_pObjBreakables)[i]->Render();
	}

	m_pGem->Render();
}

void Level_Generic::CutRope(v2float _cutLinePtA, v2float _cutLinePtB)
{
	// Cycle through all cuttable ropes backwards so ropes can be deleted without changing the indices
	for (int i = (int)m_pRopes_Cuttable->size() - 1; i >= 0; i--)
	{
		// Retrieve the two points that make up the line of the rope
		v2float ropePtA = (*m_pRopes_Cuttable)[i]->GetPositionA();
		v2float ropePtB = (*m_pRopes_Cuttable)[i]->GetPositionB();

		// Check if the cutting line intersects the current rope line
		if (CheckLinesIntersect(_cutLinePtA, _cutLinePtB, ropePtA, ropePtB))
		{
			// Delete the rope and remove it from the vector of cuttable ropes
			ReleasePtr((*m_pRopes_Cuttable)[i]);
			m_pRopes_Cuttable->erase(m_pRopes_Cuttable->begin() + i);
		}
	}
}


