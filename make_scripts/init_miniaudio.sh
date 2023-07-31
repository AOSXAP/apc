if [ -d "build_mini" ] 
then 
    rm -rf ./build_mini 
fi

if [ -f "libminiaudio.a" ]; then
    rm -f ./libminiaudio.a
fi


mkdir build_mini;
cd build_mini;
cmake ../dependencies/miniaudio;
make;

cp ./libminiaudio.a ../