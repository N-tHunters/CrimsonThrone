if [ "$USER" != "root" ]
	then echo "Please, run as root"
	exit
fi
apt install libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev libglew-dev libassimp-dev libopenal-dev libfreetype-dev