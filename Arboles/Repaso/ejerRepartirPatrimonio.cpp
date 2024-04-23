/*

    Teniendo una familia representada con un árbol general, un nodo padre tiene que repartir su 
    patrimonio y sus propiedades entre sus descendientes. Haz ese reparto de forma equitativa. 
    Cuando se haya repartido el patrimonio y sus propiedades con los hijos, esos hijos tienen que,
    de manera recursiva, repartir ese patrimonio y las propiedades de la misma forma.
    Nota: si estamos repartiendo el patrimonio y las propiedades entre los hijos, si un hijo tiene
    más hijos, ese es el que más se lleva por ejemplo.

    Padre tiene -> 40k€, un Aston Martin y una casa en la playa.
    Ese padre tiene 4 hijos, de forma que:
        - Hijo 1: no tiene hijos, entonces se lleva 10k€
        - Hijo 2: tiene 3 hijos, se lleva 10k€ y el Aston Martin.
        - Hijo 3: no tiene hijos, se lleva 10k€
        - Hijo 4: tiene 2 hijos, se lleva 10k€ y la casa en la playa.

    Luego, el hijo 2 y 4 tienen que repartir lo que han recibido con sus hijos y así sucesivamente.

    Para hacer esto:
        - Contar el nHijos del nodo por el que estamos iterando y encontrar el nodo que más hijos tenga.
        - Actualizamos el nodo por el que estamos iterando.
        - Hacemos la llamada recursiva con el hizq del nodo y luego pasamos al hermano derecho del hizq.

*/