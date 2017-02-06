using System;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Forms;
using System.Windows.Threading;

namespace PeekMetersWPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        [DllImport(@"PeekMeter.dll", EntryPoint = "GetLevel")]
        public static extern float GetLevel();

        //private DispatcherTimer timer = new DispatcherTimer();
        private Timer timer = new Timer();

        private double level = 0;
        private double lastLevel = 0;

        public MainWindow()
        {
            InitializeComponent();

            ProgressBar.Maximum = 1000;
            //timer.Interval = new TimeSpan(0, 0, 0, 0, 1000 / 30);
            timer.Interval = 1000 / 30;
            timer.Tick += timer_Tick;
            timer.Start();
        }

        void timer_Tick(object sender, EventArgs e)
        {
            level = GetLevel();
            if (level > lastLevel)
            {
                lastLevel = level;
            }
            else
            {
                lastLevel *= 0.75;
            }
            //ProgressBar.Value = 1000;
            ProgressBar.Value = (int)(lastLevel * 1000);
        }
    }
}
