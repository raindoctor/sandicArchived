brew install qt5

brew link qt5 --force

qmake -o Makefile SanDic.pro

make

mv sandic.app /Applications
