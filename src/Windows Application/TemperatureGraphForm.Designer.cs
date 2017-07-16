namespace BluetoothApplication
{
    partial class TemperatureGraphForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.tempChart = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.graphButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.tempChart)).BeginInit();
            this.SuspendLayout();
            // 
            // tempChart
            // 
            chartArea1.Name = "ChartArea1";
            this.tempChart.ChartAreas.Add(chartArea1);
            this.tempChart.Cursor = System.Windows.Forms.Cursors.No;
            legend1.Name = "Legend1";
            this.tempChart.Legends.Add(legend1);
            this.tempChart.Location = new System.Drawing.Point(136, 3);
            this.tempChart.Name = "tempChart";
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series1.IsXValueIndexed = true;
            series1.Legend = "Legend1";
            series1.Name = "Temperature [ºC]";
            series1.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Time;
            this.tempChart.Series.Add(series1);
            this.tempChart.Size = new System.Drawing.Size(708, 417);
            this.tempChart.TabIndex = 0;
            this.tempChart.Text = "temperatureChart";
            // 
            // graphButton
            // 
            this.graphButton.Location = new System.Drawing.Point(748, 439);
            this.graphButton.Name = "graphButton";
            this.graphButton.Size = new System.Drawing.Size(96, 42);
            this.graphButton.TabIndex = 1;
            this.graphButton.Text = "Display Graph";
            this.graphButton.UseVisualStyleBackColor = true;
            this.graphButton.Click += new System.EventHandler(this.button1_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(344, 439);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(104, 17);
            this.label1.TabIndex = 2;
            this.label1.Text = "Time [seconds]";
            // 
            // TemperatureGraphForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(916, 493);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.graphButton);
            this.Controls.Add(this.tempChart);
            this.Name = "TemperatureGraphForm";
            this.Text = "Temperature Line Chart";
            this.Load += new System.EventHandler(this.TemperatureGraphForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.tempChart)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataVisualization.Charting.Chart tempChart;
        private System.Windows.Forms.Button graphButton;
        private System.Windows.Forms.Label label1;
    }
}