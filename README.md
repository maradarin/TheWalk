# TheWalk
OOP game

<pre>
Start position: 'S' on the map
Robots: batman, robin, joker (represented on the map with 'R')
Items: 1 / 2 / 3 on the map; each robot reacts differently to every item
Traps:
  - 'X' on the map for bombs; when a robot lands on an 'X' cell, it loses a life
  - 'Z' on the map for sensors
            How do sensors react? Suppose a part of our map resembles the example given below; when a sensor (the 'Z' cell) comes
            into the visible perimeter of the robot, it marks the adjacent cells with 'Z'.
            When a robot lands on a 'Z', it loses two lives.
            _ _ _             _ Z _
            _ Z _       ->    Z Z Z
            _ _ _             _ Z _
            
Empty cell: '_'
Finish position: 'F' on the map

Strategies:
  1. Batman: will do its best to reach the destination with minimal losses
     Effects of each item:
	- bat-item (1)   : destroys bombs ('X')
	- robin-item (2) : if it also has bat-items, gains immunity to traps ('X'/'Z'); if it has multiple bat-items, all but one bat-item can be converted to +1 life for each item
	- joker-item (3) : loses all; can exchange 1 (bat+robin) items to cancel effect
     
  2. Robin: the destination is the goal, but it will try to collect as many 2-type items as possible
     Effects of each item:
	- bat-item (1) : if he collects bat-item and has robin-item => immunity to sensors ('Z')
	- robin-item (2) : if he only has robin-item => visibility increases with 1 + diagonal movement
	- joker-item (3) : if he has robin-item, can choose not to pick it; otherwise -2 lives whenever he crosses a trap ('X'/'Z')
     
  3. Joker: kind of a wildcard; it moves spirally and if it doesn't have auxiliary items, it will simply pass through traps
     Effects of each item:
	- bat-item (1)   : immunity to traps ('X'/'Z')
	- robin-item (2) : can skip over 3 cells
	- joker-item (3) : loses immunity to traps, gains 3 more lives
     

</pre>
