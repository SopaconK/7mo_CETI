


int Tamano;
Random rand = new Random();


Console.WriteLine("Dame tamano de el largo de la matriz");
Tamano = int.Parse(Console.ReadLine());

int[][] Matriz;
Matriz = new int[Tamano][];
for (int i = 0; i < Tamano; i++)
{
    Matriz[i] = new int[Tamano];
    for (int j = 0; j < Tamano; j++)
    {
        Matriz[i][j] = rand.Next(10);
    }
}
for(int i=0; i<Tamano; i++)
{
    for(int j=0; j<Tamano; j++)
    {
        Console.Write(Matriz[i][j]);
        Console.Write(" ");
    }
    Console.WriteLine();
}
Console.WriteLine(Determinante(Matriz));



int Determinante(int[][] Matriz)
{
    int Tamano = Matriz.Length;
    if (Tamano == 0) return 1;
    if (Tamano == 1) return Matriz[0][0];
    if (Tamano == 2)
    {
        return Matriz[0][0] * Matriz[1][1] - Matriz[0][1] * Matriz[1][0];
    }
    int ValorDeterminante = 0;
    for (int i = 0; i < Tamano; i++)
    {
        if (i % 2 == 0)
        {
            ValorDeterminante += Matriz[0][i] * Determinante(SubMatriz(Matriz, i));
        }
        else
        {
            ValorDeterminante -= Matriz[0][i] * Determinante(SubMatriz(Matriz, i));
        }
    }
    return ValorDeterminante;
}

int[][] SubMatriz(int[][] Matriz, int Columna)
{
    int[][] MatrizChiquita;

    MatrizChiquita = new int[Matriz.Length - 1][];

    for (int i = 0; i < MatrizChiquita.Length; i++)
    {
        MatrizChiquita[i] = new int[MatrizChiquita.Length];
        for (int j = 0; j < Columna; j++)
        {
            MatrizChiquita[i][j] = Matriz[i + 1][j];
        }
        for (int j = Columna + 1; j < Matriz.Length; j++)
        {
            MatrizChiquita[i][j - 1] = Matriz[i + 1][j];
        }
    }
    return MatrizChiquita;
}