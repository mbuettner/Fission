//
//  Cloner.cpp
//  Fission
//
//  Created by C0deH4cker on 2/27/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Cloner.h"
#include "macros.h"
#include "tokens.h"
#include "Component.h"
#include "DirectedComponent.h"
#include "Grid.h"
#include "Atom.h"
#include "Direction.h"

using namespace fsn;


Cloner::Cloner(char type, Grid& grid)
: Component(type), DirectedComponent(type), grid(grid), multiplier(1),
stored(UNKNOWN) {}


bool Cloner::onHit(Atom& atom) {
	Direction dir = getDir();
	
	if(atom.dir == dir) {
		multiplier = atom.mass;
		return true;
	}
	
	if((atom.dir ^ 2) == dir) {
		// The atom hit the vertex, so clone it because the law of conservation
		// of mass totally says this is okay and cool to do
		atom.mass *= multiplier;
		atom.dir = (atom.dir + 1) & 3;
		
		Atom clone(atom);
		clone.dir ^= 2;
		grid.spawn(clone);
	}
	else {
		// The atom hit a side of the cloner
		if(stored != (atom.dir ^ 2)) {
			// Either no atom was stored, or it was on the same side
			storedMass = atom.mass;
			storedEnergy = atom.energy;
			stored = atom.dir;
			return true;
		}
		
		// Combine the two atoms
		atom.mass += storedMass;
		atom.energy += storedEnergy;
		atom.dir = dir;
		
		// No longer storing an atom
		stored = UNKNOWN;
	}
	
	return false;
}

Direction Cloner::getDir() const {
	switch(type) {
		case TOK_CLONER_UP:    return UP;
		case TOK_CLONER_LEFT:  return LEFT;
		case TOK_CLONER_DOWN:  return DOWN;
		case TOK_CLONER_RIGHT: return RIGHT;
		
		default:
			fatal("Cell '%c' is not a Cloner.", type);
	}
}

