#include "Transacciones.h"
#include <string.h>
#include <fstream>
#include <iostream>

using namespace std;

void registrarCuenta() {

	ofstream ArchivoOut("Maestro de Cuentas.txt", ios::out | ios::app | ios::binary);
	if (!ArchivoOut) {
		cout << "ERROR ARCHIVO" << endl;
		return;
	}

	ArchivoOut.seekp(0, ios::end);

	cout << "\n\n * * * * * R E G I S T R O  D E  C U E N T A S * * * * * \n\n";
	cliente nuevo;
	cout << "Ingrese numero de cuenta: ";
	cin >> nuevo.codigo;;
	cout << "Ingrese nombre de cuenta: ";
	cin >> nuevo.nombre;
	nuevo.saldo = 0;

	ArchivoOut.write(reinterpret_cast<const char *>(&nuevo), sizeof(cliente));

	cout << "\nRegistro Guardado!" << endl;

	ArchivoOut.close();
}

void consultarCuentas() {

	ifstream ArchivoIn("Maestro de Cuentas.txt", ios::in | ios::binary);
	if (!ArchivoIn) {
		cout << "ERROR ARCHIVO" << endl;
		return;
	}

	ArchivoIn.seekg(0, ios::beg);

	cout << "\n\n * * * * * C O N S U L T A  D E  C U E N T A S * * * * * \n\n";
	cliente actual;
	ArchivoIn.read(reinterpret_cast<char *>(&actual), sizeof(cliente));
	while (!ArchivoIn.eof()) {

		cout << "Numero de Cuenta: " << actual.codigo << endl;
		cout << "Nombre de Cliente: " << actual.nombre << endl;
		cout << "Saldo Actual: " << actual.saldo << endl;
		cout << "\n------------------------------------------------\n";
		ArchivoIn.read(reinterpret_cast<char *>(&actual), sizeof(cliente));


	}
}

int buscaC(int codi) {

	ifstream ArchivoIn("Maestro de Cuentas.txt", ios::in | ios::binary);
	if (!ArchivoIn) {
		cout << "ERROR ARCHIVO" << endl;
		return -1;
	}

	int pos = 0, next = 0;

	ArchivoIn.seekg(0, ios::beg);
	cliente actual;
	ArchivoIn.read(reinterpret_cast<char *>(&actual), sizeof(cliente));
	while (!ArchivoIn.eof()) {
		if (actual.codigo == codi) {
			pos = next;
		}
		else {
			next++;
		}
		ArchivoIn.read(reinterpret_cast<char *>(&actual), sizeof(cliente));
	}
	int pos2 = (sizeof(cliente)) * (pos - 1);
	return pos2;
}

double buscaS(int codi) {
	ifstream ArchivoIn("Maestro de Cuentas.txt", ios::in | ios::binary);
	if (!ArchivoIn) {
		cout << "ERROR ARCHIVO" << endl;
		return -1;
	}

	double valor;

	ArchivoIn.seekg(0, ios::beg);
	cliente actual;
	ArchivoIn.read(reinterpret_cast<char *>(&actual), sizeof(cliente));
	while (!ArchivoIn.eof()) {
		if (actual.codigo == codi) {
			valor = actual.saldo;
		}
		ArchivoIn.read(reinterpret_cast<char *>(&actual), sizeof(cliente));
	}
	return valor;
}

void Transaccion() {
	ofstream ArchivoOut("Historial de Transacciones.txt", ios::out | ios::app | ios::binary);
	if (!ArchivoOut) {
		cout << "ERROR ARCHIVO" << endl;
		return;
	}
	fstream ArcOut("Maestro de Cuentas.txt", ios::in | ios::out | ios::binary);
	ifstream ArcIn("Maestro de Cuentas.txt", ios::in | ios::out |ios::binary);
	if(!ArcOut) {
		cout << "ERROR ARCHIVO" << endl;
		return;
	}
	ArchivoOut.seekp(0, ios::end);
	ArcIn.seekg(0, ios::beg);
	cout << "\n\n * * * * * T R A N S A C C I O N E S * * * * * \n\n";
	tran nuevo;
	cliente actual;
	cout << "Ingrese su numero de cuenta: ";
	cin >> nuevo.codigo;
	int code = nuevo.codigo;
	int ubi = buscaC(code);
	ArcIn.read(reinterpret_cast<char*>(&actual), sizeof(cliente));
	while(!ArcIn.eof()) {
		if (actual.codigo == code) {
			cout << "Ingrese el numero de su Transaccion\n 1. Deposito\n 2. Retiro\n";
			cin >> nuevo.tipo;
			int tip = nuevo.tipo;
			cout << "Ingrese monto a depositar o retirar: ";
			cin >> nuevo.monto;
			double mon = nuevo.monto;
			ArcOut.seekp(ubi, ios::beg);
			if (tip == 1) {
				actual.saldo = actual.saldo + mon;
			}
			else {
				actual.saldo = actual.saldo - mon;
			}
			ArcOut.write(reinterpret_cast<const char*>(&actual), sizeof(cliente));
			break;
		}
		ArcIn.read(reinterpret_cast<char*>(&actual), sizeof(cliente));
	}
	ArchivoOut.write(reinterpret_cast<const char *>(&nuevo), sizeof(tran));
	ArchivoOut.close();
	cout << "\nSaldo Actualizado!" << endl;
	ArcOut.close();
}

void HistorialCuenta() {

	ifstream ArchivoIn("Historial de Transacciones.txt", ios::in | ios::binary);
	if (!ArchivoIn) {
		cout << "ERROR ARCHIVO" << endl;
		return;
	}

	ArchivoIn.seekg(0, ios::beg);
	int user;
	cout << "Ingrese numero de cuenta: " << endl;
	cin >> user;

	cout << "\n\n * * * * * H I S T O R I A L  D E  T R A N S A C C I O N E S * * * * * \n\n";
	tran actual;
	ArchivoIn.read(reinterpret_cast<char *>(&actual), sizeof(tran));
	while (!ArchivoIn.eof()) {
		if (actual.codigo == user) {
			cout << "Codigo: " << actual.codigo << endl;
			cout << "Tipo de Transaccion: " << actual.tipo << endl;
			cout << "Monto: " << actual.monto << endl << "\n--------------------------------------------------------------------\n";
		}
		ArchivoIn.read(reinterpret_cast<char *>(&actual), sizeof(tran));
	}
}
 