# CTLModelChecking

## Authors:

	Cassiano Zaghi de Oliveira - 7987400

	Elisa Jorge Marcatto - 7961965

	Victor Marcelino Nunes - 8622381

## To compile:
	
	make

## To execute ("path" is the path of the input file):
	
	make run IN="path"

## To clean binarie and object files:
	
	make clean

## Input file example:

	7
	1 0 2 2 4
	2 2 S E 1 3
	3 3 S C E 2 2 4
	4 1 C 2 1 5
	5 2 S C 1 7
	6 2 C H 3 1 4 6
	7 3 S C H 1 6
	(AG((E)->(AF(!(E)))))

Where 

1. First line has the **totLines** value of non-null integer describing the total states of the state machine
2. The next **totLinhas** consecutive lines will have the following elements separated by space
	1. Unique state identifier (integer type)
	2. Total **totProps** of properties (integer type)
	3. Sequence of **totProps** strings representing the labels of properties given as valid identifiers, separated by space
	4. Total upcoming **totProxEstad** states (integer type)
	5. Sequence of **totProxEstad** valid identifiers of the next states, separated by space
3. The last line should include the CTL expression to be verified.
