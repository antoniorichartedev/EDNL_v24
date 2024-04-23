/*

    Dos Agen son similares si tienen la misma ramificación y sus hojas son similares tanto en contenido
    como en posición. Implementar una función que me diga si dos Agen son similares o no.
    Nota: ten en cuenta que, si en una hoja, los contenidos son distintos, aunque la ramificación es correcta,
    NO son similares. Si resulta que un nodo que tiene hijos, tiene la misma ramificación que el otro,
    pero tiene distinto contenido, de momento son similares. Entonces, en las hojas tienen que tener
    el mismo contenido y posición mientras que, en los que no son hojas, no tiene por qué tener el mismo 
    contenido, pero sí la misma ramificación.

    Para resolverlo, tenemos que tener en cuenta 4 casos:
        - Ambos agen son vacíos.
        - Uno es nulo y el otro no.
        - Ambos son hojas.
        - Si el nodo por el que estamos tiene hijos, exploramos. El núm. de hijos lo comprobamos
        con una función externa.

*/

