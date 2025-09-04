🚦 Rush Hour 2D

A chaotic battle of traffic, speed, and strategy — built in C++ with GLUT/OpenGL






🎮 Game Overview

Rush Hour 2D is a traffic-inspired arcade game where players take on two distinct roles:

🏎️ Traffic Controller — Keep the roads safe by stopping reckless drivers and managing traffic chaos.

🚚 Delivery Driver — Complete deliveries across the city while dodging other cars, conserving petrol, and racing against time.

Every game is different — random jobs, dynamic car spawns, and leaderboard competition keep you on your toes.

✨ Features

✔️ Dual Gameplay Modes (Traffic Control & Delivery Driver)
✔️ Randomized jobs and destinations
✔️ Petrol management system (don’t run out of fuel!)
✔️ Leaderboard (tracks top scorers across sessions)
✔️ Dynamic obstacles & vehicle spawns
✔️ Sound integration with mpg123
✔️ Colorful 2D graphics rendered with GLUT/OpenGL

🎮 Controls
Key	Action
w a s d	Move player vehicle
d (in menu)	Choose Delivery Driver
t (in menu)	Choose Traffic Controller
space	Deliver job
o	Quit game
p	Resume game
Escape	Return to main menu
+ -	Adjust petrol
📂 Project Structure
RushHour2D/
│── util.h                # Drawing utilities (circles, shapes, etc.)
│── main.cpp              # Main game logic
│── leaderboard.txt        # Persistent high scores
│── /assets                # Images, sounds
│── /build                 # Compiled output

🛠️ Installation & Run
Requirements

C++ Compiler (g++, clang++, or MSVC)

OpenGL & GLUT libraries

mpg123 (for sound playback)

Run Instructions
# Clone repo
git clone https://github.com/your-username/RushHour2D.git
cd RushHour2D

# Compile
g++ main.cpp -lGL -lGLU -lglut -lmpg123 -o RushHour2D

# Run
./RushHour2D

🏆 Leaderboard

Your progress is saved in leaderboard.txt. The format is:

Player: Usaid  Score: 1200
Player: Ahmed  Score: 950


The game automatically sorts scores so only the best players climb to the top.

📸 Screenshots (Optional)

(Add when you take some in-game shots)

🚀 Future Enhancements

Smarter AI cars

Power-ups & penalties

Multiplayer mode

Better UI/UX menus

🤝 Contributing

PRs are welcome! If you’d like to add a feature, fix bugs, or improve performance, feel free to fork and send a pull request.
