sudo apt-get update

sudo apt-get install freeglut3 freeglut3-dev

sudo apt-get install libglew-dev

sudo apt-get install libsoil-dev

g++ -o sistema_solar sistema_solar.cpp -lGL -lGLU -lglut -lSOIL

./sistema_solar


gcc -o solar_system solar_system.c -lGL -lGLU -lglut -lSOIL -lm
./solar_system


sudo apt-get update
sudo apt-get install build-essential libglu1-mesa-dev freeglut3-dev libsoil-dev

gcc -o sistema_solar sistema_solar.c -lGL -lGLU -lglut -lSOIL

./sistema_solar
