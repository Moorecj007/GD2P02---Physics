ABOUT:
This game is a clone of Rich Mine 2 where the player tries to get the main 'valuable'
object to a specific point in the level designated as the Win Zone.

The graphics are rendered using GDI to draw simple circle and polygon shapes.The 
physics are simulated using Box2D to create fixtures and joints that allow Newtonian
physics, kinematics and projectile motion.


INSTRUCTIONS:
The aim of the game to to get the yellow Gem to the green win zone and advance through
all the levels. You must cut the orange ropes using your mouse in strategic order and 
at the right time critical moments. Avoid hitting any red enemy objects for they will
destroy your gem and you will have to restart.


CONTROLS:
Left Mouse Press	-> Start drawing a line to cut ropes with.
Left Mouse Release	-> Cut all orange ropes that cross the red line drawn between 
			   mouse click and release positions.

[R]     		-> Reset current Level
[F1]   			-> Skip to Level 01
[F2]   			-> Skip to Level 02
[F3]   			-> Skip to Level 03
[Esc] 			-> Quit Game


GAMEPLAY FEATURES:
 ->	Destructible Objects
 -> 	Indestructable Objects
 -> 	Enemy entities
 -> 	Indestructible Ground
 -> 	Swinging Objects
 -> 	Main Object - The Gem
 -> 	Springs
 -> 	Joints
 -> 	Levers
 -> 	Pulleys

COLOR LEGEND:
Black		-> Indestructible ground
Yellow		-> The Gem
Green		-> The Win Zone
Orange		-> A Cuttable Rope
Grey		-> A Non-cuttable Rope
		-> Pulley System
Cyan		-> Interactive and dynamic object
Red 		-> Enemy - Do not touch
Pink		-> Dynamically breakable object
Dark Blue	-> Spring Object


AUTHOR:
Callan Moore
MDS
2015


KNOWN BUGS:
 -> 	Some overlap can occur between objects when their densities are vastly different and
	they collide.

