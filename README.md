## Please use the original author's github: https://github.com/novikovag/SanDic

```
brew install qt5
brew link qt5 --force
git clone https://github.com/novikovag/SanDic.git
cd SanDic
qmake -o Makefile SanDic.pro
make
cd db; unzip sandic.db.zip; unzip yukta.db.zip
mv sandic.app /Applications
```

## How to replace sidddhanta-calcutta.ttf with siddhanta.ttf
Download from: https://sites.google.com/site/bayaryn/siddhanta.ttf?attredirects=0
cp siddhanta.ttf rc/siddhanta-calcutta.ttf
