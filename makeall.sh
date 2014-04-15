#!/bin/bash -x
mkdir -p ./bin
mkdir -p ~/bin
cp ./ymake ~/bin
cp ./ypath ~/bin
for f in *.cpp
do
    fn=${f%.*}
    ymake $f
    mv $fn ./bin/
done

cp ./bin/* ~/bin/
cp ./*.py ~/bin/
cp ./*.sh ~/bin/
echo "yUtils have copied to ~/bin/ , please make sure ~/bin/ is in your \$PATH"
