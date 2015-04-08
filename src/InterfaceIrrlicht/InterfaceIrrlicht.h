#ifndef __INTERFACE_IRRLICHT_H_
#define __INTERFACE_IRRLICHT_H_

#include "interface.h"
#include "irrlicht.h"

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

	InterfaceIrrlicht(Controller *);
	virtual ~InterfaceIrrlicht();

    virtual void SetMenuState(std::vector<std::string> const * = NULL);
    virtual void SetGameState(const Board &);
    virtual void Run();
    virtual void Quit();
    virtual Piece::PIECE_TYPE eGetPromotionNewPiece();

    void SetPieceViewerState();
	virtual bool OnEvent(const irr::SEvent &);
	virtual void SwitchCameraType();
    virtual irr::scene::ISceneNode * CreateBoardNode();
	virtual irr::scene::ISceneNode * addPieceNode(Piece *, const Position &, irr::core::string<char> strName = "", irr::scene::ISceneNode * = NULL);
    virtual irr::scene::ISceneNode * addPieceNode(Piece::PIECE_TYPE, Piece::PIECE_COLOR, const Position &, irr::core::string<char> strName = "", irr::scene::ISceneNode * = NULL);
	virtual void RotateCamera(float, float, float);
	//virtual void RevolveCamera(const irr::core::vector3df &, float, float = 1000.0);

  protected :
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

    bool mbStop;
};

#endif