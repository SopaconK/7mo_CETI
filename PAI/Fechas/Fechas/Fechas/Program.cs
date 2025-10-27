// See https://aka.ms/new-console-template for more 
using System.Numerics;

int dia, mes, anio,fecha;
bool FechaValida = true;

Console.Write("Ingrese Dia ");
dia=int.Parse(Console.ReadLine());

Console.Write("Ingrese Mes ");
mes= int.Parse(Console.ReadLine());

Console.Write("Ingrese anio ");
anio = int.Parse(Console.ReadLine());


int[] DiasMes = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

if (anio % 4 == 0)
{
    if (anio % 100 == 0)
    {
        if (anio % 400 == 0)
        {
            DiasMes[2] = 29;
        }
        else
        {
            DiasMes[2] = 28;
        }
    }
    else
    {
        DiasMes[2] = 29;
    }
}
else
{
    DiasMes[2] = 28;
}


if (mes < 1 || mes > 12)
{
    FechaValida = false;
    Console.WriteLine("El mes no existe");
}
else
{
    if (dia < 1 || dia > DiasMes[mes])
    {
        FechaValida = false;
        Console.WriteLine("El mes tiene menos dias");
    }
}

if (FechaValida)
{
    fecha = dia + mes * 32 + anio * 512;
    Console.WriteLine(fecha);


    //fecha = int.Parse(Console.ReadLine());
    dia = fecha % 32;
    mes = (fecha / 32) % 16;
    anio = fecha / 512;

    if (anio % 4 == 0)
    {
        if (anio % 100 == 0)
        {
            if (anio % 400 == 0)
            {
                DiasMes[2] = 29;
            }
            else
            {
                DiasMes[2] = 28;
            }
        }
        else
        {
            DiasMes[2] = 29;
        }
    }
    else
    {
        DiasMes[2] = 28;
    }



    if (mes < 1 || mes > 12)
    {
        FechaValida = false;
        Console.WriteLine("El mes no existe");
    }
    else
    {
        if (dia < 1 || dia > DiasMes[mes])
        {
            FechaValida = false;
            Console.WriteLine("El mes tiene menos dias");
        }
    }

    if (FechaValida) Console.WriteLine("Fecha Valida");
    else Console.WriteLine("Fecha invalida");
    Console.Write("Dia: ");
    Console.WriteLine(dia);
    Console.Write("Mes: ");
    Console.WriteLine(mes);
    Console.Write("Anio: ");
    Console.WriteLine(anio);

}