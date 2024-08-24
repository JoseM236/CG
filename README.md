sudo apt-get update
sudo apt-get install freeglut3 freeglut3-dev
sudo apt-get install libglew-dev
sudo apt-get install libsoil-dev
g++ -o sistema_solar sistema_solar.cpp -lGL -lGLU -lglut -lSOIL
./sistema_solar
