set copyPath=..\..\src\Core\

cd ..\..\Release\SDK Interfaces\

copy %copyPath%\Core\board.h Core\
copy %copyPath%\Core\square.h Core\
copy %copyPath%\Core\position.h Core\
copy %copyPath%\Interface\entry.h Interface\
copy %copyPath%\Interface\interface.h Interface\
copy %copyPath%\Modules\game.h Modules\
copy %copyPath%\Modules\module.h Modules\
copy %copyPath%\Pieces\piece.h Pieces\

pause