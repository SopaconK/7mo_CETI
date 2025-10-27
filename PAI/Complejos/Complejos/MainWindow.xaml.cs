using Complejos.modelos;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Complejos
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

     

      
        private void cmdSumarComplejos(object sender, RoutedEventArgs e)
        {
            Complejo a, b;
            int r, i;
            r = int.Parse(txtReal1.Text);
            i = int.Parse(txtImg1.Text);

            a = new Complejo(r, i);
            b = new Complejo(
                int.Parse(txtReal2.Text),
                int.Parse(txtImg2.Text)
                );

            Complejo s = a.Suma(a, b);

            txtResultadoReal.Text = s.Real.ToString();
            txtResultadoImg.Text =s.Imaginario.ToString();
        }
    }
}