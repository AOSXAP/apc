if [ -d "build_mini" ] 
then 
    rm -rf ./build_mini 
fi

if [ -d "bin" ] 
then 
    rm -rf ./bin
fi

if [ -f "libminiaudio.a" ]; then
    rm -f ./libminiaudio.a
fi


mkdir build_mini;
mkdir bin;
cd build_mini;
cmake ../dependencies/miniaudio;
make;

cp ./libminiaudio.a ../