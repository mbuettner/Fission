#Fission#

The programming language that defies the laws of conservation of mass and energy.


Fission is a 2-dimensional esoteric programming language. The program is comprised of atoms moving around. Each atom has a mass and an energy level. When
an atom is first created, it has a mass of 1 unit and 0 energy. It moves in a straight line either up, down, left or right. It can change direction
through various means such as bouncing off of mirrors.

##Atom lifetime##

Atoms will continue moving around until a component destroys it. All atoms move once per tick, simultaneously. Multiple atoms can share the same
position. When they hit the edge of the grid, they are wrapped around to the other side. If an atom's mass ever goes negative, it is destroyed.
When there are no more atoms left on the grid, the program exits with status 0 (except when the `*` component is hit).


##Components##

| Component | Description      |
|-----------|------------------|
|/, \       | Purely mirrors to turn control flow. |
|^, V, <, > | From the sides, these are mirrors to turn control flow. These are fission reactors when hit at the vertex. The atom splits in two: its mass is divided by this component's stored mass (default 2), and the energy of both atoms is decreased by this component's stored energy (default 0). The left half of the split atom is set to (mass / value), and the right half is set to (mass - left). When an atom hits the back (in the split), its mass and energy are stored in this component. |
|U, D, L, R | Spawns an atom at this position when the program starts. Direction is up, down, left, or right, respectively. When another atom hits this component, its direction is changed to the component's direction. |
|A, Y, {, } | These are fusion reactors. When an atom hits a side, it waits until an atom hits the other side. At this point, the two atoms are fused together by adding their masses and energy levels. This atom is released from the vertex. Cloner when hit from the vertex (mass is multiplied by this component's value, default of 1). The two cloned atoms go 90 degrees to the left and right of the component's vertex. Sets this component's value when hit from the back using the atom's mass, and that atom is then destroyed. |
|?          | When an atom goes here, its mass is replaced by the ASCII value of the input character and its energy is set to 1 if the standard input is at EOF and 0 otherwise. All other atoms freeze until input is read. If multiple atoms hit input components at the same time, they are ordered by row, then by column from the top-left. After EOF, all subsequent atoms if any are destroyed. |
|!          | When hit by an atom, the ASCII character represented by its mass is output. Same order as `?` for simultaneous occurrences. |
|O          | Same as `!`, but the atom is destroyed after printing. |
|$, ~       | Increments or decrements the atom's energy, respectively. |
|+, _       | Increments or decrements the atom's mass, respectively. |
|%, &       | Allows for conditional control flow. If the atom's energy level is at least 1, it is decremented and the atom bounces as if this component as if it were a `\` or `/` mirror, respectively. Otherwise, the atom bounces as if it were the opposite mirror. |
|@          | Swaps the atom's mass and energy. |
|K          | This is a stack. When an atom with nonnegative energy hits this, its mass and energy are pushed onto the stack, and the atom is destroyed. When hit by an atom with negative energy and the stack is not empty, its mass and energy are replaced by those popped from the stack and its direction remains unchanged. If the stack is empty, the atom is reflected. The reflected atom's mass will remain unchanged, but its energy will become positive. |
|Q          | Same as a stack, except this is a queue (FIFO rather than LIFO). |
|E          | NOT YET IMPLEMENTED. This is basically an array. Atoms with nonnegative energy are inserted into the array. The energy is used as the index, and the atom's mass is the value. The atom is then destroyed. The array will expand to contain the index if necessary. Elements are initialized to 0, and existing elements are replaced when inserting. If the atom's energy is negative, this signals an array lookup. The energy is made positive and decremented, then the value at that index in the array is used as the atom's new mass. The atom's energy and direction remain unchanged. |
|Z, S       | Act as rotational mirrors. Atoms will turn 90 degrees to the left or right, respectively, when the hit this component. Any atom with at least 1 energy will pass straight through this, and its energy will be decremented. |
|X          | Cloning mirror that duplicates the atom. One copy keeps moving forward, and the other is reflected. |
|:          | Half mirror that splits the atom in half (integer division by 2, where the remainder is added to one half). The larger half keeps moving forward, and the smaller half is reflected. |
|;          | Destroys atoms when they hit this component. |
|*          | Causes the program to terminate and all atoms are destroyed after this tick. The mass of the atom that caused termination is used as the exit code. If multiple atoms hit the same exit cell, the highest mass will be used as the exit code. |
|#          | Makes the atom move in a random direction (forward, left, or right). Atoms will not be reflected. |
|M, W, [, ] | The atom's direction is set to down, up, right, or left, respectively. |
|&#124;, -  | Atoms are reflected horizontally or vertically, respectively. From the edge, does nothing. |
|[a-z]      | The atom's mass is set to the ASCII value of this character. |
|[0-9]      | These are teleporters. When the atom hits a teleporter it will be transported to the next teleporter in order. Atoms will retain their mass, energy, and direction upon teleportation. If there is only one teleporter, it will have no effect. The order of teleporters is defined as follows: If two teleporters are in the same row, the order is left to right. Otherwise, the order is top to bottom. If there is no teleporter after the one that was hit, the atom will be teleported to the first one on the grid. |
|"          | Toggles printing mode. When an atom is in printing mode, it will print every character it encounters until the next `"`. Once printing is done, the atom's mass is set to the number of characters printed. |
|'          | The atom's mass will be set to the ASCII value of the next character it hits, and that component will not be evaluated. |
|J          | Causes any atom that hits this to instantly jump forward a certain number of cells, depending on its energy. An atom that has 1 energy will jump forward over 1 component after this one, if it has 0 energy, it will jump to the next element (basically a, and if it has negative energy it will jump backwards. The atom's energy is spent by jumping, so it will be 0 when it lands. |
|N          | Prints a newline character. |

Reserved for future use: ``BCEFGHIPT`()=,``. These currently have no effect, but will eventually be implemented.


All other characters are ignored completely, and atoms will pass through them without changing.



##Examples##

Simplest hello world (almost looks like a normal language):

    R"Hello, world!"N;

This program is functionally the same:

    ;N"!dlrow ,olleH"L

As is this one:

    D
    "
    H
    e
    l
    l
    o
    ,
     
    w
    o
    r
    l
    d
    !
    "
    N
    ;

Slightly more complex hello world:

               [......V   !  
       Start   .      .   w  
           \   .      .   !  
            |  .      +   o  
    !l!d!N; V  .  /...^...\!r
            R../  .comment.  
                  . block .  
    !l!e!h\       \...Y.../o!
          .***********.   !  
          .*Comments *.   '  
          .* can go  *.      
    ....../*anywhere!*\......

Reverses stdin:

    Z~]Z?L
    K  A /
    \!/;

Equivalent pseudocode:

    while not eof():
        c = getchar()
        stack.push(c)
    
    while not stack.empty():
        c = stack.pop()
        putchar(c)

