namespace SerialPort01
{
    partial class Form1
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
            this.components = new System.ComponentModel.Container();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.sendBtn = new System.Windows.Forms.Button();
            this.sendTextBox = new System.Windows.Forms.TextBox();
            this.receiveTextBox = new System.Windows.Forms.TextBox();
            this.OpenBtn = new System.Windows.Forms.Button();
            this.resetBtn = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.labelReceiveCounter = new System.Windows.Forms.Label();
            this.labelGetCount = new System.Windows.Forms.Label();
            this.checkBoxHexView = new System.Windows.Forms.CheckBox();
            this.labelPortName = new System.Windows.Forms.Label();
            this.comboBaurate = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.comboPortName = new System.Windows.Forms.ComboBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.labelSendCount = new System.Windows.Forms.Label();
            this.checkBoxSendHex = new System.Windows.Forms.CheckBox();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.timerCheckReceive = new System.Windows.Forms.Timer(this.components);
            this.timerSendPer5s = new System.Windows.Forms.Timer(this.components);
            this.timerSendPer80ms = new System.Windows.Forms.Timer(this.components);
            this.backgroundWorker2 = new System.ComponentModel.BackgroundWorker();
            this.numericUpDownIndex = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.numericUpDownLeftMotor = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownRightMotor = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownFeedData1 = new System.Windows.Forms.NumericUpDown();
            this.label5 = new System.Windows.Forms.Label();
            this.numericUpDownFeedData2 = new System.Windows.Forms.NumericUpDown();
            this.label6 = new System.Windows.Forms.Label();
            this.numericUpDownFeedData3 = new System.Windows.Forms.NumericUpDown();
            this.label7 = new System.Windows.Forms.Label();
            this.numericUpDownFeedData4 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownFeedData5 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownFeedData6 = new System.Windows.Forms.NumericUpDown();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.RobotFeedData = new System.Windows.Forms.GroupBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownIndex)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownLeftMotor)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownRightMotor)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownFeedData1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownFeedData2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownFeedData3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownFeedData4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownFeedData5)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownFeedData6)).BeginInit();
            this.RobotFeedData.SuspendLayout();
            this.SuspendLayout();
            // 
            // serialPort1
            // 
            this.serialPort1.BaudRate = 115200;
            // 
            // sendBtn
            // 
            this.sendBtn.Location = new System.Drawing.Point(486, 39);
            this.sendBtn.Name = "sendBtn";
            this.sendBtn.Size = new System.Drawing.Size(75, 23);
            this.sendBtn.TabIndex = 0;
            this.sendBtn.Text = "Send";
            this.sendBtn.UseVisualStyleBackColor = true;
            this.sendBtn.Click += new System.EventHandler(this.sendBtn_Click);
            // 
            // sendTextBox
            // 
            this.sendTextBox.Location = new System.Drawing.Point(6, 40);
            this.sendTextBox.Name = "sendTextBox";
            this.sendTextBox.Size = new System.Drawing.Size(474, 21);
            this.sendTextBox.TabIndex = 1;
            // 
            // receiveTextBox
            // 
            this.receiveTextBox.Location = new System.Drawing.Point(6, 42);
            this.receiveTextBox.Multiline = true;
            this.receiveTextBox.Name = "receiveTextBox";
            this.receiveTextBox.Size = new System.Drawing.Size(555, 101);
            this.receiveTextBox.TabIndex = 1;
            // 
            // OpenBtn
            // 
            this.OpenBtn.Location = new System.Drawing.Point(421, 19);
            this.OpenBtn.Name = "OpenBtn";
            this.OpenBtn.Size = new System.Drawing.Size(75, 23);
            this.OpenBtn.TabIndex = 2;
            this.OpenBtn.Text = "Open";
            this.OpenBtn.UseVisualStyleBackColor = true;
            this.OpenBtn.Click += new System.EventHandler(this.OpenBtn_Click);
            // 
            // resetBtn
            // 
            this.resetBtn.Location = new System.Drawing.Point(502, 19);
            this.resetBtn.Name = "resetBtn";
            this.resetBtn.Size = new System.Drawing.Size(75, 23);
            this.resetBtn.TabIndex = 3;
            this.resetBtn.Text = "Reset";
            this.resetBtn.UseVisualStyleBackColor = true;
            this.resetBtn.Click += new System.EventHandler(this.resetBtn_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.labelReceiveCounter);
            this.groupBox1.Controls.Add(this.labelGetCount);
            this.groupBox1.Controls.Add(this.checkBoxHexView);
            this.groupBox1.Controls.Add(this.receiveTextBox);
            this.groupBox1.Location = new System.Drawing.Point(10, 47);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(567, 155);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Data received";
            // 
            // labelReceiveCounter
            // 
            this.labelReceiveCounter.AutoSize = true;
            this.labelReceiveCounter.Location = new System.Drawing.Point(244, 22);
            this.labelReceiveCounter.Name = "labelReceiveCounter";
            this.labelReceiveCounter.Size = new System.Drawing.Size(149, 12);
            this.labelReceiveCounter.TabIndex = 4;
            this.labelReceiveCounter.Text = "ReceiveCounterPerSecond:";
            // 
            // labelGetCount
            // 
            this.labelGetCount.AutoSize = true;
            this.labelGetCount.Location = new System.Drawing.Point(118, 23);
            this.labelGetCount.Name = "labelGetCount";
            this.labelGetCount.Size = new System.Drawing.Size(71, 12);
            this.labelGetCount.TabIndex = 3;
            this.labelGetCount.Text = "Get Count:0";
            // 
            // checkBoxHexView
            // 
            this.checkBoxHexView.AutoSize = true;
            this.checkBoxHexView.Location = new System.Drawing.Point(6, 20);
            this.checkBoxHexView.Name = "checkBoxHexView";
            this.checkBoxHexView.Size = new System.Drawing.Size(72, 16);
            this.checkBoxHexView.TabIndex = 2;
            this.checkBoxHexView.Text = "Hex view";
            this.checkBoxHexView.UseVisualStyleBackColor = true;
            // 
            // labelPortName
            // 
            this.labelPortName.AutoSize = true;
            this.labelPortName.Location = new System.Drawing.Point(8, 24);
            this.labelPortName.Name = "labelPortName";
            this.labelPortName.Size = new System.Drawing.Size(59, 12);
            this.labelPortName.TabIndex = 5;
            this.labelPortName.Text = "Port Name";
            // 
            // comboBaurate
            // 
            this.comboBaurate.FormattingEnabled = true;
            this.comboBaurate.Items.AddRange(new object[] {
            "2400",
            "4800",
            "9600",
            "19200",
            "38400",
            "57600",
            "115200"});
            this.comboBaurate.Location = new System.Drawing.Point(272, 21);
            this.comboBaurate.Name = "comboBaurate";
            this.comboBaurate.Size = new System.Drawing.Size(121, 20);
            this.comboBaurate.TabIndex = 6;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(209, 24);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(47, 12);
            this.label1.TabIndex = 7;
            this.label1.Text = "Baurate";
            // 
            // comboPortName
            // 
            this.comboPortName.FormattingEnabled = true;
            this.comboPortName.Location = new System.Drawing.Point(71, 21);
            this.comboPortName.Name = "comboPortName";
            this.comboPortName.Size = new System.Drawing.Size(121, 20);
            this.comboPortName.TabIndex = 8;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.labelSendCount);
            this.groupBox2.Controls.Add(this.checkBoxSendHex);
            this.groupBox2.Controls.Add(this.sendTextBox);
            this.groupBox2.Controls.Add(this.sendBtn);
            this.groupBox2.Location = new System.Drawing.Point(6, 385);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(567, 71);
            this.groupBox2.TabIndex = 9;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Data send";
            // 
            // labelSendCount
            // 
            this.labelSendCount.AutoSize = true;
            this.labelSendCount.Location = new System.Drawing.Point(120, 20);
            this.labelSendCount.Name = "labelSendCount";
            this.labelSendCount.Size = new System.Drawing.Size(77, 12);
            this.labelSendCount.TabIndex = 3;
            this.labelSendCount.Text = "Send Count:0";
            // 
            // checkBoxSendHex
            // 
            this.checkBoxSendHex.AutoSize = true;
            this.checkBoxSendHex.Location = new System.Drawing.Point(6, 17);
            this.checkBoxSendHex.Name = "checkBoxSendHex";
            this.checkBoxSendHex.Size = new System.Drawing.Size(42, 16);
            this.checkBoxSendHex.TabIndex = 2;
            this.checkBoxSendHex.Text = "Hex";
            this.checkBoxSendHex.UseVisualStyleBackColor = true;
            // 
            // timerCheckReceive
            // 
            this.timerCheckReceive.Interval = 1200;
            this.timerCheckReceive.Tick += new System.EventHandler(this.timerCheckReceive_Tick);
            // 
            // timerSendPer5s
            // 
            this.timerSendPer5s.Interval = 5000;
            this.timerSendPer5s.Tick += new System.EventHandler(this.timerSendPer5s_Tick);
            // 
            // timerSendPer80ms
            // 
            this.timerSendPer80ms.Interval = 80;
            this.timerSendPer80ms.Tick += new System.EventHandler(this.timerSendPer80ms_Tick);
            // 
            // numericUpDownIndex
            // 
            this.numericUpDownIndex.Hexadecimal = true;
            this.numericUpDownIndex.Location = new System.Drawing.Point(110, 29);
            this.numericUpDownIndex.Maximum = new decimal(new int[] {
            131,
            0,
            0,
            0});
            this.numericUpDownIndex.Minimum = new decimal(new int[] {
            128,
            0,
            0,
            0});
            this.numericUpDownIndex.Name = "numericUpDownIndex";
            this.numericUpDownIndex.Size = new System.Drawing.Size(65, 21);
            this.numericUpDownIndex.TabIndex = 11;
            this.numericUpDownIndex.Value = new decimal(new int[] {
            128,
            0,
            0,
            0});
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(24, 33);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 12);
            this.label2.TabIndex = 12;
            this.label2.Text = "回传序号：";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(191, 33);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(77, 12);
            this.label3.TabIndex = 12;
            this.label3.Text = "左电机速度：";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(374, 33);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(77, 12);
            this.label4.TabIndex = 12;
            this.label4.Text = "右电机速度：";
            // 
            // numericUpDownLeftMotor
            // 
            this.numericUpDownLeftMotor.Location = new System.Drawing.Point(289, 29);
            this.numericUpDownLeftMotor.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numericUpDownLeftMotor.Name = "numericUpDownLeftMotor";
            this.numericUpDownLeftMotor.Size = new System.Drawing.Size(65, 21);
            this.numericUpDownLeftMotor.TabIndex = 11;
            // 
            // numericUpDownRightMotor
            // 
            this.numericUpDownRightMotor.Location = new System.Drawing.Point(468, 29);
            this.numericUpDownRightMotor.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numericUpDownRightMotor.Name = "numericUpDownRightMotor";
            this.numericUpDownRightMotor.Size = new System.Drawing.Size(65, 21);
            this.numericUpDownRightMotor.TabIndex = 11;
            // 
            // numericUpDownFeedData1
            // 
            this.numericUpDownFeedData1.Location = new System.Drawing.Point(110, 83);
            this.numericUpDownFeedData1.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numericUpDownFeedData1.Name = "numericUpDownFeedData1";
            this.numericUpDownFeedData1.Size = new System.Drawing.Size(65, 21);
            this.numericUpDownFeedData1.TabIndex = 11;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(24, 87);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(65, 12);
            this.label5.TabIndex = 12;
            this.label5.Text = "FeedData1:";
            // 
            // numericUpDownFeedData2
            // 
            this.numericUpDownFeedData2.Location = new System.Drawing.Point(289, 83);
            this.numericUpDownFeedData2.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numericUpDownFeedData2.Name = "numericUpDownFeedData2";
            this.numericUpDownFeedData2.Size = new System.Drawing.Size(65, 21);
            this.numericUpDownFeedData2.TabIndex = 11;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(203, 87);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(65, 12);
            this.label6.TabIndex = 12;
            this.label6.Text = "FeedData2:";
            // 
            // numericUpDownFeedData3
            // 
            this.numericUpDownFeedData3.Location = new System.Drawing.Point(468, 83);
            this.numericUpDownFeedData3.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numericUpDownFeedData3.Name = "numericUpDownFeedData3";
            this.numericUpDownFeedData3.Size = new System.Drawing.Size(65, 21);
            this.numericUpDownFeedData3.TabIndex = 11;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(382, 87);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(65, 12);
            this.label7.TabIndex = 12;
            this.label7.Text = "FeedData3:";
            // 
            // numericUpDownFeedData4
            // 
            this.numericUpDownFeedData4.Location = new System.Drawing.Point(110, 137);
            this.numericUpDownFeedData4.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numericUpDownFeedData4.Name = "numericUpDownFeedData4";
            this.numericUpDownFeedData4.Size = new System.Drawing.Size(65, 21);
            this.numericUpDownFeedData4.TabIndex = 11;
            // 
            // numericUpDownFeedData5
            // 
            this.numericUpDownFeedData5.Location = new System.Drawing.Point(289, 137);
            this.numericUpDownFeedData5.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numericUpDownFeedData5.Name = "numericUpDownFeedData5";
            this.numericUpDownFeedData5.Size = new System.Drawing.Size(65, 21);
            this.numericUpDownFeedData5.TabIndex = 11;
            // 
            // numericUpDownFeedData6
            // 
            this.numericUpDownFeedData6.Location = new System.Drawing.Point(468, 137);
            this.numericUpDownFeedData6.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numericUpDownFeedData6.Name = "numericUpDownFeedData6";
            this.numericUpDownFeedData6.Size = new System.Drawing.Size(65, 21);
            this.numericUpDownFeedData6.TabIndex = 11;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(24, 141);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(65, 12);
            this.label8.TabIndex = 12;
            this.label8.Text = "FeedData4:";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(203, 141);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(65, 12);
            this.label9.TabIndex = 12;
            this.label9.Text = "FeedData5:";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(382, 141);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(65, 12);
            this.label10.TabIndex = 12;
            this.label10.Text = "FeedData6:";
            // 
            // RobotFeedData
            // 
            this.RobotFeedData.Controls.Add(this.label2);
            this.RobotFeedData.Controls.Add(this.label10);
            this.RobotFeedData.Controls.Add(this.numericUpDownIndex);
            this.RobotFeedData.Controls.Add(this.label7);
            this.RobotFeedData.Controls.Add(this.numericUpDownLeftMotor);
            this.RobotFeedData.Controls.Add(this.label9);
            this.RobotFeedData.Controls.Add(this.numericUpDownRightMotor);
            this.RobotFeedData.Controls.Add(this.label6);
            this.RobotFeedData.Controls.Add(this.numericUpDownFeedData1);
            this.RobotFeedData.Controls.Add(this.label8);
            this.RobotFeedData.Controls.Add(this.label3);
            this.RobotFeedData.Controls.Add(this.label5);
            this.RobotFeedData.Controls.Add(this.numericUpDownFeedData4);
            this.RobotFeedData.Controls.Add(this.numericUpDownFeedData6);
            this.RobotFeedData.Controls.Add(this.numericUpDownFeedData2);
            this.RobotFeedData.Controls.Add(this.numericUpDownFeedData3);
            this.RobotFeedData.Controls.Add(this.label4);
            this.RobotFeedData.Controls.Add(this.numericUpDownFeedData5);
            this.RobotFeedData.Location = new System.Drawing.Point(12, 208);
            this.RobotFeedData.Name = "RobotFeedData";
            this.RobotFeedData.Size = new System.Drawing.Size(555, 171);
            this.RobotFeedData.TabIndex = 13;
            this.RobotFeedData.TabStop = false;
            this.RobotFeedData.Text = "RobotFeedData";
            // 
            // Form1
            // 
            this.AllowDrop = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(591, 465);
            this.Controls.Add(this.RobotFeedData);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.comboPortName);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.comboBaurate);
            this.Controls.Add(this.labelPortName);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.resetBtn);
            this.Controls.Add(this.OpenBtn);
            this.Name = "Form1";
            this.Text = "Form1";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownIndex)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownLeftMotor)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownRightMotor)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownFeedData1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownFeedData2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownFeedData3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownFeedData4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownFeedData5)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownFeedData6)).EndInit();
            this.RobotFeedData.ResumeLayout(false);
            this.RobotFeedData.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Button sendBtn;
        private System.Windows.Forms.TextBox sendTextBox;
        private System.Windows.Forms.TextBox receiveTextBox;
        private System.Windows.Forms.Button OpenBtn;
        private System.Windows.Forms.Button resetBtn;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label labelGetCount;
        private System.Windows.Forms.CheckBox checkBoxHexView;
        private System.Windows.Forms.Label labelPortName;
        private System.Windows.Forms.ComboBox comboBaurate;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox comboPortName;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.CheckBox checkBoxSendHex;
        private System.Windows.Forms.Label labelSendCount;
        private System.Windows.Forms.Timer timerCheckReceive;
        private System.Windows.Forms.Label labelReceiveCounter;
        private System.Windows.Forms.Timer timerSendPer5s;
        private System.Windows.Forms.Timer timerSendPer80ms;
        private System.ComponentModel.BackgroundWorker backgroundWorker2;
        private System.Windows.Forms.NumericUpDown numericUpDownIndex;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.NumericUpDown numericUpDownLeftMotor;
        private System.Windows.Forms.NumericUpDown numericUpDownRightMotor;
        private System.Windows.Forms.NumericUpDown numericUpDownFeedData1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.NumericUpDown numericUpDownFeedData2;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.NumericUpDown numericUpDownFeedData3;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.NumericUpDown numericUpDownFeedData4;
        private System.Windows.Forms.NumericUpDown numericUpDownFeedData5;
        private System.Windows.Forms.NumericUpDown numericUpDownFeedData6;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.GroupBox RobotFeedData;
    }
}

