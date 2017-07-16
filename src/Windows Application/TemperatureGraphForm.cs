using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.Diagnostics;
using System.Timers;
using System.Windows.Forms.DataVisualization.Charting;

namespace BluetoothApplication
{
  
    public partial class TemperatureGraphForm : Form
    {
        System.Windows.Forms.Timer chartTimer;

        public TemperatureGraphForm()
        {
            InitializeComponent();
            this.chartTimer = new System.Windows.Forms.Timer();
            this.Temperature = 29;
        }

        public double Temperature { set; get; }

        public void initChart()
        {
            DateTime time = DateTime.Now;
            chartTimer.Interval = 1000;
            chartTimer.Tick += chartTimer_Tick;
            tempChart.DoubleClick += chartDemo_DoubleClick;

            Series series = tempChart.Series[0];
            series.ChartType = SeriesChartType.Spline;

            tempChart.ChartAreas[0].AxisX.LabelStyle.Format = "HH:mm:ss";
            tempChart.ChartAreas[0].AxisX.ScaleView.Size = 5;
            tempChart.ChartAreas[0].AxisX.ScrollBar.IsPositionedInside = true;
            tempChart.ChartAreas[0].AxisX.ScrollBar.Enabled = true;

            chartTimer.Start();
        }

        void chartTimer_Tick(object sender, EventArgs e)
        {
            Series series = tempChart.Series[0];
            series.Points.AddXY(DateTime.Now, this.Temperature);
            tempChart.ChartAreas[0].AxisX.ScaleView.Position = series.Points.Count - 5;
        }

        //show the scrollBar
        void chartDemo_DoubleClick(object sender, EventArgs e)
        {
            tempChart.ChartAreas[0].AxisX.ScaleView.Size = 5;
            tempChart.ChartAreas[0].AxisX.ScrollBar.IsPositionedInside = true;
            tempChart.ChartAreas[0].AxisX.ScrollBar.Enabled = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.initChart();
        }

        private void TemperatureGraphForm_Load(object sender, EventArgs e)
        {
            this.chartTimer.Stop();
        }
    }
}
        
