#pragma once
#include <string>
#include <vector>
#include <windows.h>

struct Empleado {
    int codigoEmpleado;
    std::wstring nombre;
    std::wstring rfc;
    std::wstring fechaIngreso;
};

extern std::vector<Empleado> empleados;

void LlenarListView(HWND hListView, const std::vector<Empleado>& empleados);
