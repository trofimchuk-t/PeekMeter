using PeekMeterWrapper;
using System;
using System.Windows.Forms;

namespace PeekMetersForm
{
    public partial class MainForm : Form
    {
        private PeekMeter peekMeter = new PeekMeter();
        private Timer timer = new Timer();

        private const int MaxProgressBarValue = 500;
        private const int UpdateFrequency = 30;
        private bool useFallingFading = true;
        private float fadingCoef = 0.75f;

        public MainForm()
        {
            InitializeComponent();

            progressBar1.Maximum = MaxProgressBarValue;
            progressBar2.Maximum = MaxProgressBarValue;

            timer.Interval = 1000 / UpdateFrequency;
            timer.Tick += new EventHandler(UpdateLevels);
            timer.Start();
        }

        private void UpdateLevels(object sender, EventArgs e)
        {
            var levels = peekMeter.GetLevels();

            UpdateProgressBar(progressBar1, levels[0]);
            UpdateProgressBar(progressBar2, levels[1]);
        }

        private void UpdateProgressBar(ProgressBar progressBar, float level)
        {
            int preparedValue = (int)(level * MaxProgressBarValue);
            int prevProgressBarValue = progressBar.Value;

            if (useFallingFading && preparedValue < prevProgressBarValue)
            {
                if (preparedValue < prevProgressBarValue * fadingCoef)
                {
                    preparedValue = (int)(prevProgressBarValue * fadingCoef);
                }
            }

            // need to immediately updating progress bar value
            progressBar.Value = MaxProgressBarValue;
            progressBar.Value = preparedValue;
        }
    }
}