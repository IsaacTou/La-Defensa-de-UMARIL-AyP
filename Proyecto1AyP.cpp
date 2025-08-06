#include <iostream>
#include <cmath>

using namespace std;
int main() {

    int CaXo, CaYo, Vo, tetha, NCanons, C;
    float enemyX, enemyY;
    const float pi = 3.14159;
    const float g = 9.81;
    const int ASCII = 64; // con este basicamente es para empezar en el 64 en la tabla ascii e ir sumando 
    char o = 65; // con este numero se asignara el valor de letra a cada canion sumandole 1 cada vez que se haga el bucle
    int enemy, T_enemy; // numeracion de los enemigos // Cantidad de enemigos

    cin >> C;
    if (C < 1 || C > 26) {
        cout << "datos invalidos" << endl; // aqui es para que la cantidad de ca�ones no sea mayor a 26
        return 1;
    }

    C = C + ASCII;
    //con el code de arriba cuando se ingrese un valor entonces ya empezara diciendo una letra en mayus del abecedario

    for (NCanons = 65; NCanons <= C; NCanons++, o++ /* esta o se le sumara 1 cada vez que se haga el bucle para declarar una letra*/) {

        cin >> CaXo;
        cin >> CaYo;
        if (CaYo <= -1 || CaYo > 50) {
            cout << "Datos de entrada invalidos del canon: " << o << endl;// esto es para que el ca�on no tenga altura negativa ni pase el muro
            cout << " " << endl;
            continue;
        }
        cin >> Vo;
        if (Vo < 1 || Vo > 500) {
            cout << "Datos de entrada invalidos del canon " << o << endl;// esto es para que el canon no pase la velocidad total
            cout << " " << endl;
            continue;
        }
        cin >> tetha;
        if (tetha > 180 || tetha < 0) {
            cout << "Datos de entrada invalidos del canon " << o << endl;// esto es para que el canon no tenga angulos locos
            cout << " " << endl;
            continue;
        }
        cin >> T_enemy;
        float Angulo_radianes = tetha * pi / 180.0; //Aqui se convierten 45 grados multiplicado por Pi entre 180 que da 1.30 y pico radianes

        //calcular velocidad horizontal y vertical. Aca se calcula la velocidad en X horizontal y la Y vertical
        const float Vx = Vo * cos(Angulo_radianes);
        const float Vy = Vo * sin(Angulo_radianes);
        float tt = round(2 * Vo * sin(Angulo_radianes) / g); //tiempo total

        float Ymax = 0.0;
        Ymax = round((Vy * Vy) / (2 * g) + (CaYo + Ymax)); // formula de la altura max

        cout << "Los proyectiles del canion " << o << " subiran hasta " << Ymax << " metros antes de comenzar a caer" << endl;
        cout << "Los proyectiles del canion " << o << " impactaran contra el suelo despues de " << tt << " segundos" << endl;
        cout << " " << endl;

        for (int enemy = 1; enemy <= T_enemy; enemy++) {
            cin >> enemyX >> enemyY; cout << endl;
            float t_impacto = round(enemyX / Vx);
            // FORMULA PARA EL REAJUSTE DEL ANGULO
            float distanciarealX = enemyX - CaXo; // se saca la distancia real en X considerando la posicion del canon para agregarla a la formula
            float distanciarealY = enemyY - CaYo; // se saca la distancia real en Y considerando la posicion del canon para agregarla a la formula
            float aceleration = -9.81; //la aceleracion que es A * X colocando la gravedad -9.81 de la formula que la contempla
            float a = (aceleration * pow(distanciarealX, 2)) / (2 * pow(Vo, 2)); //AL SER UNA FORMULA CUADRATICA, ya que la formula al cancelarse los lados de la ecuacion queda como una cuadratica
            float b = distanciarealX; // igual que el a, hallamos el valor de b que es la distancia real en X, en a es A*X2 / 2Vo2
            float c = a - distanciarealY; // hallamos c que es la distancia real en y - a
            float positive_root = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a); //Formulamos la cuadratica con el positivo
            float negative_root = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a); //Formulamos la cuadratica con el negativo
            float radian1 = atan(positive_root); //El resultado le aplicamos la arcotangente
            float radian2 = atan(negative_root); //El resultado le aplicamos la arcotangente
            // Como se puede observar poseemos 2 resultados por la forma de la cuadratica, teniendo asi 2 angulos posibles con todo el sentido del mundo
            float angleA1 = radian1 * 180 / pi; // convertimos los 2 angulos de radianes a grados
            float angleA2 = radian2 * 180 / pi;
            const int anglefinal1 = round(angleA1); //redondeamos esos angulos
            const int anglefinal2 = round(angleA2);
            int diferencia1 = anglefinal1 - tetha; //sacamos la diferencia 1 y diferencia 2
            int diferencia2 = anglefinal2 - tetha;
            bool angleprox = diferencia1 < diferencia2; // Esto para que? Para poder determinar cual es el que esta mas cerca del angulo que esta ingresado por el usuario y asi tener una efectividad en el reajuste para que mas rapidamente elimine al objetivo

            // CONDICIONALES PERTINENTES
            if (enemyY <= -1) {
                cout << "Datos de entrada invalidos en el canion: " << o << " enemigo en posicion invalida" << endl; //enemigo se encuentra en una posicion invalida puesto que -1 es bajo tierra
                continue;
            }

            if (tetha <= 90 && tetha >= 0) { //Aca se determinara a que direccion apunta el vector que se determinara por el angulo, si es de 0 a 90, es la derecha
                if (enemyX < CaXo) {
                    cout << "posicion comprometida" << endl;
                    cout << " " << endl;
                    continue;
                }
            }
            else if (tetha > 90 && tetha <= 180) { //Aca se determina el vector que apunta hacia la izquierda, mayor a 90 hasta 180

                if (enemyX > CaXo) {
                    cout << "posicion comprometida" << endl;
                    cout << " " << endl;

                    continue;
                }
            }

            if (CaXo == enemyX && enemyY == CaYo) {
                cout << "canion destruido" << endl; //identificacion de si el enemigo esta en el X del ca�on y en una altura igual que el mismo
                cout << " " << endl;
                break;
            }

            if (CaXo == enemyX && enemyY < CaYo) {
                cout << "enemigo bajo la muralla"; //identifiacion de si el enemigo esta bajo la muralla
                cout << " " << endl;
                continue;
            }
            int reajuste; //VARIABLE DECLARADA DE REAJUSTE
            if (anglefinal1 != tetha && anglefinal2 != tetha) { //CONDICIONAL QUE DETERMINA SI EL ANGULO CORRECTO ES DIFERENTE AL INGRESADO POR EL USUARIO

                if (tetha > 90) { //Si esta condicion se cumple quiere decir que tetha, es decir, el angulo es mayor que 90, puesto que apunta la izquierda y se hace la conversion pertinente a angulos agudos
                    if (diferencia2 < 0 && angleprox == true) { //Se hace que se escoga el angulo mas cercano si el tetha es mayor que el angulo 2 correcto
                        reajuste = (anglefinal2 - tetha) + 180; //esta es la formula que hace el reajuste de grados, el 180 representa la transformacion a angulos agudos
                        if (reajuste > 180 || reajuste < -180 || (reajuste + tetha) > 180) { //Aqui se determina que si son angulos inconclusos es fuera de alcance
                            cout << "Enemigo fuera del alcance o dato invalido" << endl;
                            cout << " " << endl;
                            continue;
                        }
                        if (reajuste == 0) { //Esto valida que si el reajuste es 0 el angulo es correcto
                            cout << "Objetivo " << enemy << " destruido por el canion " << o << " en " << t_impacto << " segundos" << endl;
                            cout << " " << endl;
                            continue;
                        }
                        cout << "Reajuste de " << reajuste << " grados requerido en el canion " << o << endl;
                        cout << " " << endl;
                        continue;
                    }
                    reajuste = (anglefinal1 - tetha) + 180; //Se hace que se escoga el angulo mayor mas cercano si el tetha es menor
                    if (reajuste > 180 || reajuste < -180 || (reajuste + tetha) > 180) { //Aqui se determina que si son angulos inconclusos es fuera de alcance
                        cout << "Enemigo fuera del alcance o dato invalido" << endl;
                        cout << " " << endl;
                        continue;
                    }
                    if (reajuste == 0) { //Esto valida que si el reajuste es 0 el angulo es correcto
                        cout << "Objetivo " << enemy << " destruido por el canion " << o << " en " << t_impacto << " segundos" << endl;
                        cout << " " << endl;
                        continue;
                    }
                    cout << "Reajuste de " << reajuste << " grados requerido en el canion " << o << endl;
                    cout << " " << endl;
                    continue;
                }
                if (diferencia2 < 0 && angleprox == true) { // Validacion con angulos agudos 
                    reajuste = anglefinal2 - tetha; //Formula del reajuste
                    if (reajuste > 180 || reajuste < -180|| (reajuste + tetha) > 90) {
                        cout << "Enemigo fuera del alcance o dato invalido" << endl; //Aqui se determina que si son angulos inconclusos es fuera de alcance
                        cout << " " << endl;
                        continue;
                    }
                    cout << "Reajuste de " << reajuste << " grados requerido en el canion " << o << endl;
                    cout << " " << endl;
                    continue;

                }
                reajuste = anglefinal1 - tetha; //Validacion con angulos agudos buscando el angulo arriba mas cercano
                if (reajuste > 180 || reajuste < -180 || (reajuste + tetha) > 90) {
                    cout << "Enemigo fuera del alcance o dato invalido" << endl; //Aqui se determina que si son angulos inconclusos es fuera de alcance
                    cout << " " << endl;
                    continue;
                }
                cout << "Reajuste de " << reajuste << " grados requerido en el canion " << o << endl;
                cout << " " << endl;
                continue;

            }
            cout << "Objetivo " << enemy << " destruido por el canion " << o << " en " << t_impacto << " segundos" << endl;
            cout << " " << endl;
        }
    }
    return 0;
}