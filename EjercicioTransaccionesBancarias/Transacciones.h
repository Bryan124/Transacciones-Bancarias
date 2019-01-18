#pragma once
#ifndef TRANSACCIONES_H
#define TRANSACCIONES_H

struct cliente{
	int codigo;
	char nombre[20];
	double saldo;
};

struct tran {
	int codigo;
	int tipo;
	double monto;
};

void registrarCuenta();
void consultarCuentas();
void HistorialCuenta();
void Transaccion();
int buscaC(int codi);
double buscaS(int codi);

#endif // !1
