using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;


namespace PeekMetersForm
{
    public partial class MainForm : Form
    {
        [DllImport(@"PeekMeter.dll", EntryPoint = "GetLevel")]
        public static extern float GetLevel();

        private Timer timer = new Timer();
        private double level = 0;
        private double lastLevel = 0;

        public MainForm()
        {
            InitializeComponent();

            progressBar1.Maximum = 1000;
            timer.Interval = 1000 / 25;
            timer.Tick += new EventHandler(timer_Tick);
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
            progressBar1.Value = 1000;
            progressBar1.Value = (int)(lastLevel * 1000);
        }
    }
}
