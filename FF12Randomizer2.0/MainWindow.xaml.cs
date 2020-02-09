using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace FF12RandomizerVer2
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            DataContext = new MainViewModel();

            OpenFileDialog openFileDialog = new OpenFileDialog();
            if (openFileDialog.ShowDialog() == true)
            {
                ByteArray data = new ByteArray(File.ReadAllBytes(openFileDialog.FileName));

                BattlePack battlePack = new BattlePack(openFileDialog.FileName);

                battlePack.WordFile.Write();

                TextFile textFile = new TextFile("word0.bin.txt");

                MessageBox.Show(textFile.Format);

                //MessageBox.Show(battlePack.Equipment[(int)EquipID.Unarmed].Power.ToString());
            }
        }

        private void FlagGrid_MouseEnter(object sender, MouseEventArgs e)
        {
            MainDataContext.CurrentFlag = (Flag)((Grid)sender).DataContext;
        }

        public MainViewModel MainDataContext => (MainViewModel)DataContext;

        private void FlagGrid_MouseLeave(object sender, MouseEventArgs e)
        {
            if (MainDataContext.CurrentFlag == (Flag)((Grid)sender).DataContext)
                MainDataContext.CurrentFlag = null;
        }
    }
}
