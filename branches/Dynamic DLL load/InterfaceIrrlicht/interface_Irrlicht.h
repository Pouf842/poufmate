#ifndef __INTERFACE_IRRLICHT_H_
#define __INTERFACE_IRRLICHT_H_

#include "../interface.h"
#include "irrlicht.h"

using namespace irr;

class InterfaceIrrlicht : public Interface
{  
  public :
	InterfaceIrrlicht(struct stExportedMethods exportedMethods);
	virtual ~InterfaceIrrlicht();
    virtual void Pause();
	virtual void DisplayGame(const Game &);
	virtual GameEntry oGetGameEntry(Game &);
	virtual void AddMessage(std::string);
	virtual EditionEntry oGetEditionEntry(const GameEdition &);
	virtual std::string strGetIPEntry();
	virtual std::string strGetPortEntry();
	virtual char cGetNewPieceType(Piece::Color);
	virtual int iGetMenuEntry(const std::vector<std::string> &);
	virtual char cGetPlayerColorChoice();

  protected :
    IrrlichtDevice * mpoMainWindow;
    video::IVideoDriver * mpoVideoDriver;
    scene::ISceneManager * mpoSceneManager;
    gui::IGUIEnvironment * mpoGUIEnvironment;
};

#endif