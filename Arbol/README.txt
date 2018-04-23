INFO sobre cómo modificar el arbol
Cada txt cuenta con tres cifras más una cadena de texto, correspondiente a:
-Numero de hijos
-Por comprar (0) / Comprado(1)
-Precio de Compra
-Descripción

Para añadir un hijo a una hoja, se ha de crear un nuevo .txt que se llame igual 
al padre + "1". IMPORTANTE, se debe modificar el número de hijos del padre.

Para añadir otro hijo en un determinado punto, se debe crear también un .txt
que se llame igual que el padre + el siguiente número natural que siga a los
hijos ya existentes. IMPORTANTE, se debe actualizar el número de hijos del padre.

INFO sobre HABILIDADES.txt 
	Es la raiz de todo el árbol, y cuenta con un número adicional
que se corresponde con la id de la raíz (en principio 1, no conviene modificar
para que no sea igual que la de algun hijo). Este es el segundo número, justo
después del número de hijos principales.
Por lo demás cuenta con la misma estructura que los demás.