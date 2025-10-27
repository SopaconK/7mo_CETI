// See https://aka.ms/new-console-template for more information


int[] lista = new int[5];
int ultimo = 0;


Console.WriteLine("Dame la cadena");
String cad = Console.ReadLine();

PasarStringAEnteros(cad);
for (int i = 0; i < ultimo; i++) { 
    Console.WriteLine(lista[i]);
}

Console.Write("Tamaño original: "); Console.WriteLine(cad.Length);
Console.Write("Tamaño comprimido: "); Console.WriteLine(ultimo);
Console.WriteLine(Descomprimir(lista));



void ChangueSize()
{
    int[] aux=new int[lista.Length*2];
    for(int i=0; i<lista.Length; i++)
    {
        aux[i]=lista[i];
    }
    lista = aux;
}


int ConvertirInt(char caracter, int posicion, int cantidad)
{
    //  Console.Write(caracter);Console.Write("  "); Console.Write(posicion); Console.Write("  "); Console.Write(cantidad); Console.Write("  ");Console.WriteLine();
    return cantidad + posicion * 16 + caracter * 256;
}

void PasarStringAEnteros(String cadena)
{
    
    int posicion = 0;

    for (; posicion < cadena.Length; posicion++)
    {
        int posicionaux = -1;
        for (int i = posicion - 1; i > posicion - 8 && i >= 0; i--)
        {
            if (cadena[i] == cadena[posicion])
            {
                posicionaux = i; break;
            }
        }


        if (posicionaux == -1)
        {
            if (ultimo < lista.Length)
            {
                lista[ultimo] = ConvertirInt(cadena[posicion], 0, 0);
                ultimo++;
            }
            else
            {
                ChangueSize();
                lista[ultimo] = ConvertirInt(cadena[posicion], 0, 0);
                ultimo++;
            }
        }
        else
        {
            int posicionfinal = posicionaux + 1;
            for (int i = posicion + 1; i < cadena.Length && i < posicion + 8; i++)
            {

                if (cadena[i] == cadena[posicionfinal])
                {
                    posicionfinal++;
                }
                else break;
            }
            if (posicion + posicionfinal - posicionaux < cadena.Length)
            {
                if (ultimo < lista.Length)
                {
                    lista[ultimo] = ConvertirInt(cadena[posicion + posicionfinal - posicionaux], posicion - posicionaux, posicionfinal - posicionaux);
                      ultimo++;
                }
                else
                {
                    ChangueSize();
                    lista[ultimo] = ConvertirInt(cadena[posicion + posicionfinal - posicionaux], posicion - posicionaux, posicionfinal - posicionaux);
                    ultimo++;
                }
            }
            else
            {
                if (ultimo < lista.Length)
                {
                    lista[ultimo] = ConvertirInt('_', posicion - posicionaux, posicionfinal - posicionaux);
                    ultimo++;
                }
                else
                {
                    ChangueSize();
                    lista[ultimo] = ConvertirInt('_', posicion - posicionaux, posicionfinal - posicionaux);
                    ultimo++;
                }
            }
            posicion += posicionfinal - posicionaux;
        }
    }
}



String Descomprimir(int[] listacomp)
{
    String cadena = "";
    for (int i = 0; i < ultimo; i++)
    {
        if (listacomp[i] % 16 == 0)
        {
            cadena += (char)(listacomp[i] / 256);
        }
        else
        {
            int posicioninicial = cadena.Length - (listacomp[i] % 256) / 16;
            for (int j = 0; j < listacomp[i] % 16; j++)
            {
                cadena += (cadena[posicioninicial + j]);
            }
            if (i != ultimo - 1)
            {
                cadena += (char)(listacomp[i] / 256);
            }
        }
    }
    return cadena;
}




