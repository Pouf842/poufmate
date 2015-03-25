#ifndef __INTERFACE_IRRLICHT_H_
#define __INTERFACE_IRRLICHT_H_

#include "Interface/interface.h"
#include "irrlicht.h"
#include "PieceNode/PieceNodeFactory.h"

class State;
class MenuState;
class GameState;

class InterfaceIrrlicht : public Interface, public irr::IEventReceiver
{
  public :
	irr::IrrlichtDevice * mpoDevice;
	irr::video::IVideoDriver * mpoVideoDriver;
	irr::gui::IGUIEnvironment * mpoGUI;
	irr::scene::ISceneManager * mpoSceneManager;
	irr::scene::ISceneNode * mpoBoardNode;
	irr::scene::IMesh * mpoBoardMesh;
	irr::core::map<Piece::PIECE_TYPE, irr::scene::IAnimatedMesh*> moPiecesMeshes;

	InterfaceIrrlicht();
	virtual ~InterfaceIrrlicht();
	virtual int iGetMenuEntry(const std::vector<std::string> oMenu);
	virtual Entry oGetEntry();
	virtual void DisplayMessage(const std::string strMessage);
	virtual std::string strGetIPEntry();
	virtual std::string strGetPortEntry();
	virtual Piece::PIECE_TYPE eGetNewPieceType(const Piece::PIECE_COLOR);
	virtual Piece::PIECE_COLOR eGetPlayerColorChoice();
	virtual Entry::ENTRY_COMMAND GameOver(std::string strMessage);
	virtual void SetBusy();
	virtual void SetProgress(unsigned int);
	virtual bool OnEvent(const irr::SEvent &);
	virtual void SwitchCameraType();

  protected :
    PieceNodeFactory moPieceNodeFactory;
	State * mpoCurrentState;
	void InitDatas();
	void PlacePieces();
	void SetState(State *);
	MenuState * mpoMenuState;
	GameState * mpoGameState;
	State * mpoPieceViewerState;
	irr::scene::ICameraSceneNode * mpoCameraFPS;
	irr::scene::ICameraSceneNode * mpoCamera;
	irr::scene::ICameraSceneNode * mpoCurrentCamera;
};

#endif