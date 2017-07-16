namespace BluetoothApplication
{
    partial class ApplicationForm
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
            this.availableBluetoothDevicesListBox = new System.Windows.Forms.ListBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.serverRadioButton = new System.Windows.Forms.RadioButton();
            this.clientRadioButton = new System.Windows.Forms.RadioButton();
            this.scanBluetoothDevicesButton = new System.Windows.Forms.Button();
            this.bluetoothCommMonitorTextBox = new System.Windows.Forms.TextBox();
            this.tbText = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.availableBtDevicesLabel = new System.Windows.Forms.Label();
            this.sendButton = new System.Windows.Forms.Button();
            this.connectedBluetoothDevicesListBox = new System.Windows.Forms.ListBox();
            this.connectedBtDevicesLabel = new System.Windows.Forms.Label();
            this.displayTemperatureChartButton = new System.Windows.Forms.Button();
            this.openSerialPortButton = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.closeSerialPortButton = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.serialBaudRateComboBox = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.serialComPortComboBox = new System.Windows.Forms.ComboBox();
            this.temperatureCharGroupBox = new System.Windows.Forms.GroupBox();
            this.serialCommMonitorTextBox = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.temperatureCharGroupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // availableBluetoothDevicesListBox
            // 
            this.availableBluetoothDevicesListBox.FormattingEnabled = true;
            this.availableBluetoothDevicesListBox.ItemHeight = 16;
            this.availableBluetoothDevicesListBox.Location = new System.Drawing.Point(629, 196);
            this.availableBluetoothDevicesListBox.Name = "availableBluetoothDevicesListBox";
            this.availableBluetoothDevicesListBox.Size = new System.Drawing.Size(385, 116);
            this.availableBluetoothDevicesListBox.TabIndex = 0;
            this.availableBluetoothDevicesListBox.DoubleClick += new System.EventHandler(this.availableDevicesListBox_DoubleClick);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.serverRadioButton);
            this.groupBox1.Controls.Add(this.clientRadioButton);
            this.groupBox1.Controls.Add(this.scanBluetoothDevicesButton);
            this.groupBox1.Location = new System.Drawing.Point(629, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(385, 129);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Bluetooth Connection Mode";
            // 
            // serverRadioButton
            // 
            this.serverRadioButton.AutoSize = true;
            this.serverRadioButton.Location = new System.Drawing.Point(12, 60);
            this.serverRadioButton.Name = "serverRadioButton";
            this.serverRadioButton.Size = new System.Drawing.Size(66, 20);
            this.serverRadioButton.TabIndex = 3;
            this.serverRadioButton.TabStop = true;
            this.serverRadioButton.Text = "Server";
            this.serverRadioButton.UseVisualStyleBackColor = true;
            // 
            // clientRadioButton
            // 
            this.clientRadioButton.AutoSize = true;
            this.clientRadioButton.Location = new System.Drawing.Point(12, 33);
            this.clientRadioButton.Name = "clientRadioButton";
            this.clientRadioButton.Size = new System.Drawing.Size(59, 20);
            this.clientRadioButton.TabIndex = 2;
            this.clientRadioButton.TabStop = true;
            this.clientRadioButton.Text = "Client";
            this.clientRadioButton.UseVisualStyleBackColor = true;
            // 
            // scanBluetoothDevicesButton
            // 
            this.scanBluetoothDevicesButton.Location = new System.Drawing.Point(239, 88);
            this.scanBluetoothDevicesButton.Name = "scanBluetoothDevicesButton";
            this.scanBluetoothDevicesButton.Size = new System.Drawing.Size(126, 23);
            this.scanBluetoothDevicesButton.TabIndex = 6;
            this.scanBluetoothDevicesButton.Text = "Scan Devices";
            this.scanBluetoothDevicesButton.UseVisualStyleBackColor = true;
            this.scanBluetoothDevicesButton.Click += new System.EventHandler(this.bluetoothDeviceScanButton_Click);
            // 
            // bluetoothCommMonitorTextBox
            // 
            this.bluetoothCommMonitorTextBox.AcceptsReturn = true;
            this.bluetoothCommMonitorTextBox.BackColor = System.Drawing.SystemColors.Window;
            this.bluetoothCommMonitorTextBox.Location = new System.Drawing.Point(9, 20);
            this.bluetoothCommMonitorTextBox.Multiline = true;
            this.bluetoothCommMonitorTextBox.Name = "bluetoothCommMonitorTextBox";
            this.bluetoothCommMonitorTextBox.ReadOnly = true;
            this.bluetoothCommMonitorTextBox.Size = new System.Drawing.Size(585, 460);
            this.bluetoothCommMonitorTextBox.TabIndex = 4;
            // 
            // tbText
            // 
            this.tbText.Location = new System.Drawing.Point(12, 498);
            this.tbText.Name = "tbText";
            this.tbText.Size = new System.Drawing.Size(501, 22);
            this.tbText.TabIndex = 5;
            this.tbText.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tbText_KeyPress);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(206, 16);
            this.label1.TabIndex = 7;
            this.label1.Text = "Bluetooth Communication Monitor";
            // 
            // availableBtDevicesLabel
            // 
            this.availableBtDevicesLabel.AutoSize = true;
            this.availableBtDevicesLabel.Location = new System.Drawing.Point(626, 161);
            this.availableBtDevicesLabel.Name = "availableBtDevicesLabel";
            this.availableBtDevicesLabel.Size = new System.Drawing.Size(177, 16);
            this.availableBtDevicesLabel.TabIndex = 8;
            this.availableBtDevicesLabel.Text = "Available Bluetooth Devices";
            // 
            // sendButton
            // 
            this.sendButton.Location = new System.Drawing.Point(519, 498);
            this.sendButton.Name = "sendButton";
            this.sendButton.Size = new System.Drawing.Size(75, 23);
            this.sendButton.TabIndex = 9;
            this.sendButton.Text = "send";
            this.sendButton.UseVisualStyleBackColor = true;
            this.sendButton.Click += new System.EventHandler(this.sendButton_Click);
            // 
            // connectedBluetoothDevicesListBox
            // 
            this.connectedBluetoothDevicesListBox.FormattingEnabled = true;
            this.connectedBluetoothDevicesListBox.ItemHeight = 16;
            this.connectedBluetoothDevicesListBox.Location = new System.Drawing.Point(629, 362);
            this.connectedBluetoothDevicesListBox.Name = "connectedBluetoothDevicesListBox";
            this.connectedBluetoothDevicesListBox.SelectionMode = System.Windows.Forms.SelectionMode.None;
            this.connectedBluetoothDevicesListBox.Size = new System.Drawing.Size(385, 116);
            this.connectedBluetoothDevicesListBox.TabIndex = 10;
            // 
            // connectedBtDevicesLabel
            // 
            this.connectedBtDevicesLabel.AutoSize = true;
            this.connectedBtDevicesLabel.Location = new System.Drawing.Point(626, 332);
            this.connectedBtDevicesLabel.Name = "connectedBtDevicesLabel";
            this.connectedBtDevicesLabel.Size = new System.Drawing.Size(185, 16);
            this.connectedBtDevicesLabel.TabIndex = 11;
            this.connectedBtDevicesLabel.Text = "Connected Bluetooth Devices";
            // 
            // displayTemperatureChartButton
            // 
            this.displayTemperatureChartButton.Location = new System.Drawing.Point(72, 88);
            this.displayTemperatureChartButton.Name = "displayTemperatureChartButton";
            this.displayTemperatureChartButton.Size = new System.Drawing.Size(108, 23);
            this.displayTemperatureChartButton.TabIndex = 12;
            this.displayTemperatureChartButton.Text = "Display";
            this.displayTemperatureChartButton.UseVisualStyleBackColor = true;
            this.displayTemperatureChartButton.Click += new System.EventHandler(this.button1_Click);
            // 
            // openSerialPortButton
            // 
            this.openSerialPortButton.ForeColor = System.Drawing.Color.Black;
            this.openSerialPortButton.Location = new System.Drawing.Point(80, 106);
            this.openSerialPortButton.Name = "openSerialPortButton";
            this.openSerialPortButton.Size = new System.Drawing.Size(138, 23);
            this.openSerialPortButton.TabIndex = 13;
            this.openSerialPortButton.Text = "Open Serial Port";
            this.openSerialPortButton.UseVisualStyleBackColor = true;
            this.openSerialPortButton.Click += new System.EventHandler(this.openSerialPortButton_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.closeSerialPortButton);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.serialBaudRateComboBox);
            this.groupBox2.Controls.Add(this.openSerialPortButton);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.serialComPortComboBox);
            this.groupBox2.Location = new System.Drawing.Point(629, 550);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(224, 174);
            this.groupBox2.TabIndex = 14;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Serial Port";
            // 
            // closeSerialPortButton
            // 
            this.closeSerialPortButton.Location = new System.Drawing.Point(80, 145);
            this.closeSerialPortButton.Name = "closeSerialPortButton";
            this.closeSerialPortButton.Size = new System.Drawing.Size(138, 23);
            this.closeSerialPortButton.TabIndex = 15;
            this.closeSerialPortButton.Text = "Close Serial Port";
            this.closeSerialPortButton.UseVisualStyleBackColor = true;
            this.closeSerialPortButton.Click += new System.EventHandler(this.closeSerialPortButton_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 64);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(72, 16);
            this.label5.TabIndex = 16;
            this.label5.Text = "Baud Rate";
            // 
            // serialBaudRateComboBox
            // 
            this.serialBaudRateComboBox.FormattingEnabled = true;
            this.serialBaudRateComboBox.Location = new System.Drawing.Point(86, 61);
            this.serialBaudRateComboBox.Name = "serialBaudRateComboBox";
            this.serialBaudRateComboBox.Size = new System.Drawing.Size(121, 24);
            this.serialBaudRateComboBox.TabIndex = 15;
            this.serialBaudRateComboBox.DropDown += new System.EventHandler(this.serialBaudRateComboBox_DropDown);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 25);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(65, 16);
            this.label4.TabIndex = 1;
            this.label4.Text = "COM Port";
            // 
            // serialComPortComboBox
            // 
            this.serialComPortComboBox.FormattingEnabled = true;
            this.serialComPortComboBox.Location = new System.Drawing.Point(86, 20);
            this.serialComPortComboBox.Name = "serialComPortComboBox";
            this.serialComPortComboBox.Size = new System.Drawing.Size(121, 24);
            this.serialComPortComboBox.TabIndex = 0;
            this.serialComPortComboBox.DropDown += new System.EventHandler(this.serialComPortComboBox_DropDown);
            // 
            // temperatureCharGroupBox
            // 
            this.temperatureCharGroupBox.Controls.Add(this.displayTemperatureChartButton);
            this.temperatureCharGroupBox.Location = new System.Drawing.Point(1045, 12);
            this.temperatureCharGroupBox.Name = "temperatureCharGroupBox";
            this.temperatureCharGroupBox.Size = new System.Drawing.Size(200, 129);
            this.temperatureCharGroupBox.TabIndex = 15;
            this.temperatureCharGroupBox.TabStop = false;
            this.temperatureCharGroupBox.Text = "Temperature Graph";
            // 
            // serialCommMonitorTextBox
            // 
            this.serialCommMonitorTextBox.Location = new System.Drawing.Point(9, 559);
            this.serialCommMonitorTextBox.Multiline = true;
            this.serialCommMonitorTextBox.Name = "serialCommMonitorTextBox";
            this.serialCommMonitorTextBox.Size = new System.Drawing.Size(585, 239);
            this.serialCommMonitorTextBox.TabIndex = 16;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(6, 539);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(185, 16);
            this.label6.TabIndex = 17;
            this.label6.Text = "Serial Communication Monitor";
            // 
            // ApplicationForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1311, 810);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.serialCommMonitorTextBox);
            this.Controls.Add(this.temperatureCharGroupBox);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.connectedBtDevicesLabel);
            this.Controls.Add(this.connectedBluetoothDevicesListBox);
            this.Controls.Add(this.sendButton);
            this.Controls.Add(this.availableBtDevicesLabel);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.bluetoothCommMonitorTextBox);
            this.Controls.Add(this.tbText);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.availableBluetoothDevicesListBox);
            this.Name = "ApplicationForm";
            this.Text = "Bluetooth & Serial Communication ";
            this.Load += new System.EventHandler(this.ApplicationForm_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.temperatureCharGroupBox.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox availableBluetoothDevicesListBox;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton serverRadioButton;
        private System.Windows.Forms.RadioButton clientRadioButton;
        private System.Windows.Forms.TextBox bluetoothCommMonitorTextBox;
        private System.Windows.Forms.TextBox tbText;
        private System.Windows.Forms.Button scanBluetoothDevicesButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label availableBtDevicesLabel;
        private System.Windows.Forms.Button sendButton;
        private System.Windows.Forms.ListBox connectedBluetoothDevicesListBox;
        private System.Windows.Forms.Label connectedBtDevicesLabel;
        private System.Windows.Forms.Button displayTemperatureChartButton;
        private System.Windows.Forms.Button openSerialPortButton;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox serialComPortComboBox;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox serialBaudRateComboBox;
        private System.Windows.Forms.Button closeSerialPortButton;
        private System.Windows.Forms.GroupBox temperatureCharGroupBox;
        private System.Windows.Forms.TextBox serialCommMonitorTextBox;
        private System.Windows.Forms.Label label6;
    }
}

