# Videogame Programming - P1
First project of the videogame programming subject, in which we have made a small 2D game using C++.


## Basic description
The aim of the game is to survive the enemies that appear until we reach the final boss and destroy it. To do this the player can move and shoot at the enemies, which are moving towards it. 

![Screenshot](https://i.imgur.com/0DFL1Pa.png)

## Features
- Enemy behavior: The basic enemies can take 3 hits before dying. with each hit they will be more wounded, and the more wounded they are, the faster they will approach the player. You can visually tell how much life they have left.
- Invulnerability of the player: If the player is hit, it has a second during which it is invulnerable and it moves much faster to escape from danger. The appearance of the character changes noticeably during the interval. If the player gets hit 3 times, it has lost, and it is also possible to appreciate how much life is left through the appearance of the character.
  
![Screenshot](https://i.imgur.com/uNT9ZFF.png)


- Final boss behaviour: The final boss can take a total of 20 hits, divided into 10 for the first phase and 5 for the two following ones. In the first phase it stays still shooting at us, in the second one it starts to approach the player slowly while shooting, and in the third phase it stops shooting for good to approach at a much higher speed. You can tell what phase he is in by his appearance.
- End of the game: The game ends when the final boss is defeated or when we the player is killed. Depending on what the cause is, the end screen will be different.

![Screenshot](https://i.imgur.com/tGYgz3Y.png)
