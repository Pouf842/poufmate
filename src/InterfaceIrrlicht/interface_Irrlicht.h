#ifndef __INTERFACE_IRRLICHT_H_
#define __INTERFACE_IRRLICHT_H_

#include <map>
#include "Interface/interface.h"
#include "irrlicht.h"

class State;

class InterfaceIrrlicht : public Interface, public irr::IEventReceiver
{
  public :
	State * mpoCurrentState;
	irr::IrrlichtDevice * mpoDevice;
	irr::video::IVideoDriver * mpoVideoDriver;
	irr::gui::IGUIEnvironment * mpoGUI;
	irr::scene::ISceneManager * mpoSceneManager;
	irr::scene::ISceneNode * mpoBoardNode;
	irr::scene::IMesh * mpoBoardMesh;
	std::map<Piece::PIECE_TYPE, irr::scene::IMesh*> moPiecesMeshs;

	InterfaceIrrlicht();
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

  protected :
	void InitMeshs();
	void SetState(State *);
};

#endif