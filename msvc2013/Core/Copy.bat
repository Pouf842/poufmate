set copyPath=..\..\src\Core

cd ..\..\Release\SDK Interfaces\

copy %copyPath%\Core\board.h Core\
copy %copyPath%\Core\square.h Core\
copy %copyPath%\Core\position.h Core\
copy %copyPath%\interface.h interface.h
copy %copyPath%\piece.h piece.h
copy %copyPath%\Controller.h Controller.h

pause