#include "Transacciones.h"
#include <iostream>
#include <string.h>

using namespace std;

int main() {
	int opcion = 0;
	do {
		cout << "\n\n * * * * *   M E N U   B A N C A R I O   * * * * * \n\n";
		cout << "1. Registrar Cuenta Nueva" << endl;
		cout << "2. Consultar Cuentas" << endl;
		cout << "3. Realizar Transaccion" << endl;
		cout << "4. Consultar Historial de Cuenta" << endl;
		cout << "5. Salir" << endl;
		cin >> opcion;
		switch (opcion) {
		case 1: {
			registrarCuenta();
			break;
		}
		case 2: {
			consultarCuentas();
			break;
		}
		case 3: {
			Transaccion();
			break;
		}
		case 4: {
			HistorialCuenta();
			break;
		}
		}
	} while (opcion != 5);
	system("pause>nul");
}