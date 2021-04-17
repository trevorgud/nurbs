# NURBS

## How to compile:

	sudo apt-get install freeglut3-dev
	mkdir build
	cd build
	cmake ..
	make

Then run with `./bin/nurbs`

## Controlling the NURBS surface:

The scene starts off with one 3 by 4 control polygon on the XZ plane.

Navigation: left click and drag to rotate around the origin.

Toggle between selection modes with tab:
toggles between selecting a point, a row, a column, or the whole surface.

Change selected control point with `ctrl+right`, `ctrl+left`, `ctrl+up`, and `ctrl+down`

Move points in the x and z coordinates with the arrow keys.
Move points in the y coordinates with `PgUp` and `PgDown`.

Add a row or column by pressing `i` (or `shift-i`)
If a row is selected a row will be added in front (or behind) it.
If a column is selected a column will be added.

Delete a selected row or column in a similar way.
Press `d` and the selected row or column will be deleted.

#### Knots can be changed interactively:
Press `k` to enter knot mode for uKnots or `shift-k` for vKnots.
Press `tab` to cycle between which knot will be moved (the one with the asterisk) and move the knot with left and right arrows.

#### Order can be changed interactively:
If a row is selected the vOrder will be changed.
If a column is selected the uOrder will be changed.
Press `o` to increase the order or `shift-o` to decrease the order.

#### Weights can be changed interactively:
Press `w` to increase the selected point's weight or press `shift-w` to decrease its weight.

## History
Originally submitted on June 2, 2016 for project 4 in ECS 178 at UC Davis.
