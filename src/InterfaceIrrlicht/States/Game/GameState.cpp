#include "GameState.h"
#include "../../Tools.h"
#include "Controller.h"

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;
using namespace gui;

extern s32 ID_BOARD;
extern s32 ID_PIECE;

GameState::GameState(InterfaceIrrlicht * poInterface) : State(poInterface), mpoHighlightedPiece(NULL), mbIsDragging(false), moRelColl(0, 0, 0)
{
    try
    {
        mpoBoardNode = mpoInterface->CreateBoardNode();
        mpoBoardNode->setVisible(false);
    }
    catch(std::exception & e)
    {
        std::cout << __FUNCTION__ << ":" << __LINE__ << " : " << std::endl;
        throw e;
    }
}

void GameState::InitBoard(const Board & oNewBoard)
{
    try
    {
        list<ISceneNode*> oChildren = mpoBoardNode->getChildren();
        for each(ISceneNode * poNode in oChildren)
            poNode->remove();

        for(s32 i = 0; i < 8; ++i)
            for(s32 j = 0; j < 8; ++j)
                if(oNewBoard.poGetPiece(i, j))
                    mpoInterface->addPieceNode(oNewBoard.poGetPiece(i, j), Position(i, j), "", mpoBoardNode);
    }
    catch(std::exception & e)
    {
        std::cout << __FUNCTION__ << ":" << __LINE__ << " : " << std::endl;
        throw e;
    }
}

void GameState::Show()
{
    try
    {
        mpoInterface->mpoBoardNode->setVisible(false);
        mpoBoardNode->setVisible(true);
        PlaceCamera();
    }
    catch(std::exception & e)
    {
        std::cout << __FUNCTION__ << ":" << __LINE__ << " : " << std::endl;
        throw e;
    }
}

void GameState::PlaceCamera(bool bBack)
{
    bool bOver = false;
    u32 uStart = mpoDevice->getTimer()->getTime();
    const u32 TOTAL_PLACEMENT_TIME = 1000;
    ICameraSceneNode * poCamera = mpoSceneManager->getActiveCamera();
    vector3df oStartPos = poCamera->getAbsolutePosition();

    while(mpoDevice->run() && !bOver)
    {
        u32 uElapsed = mpoDevice->getTimer()->getTime() - uStart;
        float fFactor = ((float) uElapsed) / TOTAL_PLACEMENT_TIME;

        if(uElapsed > TOTAL_PLACEMENT_TIME)
        {
            fFactor = 1.0;
            bOver = true;
        }

        quaternion qRot;
        qRot.fromAngleAxis(fFactor * PI / 6 * (bBack ? 1 : -1), vector3df(-1, 0, 0));

        vector3df oNewPos = oStartPos;
        qRot.getMatrix().rotateVect(oNewPos);
        float fLengthFactor = (bBack ? 1 / 0.7 : 0.7);
        fLengthFactor = 1 - ((1 - fLengthFactor) * fFactor);
        oNewPos.setLength(oStartPos.getLength() * fLengthFactor);

        poCamera->setPosition(oNewPos);
        poCamera->setTarget(vector3df(0, 0, 0));

        mpoVideoDriver->beginScene();
        mpoSceneManager->drawAll();
        mpoVideoDriver->endScene();
    }
}

void GameState::Hide()
{
    try
    {
		if(mbIsDragging)
			mpoHighlightedPiece->setPosition(mvDraggedOriginPos);

		mbIsDragging = false;
		mpoHighlightedPiece = NULL;

        PlaceCamera(true);

        mpoInterface->mpoBoardNode->setVisible(true);
        mpoBoardNode->setVisible(false);
    }
    catch(std::exception & e)
    {
        std::cout << __FUNCTION__ << ":" << __LINE__ << " : " << std::endl;
        throw e;
    }
}

bool GameState::OnEvent(const SEvent & oEvent)
{
    try
    {
        if(oEvent.EventType == EET_KEY_INPUT_EVENT)
        {
            if(!oEvent.KeyInput.PressedDown)
            {
                if(oEvent.KeyInput.Key == KEY_SPACE)
                {
                    mpoInterface->SwitchCameraType();
                    return true;
                }
                else if(oEvent.KeyInput.Key == KEY_ESCAPE)
                {
                    mpoController->Escape();
                    return true;
                }
            }
        }
        else if(oEvent.EventType == EET_MOUSE_INPUT_EVENT)
        {
			if(oEvent.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN)
			{
				if(mpoHighlightedPiece)
				{
					mvDraggedOriginPos = mpoHighlightedPiece->getPosition();
					mpoController->GrabPiece(oGetBoardPosition(mvDraggedOriginPos));
					mbIsDragging = true;
				}
			}
			else if(oEvent.MouseInput.Event == EMIE_LMOUSE_LEFT_UP)
			{
				if(mbIsDragging)
				{
					vector3df oPos(mpoHighlightedPiece->getPosition());
					mpoController->DropPiece(oGetBoardPosition(oPos));

					oPos.X = round32(oPos.X + 0.5) - 0.5;
					oPos.Z = round32(oPos.Z + 0.5) - 0.5;
					mpoHighlightedPiece->setPosition(oPos);
					mbIsDragging = false;
				}
			}
			else if(oEvent.MouseInput.Event == EMIE_MOUSE_MOVED)
			{
				if(mbIsDragging)
				{
					vector2d<s32> vMousePos(oEvent.MouseInput.X, oEvent.MouseInput.Y);
					line3df ray = mpoCollisionManager->getRayFromScreenCoordinates(vMousePos);
					vector3df oBoardCollisionPoint;
					triangle3df oTriangle;

					ISceneNode * poNode = mpoCollisionManager->getSceneNodeAndCollisionPointFromRay(ray, oBoardCollisionPoint, oTriangle, ID_BOARD);

					if(poNode)
					{
						vector3df oCameraPos = mpoSceneManager->getActiveCamera()->getPosition();
						/*/vector3df oPieceCollisionPoint = mpoHighlightedPiece->getAbsolutePosition() + moRelColl.Y;
						vector3df v1 = oPieceCollisionPoint - oBoardCollisionPoint;
						vector3df v2 = oCameraPos - oBoardCollisionPoint;
						v2.Y = 0;
						vector3df vNewPos = v2 * (v1.dotProduct(v2) / v2.getLengthSQ());

						mpoHighlightedPiece->setPosition(oBoardCollisionPoint + vNewPos);/*/
						vector3df v = oCameraPos - oBoardCollisionPoint;
						v.Y = 0;

						float a = (moRelColl.Y - oBoardCollisionPoint.Y) * v.getLength();
						a /= oCameraPos.Y - oBoardCollisionPoint.Y;

						v.normalize() * a;

						vector3df oPos(oBoardCollisionPoint + v);

						if(oPos.X < -4)
							oPos.X = -4;

						if(oPos.Z < -4)
							oPos.Z = -4;

						oPos.Y = 0.5;
						mpoHighlightedPiece->setPosition(oPos);/**/
					}
				}
				else
				{
					vector2d<s32> vMousePos = mpoDevice->getCursorControl()->getPosition();
					line3df ray = mpoCollisionManager->getRayFromScreenCoordinates(vMousePos);
					vector3df oCollisionPoint;

					ISceneNode * poHighlightedPiece = mpoCollisionManager->getSceneNodeAndCollisionPointFromRay(ray, oCollisionPoint, triangle3df(), ID_PIECE);/*/

					vector2d<s32> oMousePos = mpoDevice->getCursorControl()->getPosition();
					ISceneNode * poHighlightedPiece = mpoCollisionManager->getSceneNodeFromScreenCoordinatesBB(oMousePos, ID_PIECE, false, mpoInterface->mpoBoardNode);/**/

					if(poHighlightedPiece != mpoHighlightedPiece)
						if(mpoHighlightedPiece)
							mpoHighlightedPiece->getMaterial(0).EmissiveColor = SColor(0, 0, 0, 0);

					mpoHighlightedPiece = poHighlightedPiece;

					if(mpoHighlightedPiece)
					{
						moRelColl = oCollisionPoint - mpoHighlightedPiece->getAbsolutePosition();
						mpoHighlightedPiece->getMaterial(0).EmissiveColor = SColor(255, 255, 0, 0);
					}
				}
			}
            //if(oEvent.MouseInput.isLeftPressed())
            //{
            //    if(mpoHighlightedPiece)
            //    {
            //        if(!mbIsDragging)   // Grab piece
            //        {
            //            vector3df oPos = mpoHighlightedPiece->getPosition();
            //            mpoController->GrabPiece(oGetBoardPosition(oPos));
            //            mbIsDragging = true;
            //        }
            //        else
            //        {
            //            vector2d<s32> vMousePos(oEvent.MouseInput.X, oEvent.MouseInput.Y);
            //            line3df ray = mpoCollisionManager->getRayFromScreenCoordinates(vMousePos);
            //            vector3df oBoardCollisionPoint;
            //            triangle3df oTriangle;

            //            ISceneNode * poNode = mpoCollisionManager->getSceneNodeAndCollisionPointFromRay(ray, oBoardCollisionPoint, oTriangle, ID_BOARD);

            //            if(poNode)
            //            {
            //                vector3df oCameraPos = mpoSceneManager->getActiveCamera()->getPosition();
            //                /*/vector3df oPieceCollisionPoint = mpoHighlightedPiece->getAbsolutePosition() + moRelColl.Y;
            //                vector3df v1 = oPieceCollisionPoint - oBoardCollisionPoint;
            //                vector3df v2 = oCameraPos - oBoardCollisionPoint;
            //                v2.Y = 0;
            //                vector3df vNewPos = v2 * (v1.dotProduct(v2) / v2.getLengthSQ());

            //                mpoHighlightedPiece->setPosition(oBoardCollisionPoint + vNewPos);/*/
            //                vector3df v = oCameraPos - oBoardCollisionPoint;
            //                v.Y = 0;

            //                float a = (moRelColl.Y - oBoardCollisionPoint.Y) * v.getLength();
            //                a /= oCameraPos.Y - oBoardCollisionPoint.Y;

            //                v.normalize() * a;

            //                vector3df oPos(oBoardCollisionPoint + v);

            //                if(oPos.X < -4)
            //                    oPos.X = -4;

            //                if(oPos.Z < -4)
            //                    oPos.Z = -4;

            //                oPos.Y = 0.5;
            //                mpoHighlightedPiece->setPosition(oPos);/**/
            //            }
            //        }
            //    }
            //}
            //else
            //{
            //    if(mbIsDragging)    // Drop piece
            //    {
            //        vector3df oPos(mpoHighlightedPiece->getPosition());
            //        mpoController->DropPiece(oGetBoardPosition(oPos));

            //        oPos.X = round32(oPos.X + 0.5) - 0.5;
            //        oPos.Z = round32(oPos.Z + 0.5) - 0.5;
            //        mpoHighlightedPiece->setPosition(oPos);
            //        mbIsDragging = false;
            //    }

            //    /**/vector2d<s32> vMousePos = mpoDevice->getCursorControl()->getPosition();
            //    line3df ray = mpoCollisionManager->getRayFromScreenCoordinates(vMousePos);
            //    vector3df oCollisionPoint;

            //    ISceneNode * poHighlightedPiece = mpoCollisionManager->getSceneNodeAndCollisionPointFromRay(ray, oCollisionPoint, triangle3df(), ID_PIECE);/*/

            //    vector2d<s32> oMousePos = mpoDevice->getCursorControl()->getPosition();
            //    ISceneNode * poHighlightedPiece = mpoCollisionManager->getSceneNodeFromScreenCoordinatesBB(oMousePos, ID_PIECE, false, mpoInterface->mpoBoardNode);/**/

            //    if(poHighlightedPiece != mpoHighlightedPiece)
            //        if(mpoHighlightedPiece)
            //            mpoHighlightedPiece->getMaterial(0).EmissiveColor = SColor(0, 0, 0, 0);

            //    if(poHighlightedPiece)
            //    {
            //        moRelColl = oCollisionPoint - poHighlightedPiece->getAbsolutePosition();
            //        mpoHighlightedPiece = poHighlightedPiece;
            //        mpoHighlightedPiece->getMaterial(0).EmissiveColor = SColor(255, 255, 0, 0);
            //    }
            //}

            return true;
        }

        return State::OnEvent(oEvent);
    }
    catch(std::exception & e)
    {
        std::cout << __FUNCTION__ << ":" << __LINE__ << " : " << e.what() << std::endl;

		if(mpoHighlightedPiece)
			mpoHighlightedPiece->setPosition(mvDraggedOriginPos);

        mbIsDragging = false;
    }
}