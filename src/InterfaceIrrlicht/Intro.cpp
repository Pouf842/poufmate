#include "Intro.h"

#include <iostream>
using namespace std;
using namespace irr;
using namespace scene;
using namespace core;

//void Intro::Intro()
//{
//	std::map<Piece::PIECE_TYPE, IMesh*> oPiecesMeshs;
//	oPiecesMeshs[Piece::PT_ROOK]   = NULL;
//	oPiecesMeshs[Piece::PT_KNIGHT] = NULL;
//	oPiecesMeshs[Piece::PT_BISHOP] = NULL;
//	oPiecesMeshs[Piece::PT_QUEEN]  = NULL;
//	oPiecesMeshs[Piece::PT_KING]   = NULL;
//	oPiecesMeshs[Piece::PT_PAWN]   = NULL;
//
//	IMesh * poBoardMesh = mpoSceneManager->getGeometryCreator()->createCubeMesh(vector3df(8, 1, 8));
//	IMeshSceneNode * poBoardNode = mpoSceneManager->addMeshSceneNode(poBoardMesh);
//	poBoardMesh->drop();
//	poBoardNode->setMaterialFlag(EMF_LIGHTING, true);
//	ITexture * poBoardTexture = mpoVideoDriver->getTexture("Medias/Images/board.bmp");
//	poBoardNode->setMaterialTexture(0, poBoardTexture);
//
//	for(std::map<Piece::PIECE_TYPE, IMesh*>::iterator i = oPiecesMeshs.begin(); i != oPiecesMeshs.end(); ++i)
//	{
//		irr::core::string<char> strMeshFile = "Medias/";
//		switch(i->first)
//		{
//		  case Piece::PT_ROOK :
//			strMeshFile += "rook.3ds";
//			break;
//		  case Piece::PT_PAWN :
//		  default :
//			strMeshFile += "pawn.3ds";//"sydney.md2";
//			break;
//		}
//
//		i->second = mpoSceneManager->getMesh(strMeshFile);
//	}
//
//	/*/for(unsigned int i = 0; i < 8; ++i)/*/unsigned int i = 0;/**/
//	{
//		mpoSceneManager->addMeshSceneNode(oPiecesMeshs[Piece::PT_PAWN], poBoardNode, -1, vector3df(-3.5 + i, 0.45, -2.5))->setScale(vector3df(0.5, 0.5, 0.5));
//		/*mpoSceneManager->addMeshSceneNode(oPiecesMeshs[Piece::PT_PAWN], poBoardNode, -1, vector3df(-3.5 + i, 0.45, -3.5))->setScale(vector3df(0.5, 0.5, 0.5));
//		mpoSceneManager->addMeshSceneNode(oPiecesMeshs[Piece::PT_PAWN], poBoardNode, -1, vector3df(-3.5 + i, 0.45,  2.5))->setScale(vector3df(0.5, 0.5, 0.5));
//		mpoSceneManager->addMeshSceneNode(oPiecesMeshs[Piece::PT_PAWN], poBoardNode, -1, vector3df(-3.5 + i, 0.45,  3.5))->setScale(vector3df(0.5, 0.5, 0.5));*/
//	}
//
//	/**/ISceneNodeAnimator * poRotator = mpoSceneManager->createRotationAnimator(vector3df(0, 5*3.6*0.05, 0));
//	ISceneNodeAnimator * poTranslator = mpoSceneManager->createFlyStraightAnimator(vector3df(0, 0, 500), vector3df(0, 0, 0), 2000);
//
//	poBoardNode->addAnimator(poRotator);
//	//poBoardNode->addAnimator(poTranslator);
//
//	/*/IntroAnimator * poAnim = new IntroAnimator(vector3df(0, 0, 500), vector3df(0, 0, 0), 2000);
//	poBoardNode->addAnimator(poAnim);/**/
//
//	while(mpoDevice->run() && !mbExit)// && !poAnim->bIsDone())
//	{
//		if(mpoDevice->isWindowActive())
//		{
//			mpoVideoDriver->beginScene(true, true, SColor(255, 210, 210, 210));
//			mpoSceneManager->drawAll();
//			mpoVideoDriver->endScene();
//		}
//		else
//			mpoDevice->yield();
//	}
//}