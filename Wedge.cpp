//
//  Wedge.cpp
//  Fission
//
//  Created by C0deH4cker on 2/24/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Wedge.h"
#include "macros.h"
#include "tokens.h"
#include "Atom.h"
#include "Component.h"
#include "Direction.h"
#include "Grid.h"

using namespace fsn;


Wedge::Wedge(char type, Grid& grid)
: Component(type), DirectedComponent(type), grid(grid),
divisor(2), minusEnergy(0) {}

Direction Wedge::getDir() const {
	switch(type) {
		case TOK_WEDGE_UP:    return UP;
		case TOK_WEDGE_LEFT:  return LEFT;
		case TOK_WEDGE_DOWN:  return DOWN;
		case TOK_WEDGE_RIGHT: return RIGHT;
		
		default:
			fatal("Cell '%c' is not a Wedge.", type);
	}
}

bool Wedge::onHit(Atom& atom) {
	Direction dir(getDir());
	
	if(atom.dir == dir) {
		// Hit the inside of the fork, so consume the atom
		divisor = atom.mass;
		minusEnergy = atom.energy;
		return true;
	}
	
	if((atom.dir ^ 2) == dir) {
		// The atom hit the vertex, so split the atom.
		//
		// WARNING: DO NOT TRY THIS AT HOME. SPLITTING ATOMS IS ONLY TO BE DONE
		// BY TRAINED PROFESSIONALS. BY USING THE PRODUCT YOU ACKNOWLEDGE THAT
		// THERE IS NO WARRANTY, EXPRESS OR IMPLIED,	 AND THAT C0DEH4CKER IS NOT
		// LIABLE FOR ANY INJURIES, DECAPITATIONS, OR SPONTANEOUS COMBUSTIONS
		// THAT MAY RESULT FROM YOUR USE OF THE PRODUCT. IF THE WORLD AND/OR
		// UNIVERSE COME TO A FIERY END AS A RESULT OF SPLITTING ATOMS WITH
		// THE PRODUCT, C0DEH4CKER IS NOT TO BE HELD RESPONSIBLE IN ANY WAY.
		//
		// Have fun!
		int left = atom.mass / divisor;
		atom.mass -= left;
		atom.energy -= minusEnergy;
		atom.dir = (dir + 1) & 3;
		
		Atom split(atom);
		split.mass = left;
		split.dir = (dir + 3) & 3;
		
		grid.spawn(split);
	}
	else {
		atom.dir = dir;
	}
	
	return false;
}

