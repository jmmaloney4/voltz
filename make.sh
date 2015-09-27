git submodule init
mkdir -p build
cd ./build
make

if [[ $? != 0 ]]; then

  cd ..

  echo -e "\n *** Build Failed. Retrying From Scratch. *** \n"

  rm -rf build
  mkdir -p build
  cd build
  rm -rf CMakeCache.txt
  cmake .. -G Unix\ Makefiles
  make -k clean all

  r=$?

  if [[ $r != 0 ]]; then
    echo -e "\n *** Build Failed. *** \n"
    exit $r
  fi
fi

if [[ $1 == "test" ]]; then

  ./tests
  exit $?
fi
