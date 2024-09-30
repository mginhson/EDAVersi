# EDAversi

## Integrantes del grupo y contribución al trabajo de cada integrante

* Mateo Sosa: Algoritmo de getValidMoves e investigación de la función heurística.
* Matteo Ginhson: Implementación del recorrido del árbol con alpha beta pruning. 

## Parte 1: Generación de movimientos válidos y algoritmo de jugada

    Para verificar el correcto funcionamiento, nos aseguramos en varias partidas contra el algoritmo default de la IA (Movimientos random) de que no se ejecutasen movimientos ilegales, sumado a nosotros apretar todos los casilleros que deberían ser ilegales y verificando que el algoritmo no nos dejase posicionar fichas en ese casillero.

## Parte 2: Implementación del motor de IA

    Nos basamos en la explicación de este artículo de Medium 
    
    para entender tanto miniMax, como alpha beta pruning, y la implementación de ambos. Nos 
    guiamos también con el pseudocódigo que se encuentra al final del artículo, implementándolo en C++ y con el esqueleto para adaptarlo al Reversi. Nuestra implementación recorre el árbol con BFS sin crearlo per se, aprovechando el Stack de las funciones. Para cada jugada posible, la función minMax se llama recursivamente a si misma, cada vez con uno de todos los movimientos posibles, y se queda con el mejor.

## Parte 3: Poda del árbol

    El algoritmo sin la poda alpha beta, sin determinarle una cantidad de nodos, básicamente no termina nunca. Esto es debido a que intenta llegar al final del juego para verificar que tan buena es una rama, pero debido a que el funcionamiento es, dada una posición, probar todos los movimientos posibles, y dadas todas estas nuevas posiciones probar todos los movimientos posibles de cada una, y así recursivamente hasta que se llegase a que la partida terminase, se puede ver como la complejidad crece exponencialmente cuanto más se baja en el recorrido BFS. Calcular la complejidad computacional completa del algoritmo no es fácil, ya que la cantidad de jugadas y que tan bajo se recorre el árbol depende de cada posición en particular, pero la naturaleza exponencial de esta complejidad computacional prevalece indicando que es muy pesada. 
    Como primer mejora, implementamos un corte por profundidad: Luego de bajar tantos niveles, evalúamos la posición con una función heurística y le asignabamos ese valor a la 
    posición, para luego ser evaluado por minMax. Nuestro algoritmo denota al menos infinito como victoria del oponente, más infinito como victoria de la IA, valores positivos como favorables para la IA, y negativos como favorables para el humano. 
    Como última mejora, implementamos Alpha Beta Pruning: 

## Documentación adicional
    https://medium.com/@joancerretanids/aprendizaje-por-refuerzo-rl-capítulo-4-min-max-y-alpha-beta-pruning-parte-2-alpha-beta-c460d6e973a6




## Bonus points

[Aquí.]
